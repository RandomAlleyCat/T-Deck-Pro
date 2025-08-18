#include "ui_deckpro.h"
#include "src/assets.h"
#include "ui_deckpro_port.h"
#include "Arduino.h"

#define FONT_BOLD_MONO_SIZE_14 &Font_Mono_Bold_14
#define FONT_BOLD_MONO_SIZE_15 &Font_Mono_Bold_15

// simple back button
static void back_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED) {
        scr_mgr_pop(false);
    }
}

static lv_obj_t *scr_back_btn_create(lv_obj_t *parent, const char *text)
{
    lv_obj_t * btn = lv_btn_create(parent);
    lv_obj_set_size(btn, 60, 30);
    lv_obj_align(btn, LV_ALIGN_TOP_LEFT, 3, 3);
    lv_obj_add_event_cb(btn, back_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_t *label = lv_label_create(btn);
    lv_obj_center(label);
    lv_label_set_text(label, text);
    return btn;
}

// menu
#define MENU_BTN_NUM (sizeof(menu_btn_list) / sizeof(menu_btn_list[0]))

static void menu_btn_event_cb(lv_event_t *e)
{
    struct menu_btn *tgr = (struct menu_btn *)e->user_data;
    scr_mgr_push(tgr->idx, false);
}

static void menu_btn_create(lv_obj_t *parent, struct menu_btn *info)
{
    lv_obj_t * btn = lv_btn_create(parent);
    lv_obj_set_size(btn, 50, 50);
    lv_obj_set_pos(btn, info->pos_x, info->pos_y);
    lv_obj_set_style_bg_img_src(btn, info->icon, 0);
    lv_obj_add_event_cb(btn, menu_btn_event_cb, LV_EVENT_CLICKED, info);
    lv_obj_t *label = lv_label_create(btn);
    lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_set_style_text_font(label, FONT_BOLD_MONO_SIZE_14, 0);
    lv_label_set_text(label, info->name);
}

static struct menu_btn menu_btn_list[] = {
    {SCREEN_SHUTDOWN_ID, &img_lora, "Shutdown", 23, 13},
    {SCREEN_SLEEP_ID, &img_sleep,   "Sleep",    95, 13},
    {SCREEN_ACOS_ID,   &img_acos,   "ACOS",    167, 13},
};

static void create_menu(lv_obj_t *parent)
{
    for (uint32_t i = 0; i < MENU_BTN_NUM; i++) {
        menu_btn_create(parent, &menu_btn_list[i]);
    }
}
static void entry_menu(void){}
static void exit_menu(void){}
static void destroy_menu(void){}
static scr_lifecycle_t screen_menu = {
    .create = create_menu,
    .entry = entry_menu,
    .exit = exit_menu,
    .destroy = destroy_menu,
};

// shutdown screen
static void shutdown_timer_event(lv_timer_t *t)
{
    ui_shutdown_on();
    lv_timer_del(t);
}
static void create_shutdown(lv_obj_t *parent)
{
    lv_obj_t * img = lv_img_create(parent);
    lv_img_set_src(img, &img_start);
    lv_obj_center(img);
    lv_timer_create(shutdown_timer_event, 2000, NULL);
    scr_back_btn_create(parent, "Back");
}
static scr_lifecycle_t screen_shutdown = {
    .create = create_shutdown,
    .entry = NULL,
    .exit = NULL,
    .destroy = NULL,
};

// sleep screen
static void sleep_timer_event(lv_timer_t *t)
{
    ui_sleep_on();
    lv_timer_del(t);
}
static void create_sleep(lv_obj_t *parent)
{
    lv_obj_t * img = lv_img_create(parent);
    lv_img_set_src(img, &img_start);
    lv_obj_center(img);
    lv_timer_create(sleep_timer_event, 2000, NULL);
    scr_back_btn_create(parent, "Back");
}
static scr_lifecycle_t screen_sleep = {
    .create = create_sleep,
    .entry = NULL,
    .exit = NULL,
    .destroy = NULL,
};

// ACOS screen
static void create_acos(lv_obj_t *parent)
{
    lv_obj_t * img = lv_img_create(parent);
    lv_img_set_src(img, &img_acos_logo);
    lv_obj_center(img);
    scr_back_btn_create(parent, "Back");
}
static scr_lifecycle_t screen_acos = {
    .create = create_acos,
    .entry = NULL,
    .exit = NULL,
    .destroy = NULL,
};

void ui_deckpro_entry(void)
{
    lv_disp_t *disp = lv_disp_get_default();
    disp->theme = lv_theme_mono_init(disp, false, LV_FONT_DEFAULT);

    scr_mgr_init();
    scr_mgr_register(SCREEN0_ID, &screen_menu);
    scr_mgr_register(SCREEN_SHUTDOWN_ID, &screen_shutdown);
    scr_mgr_register(SCREEN_SLEEP_ID, &screen_sleep);
    scr_mgr_register(SCREEN_ACOS_ID, &screen_acos);

    scr_mgr_switch(SCREEN0_ID, false);
    scr_mgr_set_anim(LV_SCR_LOAD_ANIM_OVER_LEFT, LV_SCR_LOAD_ANIM_OVER_LEFT, LV_SCR_LOAD_ANIM_OVER_LEFT);
}
