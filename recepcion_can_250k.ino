// demo: CAN-BUS Shield, receive data
#include <mcp_can.h>
#include <SPI.h>

long unsigned int rxId;
long unsigned int Id=0x80;
unsigned char len = 0;
unsigned char rxBuf[8];
int interrupcion=5;
int led =8;
int Relay =7;
int llavePunto=2;
MCP_CAN CAN0(9);                               // Set CS to pin 10


void setup()
{
  Serial.begin(9600);
  CAN0.begin(CAN_500KBPS);                       // init can bus : baudrate = 500k 
  pinMode(llavePunto, INPUT);                            // Setting pin 2 for /INT input
  pinMode(led, OUTPUT);
  pinMode(Relay, OUTPUT);
  digitalWrite(Relay,HIGH );
  Serial.print("MCP2515 ok ID: ");Serial.println(Id,HEX);
  digitalWrite(led, HIGH); 
  digitalWrite(Relay,LOW );
  delay(100);
  digitalWrite(led,LOW ); 
  digitalWrite(Relay,HIGH );
  delay(100);
  digitalWrite(led,HIGH ); 
  digitalWrite(Relay,LOW );
  delay(100);
  digitalWrite(led,LOW ); 
  digitalWrite(Relay,HIGH );
}

void loop()
{
    if(!digitalRead(interrupcion))                         // If pin 2 is low, read receive buffer
    { CAN0.readMsgBuf(&len, rxBuf);              // Read data: len = data length, buf = data byte(s)
      rxId = CAN0.getCanId();                    // Get message ID
      if(Id==rxId)
         {Serial.print("ID: ");
          Serial.print(rxId,HEX);
          Serial.print("  Data: ");
          for(int i = 0; i<len; i++)                // Print each byte of the data
              {if(rxBuf[i] < 0x10)                     // If data byte is less than 0x10, add a leading zero
                    {Serial.print("0");
                              }
              Serial.print(rxBuf[i], HEX);
              Serial.print(" ");
                }
          Serial.println();
          if(rxBuf[2]==0x01)
              { digitalWrite(led, HIGH);
                digitalWrite(Relay, LOW);
              }
          else
              { digitalWrite(led, LOW);
                digitalWrite(Relay, HIGH);
              }
          }
      }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
