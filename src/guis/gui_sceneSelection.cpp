#include <lvgl.h>
#include "applicationInternal/hardware/hardwarePresenter.h"
#include "applicationInternal/gui/guiBase.h"
#include "applicationInternal/gui/guiRegistry.h"
#include "applicationInternal/scenes/sceneRegistry.h"
#include "applicationInternal/commandHandler.h"
#include "applicationInternal/omote_log.h"
#include "guis/gui_sceneSelection.h"
#include "layout.h"

static uint16_t activate_scene_command;
static bool doForceScene;

lv_obj_t *grid;

static int lastShortClickedReceived;
static unsigned long int lastShortClickedReceivedTime;

void update_button_borders()
{
  uint32_t iterator;
  lv_obj_t *child;
  lv_obj_t *label;
  char *label_text = lv_label_get_text(SceneLabel);

  for (iterator = 0; iterator < lv_obj_get_child_cnt(grid); iterator++)
  {
    //Clear borders
    child = lv_obj_get_child(grid, iterator);
    lv_obj_set_style_outline_width(child, 0, 0);

    label = lv_obj_get_child(child, 0);
    if (strcmp(lv_label_get_text(label), label_text)==0){
      //Set border if this iteration is the clicked button
      lv_obj_set_style_outline_color(child, lv_color_hex(0xffffff), 0);
      lv_obj_set_style_outline_width(child, 2, 0);
    }
  }
}

void activate_scene_cb(lv_timer_t *timer)
{
  uint16_t scene_command_including_force = (uintptr_t)(timer->user_data);
  // get the force flag from the highest bit
  uint16_t activate_scene_command = scene_command_including_force & 0x7FFF;
  bool doForceScene = (scene_command_including_force & 0x8000) == 0x8000;
  if (doForceScene)
  {
    executeCommand(activate_scene_command, "FORCE");
  }
  else
  {
    executeCommand(activate_scene_command);
  }

  update_button_borders();
}

static void sceneSelection_event_cb(lv_event_t *e)
{
  int user_data = (intptr_t)(e->user_data);

  // we will receive the following events in that order:
  // LV_EVENT_PRESSED
  // LV_EVENT_RELEASED
  // only on short press: LV_EVENT_SHORT_CLICKED
  // both on short press and long press: LV_EVENT_CLICKED
  // if (lv_event_get_code(e) == LV_EVENT_PRESSED) {
  //   omote_log_v("pressed\r\n");
  // }
  // if (lv_event_get_code(e) == LV_EVENT_RELEASED) {
  //   omote_log_v("released\r\n");
  // }
  if (lv_event_get_code(e) == LV_EVENT_SHORT_CLICKED)
  {
    lastShortClickedReceived = user_data;
    lastShortClickedReceivedTime = millis();
    omote_log_v("short clicked, will see what happens next\r\n");
    return;
  }
  else if (lv_event_get_code(e) == LV_EVENT_CLICKED)
  {
    if ((lastShortClickedReceived == user_data) && (millis() - lastShortClickedReceivedTime < 10))
    {
      omote_log_v("clicked, will send short click\r\n");
      doForceScene = false;
    }
    else
    {
      omote_log_v("clicked, will send long click\r\n");
      doForceScene = true;
    }
  }
  else
  {
    return;
  }

  std::string scene_name = get_scenes_on_sceneSelectionGUI()->at(user_data);

  activate_scene_command = get_activate_scene_command(scene_name);
  if (activate_scene_command != 0)
  {
    // this line is needed
    if (SceneLabel != NULL)
    {
      lv_label_set_text(SceneLabel, "changing...");
    }
    // Problem: screen will not get updated and show "changing..." if "executeCommand(activate_scene_command);" is called here
    // test 1 (does not work): call lv_timer_handler();
    // lv_timer_handler();
    // test 2 (does not work): async_call
    // lv_async_call(activate_scene_async, &activate_scene_command);
    // test 3: lv_timer_create()
    // needs to run only once, and a very short period of 5 ms to wait until first run is enough

    uint16_t scene_command_including_force;
    if (doForceScene)
    {
      // put the force flag into the highest bit
      scene_command_including_force = activate_scene_command | 0x8000;
      omote_log_d("Scene with index %d and name %s was FORCE selected\r\n", user_data, scene_name.c_str());
    }
    else
    {
      scene_command_including_force = activate_scene_command;
      omote_log_d("Scene with index %d and name %s was selected\r\n", user_data, scene_name.c_str());
    }
    lv_timer_t *my_timer = lv_timer_create(activate_scene_cb, 50, (void *)(uintptr_t)scene_command_including_force);
    lv_timer_set_repeat_count(my_timer, 1);
  }
  else
  {
    omote_log_w("Cannot activate scene %s, because command was not found\r\n", scene_name.c_str());
  }
}

