#include <U8x8lib.h>

#include <DHT.h>
#include <Grove_Temperature_And_Humidity_Sensor.h>

U8X8_SSD1306_128X64_ALT0_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);
DHT dht(3, DHT11);
void setup() {
  u8x8.begin();
  u8x8.setFlipMode(1);
  u8x8.clear();
  
  dht.begin();
  pinMode(4, OUTPUT);
}

void loop() {
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.setCursor(0, 0);
  //u8x8.print("Hello World!");

  double temperature = 0;
  double humidity = 0;
  temperature = dht.readTemperature();
  temperature = (temperature * 9/5) + 32;
  
  humidity = dht.readHumidity();

  u8x8.println("Temperature: ");
  u8x8.println(temperature);
  u8x8.println("Humidity: ");
  u8x8.println(humidity);

  int thisPitch = map(humidity, 400, 1000, 800, 1500);

  if(humidity > 70){
    tone(5, thisPitch, 2000);
    digitalWrite(4, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(1000);                      // wait for a second
    digitalWrite(4, LOW);   // turn the LED off by making the voltage LOW
    delay(1000);                      // wait for a second
  }
  else{
    noTone(5);
  }

}

