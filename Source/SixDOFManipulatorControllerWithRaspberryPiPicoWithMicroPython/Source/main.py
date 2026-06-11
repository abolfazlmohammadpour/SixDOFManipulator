import machine
import time


BuiltInLEDPin = 25
BuiltInLED = machine.Pin(BuiltInLEDPin, machine.Pin.OUT, machine.Pin.PULL_DOWN)

BoardLEDBluePin = 20
BoardLEDBlue = machine.Pin(BoardLEDBluePin, machine.Pin.OUT, machine.Pin.PULL_DOWN)

BoardLEDGreenPin = 21
BoardLEDGreen = machine.Pin(BoardLEDGreenPin, machine.Pin.OUT, machine.Pin.PULL_DOWN)

BoardLEDRedPin = 22
BoardLEDRed = machine.Pin(BoardLEDRedPin, machine.Pin.OUT, machine.Pin.PULL_DOWN)


FirstServoMotorPin = machine.Pin(0)
SecondServoMotorPin = machine.Pin(1)
ThirdServoMotorPin = machine.Pin(2)
FourthServoMotorPin = machine.Pin(3)
FifthServoMotorPin = machine.Pin(4)
SixthServoMotorPin = machine.Pin(5)

def TheDegreeToPWM(TheDegree: int) -> int:
    return int((((TheDegree / 180) * (8192 - 1638)) + 1638))

FirstServoMotor = machine.PWM(FirstServoMotorPin, freq=50, duty_u16=TheDegreeToPWM(90))
SecondServoMotor = machine.PWM(SecondServoMotorPin, freq=50, duty_u16=TheDegreeToPWM(90))
ThirdServoMotor = machine.PWM(ThirdServoMotorPin, freq=50, duty_u16=TheDegreeToPWM(90))
FourthServoMotor = machine.PWM(FourthServoMotorPin, freq=50, duty_u16=TheDegreeToPWM(90))
FifthServoMotor = machine.PWM(FifthServoMotorPin, freq=50, duty_u16=TheDegreeToPWM(90))
SixthServoMotor = machine.PWM(SixthServoMotorPin, freq=50, duty_u16=TheDegreeToPWM(90))


def LEDBlinkingTest() -> None:
    BuiltInLED.on()
    BoardLEDBlue.on()
    BoardLEDGreen.on()
    BoardLEDRed.on()
    time.sleep(0.350)
    
    BuiltInLED.off()
    BoardLEDBlue.off()
    BoardLEDGreen.off()
    BoardLEDRed.off()
    time.sleep(0.350)
    
    BuiltInLED.on()
    BoardLEDBlue.on()
    BoardLEDGreen.off()
    BoardLEDRed.on()
    time.sleep(0.350)
    
    BuiltInLED.off()
    BoardLEDBlue.off()
    BoardLEDGreen.on()
    BoardLEDRed.off()
    time.sleep(0.350)
    
    BuiltInLED.on()
    BoardLEDBlue.on()
    BoardLEDGreen.off()
    BoardLEDRed.off()
    time.sleep(0.350)
    
    BuiltInLED.off()
    BoardLEDBlue.off()
    BoardLEDGreen.on()
    BoardLEDRed.on()
    time.sleep(0.350)
    
    BuiltInLED.on()
    BoardLEDBlue.on()
    BoardLEDGreen.on()
    BoardLEDRed.off()
    time.sleep(0.350)
    
    BuiltInLED.off()
    BoardLEDBlue.off()
    BoardLEDGreen.off()
    BoardLEDRed.on()
    time.sleep(0.350)
 
 
def ServoMotorMotionTest() -> None:
    FirstServoMotor.duty_u16(TheDegreeToPWM(90))
    SecondServoMotor.duty_u16(TheDegreeToPWM(90))
    ThirdServoMotor.duty_u16(TheDegreeToPWM(90))
    FourthServoMotor.duty_u16(TheDegreeToPWM(90))
    FifthServoMotor.duty_u16(TheDegreeToPWM(90))
    SixthServoMotor.duty_u16(TheDegreeToPWM(90))
    time.sleep(5)
    
    FirstServoMotor.duty_u16(TheDegreeToPWM(0))
    SecondServoMotor.duty_u16(TheDegreeToPWM(90))
    ThirdServoMotor.duty_u16(TheDegreeToPWM(0))
    FourthServoMotor.duty_u16(TheDegreeToPWM(0))
    FifthServoMotor.duty_u16(TheDegreeToPWM(0))
    SixthServoMotor.duty_u16(TheDegreeToPWM(0))
    time.sleep(5)
    
    FirstServoMotor.duty_u16(TheDegreeToPWM(180))
    SecondServoMotor.duty_u16(TheDegreeToPWM(90))
    ThirdServoMotor.duty_u16(TheDegreeToPWM(180))
    FourthServoMotor.duty_u16(TheDegreeToPWM(180))
    FifthServoMotor.duty_u16(TheDegreeToPWM(180))
    SixthServoMotor.duty_u16(TheDegreeToPWM(180))
    time.sleep(5)
        


def main() -> None:   
    while True:
      LEDBlinkingTest()

        
if __name__ == "__main__":
    main()
