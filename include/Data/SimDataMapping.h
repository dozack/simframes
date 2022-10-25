#ifndef SIM_DATA_MAPPING_H_
#define SIM_DATA_MAPPING_H_

#include <Core/SimWidget.h>
#include <Data/SimDataStorage.h>

namespace SimFrames { namespace Data {

    class SimDataMapping
    {
    protected:
        RSimDataObject Object;

    public:
        bool Valid;

        SimDataMapping(SimDataStorage &storage, std::string key);
        ~SimDataMapping(){};
    };

    typedef std::shared_ptr<SimDataMapping> RSimDataMapping;

    class SimWidgetToDataMapping : public SimDataMapping,
                                   SimFrames::Core::SimWidgetEventListener
    {
    public:
        SimWidgetToDataMapping(SimDataStorage &storage, SimFrames::Core::SimWidget &widget,
                               std::string key);
        ~SimWidgetToDataMapping(){};

        void OnValueChanged(SimFrames::Core::SimWidget &widget) override;
    };

    typedef std::shared_ptr<SimWidgetToDataMapping> RSimWidgetToDataMapping;

    class SimDataToWidgetMapping : public SimDataMapping,
                                   SimDataObjectEventListener
    {
    private:
        SimFrames::Core::SimWidget &Widget;

    public:
        SimDataToWidgetMapping(SimDataStorage &storage, SimFrames::Core::SimWidget &widget,
                               std::string key);
        ~SimDataToWidgetMapping(){};

        void OnWrite(SimDataObject &object) override;
        void OnRead(SimDataObject &object) override;
    };

}}

#endif /* SIM_DATA_MAPPING_H_ */