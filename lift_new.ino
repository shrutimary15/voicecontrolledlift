
/*#define ONETOTWO 200
#define ONETOTHREE 400
#define ONETOFOUR 600

#define TWOTOONE 200
#define TWOTOTHREE 200
#define TWOTOFOUR 400

#define THREETOONE 600
#define THREETOTWO 200
#define THREETOFOUR 200

#define FOURTOONE 600
#define FOURTOTWO 400
#define FOURTOTHREE 200
*/

#define floor1 2
#define floor2 3
#define floor3 4
#define floor4 5 

#define trigPin 6
#define echoPin 7

#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <Stepper.h>

SoftwareSerial mySerial(10, 11); // RX, TX
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
 
const int stepsPerRevolution = 200;
Stepper myStepper(stepsPerRevolution, 8, 9, 12, 13);
byte com = 0; 
int flag1 = 0;
int flag2 = 0;
int flag3 = 0;
int flag4 = 0;

int counter=0;
int rotation=0;
int dir=0;


void setup() {

  Serial.begin(9600);
  mySerial.begin(9600);
  lcd.begin(16, 2);
  lcd.print(">> VOICE LIFT <<");
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(floor1, INPUT_PULLUP);
  pinMode(floor2, INPUT_PULLUP);
  pinMode(floor3, INPUT_PULLUP);
  pinMode(floor4, INPUT_PULLUP);
  delay(2000); 
  mySerial.write(0xAA); 
  delay(100);
  mySerial.write(0x37); 
  delay(1000); 
  mySerial.write(0xAA); 
  delay(100);
  mySerial.write(0x21); 
}

void loop() {

  int duration, distance;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  Serial.println(distance);
  delay(1000);

  while(mySerial.available()) 
    { 
    com = mySerial.read(); 
    Serial.write(com);
    switch(com) 
    { 
      case 0x11: 
      flag1=1;
      flag2=0;
      flag3=0;
      flag4=0;
      Serial.print("vf-g");
      break; 
      
      case 0x12:
      flag1=0;
      flag2=1;
      flag3=0;
      flag4=0; 
      Serial.print("vf-1");
      break;
      
      case 0x13: 
      flag1=0;
      flag2=0;
      flag3=1;
      flag4=0;
      Serial.print("vf-2");
      break; 
      
      case 0x14:
      flag1=0;
      flag2=0;
      flag3=0;
      flag4=1;
      Serial.print("vf-3");
      break;
      }
      }

  if (digitalRead(floor1) == LOW) ////1st_floor
  { Serial.println("b1"); 
   flag1=1;
   flag2=0;
   flag3=0;
   flag4=0;}
  if (digitalRead(floor2) == LOW) ////2nd_floor
   {
    Serial.println("b2");
   flag1=0;
   flag2=1;
   flag3=0;
   flag4=0;}
  if (digitalRead(floor3) == LOW) ////3rd_floor
   {Serial.println("b3");
   flag1=0;
   flag2=0;
   flag3=1;
   flag4=0;
   }
  if (digitalRead(floor4) == LOW) ////4th_floor
   {Serial.println("b4");
   flag1=0;
   flag2=0;
   flag3=0;
   flag4=1;
   }
  
  
  if ( flag1==1)  ///// goto _floor_GND
  {
    if (distance >= 2 && distance <= 5) 
    {
      rotation=600;
      dir=1;
      Serial.println("f4-1");
      lcd.setCursor(0, 1);
      lcd.print("FLOOR 3>>GROUND  ");
      floorgo();
      }
    else if (distance >= 10 && distance <= 12)
      {
      rotation=400;
      dir=1;
      Serial.println("f3-1");
      lcd.setCursor(0, 1);
      lcd.print("FLOOR 2>>GROUND  ");
      floorgo();
      }
    else if (distance >= 20 && distance <= 23)
      {
      rotation=200;
      dir=1;
      Serial.println("f2-1");
      lcd.setCursor(0, 1);
      lcd.print("FLOOR 1>>GROUND   ");
      floorgo();
      }
    }

  
  if ( flag2==1)       ///// goto _floor1
  {
    if (distance >= 2 && distance <= 5) 
    {
      rotation=400;
      dir=1;
      Serial.println("f4-2");
      lcd.setCursor(0, 1);
      lcd.print("FLOOR 3>>1          ");
      floorgo();
      }
   else if (distance >= 10 && distance <= 12)
    {
      rotation=200;
      dir=1;
      Serial.println("f3-2");
      lcd.setCursor(0, 1);
      lcd.print("FLOOR 2>>1         ");
      floorgo();
      }

    else if (distance >= 24 && distance <= 27)
    {
      rotation=200;
      dir=-1;
      Serial.println("f1-2");
      lcd.setCursor(0, 1);
      lcd.print("FLOOR GROUND>>1        ");
      floorgo();
      }
  }



    if (flag3==1)  ///// goto _floor2
  {
    if (distance >= 2 && distance <= 5)
    {
      rotation=200;
      dir=1;
      Serial.println("f4-3");
      lcd.setCursor(0, 1);
      lcd.print("FLOOR 3>>2        ");
      floorgo();
      }

    else if (distance >= 20 && distance <= 23)
    {
      rotation=200;
      dir=-1;
      Serial.println("f2-3");
      lcd.setCursor(0, 1);
      lcd.print("FLOOR 1>>2        ");
      floorgo();
      }
    else if (distance >= 24 && distance <= 27)
    {
      rotation=420;
      dir=-1;
      Serial.println("f1-3");
      lcd.setCursor(0, 1);
      lcd.print("FLOOR GROUND>>2       ");
      floorgo();
      }
  }


  if (flag4==1)  ///// goto _floor3
  {

    if (distance >= 10 && distance <= 12)
    {
      rotation=200;
      dir=-1;
      Serial.println("f3-4");
      lcd.setCursor(0, 1);
      lcd.print("FLOOR 2>>3         ");
      floorgo();
      }
    else if (distance >= 20 && distance <= 23)
    {
      rotation=400;
      dir=-1;
      Serial.println("f2-4");
      lcd.setCursor(0, 1);
      lcd.print("FLOOR 1>>3         ");
      floorgo();
      }
    else if (distance >= 24 && distance <= 27)
    {
      rotation=600;
      dir=-1;
      Serial.println("f1-4");
      lcd.setCursor(0, 1);
      lcd.print("FLOOR GROUND>>3          ");
      floorgo();
      }
  }

}



void floorgo()
{
    while (counter < rotation)
    {
       myStepper.step(dir);
       counter++;
       Serial.println("floorgo");
    }
      lcd.setCursor(0, 1);
      lcd.print(">>>>>>>><<<<<<<<");
      counter=0;
      rotation=0;
      dir=0;
      flag1=0;
      flag2=0;
      flag3=0;
      flag4=0;
      com=0;
}

