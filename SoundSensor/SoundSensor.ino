//const int pinsound = A2;
//const int pinlight = A6;
#include <Arduino.h>
#include <U8x8lib.h>
auto display = U8X8_SSD1306_128X64_NONAME_HW_I2C(U8X8_PIN_NONE);

void setup() 
{
  Serial.begin(115200);
  display.begin();
  display.setFlipMode(1);
  display.clearDisplay();
  display.setFont(u8x8_font_7x14B_1x2_r);

}

void sendSoundData() {
 const auto value = analogRead(A2);
 const byte data[] = {0, 0, highByte(value), lowByte(value)};
  Serial.write(data, 4); // send 0,0, "high byte", "low byte"
 Serial.println(); // send "newline"
}
// read sound and display on OLED
void displayA2(){
 const auto value = analogRead(A2);
 const byte data[] = {0, 0, highByte(value), lowByte(value)};
 display.setCursor(0,0); display.print("A0: ");
 display.setCursor(5,0); display.print(value);
 display.setCursor(0,2); display.print("Bytes 1,2: " + String(data[0]) + "," +
String(data[1]));
 display.setCursor(0,4); display.print("Byte 3: " + String(data[2]));
 display.setCursor(0,6); display.print("Byte 4: " + String(data[3]));
}
/* ---- loop -------- */
void loop() {
 displayA2(); // show on OLED
 sendSoundData(); // write to serial port
 //delay(5000); // wait so you don't saturate
 // the serial line and block
 // potential reloads of Arduino code
}
