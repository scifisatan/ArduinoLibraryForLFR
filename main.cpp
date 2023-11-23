#include <Arduino.h>
#include "IRARRAY/ARRAY.h"
#include "MOTOR/MOTORS.h"
#include "PID/PID.h"

const int MIN_SPEED = 60;
const int BASE_SPEED = 80;
const int MAX_SPEED = 100;

int ki = 0;
int kd = 0;
int kp = 0;

// motors(PWMA, AIN1, AIN2, PWMB, BIN1, BIN2);
MOTORS motors(3, 5, 6, 7, 8, 9);
ARRAY irArray(A1, A2, A3, A4, A5);
PID pid(kp, ki, kd);

void setup()
{
  Serial.begin(9600);
  motors.turnAround(70);
  irArray.calibrate();
  motors.stop();
}

void loop()
{
  irArray.readSensorValue();
  int error = irArray.calcError();

  if (irArray.isOnLine())
  {
    int pidValue = pid.calcPID(error);
    int lsp = BASE_SPEED - pidValue;
    int rsp = BASE_SPEED + pidValue;
    lsp = constrain(lsp, MIN_SPEED, MAX_SPEED);
    rsp = constrain(rsp, MIN_SPEED, MAX_SPEED);
    motors.drive(lsp, rsp);
  }
  else
  {
    motors.turnLeft(40);
  }
}