//digital light
#include <Digital_Light_ISL29035.h>
#include <Digital_Light_TSL2561.h>
//grove bar
#include <Grove_LED_Bar.h>
//temperature and humidty sesnor
#include <Seeed_BME280.h>
//wire is wire
#include <Wire.h>

//levels are based on temp between 70 and 88, each level is actually between a range of 2
//one beep is temperature is under 70
// if you get like 10 beeps it means temperature is above 88 and its na emegency also led bar is going nuts
//two beeps humidty is below 20 ( not an emregnecy
//three beeps the light in the case is not working





BME280 bme280; // this is for your temp

#define ROTARY_ANGLE_SENSOR A3 // inpit for sensor
#define ADC_REF 5 // match voltage to 5v
#define GROVE_VCC 5 // vc of the grove interface
#define NUM_OF_LEDS 10 // number of leds in the bar

int buzzerPin = 2;

// add the grovebar
Grove_LED_Bar LEDBar(9, 8,1); //clock pin, data pin, orientation

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);

  //setup your buzzer
    pinMode(buzzerPin, OUTPUT);
    
   // put your setup code here, to run once:
     pinMode( ROTARY_ANGLE_SENSOR, INPUT);

     
    //start LED BAR  
    LEDBar.begin();

  //begin wire for digital light
   Wire.begin();
   
 // call light
  TSL2561.init();

  //call temp & humid
  bme280.init();
    
  if(!bme280.init()){
    Serial.println("Device error! Check temp");
  }
 

}

void loop() {
  // put your main code here, to run repeatedly:

   //temp variable
    float temp;
  //humidity variable
    float humid;

  
  //determine the number of LEDs that are on based on the angle of he rotary sensor

  int lightLevel = getLightLevel();

  //get the light level
  int lamp = getLamp();


    
  //get and print temperatures
  Serial.print("Temp: ");
  Serial.print(bme280.getTemperature());
  Serial.println("C");//The unit for  Celsius because original arduino don't support special symbols
  temp = bme280.getTemperature();
  

  //get and print humidity data
  Serial.print("Humidity: ");
  Serial.print(bme280.getHumidity());
  Serial.println("%");
  humid = bme280.getHumidity();
  delay(1000);

   


  //if lightLevel > 0, set LEDS accordingly

  if(lightLevel){
      // ok heres where we want it to go red
      if( temp < 70 ){
          LEDBar.setLed(1,1);
          delay(100);
          digitalWrite(buzzerPin,HIGH);
          // stay on for a second
          delay(1000);
          digitalWrite(buzzerPin,LOW);
      }
      else if ( temp >= 88){

         // make the led bar go nuts
        for(int i = 1; i<= lightLevel; i++){
          
          LEDBar.setLed(i,1);
          delay(100);
          // start beeping before you have a fried gecko
          digitalWrite(buzzerPin,HIGH);
          // stay on for a second
          delay(1000);
          // turn beeps off
          digitalWrite(buzzerPin,LOW);
          
       }//end of for loop
      }//end of 88
       else if ( temp > 86 && temp < 88){
            //set it to level 9
            LEDBar.setLed(9,1);
        
        
      }
         else if ( temp > 84 && temp <= 86){
            //set it to level 8
            LEDBar.setLed(8,1);
        
        
      }
         else if ( temp > 82 && temp <= 84){
            //set it to level7 
            LEDBar.setLed(7,1);
        
        
      }
         else if ( temp > 80 && temp <= 82){
            //set it to level6 
            LEDBar.setLed(6,1);
        
        
      }
          else if ( temp > 78 && temp <= 80){
            //set it to level5
            LEDBar.setLed(5,1);
        
        
      }
          else if ( temp > 76 && temp <= 78){
            //set it to level4
            LEDBar.setLed(4,1);
        
        
      }
            else if ( temp > 74 && temp <= 76){
            //set it to level3
            LEDBar.setLed(3,1);
        
        
      }
           else if ( temp > 70 && temp <= 74){
            //set it to level2
            LEDBar.setLed(2,1);
        
        
      }
      else if (humid <=19){
        // you'll here two beeps
           digitalWrite(buzzerPin,HIGH);
          // stay on for a second
          delay(500);
          // turn beeps off
          digitalWrite(buzzerPin,LOW);
           // you'll here two beeps
           digitalWrite(buzzerPin,HIGH);
          // stay on for a second
          delay(500);
          // turn beeps off
          digitalWrite(buzzerPin,LOW);
        
      }
  }//end of light level
  else{

      Serial.println (" The led bar is broke :C");

  }


  if(lamp < 70){

        // start beeping before you have a fried gecko
          digitalWrite(buzzerPin,HIGH);
          // stay on for a second
          delay(1000);
          // turn beeps off
          digitalWrite(buzzerPin,LOW);
          // start beeping before you have a fried gecko
          digitalWrite(buzzerPin,HIGH);
          // stay on for a second
          delay(1000);
          // turn beeps off
          digitalWrite(buzzerPin,LOW);
            // start beeping before you have a fried gecko
          digitalWrite(buzzerPin,HIGH);
          // stay on for a second
          delay(1000);
          // turn beeps off
          digitalWrite(buzzerPin,LOW);
    
  }else{
      
    Serial.println (" The lamp is fine is broke :C");
  }

          
  }//end of for loop

// get the light level
int getLightLevel(){

  int reading = analogRead( ROTARY_ANGLE_SENSOR);

  float voltage = (float)reading*ADC_REF/1023;
  float level = (voltage* NUM_OF_LEDS)/ GROVE_VCC;

  return level;

  
}
//gotta add those lamp memes
int getLamp(){

  Serial.print("The Light value is: ");
  Serial.println(TSL2561.readVisibleLux());
  float lamp = TSL2561.readVisibleLux();
 

  return lamp;
  
}

  


