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

    union SimLabelValue
    {
        int         IntValue;
        std::string StringValue;

        SimLabelValue(){};

        ~SimLabelValue(){};
    };

    class SimLabel : public SimFrames::Core::SimWidget
    {
    public:
        SimLabelObject Obj;
        SimLabelValue  Value;

        SimLabel(SimFrames::Core::SimContainer &container, uint8_t width = 50,
                 std::string description = "Label");

        ~SimLabel(){};

        int WriteValue(int value);

        int WriteValue(std::string value);

        int ReadValue(int *value);

        int ReadVlaue(std::string *value);
    };

}}

#endif