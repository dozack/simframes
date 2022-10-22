#ifndef SIM_DATA_STORAGE_H_
#define SIM_DATA_STORAGE_H_

#include <Core/SimCommon.h>

namespace SimFrames { namespace Data {

    class SimDataStorageEntry;

    class SimDataStorageEventListener
    {
    public:
        ~SimDataStorageEventListener()                     = default;

        virtual void OnObjectWrite(SimDataStorageEntry &entry) = 0;
        virtual void OnObjectRead(SimDataStorageEntry &entry)  = 0;
    };

    class SimDataStorageEntry
    {
    private:
        SimDataObject                             Object;
        std::vector<SimDataStorageEventListener *> Listeners;
        std::mutex                                Lock;

    public:
        SimDataStorageEntry(bool defaultValue);
        SimDataStorageEntry(int64_t defaultValue);
        SimDataStorageEntry(double defaultValue);

        ~SimDataStorageEntry();

        void AddListener(SimDataStorageEventListener *listener);
        void RemoveListener(SimDataStorageEventListener *listener);

        SimFrames::Core::OperationResult Read(bool *dest);
        SimFrames::Core::OperationResult Read(int64_t *dest);
        SimFrames::Core::OperationResult Read(double *dest);

        SimFrames::Core::OperationResult Write(bool src);
        SimFrames::Core::OperationResult Write(int64_t src);
        SimFrames::Core::OperationResult Write(double src);
    };

    typedef std::shared_ptr<SimDataStorageEntry> RSimDataStorageEntry;

    class SimDataStorage
    {
    private:
        std::map<std::string, RSimDataStorageEntry> Entries;
        std::mutex                                  Lock;

    public:
        SimDataStorage();
        ~SimDataStorage();

        SimFrames::Core::OperationResult Add(std::string key, bool defaultValue);
        SimFrames::Core::OperationResult Add(std::string key, int64_t defaultValue);
        SimFrames::Core::OperationResult Add(std::string key, double defaultValue);

        RSimDataStorageEntry Find(std::string key);
    };

}}

#endif