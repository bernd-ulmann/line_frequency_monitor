/*
**  Simple power line frequency monitor. It requires a small
** external circuit to get a 50 Hz signal derived from
** mains. It should be noted that this little project is
** far from being "production ready" - it is more a 
** proof-of-concept. 
**
** B. Ulmann fecit  25.10.2026
*/

#include <LiquidCrystal.h>

#undef SERIAL

#define LCD_D4      4
#define LCD_D5      5
#define LCD_D6      6
#define LCD_D7      7
#define LCD_RS      8
#define LCD_EN      9
#define INT_PIN     2
#define MIN         4500    // 45.00 Hz
#define MAX         5500    // 55.00 Hz
#define BAUD_RATE   115200

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

volatile unsigned int cur = 49999, min = MAX, max = 0;

void print_data() {
  lcd.setCursor(2, 0);
  lcd.print(cur);

  lcd.setCursor(11, 0);
  lcd.print(min);

  lcd.setCursor(11, 1);
  lcd.print(max);
}

void interrupt() {
  static int first = 1;
  static unsigned long last_micros;

  if (first) {
    first = 0;
    last_micros = micros();
    return;
  }

  // micros() has a resolution of 4 us on many Arduinos such as the Uni, Mega, etc.
  // Thus, we will only get hundredth of a Hz of resolution.
  unsigned long diff = micros() - last_micros;
  last_micros = micros();
  cur = (100000000L / diff) % 10000;

   // Sometimes, spikes due to switching on or off larger loads trigger this routine spuriously:
  if (cur > MAX or cur < MIN) return;

  if (cur > max) max = cur;
  if (cur < min) min = cur;
}

void setup() {
  // Print labels:
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("F=     MIN=");
  lcd.setCursor(0, 1);
  lcd.print("       MAX=");

#ifdef SERIAL
  Serial.begin(BAUD_RATE);
#endif

  attachInterrupt(digitalPinToInterrupt(INT_PIN), interrupt, RISING);
  delay(100);
}

void loop() {
  print_data();
#ifdef SERIAL
  Serial.print(String(cur) + "\n");
#endif
  delay(100);
}
