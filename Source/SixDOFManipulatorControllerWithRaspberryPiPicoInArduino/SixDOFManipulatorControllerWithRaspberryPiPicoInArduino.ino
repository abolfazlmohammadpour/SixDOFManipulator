// Including Arduino Default Library For Using Arduino's Functionality
#include <Arduino.h>
// Including Default Arduino Library For Working With Servo Motors
#include <Servo.h>
// Including Default Arduino Library For Working With Alphanumeric Liquid Crystal Displays
#include <LiquidCrystal.h>

// Definations Of Some Of The Useful Value For Using Servo Motors Of The Manipulator
// Definations Of The Physical PIN Which Are Using For Servo Motors
#define ServoMotorOne_PIN (int)0
#define ServoMotorTwo_PIN (int)1
#define ServoMotorThree_PIN (int)2
#define ServoMotorFour_PIN (int)3
#define ServoMotorFive_PIN (int)4
#define ServoMotorSix_PIN (int)5
// Definations Of The Start Position Of The Servo Motors
#define ServoMotorOne_START (int)90
#define ServoMotorTwo_START (int)90
#define ServoMotorThree_START (int)90
#define ServoMotorFour_START (int)90
#define ServoMotorFive_START (int)90
#define ServoMotorSix_START (int)90
// Definations Of The Minimum Position Of The Servo Motors
#define ServoMotorOne_MINIMUM (int)0
#define ServoMotorTwo_MINIMUM (int)0
#define ServoMotorThree_MINIMUM (int)0
#define ServoMotorFour_MINIMUM (int)0
#define ServoMotorFive_MINIMUM (int)0
#define ServoMotorSix_MINIMUM (int)0
// Definations Of The Maximum Positions Of the Servo Motors
#define ServoMotorOne_MAXIMUM (int)180
#define ServoMotorTwo_MAXIMUM (int)180
#define ServoMotorThree_MAXIMUM (int)180
#define ServoMotorFour_MAXIMUM (int)180
#define ServoMotorFive_MAXIMUM (int)180
#define ServoMotorSix_MAXIMUM (int)180

// Declaring Some Definations For Using Push Button To Managing Servo Motors
// Declaring Some Definations Which Are Referenced To The Physical Pins That Are Using By Push Buttons
#define PushButtonReset_PIN (uint8_t)6
#define PushButtonLeft_PIN (uint8_t)7
#define PushButtonSelect_PIN (uint8_t)8
#define PushButtonRight_PIN (uint8_t)9
// Declaring Some Definations For Managing Status Of Push Buttons Signals
#define PushButtonReset_ENABLE (uint8_t) LOW
#define PushButtonReset_DISABLE (uint8_t) HIGH

#define PushButtonLeft_ENABLE (uint8_t) LOW
#define PushButtonLeft_DISABLE (uint8_t) HIGH

#define PushButtonSelect_ENABLE (uint8_t) LOW
#define PushButtonSelect_DISABLE (uint8_t) HIGH

#define PushButtonRight_ENABLE (uint8_t) LOW
#define PushButtonRight_DISABLE (uint8_t) HIGH

// Declaring Some Definations For Physical Pins Of The Alphanumeric Liquid Crystal Display
#define Display_RS_PIN (uint8_t)10
#define Display_EN_PIN (uint8_t)11
#define Display_D4_PIN (uint8_t)12
#define Display_D5_PIN (uint8_t)13
#define Display_D6_PIN (uint8_t)14
#define Display_D7_PIN (uint8_t)15
// Declaring Some Values For Configuring The Alphanumeric LCD
#define Display_ROWS (uint8_t)2
#define Display_COLUMNS (uint8_t)16

// Declaring Some Value For Managing Selected Servo Motors
#define NumberOfNoneServoMotor (uint8_t)0
#define NumberOfServoMotorOne (uint8_t)1
#define NumberOfServoMotorTwo (uint8_t)2
#define NumberOfServoMotorThree (uint8_t)3
#define NumberOfServoMotorFour (uint8_t)4
#define NumberOfServoMotorFive (uint8_t)5
#define NumberOfServoMotorSix (uint8_t)6

