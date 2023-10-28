#pragma once

#include "AdbController.h"
#include "ControllerAPI.h"
#include "MaaAdbController.h"
#include "MaatouchController.h"
#include "MinitouchController.h"
#include "PlayToolsController.h"

namespace asst
{
    class ControllerFactory
    {
    public:
        ControllerFactory(const AsstCallback& callback, Assistant* inst) : m_callback(callback), m_inst(inst) {}
        ~ControllerFactory() = default;

        std::shared_ptr<ControllerAPI> create_controller(ControllerType type, const std::string& adb_path,
                                                         const std::string& address, const std::string& config,
                                                         PlatformType platform_type)
        {
            std::shared_ptr<ControllerAPI> controller;
            try {
                switch (type) {
                case ControllerType::Adb:
                case ControllerType::Minitouch:
                case ControllerType::Maatouch:
                    controller = std::make_shared<MaaAdbController>(m_callback, m_inst, type);
                    break;
                case ControllerType::MacPlayTools:
                    controller = std::make_shared<PlayToolsController>(m_callback, m_inst, platform_type);
                    break;
                default:
                    return nullptr;
                }
            }
            catch (const std::exception& e) {
                Log.error("Cannot create controller: {}", e.what());
                return nullptr;
            }
            if (controller->connect(adb_path, address, config)) {
                return controller;
            }
            return nullptr;
        }

    private:
        AsstCallback m_callback;
        Assistant* m_inst;
    };
}
