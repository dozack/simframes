#ifndef SIM_RELAY_H_
#define SIM_RELAY_H_

#include <Core/SimCommon.h>
#include <Core/SimWidget.h>

namespace SimFrames { namespace Widgets {

    static constexpr lv_color_t RelayOnColor  = LV_COLOR_MAKE(119, 221, 119);
    static constexpr lv_color_t RelayOffColor = LV_COLOR_MAKE(220, 220, 220);

    class SimRelay;

    class SimRelayObject : public SimFrames::Core::SimWidgetObject
    {
    protected:
        bool      State;
        lv_obj_t *Body;
        lv_obj_t *Indicator;

    public:
        SimRelayObject(SimRelay &parent, uint8_t width, std::string description = "");

        ~SimRelayObject(){};
    };

    class SimRelay : public SimFrames::Core::SimWidget,
                     SimFrames::Widgets::SimRelayObject
    {
    public:
        SimRelay(SimFrames::Core::SimContainer &container, uint8_t width = 50,
                 std::string description = "Relay");

        ~SimRelay(){};

        SimFrames::Core::OperationResult SetState(bool state);

        SimFrames::Core::OperationResult GetState(bool *state);
    };

}}

#endif /* SIM_RELAY_H_ */