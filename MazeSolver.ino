/*Maze solving robot using the left hand rule
  Written By: David Wang
              Dai Hong Zheng
              Ben Wong
*/

const int trigPinLeft = 3;
const int echoPinLeft = 2;

const int trigPinFront = 5;
const int echoPinFront = 4;

long durationLeft;
long durationFront;

void setup()
{

  Serial.begin(9600);

  //LEFT
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  //RIGHT
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);

  pinMode(echoPinLeft, INPUT);
  pinMode(echoPinFront, INPUT);

  pinMode(trigPinLeft, OUTPUT);
  pinMode(trigPinFront, OUTPUT);

}

void loop()
{
  digitalWrite(trigPinLeft, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinLeft, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinLeft, LOW);

  durationLeft = pulseIn(echoPinLeft, HIGH);

  digitalWrite(trigPinFront, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinFront, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinFront, LOW);


  durationFront = pulseIn(echoPinFront, HIGH);

  sensor();
  Serial.print("Left: ");
  Serial.println(durationLeft);
  Serial.print("Front: ");
  Serial.println(durationFront);

  delay(500);
}

void sensor()
{
  /*
  //LEFT
  digitalWrite(8, LOW);
  digitalWrite(7, HIGH);
  analogWrite(9, 1 );//50

  //RIGHT
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
  analogWrite(11, 1);//0
  */
  
  if (durationFront > 650) //IF NO WALL IN FRONT
  {
    if (durationLeft < 300) //TURN SLIGHT RIGHT IF TOO CLOSE
    {
      //LEFT
      digitalWrite(8, LOW);
      digitalWrite(7, HIGH);
      analogWrite(9, 233);//50

      //RIGHT
      digitalWrite(12, LOW);
      digitalWrite(13, HIGH);
      analogWrite(11, 150);//0
    }
    else if (durationLeft < 650) //GO STRAIGHT
    {
      //LEFT
      digitalWrite(8, LOW);
      digitalWrite(7, HIGH);
      analogWrite(9, 233);
      

      //RIGHT
      digitalWrite(12, LOW);
      digitalWrite(13, HIGH);
      analogWrite(11, 200);//60
    }
    else //if (durationLeft < 750) //TURN SLIGHT LEFT IF TOO FAR
    {
      //LEFT Wheel
      digitalWrite(8, LOW);
      digitalWrite(7, HIGH);
      analogWrite(9, 175);//90

      //RIGHT Wheel
      digitalWrite(12, LOW);
      digitalWrite(13, HIGH);
      analogWrite(11, 200);//60

    }
  }
  else //IS FRONT WALL
  {
    if (durationLeft > 750) //IF NO LEFT WALL
    {
      //LEFT Wheel
      digitalWrite(8, LOW);
      digitalWrite(7, LOW);
      analogWrite(9, 1);//90

      //RIGHT Wheel
      digitalWrite(12, LOW);
      digitalWrite(13, HIGH);
      analogWrite(11, 1);//60
    }
    else
    {
      //TURN RIGHT
      //LEFT Wheel
      digitalWrite(8, LOW);
      digitalWrite(7, HIGH);
      analogWrite(9, 1);//90

      //RIGHT Wheel
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
      analogWrite(11, 0);//0
    }
  }
}

