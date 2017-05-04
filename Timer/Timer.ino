#include <LiquidCrystal.h>

int fsrAnalogPin = 0; // FSR is connected to analog 0
int fsrAnalogPin1 = 5; // FSR is connected to analog 1
int fsrReading;      // the analog reading from the FSR resistor divider
int fsrReading1;
int timer = 0;
int finished = 0;
boolean start = false;


LiquidCrystal lcd(11, 10, 9, 2, 3, 4, 5);

void setup(void)
{
  lcd.begin(16, 2);
  Serial.begin(9600);   // We'll send debugging information via the Serial monitor
}

void loop()
{
  fsrReading = analogRead(fsrAnalogPin);
  fsrReading1 = analogRead(fsrAnalogPin1);
  if (finished == 0)
  {
    if (start == false)
    {
      if (fsrReading < 200)
      {
        start = true;
      }
    }
    else if (fsrReading1 > 200)
    {
      lcd.clear();
      lcd.print("Finish time:");
      lcd.setCursor(0, 1);
      lcd.print(timer);
      lcd.print(" seconds.");
      finished = 1;
      delay(2000);
    }
    else
    {
      delay(1000);
      timer = timer + 1;
      showtime();
    }
  }
  else
  {
    restart();
  }

}

void showtime()
{
  lcd.clear();
  lcd.print(timer);
  lcd.print(" seconds");
}

void restart()
{
  if(fsrReading > 200)
  {
    timer = 0;
    finished = 0;
    start = false;
    loop();
  }
  else
  {
    restart();
  }
}

