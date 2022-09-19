#include <SimFrames.h>

namespace SimFrames { namespace Core {

    SimGridLayout::SimGridLayout(const lv_coord_t *columns, const lv_coord_t *rows)
        : Columns(columns)
        , Rows(rows)
    {}

    SimGrid::SimGrid(SimFrames::Core::SimTab &tab, SimFrames::Core::SimGridLayout &layout)
        : Layout(layout)
        , Tab(tab)
        , Lock(tab.Window.Lock)
    {
        std::lock_guard<std::mutex> lk(Lock.Lock);

        Obj = lv_obj_create(Tab.Obj);
        lv_obj_align(Obj, LV_ALIGN_TOP_MID, 0, 5);
        lv_obj_set_size(Obj, LV_PCT(100), LV_PCT(100));
        lv_obj_set_layout(Obj, LV_LAYOUT_GRID);
        lv_obj_set_style_grid_column_dsc_array(Obj, Layout.Columns, 0);
        lv_obj_set_style_grid_row_dsc_array(Obj, Layout.Rows, 0);
        lv_obj_clear_flag(Obj, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_scrollbar_mode(Obj, LV_SCROLLBAR_MODE_OFF);
    }

}}