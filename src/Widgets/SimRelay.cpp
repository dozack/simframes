#include <SimFrames.h>

namespace SimFrames { namespace Widgets {

    SimRelay::SimRelay(SimFrames::Core::SimContainer &container, uint8_t descriptionWidth,
                       std::string description)
        : SimFrames::Core::SimWidget(container, (100 - descriptionWidth), description)
    {
        std::lock_guard<std::mutex> lk(Lock.Lock);

        Body = lv_obj_create(Frame);
        lv_obj_set_size(Body, LV_PCT(descriptionWidth), LV_PCT(100));
        lv_obj_center(Body);
        lv_obj_set_style_bg_color(Body, RelayOffColor, 0);
        lv_obj_clear_flag(Body, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_scrollbar_mode(Body, LV_SCROLLBAR_MODE_OFF);
    }

    SimFrames::Core::SimWidgetType SimRelay::GetType()
    {
        return SimFrames::Core::SimWidgetType::Relay;
    }

    SimFrames::Core::OperationResult SimRelay::SetState(bool state)
    {
        lv_color_t color;

        if (state != State)
        {
            color = state ? RelayOnColor : RelayOffColor;
            State = state;
            lv_obj_set_style_bg_color(Body, color, 0);
            OnValueChanged();
        }

        return SimFrames::Core::OperationResult::Success;
    }

    SimFrames::Core::OperationResult SimRelay::GetState(bool *state)
    {
        if (state == nullptr)
        {
            return SimFrames::Core::OperationResult::Error;
        }
        *state = State;
        return SimFrames::Core::OperationResult::Success;
    }

}}