// Declaring Servo Objects For Using Servo Motors
Servo ServoMotorOne;
Servo ServoMotorTwo;
Servo ServoMotorThree;
Servo ServoMotorFour;
Servo ServoMotorFive;
Servo ServoMotorSix;

// Declaring LiquidCrystal Object As Main Display For Monitoring Data In Reality
LiquidCrystal Display((uint8_t)Display_RS_PIN, (uint8_t)Display_EN_PIN, (uint8_t)Display_D4_PIN, (uint8_t)Display_D5_PIN, (uint8_t)Display_D6_PIN, (uint8_t)Display_D7_PIN);

// This Fuction Will Move All Servo Motors To Their Start Position
void HomeAllServoMotors(void);

// This Function Will Move The Servo Motor To Its Start Position
void HomeServoMotor(Servo, int);

// This Function Will Increase Angle Of A Servo Motor According To Given Parameters And Printing Two Messages On Display According To The Input Texts
void IncreaseAngleServoMotor(Servo, LiquidCrystal, const char *, const char *, int, int, unsigned long int);

// This Function Will Decrease Angle Of A Servo Motor According To Given Parameters And Printing Two Messages On Display According To The Input Texts
void DecreaseAngleServoMotor(Servo, LiquidCrystal, const char *, const char *, int, int, unsigned long int);

// Declaring A Variable For Managing Current Selected Servo Motor By User
uint8_t SelectedServoMotor = (uint8_t)NumberOfNoneServoMotor;

// Declaring A Variable For Storing Number Of Angles That Move In Each Time Of Movement
uint8_t ServoMotorMovementAngle = (uint8_t)1;

// Declaring A Variable For Storing The Delay That Are Happening In Movement Between Each Angle
uint8_t ServoMotorMovementDelay = (uint8_t)50;

// Declaring A Temperature Array Of Characters For Handling The Text That Will Print On The Display
char TemperatureArray[17] = "                ";

// Declaring A Temperature Variable For Storing The Current Angle Of Each Servo Motor In Its Own Operation
int TemperatureAngle = (int)0;

void setup(void) {
  // Configuring Push Button Pins For Using In Physical Circuit
  pinMode((uint8_t)PushButtonReset_PIN, (uint8_t)INPUT_PULLUP);
  pinMode((uint8_t)PushButtonLeft_PIN, (uint8_t)INPUT_PULLUP);
  pinMode((uint8_t)PushButtonSelect_PIN, (uint8_t)INPUT_PULLUP);
  pinMode((uint8_t)PushButtonRight_PIN, (uint8_t)INPUT_PULLUP);

  // Configuring The Display For Starting Using Of It
  Display.begin((uint8_t)Display_COLUMNS, (uint8_t)Display_ROWS);

  // Attaching Physical Pins To The Servo Objects For Using In Reality
  while (ServoMotorOne.attached() == (bool)false)
    ServoMotorOne.attach((int)ServoMotorOne_PIN);
  while (ServoMotorTwo.attached() == (bool)false)
    ServoMotorTwo.attach((int)ServoMotorTwo_PIN);
  while (ServoMotorThree.attached() == (bool)false)
    ServoMotorThree.attach((int)ServoMotorThree_PIN);
  while (ServoMotorFour.attached() == (bool)false)
    ServoMotorFour.attach((int)ServoMotorFour_PIN);
  while (ServoMotorFive.attached() == (bool)false)
    ServoMotorFive.attach((int)ServoMotorFive_PIN);
  while (ServoMotorSix.attached() == (bool)false)
    ServoMotorSix.attach((int)ServoMotorSix_PIN);

  // Sending Servo Motors To Their Start Position
  HomeAllServoMotors();
}

