#include "MaaAdbController.h"

#include <MaaFramework/MaaAPI.h>

#include "Config/GeneralConfig.h"
#include "Utils/Logger.hpp"

asst::MaaAdbController::MaaAdbController(const AsstCallback& callback, Assistant* inst, ControllerType type)
    : InstHelper(inst), m_callback(callback), m_controller_type(type)
{
    LogTraceFunction;
}

asst::MaaAdbController::~MaaAdbController()
{
    if (m_controller_handle) {
        MaaControllerDestroy(m_controller_handle);
        m_controller_handle = nullptr;
    }
    if (m_resource_handle) {
        MaaResourceDestroy(m_resource_handle);
        m_resource_handle = nullptr;
    }
    if (m_maa_handle) {
        MaaDestroy(m_maa_handle);
        m_maa_handle = nullptr;
    }
}

bool asst::MaaAdbController::inited() const noexcept
{
    return m_maa_handle && m_controller_handle && m_resource_handle && MaaInited(m_maa_handle);
}

bool asst::MaaAdbController::connect(const std::string& adb_path, const std::string& address,
                                     [[maybe_unused]] const std::string& config)
{
    // todo 处理复用
    const static auto controller_config_path =
        asst::utils::path("resource") / asst::utils::path("controller_config.json");
    auto adb_config_opt = json::open(controller_config_path, true);
    if (!adb_config_opt) {
        Log.error("Json open failed", controller_config_path);
        return false;
    }
    int touch_type = MaaAdbControllerType_Touch_MiniTouch;
    if (m_controller_type == ControllerType::Adb) {
        touch_type = MaaAdbControllerType_Touch_Adb;
    }
    else if (m_controller_type == ControllerType::Minitouch) {
        touch_type = MaaAdbControllerType_Touch_MiniTouch;
    }
    else if (m_controller_type == ControllerType::Maatouch) {
        touch_type = MaaAdbControllerType_Touch_MaaTouch;
    }
    int key_type = MaaAdbControllerType_Key_Adb;
    [[maybe_unused]]int screencap_type = MaaAdbControllerType_Screencap_RawWithGzip; // 自动测速RawWithGzip

    MaaAdbControllerType control_type = 1 | key_type | 6 << 16;

    auto adb_config = adb_config_opt->to_string();
    m_controller_handle =
        MaaAdbControllerCreateV2(adb_path.c_str(), address.c_str(), control_type, adb_config.c_str(),
                                 asst::utils::path("MaaAgentBinary").string().c_str(), nullptr, nullptr);
    m_resource_handle = MaaResourceCreate(nullptr, nullptr);

    auto ctrl_id = MaaControllerPostConnection(m_controller_handle);
    auto res_id = MaaResourcePostPath(m_resource_handle, asst::utils::path("resource").string().c_str());

    [[maybe_unused]] auto status = MaaControllerWait(m_controller_handle, ctrl_id);
    MaaResourceWait(m_resource_handle, res_id);

    m_maa_handle = MaaCreate(nullptr, nullptr);
    [[maybe_unused]] auto br = MaaBindResource(m_maa_handle, m_resource_handle);
    [[maybe_unused]] auto bc = MaaBindController(m_maa_handle, m_controller_handle);
    [[maybe_unused]] auto cc = MaaControllerConnected(m_controller_handle);
    [[maybe_unused]] auto rc = MaaResourceLoaded(m_resource_handle);
    do {
        if (!MaaInited(m_maa_handle)) {
            break;
        }

        auto string_buffer = MaaCreateStringBuffer();
        if (!MaaControllerGetUUID(m_controller_handle, string_buffer)) {
            MaaDestroyStringBuffer(string_buffer);
            break;
        }
        m_uuid = MaaGetString(string_buffer);
        MaaDestroyStringBuffer(string_buffer);

        cv::Mat payload;
        if (!screencap(payload)) {
            break;
        }
        m_width = payload.cols;
        m_height = payload.rows;
        m_screen_res = { m_width, m_height };
        return true;
    } while (false);

    MaaControllerDestroy(m_controller_handle);
    MaaResourceDestroy(m_resource_handle);
    MaaDestroy(m_maa_handle);

    m_controller_handle = nullptr;
    m_resource_handle = nullptr;
    m_maa_handle = nullptr;
    return false;
}

