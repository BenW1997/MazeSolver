#include <LiquidCrystal.h>

int fsrAnalogPin = 0; // FSR is connected to analog 0
int fsrAnalogPin1 = 1; // FSR is connected to analog 1
int fsrReading;      // the analog reading from the FSR resistor divider
int fsrReading1;
int LEDbrightness;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup(void)
{
  Serial.begin(9600);   // We'll send debugging information via the Serial monitor
}

void loop(void)
{
  fsrReading = analogRead(fsrAnalogPin);
  fsrReading1 = analogRead(fsrAnalogPin1);
  if ()
  {
    

    Serial.print("Analog reading = ");
    Serial.println(fsrReading);

    // we'll need to change the range from the analog reading (0-1023) down to the range
    // used by analogWrite (0-255) with map!
    LEDbrightness = map(fsrReading, 0, 1023, 0, 255);
    // LED gets brighter the harder you press
    analogWrite(LEDpin, LEDbrightness);

    delay(100);
  }
  else
  {

  }

}
