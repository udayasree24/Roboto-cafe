#include <SPI.h>              //Library for using SPI Communication 
#include <mcp2515.h>          //Library for using CAN Communication
 


struct can_frame canMsg; 
MCP2515 mcp2515(53);                 // SPI CS Pin 10 
 int x=0;
const int ldrPin = A2;    // A0 as a LDR pin
const int ldrPin1 = A0;    // A0 as a LDR pin
int i;
int CW=2,CW1=5,a;               // CW pin 6 as a dc motor 
 
void setup() {
  
  delay(1000);
    
  SPI.begin();                       //Begins SPI communication
  
  Serial.begin(9600);                //Begins Serial Communication at 9600 baudrate 
  
  mcp2515.reset();      

  mcp2515.setBitrate(CAN_500KBPS,MCP_8MHZ); //Sets CAN at speed 500KBPS and Clock 8MHz 
  mcp2515.setNormalMode();                  //Sets CAN at normal mode

   pinMode(CW, OUTPUT);    // Set CW as a output

  pinMode(ldrPin, INPUT); // Set ldrpin as a input
  digitalWrite(CW,HIGH);  // initially turning  motor pin off 
   pinMode(CW1, OUTPUT);    // Set CW as a output

  pinMode(ldrPin1, INPUT); // Set ldrpin as a input
  digitalWrite(CW1,HIGH);  // initially turning  motor pin off 
}

void loop() 
{
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) // To receive data (Poll Read)
  {
     Serial.println("aa");
     if(canMsg.can_id==0x046)
     {
       //Serial.println(canMsg.can_id);
        x = canMsg.data[0];  
       Serial.println("jj");   
       Serial.println(x);
       if(x==4)
       {
         Serial.println("jj2");  
        delay(30000);
        //a=digitalRead(ldrPin);
        
      //  if (a==HIGH)
        //{
          digitalWrite(CW,LOW);   // motor on  
          //Serial.println(a);
          delay(1000);
          digitalWrite(CW,HIGH);  // motor off
          delay(3000);
        // }
        
       
      
     



         digitalWrite(CW1,LOW);   // motor on  
          //Serial.println(a);
          delay(1000);
          digitalWrite(CW1,HIGH);  // motor off
          delay(3000);

       }

      
    }
} 
}                   
