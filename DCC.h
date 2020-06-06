#ifndef DCC_h
#define DCC_h
#include <Arduino.h>
#include "Config.h"
#include <Function.h>

enum ACK_STATE {IGNORE,WAITING,HIT};
class DCC {
  public:

  static void begin();
  static void loop();

  // Public main Track DCC API functions
  static void setThrottle( uint16_t cab, uint8_t tSpeed, bool tDirection);
  static void setFunction( int cab, byte fByte, byte eByte);
  static void setFunction( int cab, byte fByte);
  static void setAccessory(int aAdd, byte aNum, bool activate) ;
  static bool writeTextPacket( byte *b, int nBytes);
  static void writeCVByteMain(int cab, int cv, byte bValue);
  static void writeCVBitMain(int cab, int cv, byte bNum, bool bValue);
  
  // Public PROG track API functions 
  static void  readCV(int cv,vl::Func<void (int)> callback);  // -1 for error
  static void writeCVByte(int cv, byte bValue, vl::Func<void (bool)> callback) ;
  static void verifyCVByte(int cv,byte bValue,vl::Func<void (bool)> callback);
  
  static void readCVBit(int cv, byte bNum, vl::Func<void (int)> callback);  // -1 for error
  static void writeCVBit(int cv, byte bNum, bool bValue, vl::Func<void (bool)> callback);
  static void verifyCVBit(int cv, byte bNum, bool bValue, vl::Func<void (bool)> callback);
 
  static void getLocoId(vl::Func<void (int)> callback);

private: 
  struct LOCO {
     int loco;
     byte speedCode;
  };
  
  static ACK_STATE ackState;
  static vl::Func<void (bool)> ackBitCallback;
  static void AckHandling();
  static void setThrottle2( uint16_t cab, uint8_t speedCode);
  static void updateLocoReminder(int loco, byte speedCode);
  static int nextLoco;
  static LOCO speedTable[MAX_LOCOS];
  static byte cv1(byte opcode, int cv);
  static byte cv2(int cv);

  // NMRA codes #
  static const byte SET_SPEED=0x3f;
  static const byte WRITE_BYTE_MAIN = 0xEC;
  static const byte WRITE_BIT_MAIN = 0xE8;
  static const byte WRITE_BYTE = 0x7C;
  static const byte VERIFY_BYTE= 0x74;
  static const byte BIT_MANIPULATE=0x78;
  static const byte WRITE_BIT=0xF0;
  static const byte VERIFY_BIT=0xE0;
  static const byte BIT_ON=0x08;
  static const byte BIT_OFF=0x00;
};
#endif
