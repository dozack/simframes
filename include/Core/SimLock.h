#ifndef SIM_LOCK_H_
#define SIM_LOCK_H_

#include <Core/SimCommon.h>

namespace SimFrames { namespace Core {

    class SimLock
    {
    public:
        std::mutex Lock;

        SimLock(){};

        ~SimLock(){};
    };

}}

#endif