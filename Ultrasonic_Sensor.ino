#define trigPin 8
#define echoPin 9


void setup()                    
{
 Serial.begin(9600);

pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);

}

void loop()
{ 

  int duration, distance;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance >= 30 || distance <= 0)
  {
  Serial.println("no object detected");
  digitalWrite(relay3, HIGH);
  }
  
  else {
     Serial.println("Obstacle_found!!");
  }
}