void loop(void) {
  // Checking For Clicking Reset Push Button And After Clicking Will Move All Servo Motors To Their Start Position
  if (digitalRead(PushButtonReset_PIN) == PushButtonReset_ENABLE) {
    delay((unsigned long int)250);
    if (digitalRead(PushButtonReset_PIN) == PushButtonReset_DISABLE) {
      HomeAllServoMotors();
    }
  }

  // Checking For Clicking Select Push Button And After Clicking Will Select A Different Servo Motor In Available Range
  if (digitalRead(PushButtonSelect_PIN) == PushButtonSelect_ENABLE) {
    delay((unsigned long int)250);
    if (digitalRead(PushButtonSelect_PIN) == PushButtonSelect_DISABLE) {
      if (SelectedServoMotor <= NumberOfServoMotorSix)
        SelectedServoMotor += (uint8_t)1;
      else
        SelectedServoMotor = NumberOfNoneServoMotor;
    }
  }

  switch (SelectedServoMotor) {
    case NumberOfNoneServoMotor:
      {
        Display.setCursor((uint8_t)0, (uint8_t)0);
        Display.print("ServoMotor: None");
        Display.setCursor((uint8_t)0, (uint8_t)1);
        Display.print("                ");

        break;
      }
    // Custom Controlling Position Of The ServoMotorOne
    case NumberOfServoMotorOne:
      {
        while (digitalRead(PushButtonRight_PIN) == PushButtonRight_ENABLE) {
          TemperatureAngle = ServoMotorOne.read();
          sprintf(TemperatureArray, "  %3d<=%3d<=%3d ", ServoMotorOne_MINIMUM, TemperatureAngle, ServoMotorOne_MAXIMUM);
          IncreaseAngleServoMotor(ServoMotorOne, Display, " ServoMotor : 1 ", TemperatureArray, (int)ServoMotorMovementAngle, (int)ServoMotorOne_MAXIMUM, (unsigned long int)ServoMotorMovementDelay);
        }
        while (digitalRead(PushButtonLeft_PIN) == PushButtonLeft_ENABLE) {
          TemperatureAngle = ServoMotorOne.read();
          sprintf(TemperatureArray, "  %3d<=%3d<=%3d ", ServoMotorOne_MINIMUM, TemperatureAngle, ServoMotorOne_MAXIMUM);
          DecreaseAngleServoMotor(ServoMotorOne, Display, " ServoMotor : 1 ", TemperatureArray, (int)ServoMotorMovementAngle, (int)ServoMotorOne_MINIMUM, (unsigned long int)ServoMotorMovementDelay);
        }

        break;
      }
    // Custom Controlling Position Of The ServoMotorTwo
    case NumberOfServoMotorTwo:
      {
        while (digitalRead(PushButtonRight_PIN) == PushButtonRight_ENABLE) {
          TemperatureAngle = ServoMotorTwo.read();
          sprintf(TemperatureArray, "  %3d<=%3d<=%3d ", ServoMotorTwo_MINIMUM, TemperatureAngle, ServoMotorTwo_MAXIMUM);
          IncreaseAngleServoMotor(ServoMotorTwo, Display, " ServoMotor : 2 ", TemperatureArray, (int)ServoMotorMovementAngle, (int)ServoMotorTwo_MAXIMUM, (unsigned long int)ServoMotorMovementDelay);
        }
        while (digitalRead(PushButtonLeft_PIN) == PushButtonLeft_ENABLE) {
          TemperatureAngle = ServoMotorTwo.read();
          sprintf(TemperatureArray, "  %3d<=%3d<=%3d ", ServoMotorTwo_MINIMUM, TemperatureAngle, ServoMotorTwo_MAXIMUM);
          DecreaseAngleServoMotor(ServoMotorTwo, Display, " ServoMotor : 2 ", TemperatureArray, (int)ServoMotorMovementAngle, (int)ServoMotorTwo_MINIMUM, (unsigned long int)ServoMotorMovementDelay);
        }

        break;
      }
    // Custom Controlling Position Of The ServoMotorThree
    case NumberOfServoMotorThree:
      {
        while (digitalRead(PushButtonRight_PIN) == PushButtonRight_ENABLE) {
          TemperatureAngle = ServoMotorThree.read();
          sprintf(TemperatureArray, "  %3d<=%3d<=%3d ", ServoMotorThree_MINIMUM, TemperatureAngle, ServoMotorThree_MAXIMUM);
          IncreaseAngleServoMotor(ServoMotorThree, Display, " ServoMotor : 3 ", TemperatureArray, (int)ServoMotorMovementAngle, (int)ServoMotorThree_MAXIMUM, (unsigned long int)ServoMotorMovementDelay);
        }
        while (digitalRead(PushButtonLeft_PIN) == PushButtonLeft_ENABLE) {
          TemperatureAngle = ServoMotorThree.read();
          sprintf(TemperatureArray, "  %3d<=%3d<=%3d ", ServoMotorThree_MINIMUM, TemperatureAngle, ServoMotorThree_MAXIMUM);
          DecreaseAngleServoMotor(ServoMotorThree, Display, " ServoMotor : 3 ", TemperatureArray, (int)ServoMotorMovementAngle, (int)ServoMotorThree_MINIMUM, (unsigned long int)ServoMotorMovementDelay);
        }

        break;
      }
    // Custom Controlling Position Of The ServoMotorFour
    case NumberOfServoMotorFour:
      {
        while (digitalRead(PushButtonRight_PIN) == PushButtonRight_ENABLE) {
          TemperatureAngle = ServoMotorFour.read();
          sprintf(TemperatureArray, "  %3d<=%3d<=%3d ", ServoMotorFour_MINIMUM, TemperatureAngle, ServoMotorFour_MAXIMUM);
          IncreaseAngleServoMotor(ServoMotorFour, Display, " ServoMotor : 4 ", TemperatureArray, (int)ServoMotorMovementAngle, (int)ServoMotorFour_MAXIMUM, (unsigned long int)ServoMotorMovementDelay);
        }
        while (digitalRead(PushButtonLeft_PIN) == PushButtonLeft_ENABLE) {
          TemperatureAngle = ServoMotorFour.read();
          sprintf(TemperatureArray, "  %3d<=%3d<=%3d ", ServoMotorFour_MINIMUM, TemperatureAngle, ServoMotorFour_MAXIMUM);
          DecreaseAngleServoMotor(ServoMotorFour, Display, " ServoMotor : 4 ", TemperatureArray, (int)ServoMotorMovementAngle, (int)ServoMotorFour_MINIMUM, (unsigned long int)ServoMotorMovementDelay);
        }

        break;
      }
    // Custom Controlling Position Of The ServoMotorFive
    case NumberOfServoMotorFive:
      {
        while (digitalRead(PushButtonRight_PIN) == PushButtonRight_ENABLE) {
          TemperatureAngle = ServoMotorFive.read();
          sprintf(TemperatureArray, "  %3d<=%3d<=%3d ", ServoMotorFive_MINIMUM, TemperatureAngle, ServoMotorFive_MAXIMUM);
          IncreaseAngleServoMotor(ServoMotorFive, Display, " ServoMotor : 5 ", TemperatureArray, (int)ServoMotorMovementAngle, (int)ServoMotorFive_MAXIMUM, (unsigned long int)ServoMotorMovementDelay);
        }
        while (digitalRead(PushButtonLeft_PIN) == PushButtonLeft_ENABLE) {
          TemperatureAngle = ServoMotorFive.read();
          sprintf(TemperatureArray, "  %3d<=%3d<=%3d ", ServoMotorFive_MINIMUM, TemperatureAngle, ServoMotorFive_MAXIMUM);
          DecreaseAngleServoMotor(ServoMotorFive, Display, " ServoMotor : 5 ", TemperatureArray, (int)ServoMotorMovementAngle, (int)ServoMotorFive_MINIMUM, (unsigned long int)ServoMotorMovementDelay);
        }

        break;
      }
    // Custom Controlling Position Of The ServoMotorSix
    case NumberOfServoMotorSix:
      {
        while (digitalRead(PushButtonRight_PIN) == PushButtonRight_ENABLE) {
          TemperatureAngle = ServoMotorSix.read();
          sprintf(TemperatureArray, "  %3d<=%3d<=%3d ", ServoMotorSix_MINIMUM, TemperatureAngle, ServoMotorSix_MAXIMUM);
          IncreaseAngleServoMotor(ServoMotorSix, Display, " ServoMotor : 6 ", TemperatureArray, (int)ServoMotorMovementAngle, (int)ServoMotorSix_MAXIMUM, (unsigned long int)ServoMotorMovementDelay);
        }
        while (digitalRead(PushButtonLeft_PIN) == PushButtonLeft_ENABLE) {
          TemperatureAngle = ServoMotorSix.read();
          sprintf(TemperatureArray, "  %3d<=%3d<=%3d ", ServoMotorSix_MINIMUM, TemperatureAngle, ServoMotorSix_MAXIMUM);
          DecreaseAngleServoMotor(ServoMotorSix, Display, " ServoMotor : 6 ", TemperatureArray, (int)ServoMotorMovementAngle, (int)ServoMotorSix_MINIMUM, (unsigned long int)ServoMotorMovementDelay);
        }

        break;
      }
  }
}

