#include <SPI.h>              //Library for using SPI Communication 
#include <mcp2515.h>          //Library for using CAN Communication

#include <Wire.h> 


struct can_frame canMsg; 
MCP2515 mcp2515(53);                 // SPI CS Pin 10 

char data = 0;                //Variable for storing Incoming_value
int x;
int relay_pin = 2;

int sensorPin = A0; // select the input pin for LDR 115200
int sensorValue = 0; // variable to store the value coming from the sensor
 
// defines pins numbers
const int stepPin1 =32; //36;    // stepper 5 for driver board
const int dirPin1 = 34;//34; 
const int en1 = 30; 

const int stepPin2 = 24;//46;    // stepper 3 for driver board
const int dirPin2 = 26;//48; 
const int en2 = 22;//62; 

const int stepPin3 = 38;//60;   // stepper 2 for driver board
const int dirPin3 = 40;//61; 
const int en3 = 36;//56;  

const int stepPin4 = 44;//60;   // stepper 2 for driver board
const int dirPin4 =46; //61; 
const int en4 = 42;//56;  


void coffee();

void setup() 
{
  pinMode(stepPin1,OUTPUT); 
  pinMode(stepPin2,OUTPUT); 
  pinMode(stepPin3,OUTPUT); 
  pinMode(stepPin4,OUTPUT);

  pinMode(dirPin1,OUTPUT);
  pinMode(dirPin2,OUTPUT);
  pinMode(dirPin3,OUTPUT);
  pinMode(dirPin4,OUTPUT);

  pinMode(en1,OUTPUT);
  pinMode(en2,OUTPUT);
  pinMode(en3,OUTPUT);
  pinMode(en4,OUTPUT);
  digitalWrite(en1,HIGH); 
  digitalWrite(en2,HIGH); 
  digitalWrite(en3,HIGH); 
  digitalWrite(en4,HIGH); 

  Serial.begin(9600);         //sets serial port for communication
  pinMode(sensorPin,INPUT);

  SPI.begin();                       //Begins SPI communication 
  mcp2515.reset();      

  mcp2515.setBitrate(CAN_500KBPS,MCP_8MHZ); //Sets CAN at speed 500KBPS and Clock 8MHz 
  mcp2515.setNormalMode();                  //Sets CAN at normal mode
    
}
void loop() 
{
   if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) // To receive data (Poll Read)
   {
      //Serial.println("aa");
       //Serial.println(canMsg.can_id);
      if(canMsg.can_id==0x036)
      {
         //Serial.println(x);
        x = canMsg.data[0];
Serial.println(x); 
      }
      if(x==3)
      {
        Serial.println(x);
        coffee();
      }
      x=0;
   }
}
void coffee()
{
  sensorValue = digitalRead(sensorPin); // read the value from the sensor
  //Serial.println(sensorValue); //prints the values coming from the sensor on the screen
 
//  if(sensorValue==HIGH)
//  {
   
    Serial.println("aa");
    digitalWrite(dirPin2,HIGH);
    for(int x = 0; x < 2000; x++) 
    {
       digitalWrite(en2,LOW); 
      digitalWrite(stepPin2,HIGH); 
      delayMicroseconds(1000); 
      digitalWrite(stepPin2,LOW); 
      delayMicroseconds(1000);  
     
    }
     digitalWrite(en2,HIGH); 
    delay(3000);
     
    digitalWrite(dirPin1,HIGH);
    for(int x = 0; x < 2000; x++) 
    {
       digitalWrite(en1,LOW); 
      digitalWrite(stepPin1,HIGH); 
      delayMicroseconds(1000); 
      digitalWrite(stepPin1,LOW); 
      delayMicroseconds(1000); 
       digitalWrite(en1,HIGH);  
    }
    delay(3000);

       
    digitalWrite(dirPin3,HIGH);
    for(int x = 0; x < 2000; x++) 
    {
       digitalWrite(en3,LOW); 
      digitalWrite(stepPin3,HIGH); 
      delayMicroseconds(1000); 
      digitalWrite(stepPin3,LOW); 
      delayMicroseconds(1000); 
       digitalWrite(en3,HIGH);  
    }
    delay(3000);


    digitalWrite(dirPin4,HIGH);
    for(int x = 0; x < 2000; x++) 
    {
       digitalWrite(en4,LOW); 
      digitalWrite(stepPin4,HIGH); 
      delayMicroseconds(1000); 
      digitalWrite(stepPin4,LOW); 
      delayMicroseconds(1000); 
       digitalWrite(en4,HIGH);  
    }
    delay(3000);
 // }
}
