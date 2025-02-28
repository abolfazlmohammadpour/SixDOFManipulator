// Including Arduino Default Library For Using Arduino's Functionality
#include <Arduino.h>
// Including Default Arduino Library For Working With Servo Motors
#include <Servo.h>

// Definations Of Some Of The Useful Value For Using Servo Motors Of The Manipulator
// Definations Of The Physical PIN Which Are Using For Servo Motors
#define ServoMotorOne_PIN (int)2
#define ServoMotorTwo_PIN (int)3
#define ServoMotorThree_PIN (int)4
#define ServoMotorFour_PIN (int)5
#define ServoMotorFive_PIN (int)6
#define ServoMotorSix_PIN (int)7
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

// Declaring Some Definations For Working With Serial Port
#define SerialPortTX_PIN (uint8_t)0
#define SerialPortRX_PIN (uint8_t)1
#define SerialPortBuffer_SIZE (uint16_t)512
#define SerialPortBaudrate_VALUE (uint32_t)115200

// Declaring Some Definations For Hnadling The SelectedServoMotor From User
#define NumberOfNoneServoMotor (uint8_t)0
#define NumberOfServoMotorOne (uint8_t)1
#define NumberOfServoMotorTwo (uint8_t)2
#define NumberOfServoMotorThree (uint8_t)3
#define NumberOfServoMotorFour (uint8_t)4
#define NumberOfServoMotorFive (uint8_t)5
#define NumberOfServoMotorSix (uint8_t)6

// Declaring Some Difinations For Handling The Operation Of The SelectedServoMotor From User
#define None_OPERATION (uint8_t)0
#define Homing_OPERATION (uint8_t)1
#define Increasing_OPERATION (uint8_t)2
#define Decreasing_OPERATION (uint8_t)3
#define HomingAll_OPERATION (uint8_t)4

// Declaring Some Difinations For Handling Incoming Command From The User
#define None_COMMAND ""
#define Homing_COMMAND "Homing"
#define Increasing_COMMAND "Increasing"
#define Decreasing_COMMAND "Decreasing"
#define HomingAll_COMMAND "HomingAll"
#define SelectingServoMotorOne_COMMAND "ServoMotorOne"
#define SelectingServoMotorTwo_COMMAND "ServoMotorTwo"
#define SelectingServoMotorThree_COMMAND "ServoMotorThree"
#define SelectingServoMotorFour_COMMAND "ServoMotorFour"
#define SelectingServoMotorFive_COMMAND "ServoMotorFive"
#define SelectingServoMotorSix_COMMAND "ServooMotorSix"

// Declaring Servo Objects For Using Servo Motors
Servo ServoMotorOne;
Servo ServoMotorTwo;
Servo ServoMotorThree;
Servo ServoMotorFour;
Servo ServoMotorFive;
Servo ServoMotorSix;

// This Function Will Move The Servo Motor To Its Start Position
void HomeAllServoMotors(void);

// This Function Will Move The Servo Motor To Its Start Position
void HomeServoMotor(Servo, const char *, const char *, int);

// This Function Will Increase Angle Of A Servo Motor According To Given Parameters
void IncreaseAngleServoMotor(Servo, int, int, unsigned long int);

// This Function Will Decrease Angle Of A Servo Motor According To Given Parameters
void DecreaseAngleServoMotor(Servo, int, int, unsigned long int);

// Declaring A Variable For Managing Current Selected Servo Motor By User
uint8_t SelectedServoMotor = (uint8_t)NumberOfNoneServoMotor;

// Declaring A Variable For Managing Current Operation Of Selected Servo Motor
uint8_t OperationOfSelectedServoMotor = (uint8_t)None_OPERATION;

// Declaring A Variable For Storing Number Of Angles That Move In Each Time Of Movement
uint8_t ServoMotorMovementAngle = (uint8_t)1;

// Declaring A Variable For Storing The Delay That Are Happening In Movement Between Each Angle
uint8_t ServoMotorMovementDelay = (uint8_t)50;

