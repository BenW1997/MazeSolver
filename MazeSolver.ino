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

  if(Serial.available() > 0)
  {
    data = Serial.read();
    Serial.print(data);
  }
  else
  {
    if(data == '2') //right-hand rule
    {
      sensor2();
    }
    else if (data == '1') //left-hand rule
    {
      sensor();
    }
    else if (data == '0') //stop
    {
      pause();
    }
    else
    {
      pause();
    }
  }
}

void sensor()
{
  //LEFT
  digitalWrite(8, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(9, 1 );//50

  //RIGHT
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
  digitalWrite(11, 1);//0
  
  if (durationFront > 200) //IF NO WALL IN FRONT
  {
    if (durationLeft < 350) //TURN SLIGHT RIGHT IF TOO CLOSE
    {
      analogWrite(9, 255);  //9 is left
      analogWrite(11, 75); //11 is right
    }
    else if (durationLeft < 625) //GO STRAIGHT
    {
      analogWrite(9, 255);
      analogWrite(11, 255);
    }
    else
    {
      analogWrite(9, 75);
      analogWrite(11, 255);

    }
  }
  else //IS FRONT WALL
  {
    if (durationLeft > 625) //IF NO LEFT WALL
    {
      analogWrite(9, 75);
      analogWrite(11, 255);
    }
    else
    {
      //RIGHT
      digitalWrite(12, HIGH);
      digitalWrite(13, LOW);
      analogWrite(9, 255);//90
      analogWrite(11, 255);//0

      delay(1800);
    }
  }
}

void sensor2()
{
  
}

void pause()
{
  digitalWrite(9, 0 );
  digitalWrite(11, 0 );
}

