//Import Library
#include <NewPing.h>
#include <Servo.h> 
#include <LiquidCrystal_I2C.h>

//Define & SetUp Sensor Luar
#define trigg_pin 4
#define echo_pin 3
#define max_distance 350
NewPing sensorLuar(trigg_pin, echo_pin, max_distance);
float duration, distance;

//Define & SetUp Servo Motor
Servo servoSampah;

//Define & SetUp LCD
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,16,2);

//Define & SetUp Timer/Counter or Interrupt
#define INT0 2

void setup() 
{
  //Inisialisasi Servo
  servoSampah.attach(5);
  servoSampah.write(0);

  //Inisialisasi Interrupt
  pinMode(INT0, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), manual, RISING);
  
  //Inisialisasi LCD
  lcd.init();
  lcd.backlight();
}

void loop() 
{
  duration = sensorLuar.ping();
  distance = (duration / 2) * 0.0343;

  if(distance<=10)
  {
    servoSampah.write(180);
  }
  else
  {
    servoSampah.write(0);
  }
  delay(50);
}

void manual() 
{
  servoSampah.write(180);
  delay(10000);
  servoSampah.write(0);
}
