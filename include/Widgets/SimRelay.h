#ifndef SIM_RELAY_H_
#define SIM_RELAY_H_

#include <Core/SimCommon.h>
#include <Core/SimWidget.h>

namespace SimFrames { namespace Widgets {

    static constexpr lv_color_t RelayOnColor  = LV_COLOR_MAKE(119, 221, 119);
    static constexpr lv_color_t RelayOffColor = LV_COLOR_MAKE(220, 220, 220);

    class SimRelay : public SimFrames::Core::SimWidget
    {
    private:
        bool      State;
        lv_obj_t *Body;
        lv_obj_t *Indicator;

    public:
        SimRelay(SimFrames::Core::SimContainer &container, uint8_t descriptionWidth,
                 std::string description = "Relay");

        ~SimRelay(){};

        SimFrames::Core::SimWidgetType GetType() override;

        SimFrames::Core::OperationResult SetState(bool state);

        SimFrames::Core::OperationResult GetState(bool *state);
    };

}}

#endif /* SIM_RELAY_H_ */