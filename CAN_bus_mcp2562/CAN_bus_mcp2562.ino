// -------------------------------------------------------------
// CANtest for Teensy 3.6 dual CAN bus
// by Collin Kidder, Based on CANTest by Pawelsky (based on CANtest by teachop)
//
// Both buses are left at default 250k speed and the second bus sends frames to the first
// to do this properly you should have the two buses linked together. This sketch
// also assumes that you need to set enable pins active. Comment out if not using
// enable pins or set them to your correct pins.
//
// This sketch tests both buses as well as interrupt driven Rx and Tx. There are only
// two Tx buffers by default so sending 5 at a time forces the interrupt driven system
// to buffer the final three and send them via interrupts. All the while all Rx frames
// are internally saved to a software buffer by the interrupt handler.
//

#include <FlexCAN.h>

static CAN_filter_t mask;
static uint8_t hex[17] = "0123456789abcdef";

// -------------------------------------------------------------
static void hexDump(uint8_t dumpLen, uint8_t *bytePtr)
{
  uint8_t working;
  while( dumpLen-- ) {
    working = *bytePtr++;
    Serial.write( hex[ working>>4 ] );
    Serial.write( hex[ working&15 ] );
  }
  Serial.write('\r');
  Serial.write('\n');
}


// -------------------------------------------------------------
void setup(void)
{
  delay(1000);
  Serial.println(F("Hello Teensy 3.5 CAN Rx Test."));

  // same as defaultmask
  //mask.flags.remote = 0;
  //mask.flags.extended = 0;
  mask.id = 0;

  Can0.begin(500000,mask,1,1);
  Serial.begin(9600);

  //if using enable pins on a transceiver they need to be set on
  //pinMode(2, OUTPUT);
  //pinMode(35, OUTPUT);

  //digitalWrite(2, HIGH);
  //digitalWrite(35, HIGH);
}


// -------------------------------------------------------------
void loop(void)
{
  CAN_message_t inMsg;
  while (Can0.available()) 
  {
    Can0.read(inMsg);
    Serial.print("CAN bus 0: "); 
    hexDump(8, inMsg.buf);
  }
}
