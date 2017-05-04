#include <LiquidCrystal.h>

int fsrAnalogPin0 = 0; // FSR is connected to analog 0
int fsrAnalogPin1 = 5; // FSR is connected to analog 5
int fsrReadingStart;      // the analog reading from the FSR resistor divider
int fsrReadingFinish;
int counter;
int done;

LiquidCrystal lcd(11, 10, 9, 2, 3, 4, 5);

void setup(void)
{
  Serial.begin(9600);   // We'll send debugging information via the Serial monitor
  lcd.begin(16, 2);
}

void loop(void)
{
  fsrReadingStart = analogRead(fsrAnalogPin0);
  fsrReadingFinish = analogRead(fsrAnalogPin1);
  Serial.println(done);

  if (fsrReadingStart >= 200 && fsrReadingFinish < 200)
  {
    counter = 0;
    lcd.clear();
    lcd.print("Timer:");
    lcd.setCursor(0, 1);
    lcd.print(counter);
    lcd.print(" seconds.");
    done = 0;
    delay(1000);
  }
  else if (fsrReadingStart < 200 && fsrReadingFinish < 100)
  {
    if (done == 1)
    {
      lcd.clear();
      lcd.print("Finish time:");
      lcd.setCursor(0, 1);
      lcd.print(counter);
      lcd.print(" seconds.");
      delay(1000);
    }
    if (done == 0)
    {
      counter++;
      lcd.clear();
      lcd.print("Timer:");
      lcd.setCursor(0, 1);
      lcd.print(counter);
      lcd.print(" seconds.");
      delay(1000);
    }
  }
  else if (fsrReadingStart < 200 && fsrReadingFinish >= 100)
  {
    lcd.clear();
    lcd.print("Finish time:");
    lcd.setCursor(0, 1);
    lcd.print(counter);
    lcd.print(" seconds.");
    done = 1;
    delay(1000);
  }
}
