#ifndef SIM_DATA_STORAGE_H_
#define SIM_DATA_STORAGE_H_

#include <Data/SimDataObject.h>

namespace SimFrames { namespace Data {

    class SimDataStorage
    {
    private:
        std::map<std::string, RSimDataObject> Entries;
        std::mutex                            Lock;

    public:
        SimDataStorage();
        ~SimDataStorage();

        SimFrames::Core::OperationResult Add(std::string key, int32_t defaultValue);

        SimFrames::Core::OperationResult Remove(std::string key);

        SimFrames::Core::OperationResult Remove(RSimDataObject object);

        RSimDataObject Find(std::string key);
    };

}}

#endif /* SIM_DATA_STORAGE_H_ */