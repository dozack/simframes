#ifndef SIM_GRID_H_
#define SIM_GRID_H_

#include <Core/SimLock.h>
#include <Core/SimTab.h>

namespace SimFrames { namespace Core {

    class SimGridLayout
    {
    public:
        const lv_coord_t *lvColumnMap;
        const lv_coord_t *lvRowMap;

        SimGridLayout(const lv_coord_t *columns, const lv_coord_t *rows);
    };

    class SimGrid
    {
    public:
        SimFrames::Core::SimGridLayout &Layout;
        SimFrames::Core::SimTab        &Tab;
        SimFrames::Core::SimLock       &Lock;
        lv_obj_t                       *lvGrid;

        SimGrid(SimFrames::Core::SimTab &tab, SimFrames::Core::SimGridLayout &layout);

        ~SimGrid(){};
    };
}}

#endif