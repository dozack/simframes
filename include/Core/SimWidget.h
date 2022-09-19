#ifndef SIM_WIDGET_H_
#define SIM_WIDGET_H_

#include <Core/SimContainer.h>
#include <Core/SimLock.h>

namespace SimFrames { namespace Core {

    class SimWidget;

    class SimWidgetObject
    {
    public:
        SimFrames::Core::SimWidget &Widget;
        SimFrames::Core::SimLock   &Lock;
        std::string                 Description;
        lv_obj_t                   *Frame;
        lv_obj_t                   *DescriptionContainer;
        lv_obj_t                   *DescriptionLabel;

        SimWidgetObject(SimWidget &widget, uint8_t descriptionWidth, std::string description = "");

        ~SimWidgetObject(){};
    };

    class SimWidget
    {
    public:
        SimFrames::Core::SimContainer &Container;
        SimFrames::Core::SimLock      &Lock;

        SimWidget(SimFrames::Core::SimContainer &container);

        ~SimWidget(){};
    };

}}

#endif