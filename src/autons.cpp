#include "globals.hpp"
#include "autons.hpp"
#include "lemlib/api.hpp"
#include "pros/misc.h"
#include "pros/llemu.hpp"
#include "liblvgl/lvgl.h"
#include "pros/apix.h"
#include "selector.hpp"
#include <stdio.h>

// Helper to set initial pose based on routine
void RedLeft() {
  // chassis.setPose(-48, -48, 90); // Example starting pose
  // Add Red Left routine here
  pros::lcd::print(0, "Running Red Left");

  // Debug: Print to controller
  pros::Controller controller(pros::E_CONTROLLER_MASTER);
  controller.print(2, 0, "Running RedLeft");

  // Debug: Move motors directly to verify connection

  chassis.setPose(0, 0, 0);
  chassis.moveToPose(-100.0f, -100.0f, 10.0f, 100000);
}

void RedRight() {
  // chassis.setPose(-48, 48, 90); // Example starting pose
  // Add Red Right routine here
  pros::lcd::print(0, "Running Red Right");
  chassis.setPose(0, 0, 0);
  chassis.moveToPose(10.0f, 10.0f, 10.0f, 10);
}

void BlueLeft() {
  // chassis.setPose(48, 48, 270); // Example starting pose
  // Add Blue Left routine here
  pros::lcd::print(0, "Running Blue Left");
  chassis.setPose(0, 0, 0);
  chassis.moveToPose(10.0f, 10.0f, 10.0f, 10);
}

void BlueRight() {
  // chassis.setPose(48, -48, 270); // Example starting pose
  // Add Blue Right routine here
  pros::lcd::print(0, "Running Blue Right");
  chassis.setPose(0, 0, 0);
  chassis.moveToPose(10.0f, 10.0f, 10.0f, 10);
}

void Skills() {
  // chassis.setPose(-48, -48, 90); // Example starting pose
  // Add Skills routine here
  intake.move_velocity(600);
  chassis.setPose(0, 0, 0);
  chassis.moveToPose(0, 40, 0, 10000);
}

void DoNothing() {
  // Do nothing
  pros::lcd::print(0, "Running Do Nothing");
  chassis.setPose(0,0,0);
  chassis.moveToPose(0, 5, 0,1000);
}

void TuneChassis() {
  // Set the pose to 0, 0, 0
  if (homeScreen != NULL) {
        lv_scr_load(homeScreen); 
    }
  chassis.setPose(0,0,0);
  intake.move_velocity(200);
  chassis.moveToPose(0, 40, 0, 10000);
}