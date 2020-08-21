#include <SPI.h>          //Library for using SPI Communication 
#include <mcp2515.h>      //Library for using CAN Communication 

int ble=0;
struct can_frame canMsg;

MCP2515 mcp2515(53); // chip select CS pin 10

char data = 0;                //Variable for storing Incoming_value

void setup() 
{
  Serial.begin(9600);
  SPI.begin();               //Begins SPI communication
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS,MCP_8MHZ); //Sets CAN at speed 500KBPS and Clock 8MHz
  mcp2515.setNormalMode();

  canMsg.can_id  = 0x036;           //CAN id as 0x036
  canMsg.can_dlc = 1;               //CAN data length as 1 byte
}
void coffee(int ble)
{
   Serial.println("coffee");
   canMsg.data[0] = ble;        // Sending data to coffee function 
   mcp2515.sendMessage(&canMsg);  
}
void tea(int data)
{
   canMsg.data[0] = data;        // Sending data to coffee function 
   mcp2515.sendMessage(&canMsg);  
}
void loop() 
{
  if(Serial.available() > 0)  
  {
     Serial.println("coffee");
     ble=Serial.read();
     switch(ble)
     {
      case '1': coffee(ble);
      break;
      case '2': tea(ble);
      break;
     }
   }
}  
  
