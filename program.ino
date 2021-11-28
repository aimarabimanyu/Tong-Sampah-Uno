//Import Library
#include <NewPing.h>
#include <ServoTimer2.h> 
#include <LiquidCrystal_I2C.h>

//Define or SetUp Sensor Luar
#define trigg_pin1 4
#define echo_pin1 3
#define max_distance 100
NewPing sensorLuar(trigg_pin1, echo_pin1, max_distance);
float durationS1, distanceS1;

//Define or SetUp Sensor Dalam
#define trigg_pin2 9
#define echo_pin2 8
NewPing sensorDalam(trigg_pin2, echo_pin2, max_distance);
float durationS2;
int distanceS2;

//Define or SetUp Servo Motor
ServoTimer2 servoSampah;

//Define or SetUp LCD
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,16,2);

//Define or SetUp Timer/Counter, Interrupt, & Delay
unsigned long prevTime = 0;
unsigned long currTime = 0;
void setup() 
{
  //Inisialisasi Servo
  servoSampah.attach(5);
  servoSampah.write(750);
  
  //Inisialisasi LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("TongSampah");
  lcd.setCursor(4, 1);
  lcd.print("Otomatis");
  delay(3000);
  lcd.clear();

  //Inisialisasi Timer1
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 49911;
  TCCR1B |= (1 << CS10)|(1 << CS12);
  TIMSK1 |= (1 << TOIE1);
  interrupts();

}

void loop() 
{
  unsigned long currTime = millis();
  // Deteksi Jarak Dari Kedua Sensor
  durationS1 = sensorLuar.ping();
  distanceS1 = (durationS1 / 2) * 0.0343;
  durationS2 = sensorDalam.ping();
  distanceS2 = (((((durationS2 / 2) * 0.0343)-10)/30)*100); //asumsi tinggi tong sampah 30 cm

  
  if (distanceS2 <= 10) //asumsi tinggi tong sampah 30 cm
  {
    lcd.setCursor(3, 0);
    lcd.print("Tong Sampah");
    lcd.setCursor(6, 1);
    lcd.print("Penuh");
    noInterrupts();
  }
  else if (distanceS2 > 10) 
  {
    lcd.setCursor(3, 0);
    lcd.print("Kapasitas:");
    lcd.setCursor(6, 1);
    lcd.print(distanceS2);
    lcd.print("%");
  }
}

ISR(TIMER1_OVF_vect)
{
  TCNT1 = 49911;

  // Jika Sensor Mendeteksi Orang Mendekati Tong Sampah dan Menjauhi Tong Sampah
  if(distanceS1<=20 && distanceS1>0)
  {
    prevTime = currTime;
    servoSampah.write(2250);
  }
  else if(distanceS1>20)
  {
    servoSampah.write(750);
  }
}
