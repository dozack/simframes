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
        lv_label_set_text(Label, "");
        lv_obj_center(Label);
        lv_obj_clear_flag(Label, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_scrollbar_mode(Label, LV_SCROLLBAR_MODE_OFF);
    }

    SimLabel::SimLabel(SimFrames::Core::SimContainer &container, uint8_t width,
                       std::string description)
        : SimFrames::Core::SimWidget(container)
        , Obj(*this, width, description)
    {}

    SimFrames::Core::OperationResult SimLabel::WriteValue(std::string value)
    {
        Value = value;
        lv_label_set_text(Obj.Label, Value.c_str());
        return SimFrames::Core::OperationResult::Success;
    }

    SimFrames::Core::OperationResult SimLabel::ReadValue(std::string *value)
    {
        if (value == nullptr)
        {
            return SimFrames::Core::OperationResult::Error;
        }

        *value = Value;
        return SimFrames::Core::OperationResult::Success;
    }

}}