// Declaring A Temperature Array Of Characters For Handling The Text That Will Print On The Display
char TemperatureArray[18] = "                 ";

// Declaring A Temperature Variable For Storing The Current Angle Of Each Servo Motor In Its Own Operation
int TemperatureAngle = (int)0;

// Declaring A String For Handling Incoming Data That Come From Serial Port
String IncommingData = String();

void setup(void) {
  // Configuring SerialPort
  Serial1.setTX(SerialPortTX_PIN);
  Serial1.setRX(SerialPortRX_PIN);
  Serial1.setFIFOSize(SerialPortBuffer_SIZE);
  Serial1.begin(SerialPortBaudrate_VALUE);

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
  // Check The Input Buffer Until A Data Recived
  if (Serial1.available()) {
    // Waiting For Compeleting Reciving Operation
    delayMicroseconds((unsigned long int)1000);

    // Reading A String From The Input Buffer
    IncommingData = String(Serial1.readString());

    // Handling The Incoming Data For Doing Its Operation
    // Handling If The Incoming Data Is (None_COMMAND)
    if ((IncommingData.c_str() == (String(None_COMMAND).c_str()))) {
      SelectedServoMotor = NumberOfNoneServoMotor;
      OperationOfSelectedServoMotor = None_OPERATION;
    }
    // Handling If The Incoming Data Is (Homing_COMMAND)
    else if ((IncommingData.c_str() == (String(Homing_COMMAND).c_str()))) {
      if (SelectedServoMotor != NumberOfNoneServoMotor) {
        OperationOfSelectedServoMotor = Homing_OPERATION;
      } else {
        OperationOfSelectedServoMotor = None_OPERATION;
        Serial1.println("Error : Please First Select A Servo Motor And Then Send Your Operation");
        if (Serial1.availableForWrite()) {
          Serial1.flush();
        }
      }
    }
    // Handling If The Incoming Data Is (Increasing_COMMAND)
    else if ((IncommingData.c_str() == (String(Increasing_COMMAND).c_str()))) {
      if (SelectedServoMotor != NumberOfNoneServoMotor) {
        OperationOfSelectedServoMotor = Increasing_OPERATION;
      } else {
        OperationOfSelectedServoMotor = None_OPERATION;
        Serial1.println("Error : Please First Select A Servo Motor And Then Send Your Operation");
        if (Serial1.availableForWrite()) {
          Serial1.flush();
        }
      }
    }
    // Handling If The Incoming Data Is (Decreasing_COMMAND)
    else if ((IncommingData.c_str() == (String(Decreasing_COMMAND).c_str()))) {
      if (SelectedServoMotor != NumberOfNoneServoMotor) {
        OperationOfSelectedServoMotor = Decreasing_OPERATION;
      } else {
        OperationOfSelectedServoMotor = None_OPERATION;
        Serial1.println("Error : Please First Select A Servo Motor And Then Send Your Operation");
        if (Serial1.availableForWrite()) {
          Serial1.flush();
        }
      }
    }
    // Handling If The Incoming Data Is (HomingAll_COMMAND)
    else if ((IncommingData.c_str() == (String(HomingAll_COMMAND).c_str()))) {
      OperationOfSelectedServoMotor = HomingAll_OPERATION;
    }
    // Handling If The Incoming Data Is (SelectingServoMotorOne_COMMAND)
    else if ((IncommingData.c_str() == (String(SelectingServoMotorOne_COMMAND).c_str()))) {
      SelectedServoMotor = NumberOfServoMotorOne;
    }
    // Handling If The Incoming Data Is (SelectingServoMotorTwo_COMMAND)
    else if ((IncommingData.c_str() == (String(SelectingServoMotorTwo_COMMAND).c_str()))) {
      SelectedServoMotor = NumberOfServoMotorTwo;
    }
    // Handling If The Incoming Data Is (SelectingServoMotorThree_COMMAND)
    else if ((IncommingData.c_str() == (String(SelectingServoMotorThree_COMMAND).c_str()))) {
      SelectedServoMotor = NumberOfServoMotorThree;
    }
    // Handling If The Incoming Data Is (SelectingServoMotorFour_COMMAND)
    else if ((IncommingData.c_str() == (String(SelectingServoMotorFour_COMMAND).c_str()))) {
      SelectedServoMotor = NumberOfServoMotorFour;
    }
    // Handling If The Incoming Data Is (SelectingServoMotorFive_COMMAND)
    else if ((IncommingData.c_str() == (String(SelectingServoMotorFive_COMMAND).c_str()))) {
      SelectedServoMotor = NumberOfServoMotorFive;
    }
    // Handling If The Incoming Data Is (SelectingServoMotorSix_COMMAND)
    else if ((IncommingData.c_str() == (String(SelectingServoMotorSix_COMMAND).c_str()))) {
    }
    // Handling If The Incoming Data Is Not Valid Command
    else {
      // Sending And Error Message For Invalid Command And Guide of Valid Messages On The Serial Port
      Serial1.println("Error : Please Enter A Valid Command.");
      if (Serial1.availableForWrite()) {
        Serial1.flush();
      }
      Serial1.println("Valid Command Are : ");
      if (Serial1.availableForWrite()) {
        Serial1.flush();
      }
      Serial1.println("Homming : Set Selected ServoMotor To Its Home Position.");
      if (Serial1.availableForWrite()) {
        Serial1.flush();
      }
      Serial1.println("Increasing : Increasing Angle Of Selected ServoMotor.");
      if (Serial1.availableForWrite()) {
        Serial1.flush();
      }
      Serial1.println("Decreasing : Decreasing Angle Of Selected ServoMotor.");
      if (Serial1.availableForWrite()) {
        Serial1.flush();
      }
      Serial1.println("HommingAll : Set All ServoMotors To Their Home Position.");
      if (Serial1.availableForWrite()) {
        Serial1.flush();
      }
      Serial1.println("ServoMotorOne : Select ServoMotorOne.");
      if (Serial1.availableForWrite()) {
        Serial1.flush();
      }
      Serial1.println("ServoMotorTwo : Select ServoMotorTwo.");
      if (Serial1.availableForWrite()) {
        Serial1.flush();
      }
      Serial1.println("ServoMotorThree : Select ServoMotorThree.");
      if (Serial1.availableForWrite()) {
        Serial1.flush();
      }
      Serial1.println("ServoMotorFour : Select ServoMotorFour.");
      if (Serial1.availableForWrite()) {
        Serial1.flush();
      }
      Serial1.println("ServoMotorFive : Select ServoMotorFive.");
      if (Serial1.availableForWrite()) {
        Serial1.flush();
      }
      Serial1.println("ServoMotorSix : Select ServoMotorSix.");
      if (Serial1.availableForWrite()) {
        Serial1.flush();
      }
    }
    // Handling Operations For All ServoMotors
    switch (SelectedServoMotor) {
      // Handling If There Is Not Any Selected ServoMotors
      case (NumberOfNoneServoMotor):
        {
          break;
        }
      // Handling If ServoMotorOne Is Selected
      case (NumberOfServoMotorOne):
        {
          // Hadling Operation For The Selected Servo Motor
          switch (OperationOfSelectedServoMotor) {
            // Handling If There Is Not Any Operation
            case (None_OPERATION):
              {
                break;
              }
            // Handling If HomingOperation Was Called
            case (Homing_OPERATION):
              {
                HomeServoMotor(ServoMotorOne, ServoMotorOne_START);
                TemperatureAngle = ServoMotorOne.read();
                sprintf(TemperatureArray, "%03d <= %03d <= %03d", ServoMotorOne_MINIMUM, TemperatureAngle, ServoMotorOne_MAXIMUM);
                Serial1.println("ServoMotorOne");
                if (Serial1.availableForWrite()) {
                  Serial1.flush();
                }
                Serial1.println(TemperatureArray);
                if (Serial1.availableForWrite()) {
                  Serial1.flush();
                }
                break;
              }
            // Handling If IncreasingOperation Was Called
            case (Increasing_OPERATION):
              {
                IncreaseAngleServoMotor(ServoMotorOne, ServoMotorMovementAngle, ServoMotorOne_MAXIMUM, ServoMotorMovementDelay);
                TemperatureAngle = ServoMotorOne.read();
                sprintf(TemperatureArray, "%03d <= %03d <= %03d", ServoMotorOne_MINIMUM, TemperatureAngle, ServoMotorOne_MAXIMUM);
                Serial1.println("ServoMotorOne");
                if (Serial1.availableForWrite()) {
                  Serial1.flush();
                }
                Serial1.println(TemperatureArray);
                if (Serial1.availableForWrite()) {
                  Serial1.flush();
                }
                break;
              }
            // Handling If DecreasingOperation Was Called
            case (Decreasing_OPERATION):
              {
                DecreaseAngleServoMotor(ServoMotorOne, ServoMotorMovementAngle, ServoMotorOne_MINIMUM, ServoMotorMovementDelay);
                TemperatureAngle = ServoMotorOne.read();
                sprintf(TemperatureArray, "%03d <= %03d <= %03d", ServoMotorOne_MINIMUM, TemperatureAngle, ServoMotorOne_MAXIMUM);
                Serial1.println("ServoMotorOne");
                if (Serial1.availableForWrite()) {
                  Serial1.flush();
                }
                Serial1.println(TemperatureArray);
                if (Serial1.availableForWrite()) {
                  Serial1.flush();
                }
                break;
              }
          }
          break;
        }
        // Handling If ServoMotorTwo Is Selected
      case (NumberOfServoMotorTwo):
        {
          // Handling Operation For The Selected Servo Motor
          switch (OperationOfSelectedServoMotor) {
            // Handling If There Is Not Any Operation
            case (None_OPERATION):
              {
                break;
              }
            // Handling If HomingOperation Was Called
            case (Homing_OPERATION):
              {
                HomeServoMotor(ServoMotorTwo, ServoMotorTwo_START);
                TemperatureAngle = ServoMotorTwo.read();
                sprintf(TemperatureArray, "%03d <= %03d <= %03d", ServoMotorTwo_MINIMUM, TemperatureAngle, ServoMotorTwo_MAXIMUM);
                Serial1.println("ServoMotorTwo");
                if (Serial1.availableForWrite()) {
                  Serial1.flush();
                }
                Serial1.println(TemperatureArray);
                if (Serial1.availableForWrite()) {
                  Serial1.flush();
                }
                break;
              }
            // Handling If IncreasingOperation Was Called
            case (Increasing_OPERATION):
              {
                IncreaseAngleServoMotor(ServoMotorTwo, ServoMotorMovementAngle, ServoMotorTwo_MAXIMUM, ServoMotorMovementDelay);
                TemperatureAngle = ServoMotorTwo.read();
                sprintf(TemperatureArray, "%03d <= %03d <= %03d", ServoMotorTwo_MINIMUM, TemperatureAngle, ServoMotorTwo_MAXIMUM);
                Serial1.println("ServoMotorTwo");
                if (Serial1.availableForWrite()) {
                  Serial1.flush();
                }
                Serial1.println(TemperatureArray);
                if (Serial1.availableForWrite()) {
                  Serial1.flush();
                }
                break;
              }
            // Handling If DecreasingOperation Was Called
            case (Decreasing_OPERATION):
              {
                DecreaseAngleServoMotor(ServoMotorTwo, ServoMotorMovementAngle, ServoMotorTwo_MINIMUM, ServoMotorMovementDelay);
                TemperatureAngle = ServoMotorTwo.read();
                sprintf(TemperatureArray, "%03d <= %03d <= %03d", ServoMotorTwo_MINIMUM, TemperatureAngle, ServoMotorTwo_MAXIMUM);
                Serial1.println("ServoMotorTwo");
                if (Serial1.availableForWrite()) {
                  Serial1.flush();
                }
                Serial1.println(TemperatureArray);
                if (Serial1.availableForWrite()) {
                  Serial1.flush();
                }
                break;
              }
          }
          break;
        }
        // Handling If ServoMotorThree Is Selected
      case (NumberOfServoMotorThree):
        {
          // Handling Operation For The Selected Servo Motor
          switch (OperationOfSelectedServoMotor) {
            // Handling If There Is Not Any Operation
            case (None_OPERATION):
              {
                break;
              }
            // Handling If HomingOperation Was Called
            case (Homing_OPERATION):
              {
                HomeServoMotor(ServoMotorThree, ServoMotorThree_START);
                TemperatureAngle = ServoMotorThree.read();
                sprintf(TemperatureArray, "%03d <= %03d <= %03d", ServoMotorThree_MINIMUM, TemperatureAngle, ServoMotorThree_MAXIMUM);
                Serial1.println("ServoMotorThree");
                if (Serial1.availableForWrite()) {
                  Serial1.flush();
                }
                Serial1.println(TemperatureArray);
                if (Serial1.availableForWrite()) {
                  Serial1.flush();
                }
                break;
              }
            // Handling If IncreasingOperation Was Called
            case (Increasing_OPERATION):
              {
                IncreaseAngleServoMotor(ServoMotorThree, ServoMotorMovementAngle, ServoMotorThree_MAXIMUM, ServoMotorMovementDelay);
                TemperatureAngle = ServoMotorThree.read();
                sprintf(TemperatureArray, "%03d <= %03d <= %03d", ServoMotorThree_MINIMUM, TemperatureAngle, ServoMotorThree_MAXIMUM);
                Serial1.println("ServoMotorThree");
                if (Serial1.availableForWrite()) {
                  Serial1.flush();
                }
                Serial1.println(TemperatureArray);
                if (Serial1.availableForWrite()) {
                  Serial1.flush();
                }
                break;
              }
            // Handling If DecreasingOperation Was Called
            case (Decreasing_OPERATION):
              {
                DecreaseAngleServoMotor(ServoMotorThree, ServoMotorMovementAngle, ServoMotorThree_MINIMUM, ServoMotorMovementDelay);
                TemperatureAngle = ServoMotorThree.read();
                sprintf(TemperatureArray, "%03d <= %03d <= %03d", ServoMotorThree_MINIMUM, TemperatureAngle, ServoMotorThree_MAXIMUM);
                Serial1.println("ServoMotorThree");
                if (Serial1.availableForWrite()) {
                  Serial1.flush();
                }
                Serial1.println(TemperatureArray);
                if (Serial1.availableForWrite()) {
                  Serial1.flush();
                }
                break;
              }
          }
          break;
        }
        // Handling If ServoMotorFour Is Selected
      case (NumberOfServoMotorFour):
        {
          // Handling Operation For The Selected Servo Motor
          switch (OperationOfSelectedServoMotor) {
            // Handling If There Is Not Any Operation
            case (None_OPERATION):
              {
                break;
              }
            // Handling If HomingOperation Was Called
            case (Homing_OPERATION):
              {
                HomeServoMotor(ServoMotorFour, ServoMotorFour_START);
                TemperatureAngle = ServoMotorFour.read();
                sprintf(TemperatureArray, "%03d <= %03d <= %03d", ServoMotorFour_MINIMUM, TemperatureAngle, ServoMotorFour_MAXIMUM);
                Serial1.println("ServoMotorFour");
                if (Serial1.availableForWrite()) {
                  Serial1.flush();
                }
                Serial1.println(TemperatureArray);
                if (Serial1.availableForWrite()) {
                  Serial1.flush();
                }
                break;
              }
            // Handling If IncreasingOperation Was Called
            case (Increasing_OPERATION):
              {
                IncreaseAngleServoMotor(ServoMotorFour, ServoMotorMovementAngle, ServoMotorFour_MAXIMUM, ServoMotorMovementDelay);
                TemperatureAngle = ServoMotorFour.read();
                sprintf(TemperatureArray, "%03d <= %03d <= %03d", ServoMotorFour_MINIMUM, TemperatureAngle, ServoMotorFour_MAXIMUM);
                Serial1.println("ServoMotorFour");
                if (Serial1.availableForWrite()) {
                  Serial1.flush();
                }
                Serial1.println(TemperatureArray);
                if (Serial1.availableForWrite()) {
                  Serial1.flush();
                }
                break;
              }
            // Handling If DecreasingOperation Was Called
            case (Decreasing_OPERATION):
              {
                DecreaseAngleServoMotor(ServoMotorFour, ServoMotorMovementAngle, ServoMotorFour_MINIMUM, ServoMotorMovementDelay);
                TemperatureAngle = ServoMotorFour.read();
                sprintf(TemperatureArray, "%03d <= %03d <= %03d", ServoMotorFour_MINIMUM, TemperatureAngle, ServoMotorFour_MAXIMUM);
                Serial1.println("ServoMotorFour");
                if (Serial1.availableForWrite()) {
                  Serial1.flush();
                }
                Serial1.println(TemperatureArray);
                if (Serial1.availableForWrite()) {
                  Serial1.flush();
                }
                break;
              }
          }
          break;
        }
        // Handling If ServoMotorFive Is Selected
      case (NumberOfServoMotorFive):
        {
          // Handling Operation For The Selected Servo Motor
          switch (OperationOfSelectedServoMotor) {
            // Handling If There Is Not Any Operation
            case (None_OPERATION):
              {
                break;
              }
            // Handling If HomingOperation Was Called
            case (Homing_OPERATION):
              {
                HomeServoMotor(ServoMotorFive, ServoMotorFive_START);
                TemperatureAngle = ServoMotorFive.read();
                sprintf(TemperatureArray, "%03d <= %03d <= %03d", ServoMotorFive_MINIMUM, TemperatureAngle, ServoMotorFive_MAXIMUM);
                Serial1.println("ServoMotorFive");
                if (Serial1.availableForWrite()) {
                  Serial1.flush();
                }
                Serial1.println(TemperatureArray);
                if (Serial1.availableForWrite()) {
                  Serial1.flush();
                }
                break;
              }
            // Handling If IncreasingOperation Was Called
            case (Increasing_OPERATION):
              {
                IncreaseAngleServoMotor(ServoMotorFive, ServoMotorMovementAngle, ServoMotorFive_MAXIMUM, ServoMotorMovementDelay);
                TemperatureAngle = ServoMotorFive.read();
                sprintf(TemperatureArray, "%03d <= %03d <= %03d", ServoMotorFive_MINIMUM, TemperatureAngle, ServoMotorFive_MAXIMUM);
                Serial1.println("ServoMotorFive");
                if (Serial1.availableForWrite()) {
                  Serial1.flush();
                }
                Serial1.println(TemperatureArray);
                if (Serial1.availableForWrite()) {
                  Serial1.flush();
                }
                break;
              }
            // Handling If DecreasingOperation Was Called
            case (Decreasing_OPERATION):
              {
                DecreaseAngleServoMotor(ServoMotorFive, ServoMotorMovementAngle, ServoMotorFive_MINIMUM, ServoMotorMovementDelay);
                TemperatureAngle = ServoMotorFive.read();
                sprintf(TemperatureArray, "%03d <= %03d <= %03d", ServoMotorFive_MINIMUM, TemperatureAngle, ServoMotorFive_MAXIMUM);
                Serial1.println("ServoMotorFive");
                if (Serial1.availableForWrite()) {
                  Serial1.flush();
                }
                Serial1.println(TemperatureArray);
                if (Serial1.availableForWrite()) {
                  Serial1.flush();
                }
                break;
              }
          }
          break;
        }
        // Handling If ServoMotorSix Is Selected
      case (NumberOfServoMotorSix):
        {
          // Handling Operation For The Selected Servo Motor
          switch (OperationOfSelectedServoMotor) {
            // Handling If There Is Not Any Operation
            case (None_OPERATION):
              {
                break;
              }
            // Handling If HomingOperation Was Called
            case (Homing_OPERATION):
              {
                HomeServoMotor(ServoMotorSix, ServoMotorSix_START);
                TemperatureAngle = ServoMotorSix.read();
                sprintf(TemperatureArray, "%03d <= %03d <= %03d", ServoMotorSix_MINIMUM, TemperatureAngle, ServoMotorSix_MAXIMUM);
                Serial1.println("ServoMotorSix");
                if (Serial1.availableForWrite()) {
                  Serial1.flush();
                }
                Serial1.println(TemperatureArray);
                if (Serial1.availableForWrite()) {
                  Serial1.flush();
                }
                break;
              }
            // Handling If IncreasingOperation Was Called
            case (Increasing_OPERATION):
              {
                IncreaseAngleServoMotor(ServoMotorSix, ServoMotorMovementAngle, ServoMotorSix_MAXIMUM, ServoMotorMovementDelay);
                TemperatureAngle = ServoMotorSix.read();
                sprintf(TemperatureArray, "%03d <= %03d <= %03d", ServoMotorSix_MINIMUM, TemperatureAngle, ServoMotorSix_MAXIMUM);
                Serial1.println("ServoMotorSix");
                if (Serial1.availableForWrite()) {
                  Serial1.flush();
                }
                Serial1.println(TemperatureArray);
                if (Serial1.availableForWrite()) {
                  Serial1.flush();
                }
                break;
              }
            // Handling If DecreasingOperation Was Called
            case (Decreasing_OPERATION):
              {
                DecreaseAngleServoMotor(ServoMotorSix, ServoMotorMovementAngle, ServoMotorSix_MINIMUM, ServoMotorMovementDelay);
                TemperatureAngle = ServoMotorSix.read();
                sprintf(TemperatureArray, "%03d <= %03d <= %03d", ServoMotorSix_MINIMUM, TemperatureAngle, ServoMotorSix_MAXIMUM);
                Serial1.println("ServoMotorSix");
                if (Serial1.availableForWrite()) {
                  Serial1.flush();
                }
                Serial1.println(TemperatureArray);
                if (Serial1.availableForWrite()) {
                  Serial1.flush();
                }
                break;
              }
          }
          break;
        }
    }
    // Handling If The Operation Is Homing All ServoMotors
    if ((OperationOfSelectedServoMotor == HomingAll_OPERATION)) {
      HomeAllServoMotors();
    }
    // Reseting The Operation Of The Selected ServoMotor
    OperationOfSelectedServoMotor = None_OPERATION;
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

// This Function Will Increase Angle Of A Servo Motor According To Given Parameters
void IncreaseAngleServoMotor(Servo ServoMotor, int StepOfAngle, int MaximumAngle, unsigned long int TimeBetweenAngle) {
  int TheAngle = (int)0;
  TheAngle = ServoMotor.read();
  if (TheAngle <= MaximumAngle) {
    TheAngle += StepOfAngle;
    ServoMotor.write(TheAngle);
  } else {
    TheAngle = MaximumAngle;
    ServoMotor.write(TheAngle);
  }

  // Waiting Between Each Angle Movement
  delay(TimeBetweenAngle);
}

// This Function Will Decrease Angle Of A Servo Motor According To Given Parameters
void DecreaseAngleServoMotor(Servo ServoMotor, int StepOfAngle, int MinimumAngle, unsigned long int TimeBetweenAngle) {
  int TheAngle = (int)0;
  TheAngle = ServoMotor.read();
  if (TheAngle >= MinimumAngle) {
    TheAngle -= StepOfAngle;
    ServoMotor.write(TheAngle);
  } else {
    TheAngle = MinimumAngle;
    ServoMotor.write(TheAngle);
  }

  // Waiting Between Each Angle Movement
  delay(TimeBetweenAngle);
}