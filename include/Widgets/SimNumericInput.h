#ifndef SIM_NUMERIC_INPUT_H_
#define SIM_NUMERIC_INPUT_H_

#include <Core/SimWidget.h>

namespace SimFrames { namespace Widgets {

    class SimNumericInput : public SimFrames::Core::SimWidget
    {
    private:
        lv_obj_t *TextArea;

        static void _event_callback(lv_event_t *event);

    public:
        SimNumericInput(SimFrames::Core::SimContainer &container, uint8_t width = 50,
                        std::string description = "TextArea");

        ~SimNumericInput(){};

        SimFrames::Core::SimWidgetType GetType() override;

        SimFrames::Core::OperationResult ReadValue(int32_t *value);
    };

}}

#endif