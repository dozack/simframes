#ifndef SIM_GRID_H_
#define SIM_GRID_H_

#include <Core/SimTab.h>

namespace SimFrames { namespace Core {

    class SimGridLayout
    {
    public:
        const lv_coord_t *Columns;
        const lv_coord_t *Rows;

        SimGridLayout(const lv_coord_t *columns, const lv_coord_t *rows);
    };

    class SimGrid
    {
    public:
        SimFrames::Core::SimGridLayout &Config;
        SimFrames::Core::SimTab        &Tab;
        lv_obj_t                       *Obj;

        SimGrid(SimFrames::Core::SimTab &tab, SimFrames::Core::SimGridLayout &layout);

        ~SimGrid();
    };
}}

#endif