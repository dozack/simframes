#ifndef SIM_LABEL_H_
#define SIM_LABEL_H_

#include <Core/SimWidget.h>

namespace SimFrames { namespace Widgets {

    class SimLabel : public SimFrames::Core::SimWidget
    {
    private:
        lv_obj_t   *LabelContainer;
        lv_obj_t   *Label;
        std::string Value;

    public:
        SimLabel(SimFrames::Core::SimContainer &container, uint8_t width = 50,
                 std::string description = "Label");

        ~SimLabel(){};

        SimFrames::Core::SimWidgetType GetType() override;

        SimFrames::Core::OperationResult WriteValue(std::string value);

        SimFrames::Core::OperationResult ReadValue(std::string *value);
    };

}}

#endif