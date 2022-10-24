#include <SimFrames.h>

namespace SimFrames { namespace Widgets {

    SimRelayObject::SimRelayObject(SimRelay &parent, uint8_t width, std::string description)
        : SimFrames::Core::SimWidgetObject(parent, (100 - width), description)
    {
        std::lock_guard<std::mutex> lk(Lock.Lock);

        Body = lv_obj_create(Frame);
        lv_obj_set_size(Body, LV_PCT(width), LV_PCT(100));
        lv_obj_center(Body);
        lv_obj_set_style_bg_color(Body, RelayOffColor, 0);
        lv_obj_clear_flag(Body, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_scrollbar_mode(Body, LV_SCROLLBAR_MODE_OFF);

#if 0
        Indicator = lv_led_create(Body);
        lv_obj_set_size(Indicator, 10, 10);
        lv_obj_center(Indicator);
        lv_obj_clear_flag(Indicator, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_scrollbar_mode(Indicator, LV_SCROLLBAR_MODE_OFF);
#endif
    }

    SimRelay::SimRelay(SimFrames::Core::SimContainer &container, uint8_t width,
                       std::string description)
        : SimFrames::Core::SimWidget(container)
        , SimFrames::Widgets::SimRelayObject(*this, width, description)
    {}

    SimFrames::Core::OperationResult SimRelay::SetState(bool state)
    {
        lv_color_t color;

        color = state ? RelayOnColor : RelayOffColor;
        State = state;
        lv_obj_set_style_bg_color(Body, color, 0);
        return SimFrames::Core::OperationResult::Success;
    }

    SimFrames::Core::OperationResult SimRelay::GetState(bool *state)
    {
        *state = State;
        return SimFrames::Core::OperationResult::Success;
    }

}}