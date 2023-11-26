#ifndef APP_TEMPLATE_UI_H
#define APP_TEMPLATE_UI_H

#include "u8g2.h"

typedef struct menu_items_t {
    size_t selected;
    const char **items;
    size_t count;
} menu_items_t;

void init_screen(u8g2_t *u8g2);

void show_menu_items(u8g2_t *u8g2, menu_items_t *items);

#endif //APP_TEMPLATE_UI_H
