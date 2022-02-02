#include <Arduino.h>
#include <U8x8lib.h>
#include "DHT.h"

#define DHTPIN 3 
#define MOSFET 2   // The MOSFET driver for the water pump on digital I/O 2
#define REDLED 4   // Big red LED on digital I/O 4
#define DHTTYPE DHT22   // DHT 11 
#define GREENLED 13   // Big red LED on digital I/O 13
#define BUZZER 5   // Big red LED on digital I/O 5
#define BUTTON 6   // Push button on digital I/O 6
#define MOISTURE A1

DHT dht(DHTPIN, DHTTYPE); // Sets up dht temp sensor
int sending = 0; // Integer used for determinging which sensor to read
auto display = U8X8_SSD1306_128X64_NONAME_HW_I2C(U8X8_PIN_NONE); // setups diplay

/* ----- setup --------- */
void setup() {
 Serial.begin(9600);
 Wire.begin();
 pinMode(MOSFET, OUTPUT); // Sets the D2 pin (MOSFET + Pump) to output
 pinMode(REDLED, OUTPUT); // Sets the D4 pin (LED) to output
 pinMode(GREENLED, OUTPUT); // Sets the D4 pin (LED) to output
 pinMode(BUZZER, OUTPUT); // Sets the D4 pin (LED) to output
 pinMode(BUTTON, INPUT); // Sets the D6 pin (Button) to input
 pinMode(MOISTURE, INPUT); // Sets the A0 pin (SoilSensor) to input

 dht.begin(); // starts dht sensor
 display.begin();
 display.setFlipMode(1);
 display.clearDisplay();
 display.setFont(u8x8_font_7x14B_1x2_r); // sets up display

}

/* -------- Pot read function. ----------
* Read the potentiometer value (or any other analogue sensor on A0)
* Break up the two bytes of data from A0 into "high" and "low"
* Move those two bytes into an array of four bytes.
* First two bytes are zero. Then high byte. Then low byte.
 */

void sendPotentiometerData() {
 const auto value = analogRead(A0);
 const byte data[] = {0, 0, highByte(value), lowByte(value)};
 Serial.write(data, 4); // send 0,0, "high byte", "low byte"
 Serial.println(); // send "newline"
 delay(1000);
}

/* -------- Sound read function. ----------
* Read the sound sensor value (or any other analogue sensor on A0)
* Break up the two bytes of data from A2 into "high" and "low"
* Move those two bytes into an array of four bytes.
* First two bytes are zero. Then high byte. Then low byte.
 */
void sendSoundData() {
 const auto value = analogRead(A2);
 const byte data[] = {0, 0, highByte(value), lowByte(value)};
 Serial.write(data, 4); // send 0,0, "high byte", "low byte"
 Serial.println(); // send "newline"
 delay(1000);
}

/* -------- Light read function. ----------
* Read the light sensor value (or any other analogue sensor on A0)
* Break up the two bytes of data from A6 into "high" and "low"
* Move those two bytes into an array of four bytes.
* First two bytes are zero. Then high byte. Then low byte.
 */
void sendLightData() {
 const auto value = analogRead(A6);
 const byte data[] = {0, 0, highByte(value), lowByte(value)};
 Serial.write(data, 4); // send 0,0, "high byte", "low byte"
 Serial.println(); // send "newline"
 delay(1000);
}

/* -------- Temp read function. ----------
* Read the temperature value (or any other analogue sensor on A0)
* Break up the two bytes of data from A3 into "high" and "low"
* Move those two bytes into an array of four bytes.
* First two bytes are zero. Then high byte. Then low byte.
 */
void sendTempData() {
 const auto value = analogRead(A3);
 const byte data[] = {0, 0, highByte(value), lowByte(value)};
 Serial.write(data,4); // send 0,0, "high byte", "low byte"
 Serial.println(); // send "newline"
 delay(1000);
}

/* -------- Moisture read function. ----------
* Read the moisture value (or any other analogue sensor on A0)
* Break up the two bytes of data from A1 into "high" and "low"
* Move those two bytes into an array of four bytes.
* First two bytes are zero. Then high byte. Then low byte.
 */
void sendMoistData() {
 const auto value = analogRead(A1);
 const byte data[] = {0, 0, highByte(value), lowByte(value)};
 Serial.write(data,4); // send 0,0, "high byte", "low byte"
 Serial.println(); // send "newline"
 delay(1000);
}

