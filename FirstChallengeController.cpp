
#include <iostream>
#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/Camera.hpp>
#include <webots/TouchSensor.hpp>

#define TIME_STEP 4
#define MAX_SPEED .5
#define MAX_CAMERA_SPEED 2.0

// All the webots classes are defined in the "webots" namespace
using namespace webots;

//All components of the robot
static Motor* leftMotor;
static Motor* rightMotor;
static TouchSensor* leftSensor;
static TouchSensor* rightSensor;
static Camera* camera;
static Motor* cameraMotor;

//High level functions
static void MoveForward() {
    leftMotor->setVelocity(MAX_SPEED);
    rightMotor->setVelocity(MAX_SPEED);
}

static void MoveBack() {
    leftMotor->setVelocity(-MAX_SPEED);
    rightMotor->setVelocity(-MAX_SPEED);
}

static void TurnLeft() {
    leftMotor->setVelocity(-MAX_SPEED);
    rightMotor->setVelocity(MAX_SPEED);
}

static void TurnRight() {
    leftMotor->setVelocity(MAX_SPEED);
    rightMotor->setVelocity(-MAX_SPEED);
}

static void ResetMotors() {
    leftMotor->setVelocity(0);
    rightMotor->setVelocity(0);
    cameraMotor->setVelocity(0);
}

int main(int argc, char** argv) {
    //Create the robot instance.
    Robot* robot = new Robot();

    //Set up motor/track wheels
    leftMotor = robot->getMotor("leftMotor");
    rightMotor = robot->getMotor("rightMotor");
    leftMotor->setPosition(INFINITY);
    rightMotor->setPosition(INFINITY);

    //Set up touch sensors
    leftSensor = robot->getTouchSensor("left sensor");
    rightSensor = robot->getTouchSensor("right sensor");
    leftSensor->enable(TIME_STEP);
    rightSensor->enable(TIME_STEP);

    //Set up camera and camera motor
    camera = robot->getCamera("camera");
    camera->enable(TIME_STEP);
    cameraMotor = robot->getMotor("camera motor");
    cameraMotor->setPosition(INFINITY);
    cameraMotor->setVelocity(0.0);
    
    //*********Robot AI goes here*********
    
    int k = 0;
    while (robot->step(TIME_STEP) != -1 && k < 4)
    {
        for (int i = 0; i < 40; i++) // get to the next corner
        {
            MoveForward();
            robot->step(TIME_STEP);
        }
          
        for (int i = 0; i < 36; i++) // turn left 90 degrees
        {
            TurnLeft();
            robot->step(1);
        }
        k++;
    }
    
    while (robot->step(TIME_STEP) != -1 && k < 8)
    {
      for (int i=0; i < 40 ; i++)
      {
          MoveBack();
          robot->step(TIME_STEP);
      }
      for (int i = 0 ; i < 36; i++)
      {
          TurnLeft();
          robot->step(1);
      }
      k++;
     }
    //End of AI
    ResetMotors();
    delete robot;
    return 0;  // EXIT_SUCCESS
}