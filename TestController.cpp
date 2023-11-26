// File:          TestController.cpp
// Date:
// Description:
// Author:
// Modifications:

// You may need to add webots include files such as
// <webots/DistanceSensor.hpp>, <webots/Motor.hpp>, etc.
// and/or to add some other includes
#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/Camera.hpp>
#include <webots/TouchSensor.hpp>
// All the webots classes are defined in the "webots" namespace
using namespace webots;

#define TIME_STEP 64
#define MAX_SPEED .5
#define MAX_CAMERA_SPEED 2.0


static Motor* leftMotor;
static Motor* rightMotor;
static TouchSensor* leftSensor;
static TouchSensor* rightSensor;
static Camera* camera;
static Motor* cameraMotor;

// This is the main program of your controller.
// It creates an instance of your Robot instance, launches its
// function(s) and destroys it at the end of the execution.
// Note that only one instance of Robot should be created in
// a controller program.
// The arguments of the main function can be specified by the
// "controllerArgs" field of the Robot node

void rotate_pi(Robot* robot)
{
    leftMotor->setVelocity(-1.0);
    rightMotor->setVelocity(1.0);
    for (int i=0; i < 24; i++)
    {
        robot->step(1);
    }
    
    leftMotor->setVelocity(1.0);
    for (int i = 0; i < 5; i++)
    {
        robot->step(TIME_STEP);
    }
    
    leftMotor->setVelocity(-1.0);
    
    for (int i = 0; i < 24; i++)
    {
         robot->step(1);
    }
    
     rightMotor->setVelocity(0.0);
     leftMotor->setVelocity(0.0);
}

void rotate_minus_pi(Robot* robot)
{
    leftMotor->setVelocity(1.0);
    rightMotor->setVelocity(-1.0);
    for (int i=0; i < 24; i++)
    {
        robot->step(1);
    }
    
    
    rightMotor->setVelocity(1.0);
    for (int i = 0; i < 5; i++)
    {
        robot->step(TIME_STEP);
    }
    
    rightMotor->setVelocity(-1.0);
    
    for (int i = 0; i < 24; i++)
    {
         robot->step(1);
    }
    
     rightMotor->setVelocity(0.0);
     leftMotor->setVelocity(0.0);
}


int main(int argc, char **argv) {
  // create the Robot instance.
  Robot *robot = new Robot();
  
  leftMotor = robot->getMotor("leftMotor");
  rightMotor = robot->getMotor("rightMotor");
  leftMotor->setPosition(INFINITY);
  rightMotor->setPosition(INFINITY);
  leftMotor->setVelocity(0.0);
  rightMotor->setVelocity(0.0);
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
  cameraMotor->setVelocity(2.0);
  
  int height = camera->getWidth();
  int width = camera->getWidth();
  
  for (int i= 0; i < 10; i++)
  {
      robot->step(TIME_STEP);
   
  }
  
  cameraMotor->setVelocity(0.0);
  leftMotor->setVelocity(-0.5*MAX_SPEED);
  rightMotor->setVelocity(-0.5*MAX_SPEED);
  for (int i= 0; i < 5; i++)
  {
       
       camera->saveImage("camera_down_test" + std::to_string(i) + ".jpg", 100);
       robot->step(TIME_STEP);
  }
  
  leftMotor->setVelocity(1.5);
  rightMotor->setVelocity(1.5);
  for (int i = 0 ; i < 10 ; i++)
  {
  robot->step(TIME_STEP);
  }
  bool keep_going = true;
  bool turn_left = true;
  while (keep_going)
  {
      int red = camera->imageGetRed(camera->getImage(), width, width / 2, height-1);
      
      if (leftSensor->getValue() == 1 || rightSensor->getValue() == 1)
      {
          leftMotor->setVelocity(1.5);
          rightMotor->setVelocity(1.5);
      }
      if (red < 30) // we hit the black line
      {
          leftMotor->setVelocity(-1.25);
          rightMotor->setVelocity(-1.25);
          for (int i= 0 ; i < 5; i++)
          {
              robot->step(TIME_STEP);
          }
          if (turn_left)
          {
              rotate_pi(robot);
              turn_left = false;
          }
          else
          {
              rotate_minus_pi(robot);
              turn_left = true;
          }
          leftMotor->setVelocity(0.9);
          rightMotor->setVelocity(0.9);
          for (int i= 0 ; i<10; i++)
          {
              robot->step(TIME_STEP);
          }
      }
      
      
      robot->step(TIME_STEP);
      
  }
  leftMotor->setVelocity(0.0);
  rightMotor->setVelocity(0.0);
  // You should insert a getDevice-like function in order to get the
  // instance of a device of the robot. Something like:
  //  Motor *motor = robot->getMotor("motorname");
  //  DistanceSensor *ds = robot->getDistanceSensor("dsname");
  //  ds->enable(timeStep);

  

  // - perform simulation steps until Webots is stopping the controller
 /* int images_captured = 1000;
  
  for (; images_captured < 1025; images_captured++)
  {
      robot->step(TIME_STEP);
      camera->saveImage("image_" + std::to_string(images_captured) + ".jpg", 100);
  }
  
  left->setPosition(INFINITY);
  right->setPosition(INFINITY);
  left->setVelocity(MAX_SPEED*0.5);
  right->setVelocity(MAX_SPEED);
  for (;images_captured < 1050; images_captured++)
  {
      robot->step(TIME_STEP);
      camera->saveImage("image_" + std::to_string(images_captured) + ".jpg", 100);
  }
  
  left->setVelocity(MAX_SPEED);
  right->setVelocity(-MAX_SPEED);
  
  for (; images_captured < 1075; images_captured++)
  {
      
      robot->step(TIME_STEP);
      camera->saveImage("image_" + std::to_string(images_captured) + ".jpg", 100);
      
  }
  
  for (; images_captured < 2000; images_captured++)
  {
      robot->step(TIME_STEP);
      camera->saveImage("image_" + std::to_string(images_captured) + ".jpg", 100);
  }
  */
//  while (robot->step(timeStep) != -1) {
    
    // Read the sensors:
    // Enter here functions to read sensor data, like:
    //  double val = ds->getValue();

    // Process sensor data here.

    // Enter here functions to send actuator commands, like:
    //  motor->setPosition(10.0);
//  };

  // Enter here exit cleanup code.

  delete robot;
  return 0;
}
