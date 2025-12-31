#pragma once
// ===PROS & LemLib Includes=== //
#include "lemlib/api.hpp"
#include "autons.hpp"
#include "selector.hpp"
#include <string>

// Motors
extern pros::MotorGroup left_motors;
extern pros::MotorGroup right_motors;
// tracking wheels
extern lemlib::TrackingWheel horizontal_tracking_wheel;
extern lemlib::TrackingWheel vertical_tracking_wheel;

// odom
extern lemlib::OdomSensors sensors;

// drivetrain
extern lemlib::Drivetrain drivetrain;

// PID
extern lemlib::ControllerSettings lateral_controller;
extern lemlib::ControllerSettings angular_controller;

// drive curves
extern lemlib::ExpoDriveCurve throttle_curve;
extern lemlib::ExpoDriveCurve steer_curve;

// chassis
extern lemlib::Chassis chassis;

extern pros::MotorGroup intake;

// IMU
extern pros::Imu imu;

// Rotation Sensors
extern pros::Rotation horizontal_sensor;
extern pros::Rotation vertical_sensor;

// Pneumatics
extern pros::adi::DigitalOut LongGoal;
extern pros::adi::DigitalOut MidGoal;
extern pros::adi::DigitalOut MatchLoader;
extern pros::adi::DigitalOut Descorer;

// State variables //
extern bool LongGoalFlap;
extern bool MidGoalFlap;
extern bool MatchLoaderFlap;
extern bool DescorerFlap;

//Global state management
extern bool driver_control_active;
void startAuton();
void stopAuton();