void create_button(lv_obj_t *parent, const char *label_text, int row, int column, void *user_data)
{
  lv_obj_t *label;
  lv_obj_t *button;

  button = lv_btn_create(parent);
  lv_obj_set_grid_cell(button, LV_GRID_ALIGN_STRETCH, column, 1, LV_GRID_ALIGN_STRETCH, row, 1);
  lv_obj_set_style_radius(button, radius_primary, LV_PART_MAIN);
  lv_obj_set_style_bg_color(button, color_primary, LV_PART_MAIN);
  lv_obj_add_event_cb(button, sceneSelection_event_cb, LV_EVENT_CLICKED, user_data);
  lv_obj_add_event_cb(button, sceneSelection_event_cb, LV_EVENT_SHORT_CLICKED, user_data);

  label = lv_label_create(button);
  lv_label_set_text(label, label_text);
  lv_obj_center(label);
}

void create_tab_content_sceneSelection(lv_obj_t *tab)
{
  // Configure button grid
  static lv_coord_t col_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
  static lv_coord_t row_dsc[] = {height_primary, height_primary, height_primary, height_primary, height_primary, height_primary, LV_GRID_TEMPLATE_LAST};

  lv_obj_set_style_pad_all(tab, 0, LV_PART_MAIN);

  grid = lv_obj_create(tab);
  lv_obj_set_style_shadow_width(grid, 0, LV_PART_MAIN);
  lv_obj_set_style_bg_color(grid, lv_color_black(), LV_PART_MAIN);
  lv_obj_set_style_border_width(grid, 0, LV_PART_MAIN);
  lv_obj_set_style_grid_column_dsc_array(grid, col_dsc, 0);
  lv_obj_set_style_grid_row_dsc_array(grid, row_dsc, 0);
  lv_obj_set_size(grid, SCR_WIDTH, 270);
  lv_obj_set_layout(grid, LV_LAYOUT_GRID);
  lv_obj_align(grid, LV_ALIGN_TOP_MID, 0, 0);
  lv_obj_set_style_radius(grid, 0, LV_PART_MAIN);

  int rowIndex = 0;
  bool useLeft = true;

  scene_list scenes = get_scenes_on_sceneSelectionGUI();
  if ((scenes != NULL) && (scenes->size() > 0))
  {
    for (int i = 0; i < scenes->size(); i++)
    {
      create_button(
          grid,
          scenes->at(i).c_str(),
          rowIndex,
          useLeft ? 0 : 1,
          (void *)(intptr_t) i
      );

      useLeft = !useLeft;
      if (i > 0 && i % 2 != 0)
      {
        rowIndex++;
      }
    }
  }
}

void notify_tab_before_delete_sceneSelection(void)
{
  // remember to set all pointers to lvgl objects to NULL if they might be accessed from outside.
  // They must check if object is NULL and must not use it if so
}

void register_gui_sceneSelection(void)
{
  register_gui(std::string(tabName_sceneSelection), &create_tab_content_sceneSelection, &notify_tab_before_delete_sceneSelection);
}