void asst::MaaAdbController::callback(AsstMsg msg, const json::value& details)
{
    if (m_callback) {
        m_callback(msg, details, m_inst);
    }
}

bool asst::MaaAdbController::screencap(cv::Mat& image_payload, [[maybe_unused]] bool allow_reconnect)
{
    using namespace std::chrono_literals;
    using namespace std::chrono;

    auto start_time = steady_clock::now();
    // todo 处理重连
    auto ctrl_id = MaaControllerPostScreencap(m_controller_handle);
    if (MaaControllerWait(m_controller_handle, ctrl_id) != MaaStatus_Success) {
        return false;
    }
    auto img_buffer = MaaCreateImageBuffer();
    auto result = MaaControllerGetImage(m_controller_handle, img_buffer);
    auto duration = duration_cast<milliseconds>(steady_clock::now() - start_time).count();
    if (result) {
        void* raw_data = MaaGetImageRawData(img_buffer);
        auto rows = MaaGetImageHeight(img_buffer);
        auto cols = MaaGetImageWidth(img_buffer);
        auto type = MaaGetImageType(img_buffer);
        auto img = cv::Mat(rows, cols, type, const_cast<void*>(raw_data));
        img.copyTo(image_payload);
        // image_payload = cv::Mat(img, true);
    }
    MaaDestroyImageBuffer(img_buffer);

    Log.info("Call screencap, cost", duration, "ms , size:", image_payload.size);
    return result;
}

bool asst::MaaAdbController::start_game(const std::string& client_type)
{
    if (client_type.empty()) {
        return false;
    }
    auto intent_name = Config.get_intent_name(client_type);
    if (!intent_name) {
        return false;
    }
    m_intent_name = *intent_name;
    json::object param = { { "action", "StartApp" }, { "package", *intent_name } };
    auto task_id = MaaPostTask(m_maa_handle, "StartGame", param.to_string().c_str());
    return MaaWaitTask(m_maa_handle, task_id) == MaaStatus_Success;
}

bool asst::MaaAdbController::stop_game()
{
    std::string_view intent_name_view = m_intent_name;
    if (auto split_index = m_intent_name.find("/"); split_index != std::string::npos) {
        intent_name_view = intent_name_view.substr(0, split_index);
    }
    json::object param = { { "action", "StopApp" }, { "package", std::string(intent_name_view) } };
    auto task_id = MaaPostTask(m_maa_handle, "StopGame", param.to_string().c_str());
    return MaaWaitTask(m_maa_handle, task_id) == MaaStatus_Success;
}

bool asst::MaaAdbController::click(const Point& p)
{
    auto ctrl_id = MaaControllerPostClick(m_controller_handle, p.x, p.y);
    return MaaControllerWait(m_controller_handle, ctrl_id) == MaaStatus_Success;
}

bool asst::MaaAdbController::swipe(const Point& p1, const Point& p2, int duration, [[maybe_unused]] bool extra_swipe,
                                   [[maybe_unused]] double slope_in, [[maybe_unused]] double slope_out,
                                   [[maybe_unused]] bool with_pause)
{
    // todo 先不处理额外滑动
    auto ctrl_id = MaaControllerPostSwipe(m_controller_handle, p1.x, p1.y, p2.x, p2.y, duration);
    return MaaControllerWait(m_controller_handle, ctrl_id) == MaaStatus_Success;
}

bool asst::MaaAdbController::press_esc()
{
    auto ctrl_id = MaaControllerPostPressKey(m_controller_handle, 111);
    return MaaControllerWait(m_controller_handle, ctrl_id) == MaaStatus_Success;
}
