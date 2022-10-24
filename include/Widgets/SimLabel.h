#ifndef SIM_LABEL_H_
#define SIM_LABEL_H_

#include <Core/SimWidget.h>

namespace SimFrames { namespace Widgets {

    class SimLabel;

    class SimLabelObject : public SimFrames::Core::SimWidgetObject
    {
    public:
        lv_obj_t *LabelContainer;
        lv_obj_t *Label;

        SimLabelObject(SimLabel &parent, uint8_t width, std::string description = "");

        ~SimLabelObject(){};
    };

    class SimLabel : public SimFrames::Core::SimWidget
    {
    public:
        SimLabelObject Obj;
        std::string    Value;

        SimLabel(SimFrames::Core::SimContainer &container, uint8_t width = 50,
                 std::string description = "Label");

        ~SimLabel(){};

        SimFrames::Core::OperationResult WriteValue(std::string value);

        SimFrames::Core::OperationResult ReadValue(std::string *value);
    };

}}

#endif