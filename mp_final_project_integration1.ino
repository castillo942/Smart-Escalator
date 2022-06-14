#include<LiquidCrystal.h>
#include <Adafruit_NeoPixel.h>
#include <Servo.h>
#define N_LEDS 144
#define PIN A3
int time;
int distance;
int timeDelay = 10;
int ForceValue  = 0;
int lbs = 0;
LiquidCrystal lcd(12,11,5,4,3,2);

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);
int gas = 0;
int redColor = 0;
int greenColor = 0;
int blueColor = 0;
int i = 0;

Servo myservo;

void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
  pinMode(A1, INPUT);
  
  myservo.attach(6);
  pinMode(A2, INPUT);
  
  pinMode (8, OUTPUT);
  pinMode (9, INPUT);
  pinMode (7, OUTPUT);
  
  pinMode(13, OUTPUT);
  pinMode(10, INPUT);
  
  pinMode(A0,INPUT);
  pinMode(A3,OUTPUT);
  strip.begin();

}

void loop()
{
    gas  = analogRead(A0);
  
  	if (gas >= 750) {
      digitalWrite (7,HIGH);
      myservo.write(0);
      lcd.setCursor(0,0);
      lcd.print("Fire Fire Fire  ");
      lcd.setCursor(0,1);
      lcd.print("Fire Fire       ");
      timeDelay = 10;
      Serial.println(gas);	
      i = i+1;
      if (i>0){
  	  strip.setPixelColor(i-1, strip.Color(255, 0, 0)); 
   	  strip.show(); 
   	  delay(100);
      }
      
  		} 
  else{
    i=0;
    strip.setPixelColor(3, strip.Color(0, 0, 0));
         strip.show(); 
        strip.setPixelColor(2, strip.Color(0, 0, 0)); 
         strip.show(); 
        strip.setPixelColor(1, strip.Color(0, 0, 0)); 
         strip.show(); 
        strip.setPixelColor(0, strip.Color(0, 0, 0)); 
   	  strip.show(); 
   if(digitalRead(10) == 1)
  {
    digitalWrite(13, HIGH);
    myservo.write(0);
    digitalWrite (7,LOW);
    lcd.setCursor(0,0);
    timeDelay = 10;
    lcd.print("Emergency Stop  ");
     lcd.setCursor(0,1);
     lcd.print("stop stop  ");
   
  }
  else
  {
   
    digitalWrite(13, LOW);
  	m2();
  	float ForceValue = analogRead(A1);
  	float N = exp((ForceValue-555.53) / 156.34);
  	float Lb = N * .224; // N* .224
 
  	lcd.setCursor(0,0);
  	lcd.print("Escalator total");
  	lcd.setCursor(0,1);
  	lcd.print("Lb: ");
  	lcd.print(Lb);
  	lcd.print("      ");
    
    
    m1();
  
  }
  }
  
}

void m1()
{
	int val = digitalRead(A2);
  	Serial.println(val);
  		if (val==HIGH)
    		{
          timeDelay = 0;
          		myservo.write(0);
      			
      				delay(200);
      			myservo.write(180);
      				delay(200);
      					
  			}
  		else
    		{
          if(timeDelay < 10)
          {
            timeDelay = timeDelay +1;
            myservo.write(180);
      				delay(200);
      			myservo.write(0);
      				delay(200);
          }
   				myservo.write(0);
 	 	} 
}

void m2()
{
	digitalWrite (8, HIGH);
	digitalWrite (8, LOW);
	time = pulseIn (9, HIGH);
	distance = (time * 0.034) / 2;
 		if (distance <= 200)
  			{
    			digitalWrite (7,HIGH);
    			delay (100);
  			}
  		else 
        	{
    			digitalWrite (7,LOW);
    			delay (100);
        	}   
 
}