/* ---- loop -------- */
void loop() {

// Swtich statement that reads from a specific sensor based on the value of the sending interger
  switch (sending) {
  case 0:
    break; // //Reads bothing when sending value is 0
  case 1: 
    sendSoundData(); //Reads sound sensor when sending value is 1
    break;
 case 2:
    sendLightData(); //Reads light sensor when sending value is 2
    break;
 case 3:
    sendTempData(); //Reads temperature sensor when sending value is 3
    break;
 case 4:
    sendPotentiometerData(); //Reads potentiometer when sending value is 4
    break;

 case 5:
    sendMoistData(); //Reads mositure sensor when sending value is 5
    break;
  }

 if (!Serial.available()) {
        return;
    }
    
    auto valueRecived = Serial.read();
    display.setCursor(0,0);

       
   if ( valueRecived == 110) 
  {   
    // When 110 is the value recvieved red led is turned on 
      digitalWrite ( REDLED , HIGH );
  } 

   else if ( valueRecived == 111) 
  { 
      // When 110 is the value recvieved red led is turned off 
      digitalWrite ( REDLED , LOW );
  } 

   else if ( valueRecived == 112) 
  { 
    // When 112 is the value recvieved green led is turned on 
      digitalWrite ( GREENLED , HIGH );
  } 

   else if ( valueRecived == 113) 
  { 
    // When 113 is the value recvieved green led is turned off 
      digitalWrite ( GREENLED , LOW );
  } 

   else if ( valueRecived == 114) 
  { 
    // When 114 is the value recvieved the buzzer is turned on 
     tone(BUZZER, 1000); 
  } 

     else if ( valueRecived == 115) 
  { 
    // When 110 is the value recvieved the buzzer is turned off 
     noTone(BUZZER); 
  } 

    else if ( valueRecived == 121) 
  { 
    // When 121 is the value recvieved Sound sensor value is displayed on screen
     const auto value = analogRead(A2);
     display.setCursor(0, 2); 
     display.print("Sound: "  + (String)value);
     display.setCursor(0, 0);
  } 

   else if ( valueRecived == 122) 
  { 
     // When 122 is the value recvieved Light sensor value is displayed on screen
     const auto value = analogRead(A6);
     display.setCursor(0, 4);
     display.print("Light: "  + (String)value);
     display.setCursor(0, 0);
  } 

   else if ( valueRecived == 123) 
  { 
    // When 123 is the value recvieved temp sensor value is displayed on screen     
     const auto value = analogRead(A7);
     display.setCursor(0, 6);
     display.print("Temperature: "  + (String)value);
     display.setCursor(0, 0);
  } 

     else if ( valueRecived == 124) 
  { 
    // When 124 is the value recvieved mosfet is turned on 
      digitalWrite ( MOSFET , HIGH );

  } 

     else if ( valueRecived == 125) 
  { 
    // When 125 is the value recvieved mosfet is turned off 
     digitalWrite ( MOSFET , LOW );

  } 

    else if ( valueRecived == 131) 
  { 
    // When 131 is the value recvieved sending is assigned 1
     sending = 1;
  } 
    else if ( valueRecived == 132) 
  { 
    // When 132 is the value recvieved sending is assigned 2
     sending = 2;
  } 
    else if ( valueRecived == 133) 
  { 
    // When 133 is the value recvieved sending is assigned 3
     sending = 3;
  } 
    else if ( valueRecived == 134) 
  { 
    // When 134 is the value recvieved sending is assigned 4
     sending = 4;
  } 
    else if ( valueRecived == 135) 
  { 
    // When 135 is the value recvieved sending is assigned 5
     sending = 5;
  } 
 
   else if ( valueRecived == 140) 
  { 
    // When 140 is the value recvieved sending is assigned 0
     sending = 0;
  } 
  else if ( valueRecived == ( byte ) -1) 
  { 
    //Wehb byte value is -1 that means that the countdown is done so turn on red led
    digitalWrite ( REDLED , HIGH );
  } 
  else if( valueRecived <= ( byte ) 101 && valueRecived > 0)
  {  // this indicates the countdown is in progress
    display.clear();   
    display.print ( (String) valueRecived );
    digitalWrite ( REDLED , LOW );
  }

   else if( valueRecived == 0 )
  { 
    // Once the countdown is done no sensor should be read so sending is assigned 0
    sending = 0;
  }

}
