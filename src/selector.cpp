#include "selector.hpp"
#include "liblvgl/lvgl.h"
#include "pros/apix.h"
#include "globals.hpp"
#include <stdio.h>

lv_obj_t *homeScreen; // define homeScreen

// Global variables to store selection
int selectedAuton = -1; // -1: None, 0: Do Nothing, 1: Left, 2: Right, 3: Skills
int selectedAlliance = -1; // -1: None, 0: Red, 1: Blue

// LVGL Objects
lv_obj_t *allianceScreen;
lv_obj_t *autonScreen;
lv_obj_t *confirmLabel;

// Forward declarations
void createAllianceScreen();
void createAutonScreen();
void updateConfirmation();

// Button event callbacks
static void red_btn_event_handler(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_CLICKED) {
    selectedAlliance = 0;
    lv_scr_load(autonScreen);
    updateConfirmation();
  }
}

static void blue_btn_event_handler(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_CLICKED) {
    selectedAlliance = 1;
    lv_scr_load(autonScreen);
    updateConfirmation();
  }
}

static void left_btn_event_handler(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_CLICKED) {
    selectedAuton = 1;
    updateConfirmation();
    startAuton();
  }
}

static void right_btn_event_handler(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_CLICKED) {
    selectedAuton = 2;
    updateConfirmation();
    startAuton();
  }
}

static void skills_btn_event_handler(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_CLICKED) {
    selectedAuton = 3;
    updateConfirmation();
    startAuton();
  }
}

static void nothing_btn_event_handler(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_CLICKED) {
    selectedAuton = 0;
    updateConfirmation();
    startAuton();
  }
}

static void back_btn_event_handler(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_CLICKED) {
    lv_scr_load(allianceScreen);
  }
}


void initializeSelector() {
  homeScreen = lv_scr_act(); // set homeScreen to the current active screen
  // Create screens
  allianceScreen = lv_obj_create(NULL);
  autonScreen = lv_obj_create(NULL);

  createAllianceScreen();
  createAutonScreen();

  // Load initial screen
  lv_scr_load(allianceScreen);
}

void createAllianceScreen() {
  // Red Alliance Button
  lv_obj_t *redBtn = lv_btn_create(allianceScreen);
  lv_obj_set_pos(redBtn, 0, 0);
  lv_obj_set_size(redBtn, 240, 240);
  lv_obj_add_event_cb(redBtn, red_btn_event_handler, LV_EVENT_ALL, NULL);

  static lv_style_t redStyle;
  lv_style_init(&redStyle);
  lv_style_set_bg_color(&redStyle, lv_palette_main(LV_PALETTE_RED));
  lv_obj_add_style(redBtn, &redStyle, 0);

  lv_obj_t *redLabel = lv_label_create(redBtn);
  lv_label_set_text(redLabel, "RED ALLIANCE");
  lv_obj_center(redLabel);

  // Blue Alliance Button
  lv_obj_t *blueBtn = lv_btn_create(allianceScreen);
  lv_obj_set_pos(blueBtn, 240, 0);
  lv_obj_set_size(blueBtn, 240, 240);
  lv_obj_add_event_cb(blueBtn, blue_btn_event_handler, LV_EVENT_ALL, NULL);

  static lv_style_t blueStyle;
  lv_style_init(&blueStyle);
  lv_style_set_bg_color(&blueStyle, lv_palette_main(LV_PALETTE_BLUE));
  lv_obj_add_style(blueBtn, &blueStyle, 0);

  lv_obj_t *blueLabel = lv_label_create(blueBtn);
  lv_label_set_text(blueLabel, "BLUE ALLIANCE");
  lv_obj_center(blueLabel);
}

void createAutonScreen() {
  // Create buttons for routines
  lv_obj_t *leftBtn = lv_btn_create(autonScreen);
  lv_obj_set_pos(leftBtn, 10, 10);
  lv_obj_set_size(leftBtn, 140, 80);
  lv_obj_add_event_cb(leftBtn, left_btn_event_handler, LV_EVENT_ALL, NULL);
  lv_obj_t *leftLabel = lv_label_create(leftBtn);
  lv_label_set_text(leftLabel, "Left Side");
  lv_obj_center(leftLabel);

  lv_obj_t *rightBtn = lv_btn_create(autonScreen);
  lv_obj_set_pos(rightBtn, 160, 10);
  lv_obj_set_size(rightBtn, 140, 80);
  lv_obj_add_event_cb(rightBtn, right_btn_event_handler, LV_EVENT_ALL, NULL);
  lv_obj_t *rightLabel = lv_label_create(rightBtn);
  lv_label_set_text(rightLabel, "Right Side");
  lv_obj_center(rightLabel);

  lv_obj_t *skillsBtn = lv_btn_create(autonScreen);
  lv_obj_set_pos(skillsBtn, 10, 100);
  lv_obj_set_size(skillsBtn, 140, 80);
  lv_obj_add_event_cb(skillsBtn, skills_btn_event_handler, LV_EVENT_ALL, NULL);
  lv_obj_t *skillsLabel = lv_label_create(skillsBtn);
  lv_label_set_text(skillsLabel, "Skills");
  lv_obj_center(skillsLabel);

  lv_obj_t *nothingBtn = lv_btn_create(autonScreen);
  lv_obj_set_pos(nothingBtn, 160, 100);
  lv_obj_set_size(nothingBtn, 140, 80);
  lv_obj_add_event_cb(nothingBtn, nothing_btn_event_handler, LV_EVENT_ALL,
                      NULL);
  lv_obj_t *nothingLabel = lv_label_create(nothingBtn);
  lv_label_set_text(nothingLabel, "Do Nothing");
  lv_obj_center(nothingLabel);

  // Back Button
  lv_obj_t *backBtn = lv_btn_create(autonScreen);
  lv_obj_set_pos(backBtn, 350, 10);
  lv_obj_set_size(backBtn, 100, 50);
  lv_obj_add_event_cb(backBtn, back_btn_event_handler, LV_EVENT_ALL, NULL);
  lv_obj_t *backLabel = lv_label_create(backBtn);
  lv_label_set_text(backLabel, "Back");
  lv_obj_center(backLabel);

  // Confirmation Label
  confirmLabel = lv_label_create(autonScreen);
  lv_obj_set_pos(confirmLabel, 320, 100);
  lv_label_set_text(confirmLabel, "Selected:\nNone");
}

void updateConfirmation() {
  char buffer[100];
  const char *allianceStr = (selectedAlliance == 0)   ? "Red"
                            : (selectedAlliance == 1) ? "Blue"
                                                      : "None";
  const char *autonStr = "None";

  switch (selectedAuton) {
  case 0:
    autonStr = "Do Nothing";
    break;
  case 1:
    autonStr = "Left";
    break;
  case 2:
    autonStr = "Right";
    break;
  case 3:
    autonStr = "Skills";
    break;
  }

  sprintf(buffer, "Alliance: %s\nAuton: %s", allianceStr, autonStr);
  lv_label_set_text(confirmLabel, buffer);
}

int getSelectedAuton() { return selectedAuton; }

bool isRedAlliance() { return selectedAlliance == 0; }

bool isBlueAlliance() { return selectedAlliance == 1; }