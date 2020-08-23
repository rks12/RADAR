#include <Servo.h>
#include <LiquidCrystal.h>
const int rs=9,en=8,d4=5,d5=4,d6=3,d7=2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); //lcd object
const int trigPin = 10;
const int echoPin = 11;
long duration;
int distance,led=13,yellow_led=7;
Servo myServo; //servo object
void setup()
    {
                pinMode(trigPin, OUTPUT); 
                pinMode(echoPin, INPUT); 
                pinMode(led, OUTPUT);
                 pinMode(yellow_led, OUTPUT);
                 digitalWrite(led,LOW);
                  digitalWrite(yellow_led,LOW);
                Serial.begin(9600);
                myServo.attach(12); // Defines on which pin is the servo motor attached
                
                analogWrite(6,20);
              lcd.begin(16,2);

     }
void loop()
  {    lcd.setCursor(0,0);
      lcd.print("hi");
     //llcd();
      digitalWrite(led,LOW);
      for(int i=15;i<=165;i++){  
      myServo.write(i);
      delay(30);
      distance = calculateDistance();
      check();
       // Serial.print("angle ");
      Serial.print(i); // Sends the current degree into the Serial Port
      Serial.println(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
       Serial.print(distance); 
      Serial.println("."); 
      }
     
      for(int i=165;i>15;i--){  
      myServo.write(i);
      delay(30);
      distance = calculateDistance();
      check();
    
      
      Serial.print(i);
      Serial.print(",");
      Serial.println(distance);
    
    
      Serial.print(".");
      }
   }

int calculateDistance(){ 
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2;

//VSS-GND,VDD-5V,VO-6,RS-13,RW-GND,E-8,A-5V,K-GND
    if(distance<=8)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("  DANGER");
      lcd.setCursor(0,1);
      lcd.print("distance= ");
      lcd.print(distance);
    }else if(distance<=30&&distance>8)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("  INCOMING");
    }else if(distance>1490)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("  REST IN PEACE ");
    }
    else
    {
      lcd.setCursor(0,0);
      lcd.clear();
      lcd.print("   ALL CLEAR");
    }
  
  return distance;
}
  int check()
  {
    if(distance<=8&&distance>6)
      {
        digitalWrite(led,HIGH);
        delay(300);
        digitalWrite(led,LOW);
        delay(200);
      }else if(distance<=6&&distance>4)
      {
        digitalWrite(led,HIGH);
        delay(200);
        digitalWrite(led,LOW);
        delay(100);
      }else if(distance<=4&&distance>2)
      {
        digitalWrite(led,HIGH);
        delay(100);
        digitalWrite(led,LOW);
        delay(50);
      }else if(distance<=2&&distance>0)
      {
        digitalWrite(led,HIGH);
        delay(50);
        digitalWrite(led,LOW);
        delay(25);
      }else if(distance<=30&&distance>8)
      {
        digitalWrite(yellow_led,HIGH);
        delay(300);
        digitalWrite(yellow_led,LOW);
        delay(200);
      }else if(distance>1490)
      {
        digitalWrite(led,HIGH);
        delay(100);
      }else
      {
        digitalWrite(led,LOW);
        delay(100);
      }
  }

  
