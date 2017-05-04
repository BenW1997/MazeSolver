/*Maze solving robot using the left hand rule
  Written By: David Wang
              Dai Hong Zheng
              Ben Wong
*/

const int trigPinLeft = 3;
const int echoPinLeft = 2;

const int trigPinFront = 5;
const int echoPinFront = 4;

const int trigPinRight = 6;
const int echoPinRight = 10;

long durationLeft;
long durationFront;
long durationRight;

int STATE = 0;
int NS = 0;

int STATE2 = 0;
int NS2 = 0;

const int idle = 0;
const int left = 1;
const int straight = 2;
const int right = 3;
const int slightRight = 4;
const int slightLeft = 5;

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
  pinMode(echoPinRight, INPUT);

  pinMode(trigPinLeft, OUTPUT);
  pinMode(trigPinFront, OUTPUT);
  pinMode(trigPinRight, OUTPUT);
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

  digitalWrite(trigPinRight, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinRight, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinRight, LOW);

  durationRight = pulseIn(echoPinRight, HIGH);

  //left motor
  digitalWrite(8, LOW);
  digitalWrite(7, HIGH);
  //right motor
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);

  bluetoothInput();
}

void bluetoothInput() {
  if (Serial.available())
  {
    data = Serial.read();
  }
  else if (data == '2') //right-hand rule
  {
    rightRule();
  }
  else if (data == '1') //left-hand rule
  {
    leftRule();
  }
  else if (data == '0') //stop
  {
    pause();
  }

}

void leftRule() {
  STATE = NS;

  switch (STATE) {
    case idle:
      if (durationLeft < 350 && durationFront >= 200)
        NS = slightRight;
      else if (durationLeft < 625 && durationFront >= 200)
        NS = straight;
      else if (durationLeft < 625 && durationFront < 200)
        NS = right;
      else if (durationLeft >= 625 || durationFront < 200)
        NS = left;
      else
        NS = idle;
      break;

    case left:
      NS = idle;
      break;

    case straight:
      NS = idle;
      break;

    case right:
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

    case left:
      turnSlightLeft();
      break;

    case straight:
      goStraight();
      break;

    case right:
      turnSharpRight();
      break;

    case slightRight:
      turnSlightRight();
      break;

  }
}

void rightRule() {
  STATE2 = NS2;

  switch (STATE2) {
    case idle:
      if (durationRight < 350 && durationFront >= 200)
        NS2 = slightLeft;
      else if (durationRight < 625 && durationFront >= 200)
        NS2 = straight;
      else if (durationRight < 625 && durationFront < 200)
        NS2 = left;
      else if (durationRight >= 625 || durationFront < 200)
        NS2 = right;
      else
        NS2 = idle;
      break;

    case left:
      NS2 = idle;
      break;

    case straight:
      NS2 = idle;
      break;

    case right:
      NS2 = idle;
      break;

    case slightLeft:
      NS2 = idle;
      break;

  }

  STATE2 = NS2;

  switch (STATE2) {

    case idle:
      break;

    case left:
      turnSharpLeft();
      break;

    case straight:
      goStraight();
      break;

    case right:
      turnSlightRight();
      break;

    case slightLeft:
      turnSlightLeft();
      break;

  }
}

void pause() {
  digitalWrite(9, 0 );
  digitalWrite(11, 0 );
}

void turnSlightLeft() {
  analogWrite(9, 60);
  analogWrite(11, 255);
}

void goStraight() {
  analogWrite(9, 255);
  analogWrite(11, 255);
}

void turnSharpRight() {
  //RIGHT
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  analogWrite(9, 255);
  analogWrite(11, 255);

  delay(1100);
}

void turnSlightRight() {
  analogWrite(9, 255);  //9 is left
  analogWrite(11, 55); //11 is right
}

void turnSharpLeft() {
  //RIGHT
  digitalWrite(8, HIGH);
  digitalWrite(7, LOW);
  analogWrite(9, 255);
  analogWrite(11, 255);

  delay(1000);
}
