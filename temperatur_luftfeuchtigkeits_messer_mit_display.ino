

// required adafruits dht library
#include "DHT.h"
 

// install LiquidCrystal_I2C (https://github.com/johnrickman/LiquidCrystal_I2C). git clone https://github.com/johnrickman/LiquidCrystal_I2C  $HOME/Arduino/libraries/
#include "LiquidCrystal_I2C.h"


#define DHT_PIN 4

#define DHT_TYPE DHT22

#define LCD_ADDRESS 0x3F

// + -> 3V,   out/data -> G4,   - -> GND
DHT dht(DHT_PIN, DHT_TYPE);


// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;


// GND -> GND,  VCC -> V5,  SDA -> G21,   SCL -> G22
// set LCD address, number of columns and rows
LiquidCrystal_I2C lcd(LCD_ADDRESS, lcdColumns, lcdRows);


void setup() {
  Serial.begin(9600);
  
  dht.begin();


  // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();

}

void loop() {
  
  // read humidity
  float humidity  = dht.readHumidity();
  // read temperature in Celsius
  float tempC = dht.readTemperature();
 
  // float heatIndexC = dht.computeHeatIndex(tempC,  humi, false);

  // check whether the reading is successful or not
  if ( isnan(tempC) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
  } 
  else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: "+String(tempC)+"\337C");
    lcd.setCursor(0, 1);
    lcd.print("Humidity: "+String(humidity)+"%");

    // output serial monitor
    Serial.println("Temp: "+String(tempC)+"\337C");
    Serial.println("Humidity: "+String(humidity)+"%");
    Serial.println();
    
  }
  
  // wait a 2 seconds between readings
  delay(2000);

 
}
