#include "globals.hpp"
#include "lemlib/api.hpp"

//
// ===================== MOTORS =====================
//
pros::MotorGroup left_motors({-1, -2, -3}, pros::MotorGearset::blue);
pros::MotorGroup right_motors({8, 9, 10}, pros::MotorGearset::blue);
pros::MotorGroup intake({20, -21}, pros::MotorGearset::blue);

//
// ===================== SENSORS =====================
//
pros::Imu imu(6);

pros::Rotation horizontal_sensor(-5);
pros::Rotation vertical_sensor(-7);

//
// ===================== TRACKING WHEELS =====================
//
lemlib::TrackingWheel horizontal_tracking_wheel(
    &horizontal_sensor,
    lemlib::Omniwheel::NEW_2,
    -2.4
);

lemlib::TrackingWheel vertical_tracking_wheel(
    &vertical_sensor,
    lemlib::Omniwheel::NEW_2,
    0.1
);

//
// ===================== ODOMETRY =====================
//
lemlib::OdomSensors sensors(
    &vertical_tracking_wheel,   // vertical wheel
    nullptr,                    // no second vertical wheel
    &horizontal_tracking_wheel, // horizontal wheel
    nullptr,                    // no second horizontal wheel
    &imu
);

//
// ===================== DRIVETRAIN =====================
//
lemlib::Drivetrain drivetrain(
    &left_motors,
    &right_motors,
    12.75,                     // track width (in)
    lemlib::Omniwheel::NEW_275, // wheel type
    450,                       // RPM
    2                          // horizontal drift
);

//
// ===================== PID CONTROLLERS =====================
//
lemlib::ControllerSettings lateral_controller(
    8.8,    // kP
    0,      // kI
    0.315,  // kD
    0,      // anti-windup
    0,      // small error range
    0,      // small error timeout
    0,      // large error range
    0,      // large error timeout
    0       // slew
);

lemlib::ControllerSettings angular_controller(
    2.25,   // kP
    0,      // kI
    16.5,   // kD
    3,      // anti-windup
    1,      // small error range (deg)
    100,    // small error timeout (ms)
    3,      // large error range
    500,    // large error timeout
    0       // slew
);

//
// ===================== DRIVE CURVES =====================
//
lemlib::ExpoDriveCurve throttle_curve(
    3,      // deadband
    10,     // min output
    1.019   // expo
);

lemlib::ExpoDriveCurve steer_curve(
    3,
    10,
    1.0625
);

//
// ===================== CHASSIS =====================
//
lemlib::Chassis chassis(
    drivetrain,
    lateral_controller,
    angular_controller,
    sensors,
    &throttle_curve,
    &steer_curve
);

//
// ===================== PNEUMATICS =====================
//
pros::adi::DigitalOut LongGoal('A');
pros::adi::DigitalOut MidGoal('B');
pros::adi::DigitalOut MatchLoader('C');
pros::adi::DigitalOut Descorer('D');

//
// ===================== STATE VARIABLES =====================
//
bool LongGoalFlap = false;
bool MidGoalFlap = false;
bool MatchLoaderFlap = false;
bool DescorerFlap = false;
