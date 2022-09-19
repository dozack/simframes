#include <SimFrames.h>

namespace SimFrames { namespace Widgets {

    SimTextAreaObject::SimTextAreaObject(SimTextArea &parent, uint8_t width,
                                         std::string description)
        : SimFrames::Core::SimWidgetObject(parent, (100 - width), description)
        , Parent(parent)
    {
        std::lock_guard<std::mutex> lk(Lock.Lock);

        TextArea = lv_textarea_create(Frame);
        lv_obj_set_size(TextArea, LV_PCT(width), LV_SIZE_CONTENT);
        lv_obj_clear_flag(TextArea, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
        lv_textarea_set_one_line(TextArea, true);
        lv_textarea_set_accepted_chars(TextArea, "1234567890-");
        lv_obj_add_event_cb(TextArea, &SimTextAreaObject::OnEvent, LV_EVENT_READY, this);
        lv_obj_add_event_cb(TextArea, &SimTextAreaObject::OnEvent, LV_EVENT_VALUE_CHANGED, this);
        lv_obj_center(TextArea);
    }

    void SimTextAreaObject::OnEvent(lv_event_t *event)
    {
        SimTextAreaObject *obj;

        if (event == nullptr)
        {
            return;
        }

        obj = static_cast<SimTextAreaObject *>(lv_event_get_user_data(event));

        if (obj)
        {
            lv_event_code_t eventCode  = lv_event_get_code(event);
            const char     *objectText = lv_textarea_get_text(obj->TextArea);

            if (strlen(objectText) <= 0)
            {
                lv_textarea_set_accepted_chars(obj->TextArea, "1234567890-");
            }
            else
            {
                lv_textarea_set_accepted_chars(obj->TextArea, "1234567890");
            }

            if ((obj->Events) && (eventCode == LV_EVENT_READY))
            {
                obj->Events->OnValueChanged(&obj->Parent);
            }
        }
    }

    SimTextArea::SimTextArea(SimFrames::Core::SimContainer &container, uint8_t width,
                             std::string description)
        : SimFrames::Core::SimWidget(container)
        , Obj(*this, width, description)
    {}

    int SimTextArea::ReadValue(int *value)
    {
        if (value == nullptr)
        {
            return (-1);
        }

        *value = atoi(lv_textarea_get_text(Obj.TextArea));
        return (0);
    }

    void SimTextArea::SetEvents(SimTextAreaEvents *events)
    {
        Obj.Events = events;
    }

}}