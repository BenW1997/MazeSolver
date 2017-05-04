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

void setup() {
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

void loop() {
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
  
  //left
  digitalWrite(8, LOW);
  digitalWrite(7, HIGH);
  //right
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);

  bluetoothInput();
}

void bluetoothInput() {
  if (Serial.available())
  {
    data = Serial.read();
  }
  else if (data == '1') //left-hand rule
  {
    sensor();
  }
  else if (data == '0') //stop
  {
    pause();
  }

}

void sensor() {
  STATE = NS;

  switch (STATE) {
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

  }

  STATE = NS;

  switch (STATE) {

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
      analogWrite(9, 255);
      analogWrite(11, 255);

      delay(1100);
      break;

    case slightRight:
      analogWrite(9, 255);  //9 is left
      analogWrite(11, 65); //11 is right
      break;

  }
}

void pause() {
  digitalWrite(9, 0 );
  digitalWrite(11, 0 );
}