// This Fuction Will Move All Servo Motors To Their Start Position
void HomeAllServoMotors(void) {
  ServoMotorOne.write((int)ServoMotorOne_START);
  ServoMotorTwo.write((int)ServoMotorTwo_START);
  ServoMotorThree.write((int)ServoMotorThree_START);
  ServoMotorFour.write((int)ServoMotorFour_START);
  ServoMotorFive.write((int)ServoMotorFive_START);
  ServoMotorSix.write((int)ServoMotorSix_START);
}

// This Function Will Move The Servo Motor To Its Start Position
void HomeServoMotor(Servo ServoMotor, int StartPosition) {
  ServoMotor.write((int)StartPosition);
}

// This Function Will Increase Angle Of A Servo Motor According To Given Parameters And Printing Two Messages On Display According To The Input Texts
void IncreaseAngleServoMotor(Servo ServoMotor, LiquidCrystal Display, const char *FirstLine, const char *SecondLine, int StepOfAngle, int MaximumAngle, unsigned long int TimeBetweenAngle) {
  int TheAngle = (int)0;
  TheAngle = ServoMotor.read();
  if (TheAngle <= MaximumAngle) {
    TheAngle += StepOfAngle;
    ServoMotor.write(TheAngle);
  } else {
    TheAngle = MaximumAngle;
    ServoMotor.write(TheAngle);
  }

  delay(TimeBetweenAngle);

  Display.setCursor((uint8_t)0, (uint8_t)0);
  Display.print(FirstLine);
  Display.setCursor((uint8_t)1, (uint8_t)0);
  Display.print(SecondLine);
}

// This Function Will Decrease Angle Of A Servo Motor According To Given Parameters And Printing Two Messages On Display According To The Input Texts
void DecreaseAngleServoMotor(Servo ServoMotor, LiquidCrystal Display, const char *FirstLine, const char *SecondLine, int StepOfAngle, int MinimumAngle, unsigned long int TimeBetweenAngle) {
  int TheAngle = (int)0;
  TheAngle = ServoMotor.read();
  if (TheAngle >= MinimumAngle) {
    TheAngle -= StepOfAngle;
    ServoMotor.write(TheAngle);
  } else {
    TheAngle = MinimumAngle;
    ServoMotor.write(TheAngle);
  }

  delay(TimeBetweenAngle);

  Display.setCursor((uint8_t)0, (uint8_t)0);
  Display.print(FirstLine);
  Display.setCursor((uint8_t)1, (uint8_t)0);
  Display.print(SecondLine);
}