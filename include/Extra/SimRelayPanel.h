#ifndef SIM_RELAY_PANEL_H_
#define SIM_RELAY_PANEL_H_

#include <Core/SimWidget.h>
#include <Core/SimCommon.h>

namespace SimFrames { namespace Extra {

    static constexpr lv_color_t RelayOnColor  = LV_COLOR_MAKE(119, 221, 119);
    static constexpr lv_color_t RelayOffColor = LV_COLOR_MAKE(220, 220, 220);

    class SimRelayPanel;
    class SimRelayPanelObject;

    class SimRelay
    {
    public:
        SimRelayPanelObject *Parent;
        uint32_t             Index;
        bool                 State;
        lv_obj_t            *Body;
        lv_obj_t            *Label;

        SimRelay(uint32_t index, SimRelayPanelObject *parent);

        ~SimRelay(){};
    };

    class SimRelayPanelObject : public SimFrames::Core::SimWidgetObject
    {
    public:
        std::vector<SimRelay> Relays;

        SimRelayPanelObject(SimRelayPanel &parent, uint32_t relayCount, uint8_t width,
                            std::string description = "");

        ~SimRelayPanelObject(){};
    };

    class SimRelayPanel : public SimFrames::Core::SimWidget
    {
    public:
        SimRelayPanelObject Obj;

        SimRelayPanel(SimFrames::Core::SimContainer &container, uint32_t relayCount,
                      uint8_t width = 50, std::string description = "Relay Panel");

        ~SimRelayPanel(){};

        int SetState(int index, bool state);

        int GetState(int index, bool *state);
    };

}}

#endif