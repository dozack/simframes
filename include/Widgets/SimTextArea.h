#ifndef SIM_TEXTAREA_H_
#define SIM_TEXTAREA_H_

#include <Core/SimWidget.h>

namespace SimFrames { namespace Widgets {

    class SimTextArea;

    class SimTextAreaEvents
    {
    public:
        virtual void OnValueChanged(SimTextArea *sender) = 0;
    };

    class SimTextAreaObject : public SimFrames::Core::SimWidgetObject
    {
    public:
        SimTextArea       &Parent;
        lv_obj_t          *TextArea;
        SimTextAreaEvents *Events;

        SimTextAreaObject(SimTextArea &parent, uint8_t width, std::string description = "");

        ~SimTextAreaObject(){};

    private:
        static void OnEvent(lv_event_t *event);
    };

    class SimTextArea : public SimFrames::Core::SimWidget
    {
    public:
        SimTextAreaObject Obj;

        SimTextArea(SimFrames::Core::SimContainer &container, uint8_t width = 50,
                    std::string description = "TextArea");

        ~SimTextArea(){};

        int ReadValue(int *value);

        void SetEvents(SimTextAreaEvents *events);
    };

}}

#endif