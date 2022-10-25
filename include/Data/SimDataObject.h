#ifndef SIM_DATA_OBJECT_H_
#define SIM_DATA_OBJECT_H_

#include <Core/SimCommon.h>

namespace SimFrames { namespace Data {

    class SimDataObject;

    class SimDataObjectEventListener
    {
    public:
        /**
         * @brief Destructor
         */
        virtual ~SimDataObjectEventListener()       = default;
        /**
         * @brief   Event handler called AFTER new src value is written to object
         *
         * @param   object      Reference to related object
         */
        virtual void OnWrite(SimDataObject &object) = 0;
        /**
         * @brief   Event handler called AFTER actual value is read into dest
         *
         * @param   object      Reference to related object
         */
        virtual void OnRead(SimDataObject &object)  = 0;
    };

    class SimDataObject
    {
    private:
        std::vector<SimDataObjectEventListener *> Listeners;
        std::mutex                                Lock;
        int32_t                                   Value;

        void OnWrite();
        void OnRead();

    public:
        SimDataObject(int32_t defaultValue = 0);
        ~SimDataObject(){};

        SimFrames::Core::OperationResult AddListener(SimDataObjectEventListener *listener);

        SimFrames::Core::OperationResult RemoveListener(SimDataObjectEventListener *listener);

        SimFrames::Core::OperationResult Read(int32_t *dest);

        SimFrames::Core::OperationResult Write(int32_t *src);
    };

    typedef std::shared_ptr<SimDataObject> RSimDataObject;

}}

#endif /* SIM_DATA_OBJECT_H_ */