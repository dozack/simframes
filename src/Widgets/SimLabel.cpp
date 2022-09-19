#include <SimFrames.h>

namespace SimFrames { namespace Widgets {

    SimLabelObject::SimLabelObject(SimLabel &parent, uint8_t width, std::string description)
        : SimFrames::Core::SimWidgetObject(parent, (100 - width), description)
    {
        std::lock_guard<std::mutex> lk(Lock.Lock);

        LabelContainer = lv_obj_create(Frame);
        lv_obj_set_size(LabelContainer, LV_PCT(width), LV_SIZE_CONTENT);
        lv_obj_center(LabelContainer);
        lv_obj_clear_flag(LabelContainer, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_scrollbar_mode(LabelContainer, LV_SCROLLBAR_MODE_OFF);

        Label = lv_label_create(LabelContainer);
        lv_label_set_text(Label, "0");
        lv_obj_center(Label);
        lv_obj_clear_flag(Label, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_scrollbar_mode(Label, LV_SCROLLBAR_MODE_OFF);
    }

    SimLabel::SimLabel(SimFrames::Core::SimContainer &container, uint8_t width,
                       std::string description)
        : SimFrames::Core::SimWidget(container)
        , Obj(*this, width, description)
    {}

    int SimLabel::WriteValue(int value)
    {
        Value.IntValue = value;
        lv_label_set_text_fmt(Obj.Label, "%d", Value.IntValue);
        return (0);
    }

    int SimLabel::WriteValue(std::string value)
    {
        Value.StringValue = value;
        lv_label_set_text(Obj.Label, Value.StringValue.c_str());
        return (0);
    }

    int SimLabel::ReadValue(int *value)
    {
        if (value == nullptr)
        {
            return (-1);
        }

        *value = Value.IntValue;
        return (0);
    }

    int SimLabel::ReadVlaue(std::string *value)
    {
        if (value == nullptr)
        {
            return (-1);
        }

        *value = Value.StringValue;
        return (0);
    }

}}