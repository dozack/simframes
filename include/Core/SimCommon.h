#ifndef SIM_COMMON_H_
#define SIM_COMMON_H_

#include <lvgl/lvgl.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <algorithm>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

namespace SimFrames { namespace Core {
    enum OperationResult
    {
        Success,
        Error
    };
}}

#endif /* SIM_COMMON_H_ */