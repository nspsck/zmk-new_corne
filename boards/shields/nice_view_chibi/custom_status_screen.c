/* SPDX-License-Identifier: MIT */

#include <lvgl.h>
#include <zmk/activity.h>
#include <zmk/display/status_screen.h>

LV_IMG_DECLARE(sleepy_chibi);

static void breathe(void *obj, int32_t offset) {
    /* Keep the memory LCD image visible, but stop moving it while idle. */
    lv_obj_set_x(obj, zmk_activity_get_state() == ZMK_ACTIVITY_ACTIVE ? offset : 0);
}

lv_obj_t *zmk_display_status_screen(void) {
    lv_obj_t *screen = lv_obj_create(NULL);
    lv_obj_remove_style_all(screen);
    /* The pinned Zephyr MONO01 bridge maps LVGL white to panel black. */
    lv_obj_set_style_bg_color(screen, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);

    /*
     * nice!view exposes a native 160x68 framebuffer. The bitmap is already
     * rotated clockwise, matching the upstream shield's portrait orientation.
     * Moving native X raises/lowers the upright portrait. Its black margins
     * leave room for the gentle motion without clipping the character.
     */
    lv_obj_t *portrait = lv_img_create(screen);
    lv_img_set_src(portrait, &sleepy_chibi);
    lv_obj_set_pos(portrait, 0, 0);

    /* A five-second breath: two seconds up, two down, one at rest. */
    lv_anim_t breath;
    lv_anim_init(&breath);
    lv_anim_set_var(&breath, portrait);
    lv_anim_set_exec_cb(&breath, breathe);
    lv_anim_set_values(&breath, 0, 2);
    lv_anim_set_time(&breath, 2000);
    lv_anim_set_playback_time(&breath, 2000);
    lv_anim_set_repeat_delay(&breath, 1000);
    lv_anim_set_repeat_count(&breath, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&breath);

    return screen;
}
