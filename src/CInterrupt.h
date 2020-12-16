#ifndef _C_INTERRUPT_H_
#define _C_INTERRUPT_H_

enum interrupts
{
  INTRPT_NONE       = 0,
  INTRPT_CHANGE_BG  = 0x00000001,		// intrpt via bg tile change
  INTRPT_CHANGE_FG  = 0x00000002,		// intrpt via fg tile change
  INTRPT_MAP_MODEL  = 0x00000004,   // show a simple model of the area
  INTRPT_CHANGE_TS  = 0x00000008,   // change tileset
  INTRPT_CHANGE_EN  = 0x00000010,   // change/explore entity groups
  INTRPT_CHANGE_SC  = 0x00000020,   // change/explore scenery groups
  INTRPT_CHANGE_LA  = 0x00000040,   // change/make scenery layers
  INTRPT_MODIFY_HB  = 0x00000080,   // modify primary hitbox within active entity group
  INTRPT_NEW        = 0x00000100,   // reset stage prompt
  INTRPT_LOAD       = 0x00000200,   // load stage prompt
  INTRPT_SAVE       = 0x00000400,   // save stage prompt
};

class CInterrupt {

private:
  static int handle;

public:
  CInterrupt();

  // turns off a bitwise flag in handle
  static void removeFlag(int flag);

  // turns on a bitwise flag in handle
  static void appendFlag(int flag);

  // turns all flags off
  static void resetFlags();

  // returns true if the flag is on in handle
  static bool isFlagOn(int flag);

  // returns true if the flag is off in handle
  static bool isFlagOff(int flag);

  // returns true if there are no interruptions
  static bool isNone();
};
#endif
