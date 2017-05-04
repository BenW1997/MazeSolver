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

int STATE = 0;
int NS = 0;
const int idle = 0;
const int turnLeft = 1;
const int goStraight = 2;
const int turnRight = 3;
const int slightRight = 4;

char data = 0;

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

<<<<<<< HEAD
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
=======
  //LEFT
  digitalWrite(8, LOW);
  digitalWrite(7, HIGH);
>>>>>>> origin/master

  //RIGHT
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
<<<<<<< HEAD
  analogWrite(11, 1);//0
  */
  
  if (durationFront > 650) //IF NO WALL IN FRONT
=======

  if (Serial.available())
>>>>>>> origin/master
  {
    data = Serial.read();
 //   Serial.print(data);
 //   Serial.print("Serial available");
  }
  /*  if (data == '2') //right-hand rule
    {
<<<<<<< HEAD
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
=======
      sensor2();
    } */
  // Serial.println("in first else");
  else if (data == '1') //left-hand rule
  {
    sensor();
 //   Serial.println("sensor");
  }
  else if (data == '0') //stop
  {
    pause();
 //   Serial.println("pause");
  }
  //else
  //{
    //pause();
 //   Serial.println("else pause");
  //}

}

void sensor()
{
  STATE = NS;

  switch (STATE)
  {
    case idle:
      if (durationLeft < 350 && durationFront >= 200)
        NS = slightRight;
      else if (durationLeft < 625 && durationFront >= 200)
        NS = goStraight;
      else if (durationLeft < 625 && durationFront < 200)
        NS = turnRight;
      else if (durationLeft >= 625 || durationFront < 200)
        NS = turnLeft;
      else
        NS = idle;
      break;

    case turnLeft:
      NS = idle;
      break;

    case goStraight:
      NS = idle;
      break;

    case turnRight:
      NS = idle;
      break;

    case slightRight:
      NS = idle;
      break;
>>>>>>> origin/master

  }
  STATE = NS;
  switch (STATE)
  {
<<<<<<< HEAD
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
=======
    case idle:
      break;

    case turnLeft:
      analogWrite(9, 65);
      analogWrite(11, 255);
      break;

    case goStraight:
      analogWrite(9, 255);
      analogWrite(11, 255);
      break;

    case turnRight:
      //RIGHT
      digitalWrite(12, HIGH);
      digitalWrite(13, LOW);
      analogWrite(9, 255);//90
      analogWrite(11, 255);//0

      delay(1400);
      break;

    case slightRight:
      analogWrite(9, 255);  //9 is left
      analogWrite(11, 75); //11 is right
      break;

>>>>>>> origin/master
  }
}
/*
void sensor2()
{

}
*/
void pause()
{
  digitalWrite(9, 0 );
  digitalWrite(11, 0 );
}

