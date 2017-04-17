//left
const int trigPin = 4;
const int echoPin = 2;
//front
const int trigPin1 = 5;
const int echoPin1 = 3;

void setup()
{
  Serial.begin(9600);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);

  
}

void loop()
{
  long durationLeft, inches, cm;
  //left
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
   //front
  pinMode(trigPin1, OUTPUT);
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  pinMode(echoPin, INPUT);
  durationLeft = pulseIn(echoPin, HIGH);

  inches = microsecondsToInches(durationLeft);
  cm = microsecondsToCentimeters(durationLeft);

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  if(durationLeft < 300)
  {
    //LEFT
      digitalWrite(8, LOW);
      digitalWrite(7, HIGH);
      digitalWrite(9, 50 );  

      //RIGHT
      digitalWrite(12, LOW);
      digitalWrite(13, HIGH);
      digitalWrite(11, 0);
  }
  else
  {
    if(durationLeft < 650)
   {
    //LEFT
      digitalWrite(8, LOW);
      digitalWrite(7, HIGH);
      digitalWrite(9, 200 );  

      //RIGHT
      digitalWrite(12, LOW);
      digitalWrite(13, HIGH);
      digitalWrite(11, 60);
   }
   else if(durationLeft >= 650)
   {
      //LEFT Wheel
      digitalWrite(8, LOW);
      digitalWrite(7, LOW);
      digitalWrite(9, 90);

      //RIGHT Wheel
      digitalWrite(12, LOW);
      digitalWrite(13, HIGH);
      digitalWrite(11, 60);

   }
  }
   delay(100);
}

long microsecondsToInches(long microseconds) 
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) 
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

