#ifndef SIM_WIDGET_H_
#define SIM_WIDGET_H_

/*
 * ------------------------------------------------------------------------------------------------
 * Includes
 * ------------------------------------------------------------------------------------------------
 */

#include <Core/SimContainer.h>
#include <Core/SimLock.h>

/*
 * ------------------------------------------------------------------------------------------------
 * Namespace
 * ------------------------------------------------------------------------------------------------
 */

namespace SimFrames { namespace Core {

    /**
     * @brief   Widget type
     */
    enum SimWidgetType
    {
        Unknown      = 0, /* !< Unsupported widget type */
        Custom       = 1, /* !< Custom non-standard widget */
        Label        = 2, /* !< String label widget */
        Relay        = 3, /* !< Relay indicator widget */
        Slider       = 4, /* !< Slider widget */
        NumericInput = 5, /* !< Numeric input text area */
        __WIDGET_TYPE_NUM /* !< Number of widget types (do not use!) */
    };

    /**
     * @brief   Forward declaration of widget base class
     */
    class SimWidget;

    /**
     * @brief   Widget event listener
     */
    class SimWidgetEventListener
    {
    public:
        ~SimWidgetEventListener()                      = default;

        /**
         * @brief   Event triggered when value of widget has changed
         *
         * @param   widget Reference to related widget
         */
        virtual void OnValueChanged(SimWidget &widget) = 0;
    };

    /**
     * @brief   Base class for widget implementation
     */
    class SimWidget
    {
    protected:
        /**
         * @brief   Container that widget is assigned to
         */
        SimContainer &Container;
        /**
         * @brief   Main widget body frame
         */
        lv_obj_t *Frame;
        /**
         * @brief   Container for widget description label
         */
        lv_obj_t *DescriptionContainer;
        /**
         * @brief   Description label
         */
        lv_obj_t *DescriptionLabel;
        /**
         * @brief   Vector of attached event listeners
         */
        std::vector<SimWidgetEventListener *> Listeners;
        /**
         * @brief   Trigger event for all listeners
         */
        void OnValueChanged();

    public:
        /**
         * @brief   Reference to SimFrames runtime lock
         */
        SimLock &Lock;

        /**
         * @brief   Constructor
         *
         * @param   container           Reference to parent container
         * @param   descriptionWidth    Widget description width (set to 0 for no description)
         * @param   description         Description text
         */
        SimWidget(SimContainer &container, uint8_t descriptionWidth, std::string description = "");
        /**
         * @brief   Destructor
         *
         */
        ~SimWidget(){};
        /**
         * @brief   Add event listener to widget
         *
         * @param   listener    Pointer to listener class to be added
         * @return              Operation result
         */
        OperationResult AddListener(SimWidgetEventListener *listener);
        /**
         * @brief   Remove event listener from widget
         *
         * @param   listener    Pointer to listener class to be removed
         * @return              Operation result
         */
        OperationResult RemoveListener(SimWidgetEventListener *listener);
        /**
         * @brief   Get widget type
         *
         * @return  Widget type
         */
        virtual SimWidgetType GetType();
    };

}}

#endif /* SIM_WIDGET_H_ */