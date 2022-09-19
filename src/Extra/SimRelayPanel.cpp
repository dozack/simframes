#include <SimFrames.h>

#include <iostream>

namespace SimFrames { namespace Extra {

    SimRelay::SimRelay(uint32_t index, SimRelayPanelObject *parent)
        : Parent(parent)
        , Index(index)
        , State(false)
    {
        std::lock_guard<std::mutex> lk(parent->Lock.Lock);

        Body = lv_obj_create(Parent->Frame);

        lv_obj_set_flex_grow(Body, 1);
        lv_obj_set_style_bg_color(Body, RelayOffColor, 0);
        lv_obj_set_height(Body, LV_SIZE_CONTENT);
        lv_obj_clear_flag(Body, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_scrollbar_mode(Body, LV_SCROLLBAR_MODE_OFF);

        Label = lv_label_create(Body);
        lv_label_set_text_fmt(Label, "%d", Index);
        lv_obj_center(Label);
    }

    SimRelayPanelObject::SimRelayPanelObject(SimRelayPanel &parent, uint32_t relayCount,
                                             uint8_t width, std::string description)
        : SimFrames::Core::SimWidgetObject(parent, (100 - width), description)
    {
        for (uint32_t i = 0; i < relayCount; i++) { Relays.emplace(Relays.end(), i, this); }
    }

    SimRelayPanel::SimRelayPanel(SimFrames::Core::SimContainer &container, uint32_t relayCount,
                                 uint8_t width, std::string description)
        : SimFrames::Core::SimWidget(container)
        , Obj(*this, relayCount, width, description)
    {}

    int SimRelayPanel::SetState(int index, bool state)
    {
        lv_color_t color;

        try
        {
            SimRelay &relay = Obj.Relays.at(index);
            color           = state ? RelayOnColor : RelayOffColor;
            relay.State     = state;
            lv_obj_set_style_bg_color(relay.Body, color, 0);
            return (0);

        } catch (const std::out_of_range &e)
        {
            std::cout << e.what() << std::endl;

            return (-1);
        }
    }

    int SimRelayPanel::GetState(int index, bool *state)
    {
        try
        {
            SimRelay &relay = Obj.Relays.at(index);
            *state          = relay.State;
            return (0);

        } catch (const std::out_of_range &e)
        {
            std::cout << e.what() << std::endl;
            return (-1);
        }
    }

}}