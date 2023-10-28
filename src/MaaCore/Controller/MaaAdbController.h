#pragma once

#include "ControllerAPI.h"
#include "InstHelper.h"

#include "Common/AsstMsg.h"
#include "Platform/PlatformIO.h"

#include <MaaFramework/MaaDef.h>

namespace asst
{
    class MaaAdbController : public ControllerAPI, protected InstHelper
    {
    public:
        MaaAdbController(const AsstCallback& callback, Assistant* inst, ControllerType type);
        MaaAdbController(const MaaAdbController&) = delete;
        MaaAdbController(MaaAdbController&&) = delete;
        virtual ~MaaAdbController();

        virtual bool inited() const noexcept override;
        virtual bool connect(const std::string& adb_path, const std::string& address,
                             const std::string& config) override;
        virtual const std::string& get_uuid() const override { return m_uuid; }

        virtual void set_kill_adb_on_exit([[maybe_unused]] bool enable) noexcept override { /*todo*/ };

        virtual bool start_game(const std::string& client_type) override;
        virtual bool stop_game() override;

        virtual bool screencap(cv::Mat& image_payload, bool allow_reconnect = false) override;
        virtual bool click(const Point& p) override;
        virtual bool swipe(const Point& p1, const Point& p2, int duration = 0, bool extra_swipe = false,
                           double slope_in = 1, double slope_out = 1, bool with_pause = false) override;
        virtual bool press_esc() override;

        virtual bool inject_input_event([[maybe_unused]] const InputEvent& event) override { return false; }
        virtual ControlFeat::Feat support_features() const noexcept override { return ControlFeat::NONE; }
        virtual std::pair<int, int> get_screen_res() const noexcept override { return m_screen_res; }

        MaaAdbController& operator=(const MaaAdbController&) = delete;
        MaaAdbController& operator=(MaaAdbController&&) = delete;

        void set_controller_type(ControllerType type) { m_controller_type = type; }

    protected:
        void callback(AsstMsg msg, const json::value& details);

        AsstCallback m_callback;
        MaaInstanceHandle m_maa_handle = nullptr;
        MaaControllerHandle m_controller_handle = nullptr;
        MaaResourceHandle m_resource_handle = nullptr;

    private:
        ControllerType m_controller_type = ControllerType::Minitouch;
        std::string m_uuid;
        bool m_inited = false;
        std::string m_intent_name;
        std::pair<int, int> m_screen_res;
        int m_width = 0;
        int m_height = 0;
    };
} // namespace asst
