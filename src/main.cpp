#include "main.h"
#include "lemlib/api.hpp"
#include "globals.hpp"    // defines chassis, motors, pneumatics, IMU, etc.
#include "selector.hpp"   // declares getSelectedAuton(), isRedAlliance(), isBlueAlliance()
#include "autons.hpp"     // declares DoNothing(), RedLeft(), RedRight(), BlueLeft(), BlueRight(), Skills(), TuneChassis()
#include "pros/llemu.hpp"

// Button previous states for toggles
bool prevX = false;
bool prevY = false;
bool prevUp = false;
bool driveReversed = false;

// Optional: Track odometry display start
bool odometry_started = false;
pros::Task *auton_task = nullptr;
bool driver_control_active = true;

// Start autonomous task
void startAuton() {
    driver_control_active = false;

    if (auton_task != nullptr) {
        auton_task->remove();
        delete auton_task;
        auton_task = nullptr;
    }

    auton_task = new pros::Task([] {
        autonomous();
        driver_control_active = true;
    });

    pros::lcd::set_text(0, "Autonomous Running");
}

// Stop autonomous task
void stopAuton() {
    driver_control_active = true;

    if (auton_task != nullptr) {
        auton_task->remove();
        delete auton_task;
        auton_task = nullptr;
    }

    pros::lcd::set_text(0, "Driver Control");
}

// Odometry LCD display
void startOdometryDisplay() {
    if (odometry_started)
        return;
    odometry_started = true;

    pros::lcd::initialize();
    pros::lcd::set_text(0, "Robot Initialized");

    pros::Task screen_task([] {
        while (true) {
            auto pose = chassis.getPose();
            pros::lcd::print(1, "X:%.1f Y:%.1f T:%.1f", pose.x, pose.y, pose.theta);
            pros::delay(20);
        }
    });
}

// === Initialize ===
void initialize() {
    pros::lcd::initialize();
    // Calibrate IMU and tracking wheels
    chassis.calibrate();
    chassis.setPose(0, 0, 0); // set initial chassis pose
    initializeSelector();
    pros::delay(2000); // give time for imu to calibrate
    // Set initial state of pneumatics
    LongGoal.set_value(0);
    MidGoal.set_value(0);
    MatchLoader.set_value(0);
    Descorer.set_value(0);

    LongGoalFlap = false;
    MidGoalFlap = false;
    MatchLoaderFlap = false;
    DescorerFlap = false;

    // Optional: start odometry display
    startOdometryDisplay();
}


// === Autonomous ===
void autonomous() {
    startOdometryDisplay();

    int selected = getSelectedAuton();
    bool isRed = isRedAlliance();
    bool isBlue = isBlueAlliance();

    pros::Controller controller(pros::E_CONTROLLER_MASTER);
    controller.print(1, 0, "Sel:%d R:%d B:%d", selected, isRed, isBlue);

    switch (selected) {
        case 0:
            DoNothing();
            break;
        case 1:
            if (isRed) RedLeft();
            else if (isBlue) BlueLeft();
            else DoNothing();
            break;
        case 2:
            if (isRed) RedRight();
            else if (isBlue) BlueRight();
            else DoNothing();
            break;
        case 3:
            Skills();
            break;
        default:
            TuneChassis();
            break;
    }
}

// === Disabled & Competition Init ===
void disabled() {}
void competition_initialize() {}

// === Operator Control ===
void opcontrol() {
    pros::Controller controller(pros::E_CONTROLLER_MASTER);

    while (true) {
        // Toggle drive reverse
        bool currUp = controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP);
        if (currUp && !prevUp) driveReversed = !driveReversed;
        prevUp = currUp;

        // Driver control
        if (!driver_control_active) {
            left_motors.move(0);
            right_motors.move(0);
            intake.move_velocity(0);
            pros::delay(20);
            continue;
        }

        int forward = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        if (driveReversed) forward = -forward;

        chassis.arcade(forward, turn);

         // ================= INTAKE =================
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            intake.move_velocity(600);
            intake.move_velocity(600);
        }
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            intake.move_velocity(-600);
        }else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){ 
            intake.move_velocity(600); 
            LongGoalFlap = true; 
            MidGoalFlap = false; 
        }else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){ 
            intake.move_velocity(600); 
            LongGoalFlap = false; 
            MidGoalFlap = true; }
        else {
            intake.move_velocity(0);
            LongGoalFlap = false;
            MidGoalFlap = false;
        }

        // Pneumatic toggles
        bool currX = controller.get_digital(pros::E_CONTROLLER_DIGITAL_X);
        bool currY = controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y);

        if (currX && !prevX) MatchLoaderFlap = !MatchLoaderFlap;
        if (currY && !prevY) DescorerFlap = !DescorerFlap;

        prevX = currX;
        prevY = currY;

        // Update pneumatics
        MatchLoader.set_value(MatchLoaderFlap);
        Descorer.set_value(DescorerFlap);
        LongGoal.set_value(LongGoalFlap);
        MidGoal.set_value(MidGoalFlap);

        pros::delay(20);
    }
}
