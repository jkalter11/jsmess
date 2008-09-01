/**********************************************************************************
 *
 *		machine/cbmipt.c
 * 
 *				Input port macros shared by various CBM computers
 *
 *
 *		TO DO:
 *
 *		- investigate C128 inputs problems (bugzilla #1240)
 *		- investigate superpet different reading of Caps Lock (check machine/pet.c)
 *		- move here lightpen inputs from vc20.c, eventually
 *		- clean up the "SPECIAL" and "CFG" input ports (e.g. there a quite a lot
 *		  of settings that are not checked anymore! we have either to implement
 *		  the features properly or, if they're hacks, to remove them)
 *
 *********************************************************************************/

#include "driver.h"
#include "machine/cbmipt.h"

/***************************** Commodore 64 ****************************************
 *
 *	- common_cbm_keyboard: C64 keyboard; used by C16, C65 and C128 as well
 *	- c64_special: input port for the Restore key and the Shift Lock Switch
 *	- c64_controls: joypads, paddles and lightpen; shared with C65, C128 
 *			and CBMB
 *	- c64_control_cfg: input port to select controllers and switch 
 *			gameports A/B; shared with C65, C128 and CBMB
 *	- c64_config: devices and serial configurations
 *
 **********************************************************************************/

/*

C64 Keyboard Layout
-------------------

                                                                           CLR    INST
    <-   1!   2"   3#   4$   5%   6&   7'   8(   9)   0     +    -    �    HOME   DEL           f 1

 
    CTRL   Q    W    E    R    T     Y    U    I    O    P    @    *     UP    RESTORE          f 3

RUN   SHIFT
STOP  LOCK   A    S    D    F     G     H    J    K    L   :[   ;]    =      RETURN             f 5

                                                                           CRSR  CRSR
C=    SHIFT     Z    X    C    V    B     N    M    ,<   .>   /?   SHIFT   U/D    L/R           f 7


                                 SPACEBAR


Notes: �C=� is a key with the Commodore logo, �UP� is an arrow pointing up, the �CRSR� keys at the 
bottom-right corner are used to move the cursor on screen (Up/Down and Left/Right resp.). 
*/


INPUT_PORTS_START( common_cbm_keyboard )
	PORT_START( "ROW0" )
	PORT_BIT( 0x80, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_NAME("Crsr Down Up") PORT_CODE(KEYCODE_RALT)		PORT_CHAR(UCHAR_MAMEKEY(DOWN)) PORT_CHAR(UCHAR_MAMEKEY(UP))
	PORT_BIT( 0x40, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_F3)									PORT_CHAR(UCHAR_MAMEKEY(F5)) PORT_CHAR(UCHAR_MAMEKEY(F6))
	PORT_BIT( 0x20, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_F2)									PORT_CHAR(UCHAR_MAMEKEY(F3)) PORT_CHAR(UCHAR_MAMEKEY(F4))
	PORT_BIT( 0x10, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_F1)									PORT_CHAR(UCHAR_MAMEKEY(F1)) PORT_CHAR(UCHAR_MAMEKEY(F2))
	PORT_BIT( 0x08, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_F4)									PORT_CHAR(UCHAR_MAMEKEY(F7)) PORT_CHAR(UCHAR_MAMEKEY(F8))
	PORT_BIT( 0x04, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_NAME("Crsr Right Left") PORT_CODE(KEYCODE_RCONTROL)	PORT_CHAR(UCHAR_MAMEKEY(RIGHT)) PORT_CHAR(UCHAR_MAMEKEY(LEFT))
	PORT_BIT( 0x02, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_NAME("Return") PORT_CODE(KEYCODE_ENTER)				PORT_CHAR(13)
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_NAME("Del  Inst") PORT_CODE(KEYCODE_BACKSPACE)		PORT_CHAR(8) PORT_CHAR(UCHAR_MAMEKEY(INSERT))

	PORT_START( "ROW1" )
	PORT_BIT( 0x80, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_NAME("Shift (Left)") PORT_CODE(KEYCODE_LSHIFT)		
	PORT_BIT( 0x40, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_E) 		PORT_CHAR('E')	
	PORT_BIT( 0x20, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_S) 		PORT_CHAR('S')	
	PORT_BIT( 0x10, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_Z)			PORT_CHAR('Z')	
	PORT_BIT( 0x08, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_4)			PORT_CHAR('4') PORT_CHAR('$')
	PORT_BIT( 0x04, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_A) 		PORT_CHAR('A')	
	PORT_BIT( 0x02, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_W) 		PORT_CHAR('W')	
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_3)			PORT_CHAR('3') PORT_CHAR('#')

	PORT_START( "ROW2" )
	PORT_BIT( 0x80, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_X) 		PORT_CHAR('X')	
	PORT_BIT( 0x40, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_T) 		PORT_CHAR('T')	
	PORT_BIT( 0x20, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_F) 		PORT_CHAR('F')	
	PORT_BIT( 0x10, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_C) 		PORT_CHAR('C')	
	PORT_BIT( 0x08, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_6)			PORT_CHAR('6') PORT_CHAR('&')
	PORT_BIT( 0x04, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_D) 		PORT_CHAR('D')	
	PORT_BIT( 0x02, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_R) 		PORT_CHAR('R')	
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_5)			PORT_CHAR('5') PORT_CHAR('%')

	PORT_START( "ROW3" )
	PORT_BIT( 0x80, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_V) 		PORT_CHAR('V')	
	PORT_BIT( 0x40, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_U) 		PORT_CHAR('U')	
	PORT_BIT( 0x20, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_H) 		PORT_CHAR('H')	
	PORT_BIT( 0x10, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_B) 		PORT_CHAR('B')	
	PORT_BIT( 0x08, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_8)			PORT_CHAR('8') PORT_CHAR('(')
	PORT_BIT( 0x04, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_G) 		PORT_CHAR('G')	
	PORT_BIT( 0x02, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_Y) 		PORT_CHAR('Y')	
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_7)			PORT_CHAR('7') PORT_CHAR('\'')

	PORT_START( "ROW4" )
	PORT_BIT( 0x80, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_N) 		PORT_CHAR('N')	
	PORT_BIT( 0x40, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_O) 		PORT_CHAR('O')	
	PORT_BIT( 0x20, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_K) 		PORT_CHAR('K')	
	PORT_BIT( 0x10, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_M) 		PORT_CHAR('M')	
	PORT_BIT( 0x08, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_0)			PORT_CHAR('0')	
	PORT_BIT( 0x04, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_J) 		PORT_CHAR('J')	
	PORT_BIT( 0x02, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_I) 		PORT_CHAR('I')	
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_9)			PORT_CHAR('9') PORT_CHAR(')')

	PORT_START( "ROW5" )
	PORT_BIT( 0x80, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_COMMA) 	PORT_CHAR(',') PORT_CHAR('<')
	PORT_BIT( 0x40, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_OPENBRACE) PORT_CHAR('@')	
	PORT_BIT( 0x20, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_COLON)		PORT_CHAR(':') PORT_CHAR('[')
	PORT_BIT( 0x10, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_STOP) 		PORT_CHAR('.') PORT_CHAR('>')
	PORT_BIT( 0x08, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_EQUALS)	PORT_CHAR('-')	
	PORT_BIT( 0x04, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_L) 		PORT_CHAR('L')	
	PORT_BIT( 0x02, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_P) 		PORT_CHAR('P')	
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_MINUS)		PORT_CHAR('+')	

	PORT_START( "ROW6" )
	PORT_BIT( 0x80, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_SLASH)								PORT_CHAR('/') PORT_CHAR('?')
	PORT_BIT( 0x40, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_NAME("\xE2\x86\x91  Pi") PORT_CODE(KEYCODE_DEL)	PORT_CHAR(0x2191) PORT_CHAR(0x03C0)
	PORT_BIT( 0x20, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_BACKSLASH)							PORT_CHAR('=')
	PORT_BIT( 0x10, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_NAME("Shift (Right)") PORT_CODE(KEYCODE_RSHIFT)	
	PORT_BIT( 0x08, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_NAME("Home  Clr") PORT_CODE(KEYCODE_INSERT)		PORT_CHAR(UCHAR_MAMEKEY(HOME))
	PORT_BIT( 0x04, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_QUOTE)								PORT_CHAR(';') PORT_CHAR(']')
    PORT_BIT( 0x02, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_CLOSEBRACE)						PORT_CHAR('*')
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_BACKSLASH2)						PORT_CHAR('\xA3')

	PORT_START( "ROW7" )
	PORT_BIT( 0x80, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_NAME("Stop Run") PORT_CODE(KEYCODE_HOME)				
	PORT_BIT( 0x40, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_Q)									PORT_CHAR('Q')	
	PORT_BIT( 0x20, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_NAME("CBM") PORT_CODE(KEYCODE_LCONTROL)				
	PORT_BIT( 0x10, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_SPACE)								PORT_CHAR(' ')	
	PORT_BIT( 0x08, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_2)									PORT_CHAR('2') PORT_CHAR('"')
	PORT_BIT( 0x04, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_TAB)								PORT_CHAR(UCHAR_SHIFT_2)
	PORT_BIT( 0x02, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_NAME("\xE2\x86\x90") PORT_CODE(KEYCODE_TILDE)	PORT_CHAR(0x2190)	
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_1)									PORT_CHAR('1') PORT_CHAR('!')
INPUT_PORTS_END


INPUT_PORTS_START( c64_special )
	PORT_START( "SPECIAL" )  /* special keys */	
    PORT_BIT( 0x80, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_NAME("Restore") PORT_CODE(KEYCODE_PRTSCR)
	PORT_BIT( 0x40, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_NAME("Shift Lock (switch)") PORT_CODE(KEYCODE_CAPSLOCK) PORT_TOGGLE PORT_CHAR(UCHAR_MAMEKEY(CAPSLOCK))
	PORT_BIT( 0x20, IP_ACTIVE_HIGH, IPT_UNUSED )													
	PORT_BIT( 0x10, IP_ACTIVE_HIGH, IPT_UNUSED )	
INPUT_PORTS_END


INPUT_PORTS_START( c64_controls )
	PORT_START("JOY0")
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_JOYSTICK_UP )		PORT_8WAY
	PORT_BIT( 0x02, IP_ACTIVE_HIGH, IPT_JOYSTICK_DOWN )		PORT_8WAY
	PORT_BIT( 0x04, IP_ACTIVE_HIGH, IPT_JOYSTICK_LEFT )		PORT_8WAY
	PORT_BIT( 0x08, IP_ACTIVE_HIGH, IPT_JOYSTICK_RIGHT )	PORT_8WAY
	PORT_BIT( 0x10, IP_ACTIVE_HIGH, IPT_BUTTON1 ) 
	PORT_BIT( 0x20, IP_ACTIVE_HIGH, IPT_BUTTON2 ) 
    PORT_BIT( 0xc0, IP_ACTIVE_HIGH, IPT_UNUSED ) 

	PORT_START("JOY1") 
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_JOYSTICK_UP )		PORT_NAME("P2 Up") PORT_CODE(KEYCODE_HOME) PORT_CODE(JOYCODE_Y_UP_SWITCH) PORT_PLAYER(2) PORT_8WAY
	PORT_BIT( 0x02, IP_ACTIVE_HIGH, IPT_JOYSTICK_DOWN )		PORT_NAME("P2 Down") PORT_CODE(KEYCODE_END) PORT_CODE(JOYCODE_Y_DOWN_SWITCH) PORT_PLAYER(2) PORT_8WAY
	PORT_BIT( 0x04, IP_ACTIVE_HIGH, IPT_JOYSTICK_LEFT )		PORT_NAME("P2 Left") PORT_CODE(KEYCODE_DEL) PORT_CODE(JOYCODE_X_LEFT_SWITCH ) PORT_PLAYER(2) PORT_8WAY
	PORT_BIT( 0x08, IP_ACTIVE_HIGH, IPT_JOYSTICK_RIGHT )	PORT_NAME("P2 Right") PORT_CODE(KEYCODE_PGDN) PORT_CODE(JOYCODE_X_RIGHT_SWITCH ) PORT_PLAYER(2) PORT_8WAY
	PORT_BIT( 0x10, IP_ACTIVE_HIGH, IPT_BUTTON1 )			PORT_NAME("P2 Button") PORT_CODE(KEYCODE_INSERT) PORT_CODE(JOYCODE_BUTTON1 ) PORT_PLAYER(2)
	PORT_BIT( 0x20, IP_ACTIVE_HIGH, IPT_BUTTON2 )			PORT_NAME("P2 Button 2") PORT_CODE(KEYCODE_PGUP) PORT_CODE(JOYCODE_BUTTON2 ) PORT_PLAYER(2)
    PORT_BIT( 0xc0, IP_ACTIVE_HIGH, IPT_UNUSED ) 

	PORT_START("PADDLE0") 
	PORT_BIT( 0x100, IP_ACTIVE_HIGH, IPT_BUTTON1) PORT_NAME("Paddle 1 Button") PORT_CODE(KEYCODE_LCONTROL) PORT_CODE(JOYCODE_BUTTON1)
	PORT_BIT( 0xff,128,IPT_PADDLE) PORT_SENSITIVITY(30) PORT_KEYDELTA(20) PORT_MINMAX(0,255) PORT_CODE_DEC(KEYCODE_LEFT) PORT_CODE_INC(KEYCODE_RIGHT) PORT_CODE_DEC(JOYCODE_X_LEFT_SWITCH) PORT_CODE_INC(JOYCODE_X_RIGHT_SWITCH) PORT_REVERSE

	PORT_START("PADDLE1") 
	PORT_BIT( 0x100, IP_ACTIVE_HIGH, IPT_BUTTON2) PORT_NAME("Paddle 2 Button") PORT_CODE(KEYCODE_LALT) PORT_CODE(JOYCODE_BUTTON2)
	PORT_BIT( 0xff,128,IPT_PADDLE) PORT_SENSITIVITY(30) PORT_KEYDELTA(20) PORT_MINMAX(0,255) PORT_CODE_DEC(KEYCODE_DOWN) PORT_CODE_INC(KEYCODE_UP) PORT_CODE_DEC(JOYCODE_Y_UP_SWITCH) PORT_CODE_INC(JOYCODE_Y_DOWN_SWITCH) PORT_PLAYER(2) PORT_REVERSE

	PORT_START("PADDLE2") 
	PORT_BIT( 0x100, IP_ACTIVE_HIGH, IPT_BUTTON3) PORT_NAME("Paddle 3 Button") PORT_CODE(KEYCODE_INSERT) PORT_CODE(JOYCODE_BUTTON1)
	PORT_BIT( 0xff,128,IPT_PADDLE) PORT_SENSITIVITY(30) PORT_KEYDELTA(20) PORT_MINMAX(0,255) PORT_CODE_DEC(KEYCODE_HOME) PORT_CODE_INC(KEYCODE_PGUP) PORT_PLAYER(3) PORT_REVERSE

	PORT_START("PADDLE3") 
	PORT_BIT( 0x100, IP_ACTIVE_HIGH, IPT_BUTTON4) PORT_NAME("Paddle 4 Button") PORT_CODE(KEYCODE_DEL) PORT_CODE(JOYCODE_BUTTON2)
	PORT_BIT( 0xff,128,IPT_PADDLE) PORT_SENSITIVITY(30) PORT_KEYDELTA(20) PORT_MINMAX(0,255) PORT_CODE_DEC(KEYCODE_END) PORT_CODE_INC(KEYCODE_PGDN) PORT_PLAYER(4) PORT_REVERSE

	PORT_START("TRACKX") 
	PORT_BIT( 0x7e, 0x00, IPT_TRACKBALL_X) PORT_SENSITIVITY(100) PORT_KEYDELTA(0) PORT_PLAYER(1)
	/* PORT_BIT( 0x1ff,0,IPT_PADDLE) PORT_SENSITIVITY(30) PORT_KEYDELTA(2) PORT_MINMAX(0,320-1) PORT_CODE_DEC(KEYCODE_LEFT) PORT_CODE_INC(KEYCODE_RIGHT) PORT_CODE_DEC(JOYCODE_X_LEFT_SWITCH) PORT_CODE_INC(JOYCODE_X_RIGHT_SWITCH) PORT_PLAYER(1) */ 

	PORT_START("TRACKY") 
	PORT_BIT( 0x7e, 0x00, IPT_TRACKBALL_Y) PORT_SENSITIVITY(100) PORT_KEYDELTA(0) PORT_PLAYER(1) PORT_REVERSE
	/* PORT_BIT( 0xff,0,IPT_PADDLE) PORT_SENSITIVITY(30) PORT_KEYDELTA(2) PORT_MINMAX(0,200-1) PORT_CODE_DEC(KEYCODE_UP) PORT_CODE_INC(KEYCODE_DOWN) PORT_CODE_DEC(JOYCODE_Y_UP_SWITCH) PORT_CODE_INC(JOYCODE_Y_DOWN_SWITCH) PORT_PLAYER(2) */ 

	PORT_START("TRACKIPT")
	PORT_BIT( 0x02, IP_ACTIVE_HIGH, IPT_BUTTON1) PORT_NAME("Mouse Button Left") PORT_CODE(KEYCODE_LCONTROL) PORT_CODE(JOYCODE_BUTTON1)
	/* PORT_BIT( 0x02, IP_ACTIVE_HIGH, IPT_BUTTON2) PORT_NAME("Lightpen Signal") PORT_CODE(KEYCODE_LCONTROL) */ 
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_BUTTON1) PORT_NAME("Mouse Button Right") PORT_CODE(KEYCODE_LALT) PORT_CODE(JOYCODE_BUTTON2)
INPUT_PORTS_END


INPUT_PORTS_START( c64_control_cfg )
	PORT_START("DSW0") 
	PORT_DIPNAME( 0xe000, 0x2000, "Gameport A")		
	PORT_DIPSETTING(	0x0000, DEF_STR( None ) )	
	PORT_DIPSETTING(	0x2000, "Joystick 1" )		
	PORT_DIPSETTING(	0x4000, "Paddles 1, 2" )	
	PORT_DIPSETTING(	0x6000, "Mouse Joystick Emulation/2 Button Joystick" )
	PORT_DIPSETTING(	0x8000, "Mouse" )			
	PORT_DIPSETTING(	0xa000, "Lightpen" )		
	PORT_DIPNAME( 0x1000, 0x1000, "Lightpen Draw Pointer")
	PORT_DIPSETTING(	0x0000, DEF_STR( Off ) )	
	PORT_DIPSETTING(	0x1000, DEF_STR( On ) )		
	PORT_DIPNAME( 0x0e00, 0x0200, "Gameport B")		
	PORT_DIPSETTING(	0x0000, DEF_STR( None ) )	
	PORT_DIPSETTING(	0x0200, "Joystick 2" )		
	PORT_DIPSETTING(	0x0400, "Paddles 3, 4" )	
	PORT_DIPSETTING(	0x0600, "Mouse Joystick Emulation/2 Button Joystick" )
	PORT_DIPSETTING(	0x0800, "Mouse" )			
	PORT_DIPNAME( 0x0100, IP_ACTIVE_HIGH, "Swap Gameport 1 and 2") PORT_CODE(KEYCODE_NUMLOCK)
	PORT_DIPSETTING(	0x0000, DEF_STR( No ) )		
	PORT_DIPSETTING(	0x0100, DEF_STR( Yes ) )
INPUT_PORTS_END


INPUT_PORTS_START( c64_config )
	PORT_START( "CFG" )
	PORT_DIPNAME( 0x4000, 0x4000, "Tape Drive/Device 1")									
	PORT_DIPSETTING(	0x0000, DEF_STR( Off ) )											
	PORT_DIPSETTING(	0x4000, DEF_STR( On ) )												
	PORT_DIPNAME( 0x2000, 0x0000, "Tape Sound")											
	PORT_DIPSETTING(	0x0000, DEF_STR( Off ) )											
	PORT_DIPSETTING(	0x2000, DEF_STR( On ) )												
	PORT_DIPNAME( 0x80, 0x00, "Sid Chip Type")											
	PORT_DIPSETTING(	0x00, "MOS6581" )													
	PORT_DIPSETTING(	0x80, "MOS8580" )													
	PORT_DIPNAME( 0x1c, 0x00, "Cartridge Type")												
	PORT_DIPSETTING(	0x00, "Automatic")													
	PORT_DIPSETTING(	0x04, "Ultimax (GAME)")												
	PORT_DIPSETTING(	0x08, "C64 (EXROM)")												
	PORT_BIT( 0x02, 0x00, IPT_UNUSED )	/* no serial bus */									
	PORT_BIT( 0x01, 0x00, IPT_UNUSED )
INPUT_PORTS_END



/***************************** Commodore 16 ****************************************
 *
 *	- C16 shares Keyboard with C64 (only few changes, see c16.c)
 *	- c16_special: input port for the Shift Lock Switch
 *	- c16_controls: control inputs
 *	- c16_config: control and devices configurations
 *
 **********************************************************************************/

/*

C16 Keyboard Layout
-------------------

                                                                                   INST
     ESC   1!   2"   3#   4$   5%   6&   7'   8(   9)   0^  LEFT RIGHT  UP  DOWN    DEL           f 1
  
                                                                                  CLEAR
      CTRL   Q    W    E    R    T     Y    U    I    O    P    @    +     -      HOME            f 3
  
  RUN   SHIFT
  STOP  LOCK   A    S    D    F     G     H    J    K    L   :[   ;]    *      RETURN             f 5
  
  
  C=    SHIFT     Z    X    C    V    B     N    M    ,<   .>   /?   SHIFT     �     =           HELP
  
  
                                 SPACEBAR


Notes: "C=" is a key with the Commodore logo, Shift+0 produces an arrow pointing up (''^'' above). 

C116 Keyboard Layout
--------------------

           F1/F4      F2/F5     F3/F6    HELP/F7     HOME/CLEAR   DEL/INST
  
  
     ESC   1!   2"   3#   4$   5%   6&   7'   8(   9)   0^   +    -     * 
  
                                                                                  
   CONTROL   Q    W    E    R    T     Y    U    I    O    P    @   RETURN
  
  RUN   
  STOP    �    A    S    D    F     G     H    J    K    L   :[   ;]    =
  
  
  C=    SHIFT     Z    X    C    V    B     N    M    ,<   .>   /?   SHIFT
                                                                                    UP  
																		     LEFT       RIGHT
                                 SPACEBAR                                          DOWN


Plus/4 (also 232/264/364 proto)
-----------------------------------

           F1/F4      F2/F5     F3/F6    HELP/F7
  
                                                                            CLEAR   INST
     ESC   1!   2"   3#   4$   5%   6&   7'   8(   9)   0^   +    -     =    HOME    DEL        ||      @  +  -  =
                                                                                                ||
                                                                                                ||
   CONTROL   Q    W    E    R    T     Y    U    I    O    P    @    �     *    CONTROL         ||      7  8  9  *
                                                                                                ||
  RUN   SHIFT                                                                                   ||
  STOP  LOCK   A    S    D    F     G     H    J    K    L   :[   ;]    RETURN                  ||      4  5  6  /
                                                                                                ||
                                                                                                ||               E
  C=    SHIFT     Z    X    C    V    B     N    M    ,<   .>   /?   SHIFT                      ||      1  2  3  n
                                                                                UP              ||               t
                                                                          LEFT       RIGHT      ||               e
                                 SPACEBAR                                      DOWN             ||      0  .  :  r

The 19-keys keypad on the left was present only in the 364 prototype (but probably those 
keys were simply wired to the lines of regular number keys of the keyboard).

*/

INPUT_PORTS_START( c16_special )
	PORT_START("SPECIAL")																
	PORT_BIT( 0x80, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_NAME("Shift Lock (switch)") PORT_CODE(KEYCODE_CAPSLOCK) PORT_TOGGLE
	PORT_DIPNAME( 0x40, 0x00, "Swap Gameport 1 and 2") PORT_CODE(KEYCODE_NUMLOCK)			
	PORT_DIPSETTING(	0x00, DEF_STR( No ) )												
	PORT_DIPSETTING(	0x40, DEF_STR( Yes ) )
INPUT_PORTS_END


INPUT_PORTS_START( c16_controls )
	PORT_START("JOY0") 
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_JOYSTICK_UP)	PORT_8WAY 
	PORT_BIT( 0x02, IP_ACTIVE_HIGH, IPT_JOYSTICK_DOWN)	PORT_8WAY 
	PORT_BIT( 0x04, IP_ACTIVE_HIGH, IPT_JOYSTICK_LEFT)	PORT_8WAY 
	PORT_BIT( 0x08, IP_ACTIVE_HIGH, IPT_JOYSTICK_RIGHT) PORT_8WAY 
	PORT_BIT( 0x10, IP_ACTIVE_HIGH, IPT_BUTTON1) 

	PORT_START("JOY1") 
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_JOYSTICK_UP)	PORT_NAME("P2 Up") PORT_CODE(KEYCODE_HOME) PORT_CODE(JOYCODE_Y_UP_SWITCH) PORT_8WAY PORT_PLAYER(2) 
	PORT_BIT( 0x02, IP_ACTIVE_HIGH, IPT_JOYSTICK_DOWN)	PORT_NAME("P2 Down") PORT_CODE(KEYCODE_END) PORT_CODE(JOYCODE_Y_DOWN_SWITCH) PORT_8WAY PORT_PLAYER(2) 
	PORT_BIT( 0x04, IP_ACTIVE_HIGH, IPT_JOYSTICK_LEFT)	PORT_NAME("P2 Left") PORT_CODE(KEYCODE_DEL) PORT_CODE(JOYCODE_X_LEFT_SWITCH ) PORT_8WAY PORT_PLAYER(2) 
	PORT_BIT( 0x08, IP_ACTIVE_HIGH, IPT_JOYSTICK_RIGHT)	PORT_NAME("P2 Right") PORT_CODE(KEYCODE_PGDN) PORT_CODE(JOYCODE_X_RIGHT_SWITCH ) PORT_8WAY PORT_PLAYER(2) 
	PORT_BIT( 0x10, IP_ACTIVE_HIGH, IPT_BUTTON1)		PORT_NAME("P2 Button") PORT_CODE(KEYCODE_LALT) PORT_CODE(JOYCODE_BUTTON1 ) PORT_PLAYER(2) 
INPUT_PORTS_END


INPUT_PORTS_START( c16_config )
	PORT_START("DSW0")
	PORT_DIPNAME( 0x80, 0x80, "Joystick 1")			
	PORT_DIPSETTING(	0x00, DEF_STR( Off ) )		
	PORT_DIPSETTING(	0x80, DEF_STR( On ) )		
	PORT_DIPNAME( 0x40, 0x40, "Joystick 2")			
	PORT_DIPSETTING(	0x00, DEF_STR( Off ) )		
	PORT_DIPSETTING(	0x40, DEF_STR( On ) )		
	PORT_DIPNAME( 0x20, 0x20, "Tape Drive / Device 1")
	PORT_DIPSETTING(	0x00, DEF_STR( Off ) )		
	PORT_DIPSETTING(	0x20, DEF_STR( On ) )		
	PORT_DIPNAME( 0x10, 0x00, "Tape Sound")			
	PORT_DIPSETTING(	0x00, DEF_STR( Off ) )		
	PORT_DIPSETTING(	0x10, DEF_STR( On ) )		

	PORT_START("CFG0")
	PORT_BIT( 0xc0, 0x00, IPT_UNUSED )								
	PORT_DIPNAME( 0x38, 0x08, "Device 8")							
	PORT_DIPSETTING(	0x00, DEF_STR( None ) )						
	PORT_DIPSETTING(	0x08, "C1551 Floppy Drive Simulation" )		
	PORT_DIPSETTING(	0x18, "Serial Bus / VC1541 Floppy Drive Simulation" )
	PORT_DIPNAME( 0x07, 0x01, "Device 9")							
	PORT_DIPSETTING(	0x00, DEF_STR( None ) )						
	PORT_DIPSETTING(	0x01, "C1551 Floppy Drive Simulation" )		
	PORT_DIPSETTING(	0x03, "Serial Bus / VC1541 Floppy Drive Simulation" )

	PORT_START("CFG1")
	PORT_DIPNAME( 0x80, 0x80, "Sidcard")					
	PORT_DIPSETTING(	0x00, DEF_STR( Off ) )				
	PORT_DIPSETTING(	0x80, DEF_STR( On ) )				
	PORT_BIT( 0x40, 0x00, IPT_UNUSED )			/* 2008-05 FP: removed the SID card hack cfg */
	PORT_BIT( 0x10, 0x00, IPT_UNUSED )			/* pal */	
	PORT_BIT( 0x0c, 0x00, IPT_UNUSED )			/* c16 */
INPUT_PORTS_END


/***************************** Commodore 128 ***************************************
 *
 *	- C128 shares Controls and Keyboard with C64 (+ a keypad, see c128.c)
 *	- c128_special: input port for the Restore key and the Shift Lock, 
 *			TV/RGBI and 40/80 columns switches
 *	- c128_config: memory and devices configurations
 *
 **********************************************************************************/

/*

C128 Keyboard Layout
--------------------


                    CAPS                 LINE   40/80    NO
     ESC  TAB  ALT  LOCK           HELP  FEED  DISPLAY SCROLL      UP  DOWN  LEFT  RIGHT          F1  F3  F5  F7
  
                                                                             CLR    INST
      <-   1!   2"   3#   4$   5%   6&   7'   8(   9)   0     +    -    �    HOME   DEL           7   8   9   +
  
   
   CONTROL   Q    W    E    R    T     Y    U    I    O    P    @    *     UP    RESTORE          4   5   6   -
  
  RUN   SHIFT                                                                                                 E
  STOP  LOCK   A    S    D    F     G     H    J    K    L   :[   ;]    =      RETURN             1   2   3   n
                                                                                                              t
                                                                             CRSR  CRSR                       e
  C=    SHIFT     Z    X    C    V    B     N    M    ,<   .>   /?   SHIFT   U/D    L/R             0     .   r
  
  
                                   SPACEBAR

Notes: "C=" is a key with the Commodore logo, "UP" is an arrow pointing up, the "CRSR" keys at the bottom-right 
corner are used to move the cursor on screen (Up/Down and Left/Right resp.).  

*/

INPUT_PORTS_START( c128_special )
	PORT_START( "SPECIAL" )  /* special keys */	
    PORT_BIT( 0x80, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_NAME("Restore") PORT_CODE(KEYCODE_PRTSCR)	
	PORT_BIT( 0x40, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_NAME("Shift Lock (switch)") PORT_CODE(KEYCODE_CAPSLOCK) PORT_TOGGLE PORT_CHAR(UCHAR_MAMEKEY(CAPSLOCK))
//	PORT_DIPNAME( 0x40, 0x00, "Shift Lock (switch)") PORT_CODE(KEYCODE_CAPSLOCK)			
//	PORT_DIPSETTING(	0x00, DEF_STR( Off ) )														
//	PORT_DIPSETTING(	0x40, DEF_STR( On ) )														
	PORT_DIPNAME( 0x20, 0x00, "Caps Lock (switch)")													
	PORT_DIPSETTING(	0x00, DEF_STR( Off ) )														
	PORT_DIPSETTING(	0x20, DEF_STR( On ) )														
	PORT_DIPNAME( 0x10, 0x10, "40 80 Display (switch) (active after a rebooting)")					
	PORT_DIPSETTING(	0x00, "40 Columns (DIN/TV)")												
	PORT_DIPSETTING(	0x10, "80 Columns (RGBI)")
INPUT_PORTS_END


INPUT_PORTS_START( c128_config )
	PORT_START("CFG") 
	PORT_DIPNAME( 0x4000, 0x4000, "Tape Drive / Device 1")									
	PORT_DIPSETTING(	0x0000, DEF_STR( Off ) )											
	PORT_DIPSETTING(	0x4000, DEF_STR( On ) )												
	PORT_DIPNAME( 0x2000, 0x00, "Tape Sound")												
	PORT_DIPSETTING(	0x0000, DEF_STR( Off ) )											
	PORT_DIPSETTING(	0x2000, DEF_STR( On ) )												
	PORT_DIPNAME( 0x0300, 0x0000, "Main Memory / MMU Version")								
	PORT_DIPSETTING(	0x0000, "128 KByte" )												
	PORT_DIPSETTING(	0x0100, "256 KByte" )												
	PORT_DIPSETTING(	0x0200, "1024 KByte" )												
	PORT_DIPNAME( 0x80, 0x80, "Sid Chip Type")												
	PORT_DIPSETTING(	0x00, "MOS6581" )													
	PORT_DIPSETTING(	0x80, "MOS8580" )													
	PORT_DIPNAME( 0x40, 0x40, "VDC Memory (RGBI)")											
	PORT_DIPSETTING(	0x00, "16 KByte" )													
	PORT_DIPSETTING(	0x40, "64 KByte" )													
	PORT_DIPNAME( 0x20, 0x20, "DIN,TV / RGBI Monitor (switch)") PORT_CODE(KEYCODE_ENTER_PAD)
	PORT_DIPSETTING(	0x00, "DIN,TV" )													
	PORT_DIPSETTING(	0x20, "RGBI" )														
	PORT_DIPNAME( 0x1c, 0x00, "Cartridge Type")												
	PORT_DIPSETTING(	0x00, "Automatic")													
	PORT_DIPSETTING(	0x04, "Ultimax (GAME)")												
	PORT_DIPSETTING(	0x08, "C64 (EXROM)")												
	PORT_BIT( 0x02, 0x00, IPT_UNUSED )	/* no serial bus */									
	PORT_BIT( 0x01, 0x00, IPT_UNUSED )
INPUT_PORTS_END


/***************************** Commodore 65 ****************************************
 *
 *	- C65 shares Keyboard and Inputs with C64 (+ some function keys, see c65.c)
 *	- c65_special: input port for the Restore key and the Shift Lock and DIN 
 *			switches
 *	- c65_config: devices configurations
 *
 **********************************************************************************/

/*

C65 Keyboard Layout
-------------------

    RUN                  CAPS    NO
    STOP       ESC  ALT  LOCK  SCROLL    F1   F3   F5   F7        F9    F11   F13   HELP
  
                                                                             CLR    INST
      <-   1!   2"   3#   4$   5%   6&   7'   8(   9)   0     +    -    �    HOME   DEL 
  
   
   TAB       Q    W    E    R    T     Y    U    I    O    P    @    *     UP    RESTORE
  
        SHIFT
  CTRL  LOCK   A    S    D    F     G     H    J    K    L   :[   ;]    =      RETURN


  C=    SHIFT     Z    X    C    V    B     N    M    ,<   .>   /?   SHIFT   UP
  
  
                                   SPACEBAR                           LEFT  DOWN  RIGHT

Notes: "C=" is a key with the Commodore logo, "UP" is an arrow pointing up.

*/
INPUT_PORTS_START( c65_special )
	PORT_START( "SPECIAL" )  /* special keys */	
    PORT_BIT( 0x80, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_NAME("Restore") PORT_CODE(KEYCODE_PRTSCR)	
	PORT_BIT( 0x40, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_NAME("Shift Lock (switch)") PORT_CODE(KEYCODE_CAPSLOCK) PORT_TOGGLE PORT_CHAR(UCHAR_MAMEKEY(CAPSLOCK))
	PORT_DIPNAME( 0x20, 0x00, "(C65) Caps Lock (switch)") PORT_CODE(KEYCODE_F3)						
	PORT_DIPSETTING(	0x00, DEF_STR( Off ) )														
	PORT_DIPSETTING(	0x20, DEF_STR( On ) )														
	PORT_BIT( 0x10, IP_ACTIVE_HIGH, IPT_UNUSED )	
INPUT_PORTS_END


INPUT_PORTS_START( c65_config )
	PORT_START( "CFG" )
	PORT_BIT( 0x8000, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_NAME("Quickload") PORT_CODE(KEYCODE_SLASH_PAD)
	PORT_BIT( 0x7c00, 0x0, IPT_UNUSED )	/* no tape */										
	PORT_DIPNAME( 0x80, 0x00, "Sid Chip Type")											
	PORT_DIPSETTING(	0x00, "MOS6581" )													
	PORT_DIPSETTING(	0x80, "MOS8580" )													
	PORT_BIT( 0x1c, 0x00, IPT_UNUSED )	/* no cart type ever supported */					
	PORT_DIPNAME( 0x02, 0x02, "Serial Bus/Device 10")										
	PORT_DIPSETTING(	0x00, DEF_STR( None ))
	PORT_DIPSETTING(	0x02, "Floppy Drive Simulation")									
	PORT_DIPNAME( 0x01, 0x01, "Serial Bus/Device 11")										
	PORT_DIPSETTING(	0x00, DEF_STR( None ))
	PORT_DIPSETTING(	0x01, "Floppy Drive Simulation")
INPUT_PORTS_END


/***************************** Commodore Pet ***************************************
 *
 *	- pet_keyboard: original keyboard used by PET2001
 *	- pet_business_keyboard: business keyboard is used by the other computers 
 *			in pet.c
 *	- pet_special: input port for the Shift Lock Switch
 *	- pet_config: memory and serial port configurations
 *
 **********************************************************************************/

/*

PET Keyboard Layout
-------------------

                                                                                CLR CRSR CRSR INST
  @    !    "    #    $    %    '    &    \    (    )    <-    [    ]          HOME  U/D  L/R  DEL
  
 RVS
 OFF     Q    W    E    R    T     Y    U    I    O    P    UP   <    >          7    8    9    /

  SHIFT                                                      STOP
  LOCK     A    S    D    F     G     H    J    K    L   :   RUN  RETURN         4    5    6    *
  
  																				
   SHIFT     Z    X    C    V    B     N    M     ,    ;   ?    SHIFT            1    2    3    +
  
  
                                 SPACEBAR                                        0    .    -    =


The PET Keypad has 16 keys, making impossible to map it in a satisfactory way to a PC keypad. 
Therefore, default settings for these keys in Full Emulation are currently based on the effect 
of the key and not on their real position


PET Business Keyboard Layout
----------------------------

                                                                           CRSR  STOP
    <-   1!   2"   3#   4$   5%   6&   7'   8(   9)   0     :*   -=   UP    L/R   RUN           7   8   9

                                                                        CRSR    DEL
    TAB    Q    W    E    R    T     Y    U    I    O    P    [    \    U/D    INST             4   5   6

	 SHIFT
ESC   LOCK   A    S    D    F     G     H    J    K    L   ;+    @     ]      RETURN            1   2   3

RVS                                                                                HOME
OFF   SHIFT     Z    X    C    V    B     N    M    ,<   .>   /?   SHIFT   REPEAT   CLR           0     .


                                   SPACEBAR

*/

INPUT_PORTS_START( pet_keyboard )
	PORT_START( "ROW0" )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_NAME("Crsr Right Left") PORT_CODE(KEYCODE_PGDN) PORT_CHAR(UCHAR_MAMEKEY(RIGHT)) PORT_CHAR(UCHAR_MAMEKEY(LEFT))
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_NAME("Home  Clr Screen") PORT_CODE(KEYCODE_HOME) PORT_CHAR(UCHAR_MAMEKEY(HOME)) 
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_NAME("\xE2\x86\x90") PORT_CODE(KEYCODE_MINUS) PORT_CHAR(0x2190)
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_9)			PORT_CHAR('(')
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_7)			PORT_CHAR('&')
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_5)			PORT_CHAR('%')
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_3)			PORT_CHAR('#')
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_1)			PORT_CHAR('!')

	PORT_START( "ROW1" )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_NAME("Del  Inst") PORT_CODE(KEYCODE_DEL) PORT_CHAR(8) PORT_CHAR(UCHAR_MAMEKEY(INSERT))
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_NAME("Crsr Down Up") PORT_CODE(KEYCODE_PGUP) PORT_CHAR(UCHAR_MAMEKEY(DOWN)) PORT_CHAR(UCHAR_MAMEKEY(UP))	
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_0)			PORT_CHAR(')')
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_8)			PORT_CHAR('\\')
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_6)			PORT_CHAR('\'')
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_4)			PORT_CHAR('$')
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_2)			PORT_CHAR('"')

	PORT_START( "ROW2" )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_9_PAD)		PORT_CHAR('9')
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_7_PAD)		PORT_CHAR('7')
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_NAME("\xE2\x86\x91 Pi") PORT_CODE(KEYCODE_OPENBRACE) PORT_CHAR(0x2191) PORT_CHAR(0x03C0)
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_O)			PORT_CHAR('O')	
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_U)			PORT_CHAR('U')	
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_T)			PORT_CHAR('T')	
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_E)			PORT_CHAR('E')	
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_Q)			PORT_CHAR('Q')	

	PORT_START( "ROW3" )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_SLASH_PAD)	PORT_CHAR('/') 
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_8_PAD)		PORT_CHAR('8')
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_P)			PORT_CHAR('P')	
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_I)			PORT_CHAR('I')	
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_Y)			PORT_CHAR('Y')	
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_R)			PORT_CHAR('R')	
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_W)			PORT_CHAR('W')	

	PORT_START( "ROW4" )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_6_PAD)		PORT_CHAR('6')
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_4_PAD)		PORT_CHAR('4')
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_L)			PORT_CHAR('L')	
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_J)			PORT_CHAR('J')	
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_G)			PORT_CHAR('G')	
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_D)			PORT_CHAR('D')	
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_A)			PORT_CHAR('A')	

	PORT_START( "ROW5" )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_ASTERISK)	PORT_CHAR('*') 
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_5_PAD)		PORT_CHAR('5')
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_COLON)		PORT_CHAR(':')	
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_K)			PORT_CHAR('K')	
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_H)			PORT_CHAR('H')	
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_F)			PORT_CHAR('F')	
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_S)			PORT_CHAR('S')	

	PORT_START( "ROW6" )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_3_PAD)		PORT_CHAR('3')
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_1_PAD)		PORT_CHAR('1')
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_NAME("Return") PORT_CODE(KEYCODE_ENTER) PORT_CHAR(13)
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_STOP)		PORT_CHAR(';')	
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_M)			PORT_CHAR('M')	
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_B)			PORT_CHAR('B')	
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_C)			PORT_CHAR('C')	
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_Z)			PORT_CHAR('Z')	

	PORT_START( "ROW7" )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_PLUS_PAD)	PORT_CHAR('+') 
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_2_PAD)		PORT_CHAR('2')
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_SLASH)		PORT_CHAR('?')	
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_COMMA)		PORT_CHAR(',')	
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_N)			PORT_CHAR('N')	
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_V)			PORT_CHAR('V')	
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_X)			PORT_CHAR('X')	

	PORT_START( "ROW8" )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_MINUS_PAD)	PORT_CHAR('-')
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_0_PAD)		PORT_CHAR('0')
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_NAME("Shift (Right)") PORT_CODE(KEYCODE_RSHIFT) PORT_CHAR(UCHAR_SHIFT_1) 
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_BACKSLASH)	PORT_CHAR('>')	
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_BACKSPACE)	PORT_CHAR(']')	
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_TILDE)		PORT_CHAR('@')	
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_NAME("Shift (Left)") PORT_CODE(KEYCODE_LSHIFT)

	PORT_START( "ROW9" )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_NAME("Keypad =") PORT_CODE(KEYCODE_ENTER_PAD) PORT_CHAR('=') 
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_DEL_PAD)	PORT_CHAR('.')
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_NAME("Stop Run") PORT_CODE(KEYCODE_QUOTE)
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_CLOSEBRACE)	PORT_CHAR('<')	
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_SPACE)		PORT_CHAR(' ')	
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_EQUALS)		PORT_CHAR('[')	
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_NAME("Rvs Off") PORT_CODE(KEYCODE_TAB)
INPUT_PORTS_END


INPUT_PORTS_START( pet_business_keyboard )
	PORT_START( "ROW0" )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_NAME("Crsr Right Left") PORT_CODE(KEYCODE_PGUP) PORT_CHAR(UCHAR_MAMEKEY(RIGHT)) PORT_CHAR(UCHAR_MAMEKEY(LEFT))
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_8_PAD)		PORT_CHAR(UCHAR_MAMEKEY(8_PAD)) 
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_EQUALS)		PORT_CHAR('-') PORT_CHAR('=')
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_8)			PORT_CHAR('8') PORT_CHAR('\\')
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_5)			PORT_CHAR('5') PORT_CHAR('%')
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_2)			PORT_CHAR('2') PORT_CHAR('"')

	PORT_START( "ROW1" )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_9_PAD)		PORT_CHAR(UCHAR_MAMEKEY(9_PAD)) 
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_NAME("\xE2\x86\x91") PORT_CODE(KEYCODE_BACKSPACE) PORT_CHAR(0x2191)
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_7_PAD)		PORT_CHAR(UCHAR_MAMEKEY(7_PAD)) 
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_0_PAD)		PORT_CHAR(UCHAR_MAMEKEY(0_PAD)) 
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_7)			PORT_CHAR('7') PORT_CHAR('&')
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_4)			PORT_CHAR('4') PORT_CHAR('$')
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_1)			PORT_CHAR('1') PORT_CHAR('!')

	PORT_START( "ROW2" )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_5_PAD)		PORT_CHAR(UCHAR_MAMEKEY(5_PAD)) 
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_COLON)		PORT_CHAR(';') PORT_CHAR('+')
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_K)			PORT_CHAR('K')	
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_BACKSLASH)	PORT_CHAR(']')	
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_H)			PORT_CHAR('H')	
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_F)			PORT_CHAR('F')	
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_S)			PORT_CHAR('S')	
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_ESC)		PORT_CHAR(UCHAR_MAMEKEY(ESC)) 

	PORT_START( "ROW3" )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_6_PAD)		PORT_CHAR(UCHAR_MAMEKEY(6_PAD)) 
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_QUOTE)		PORT_CHAR('@')	
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_L)			PORT_CHAR('L')	
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_NAME("Return") PORT_CODE(KEYCODE_ENTER) PORT_CHAR(13)
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_J)			PORT_CHAR('J')	
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_G)			PORT_CHAR('G')	
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_D)			PORT_CHAR('D')	
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_A)			PORT_CHAR('A')	

	PORT_START( "ROW4" )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_NAME("Del  Inst") PORT_CODE(KEYCODE_DEL) PORT_CHAR(8) PORT_CHAR(UCHAR_MAMEKEY(INSERT))
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_P)			PORT_CHAR('P')	
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_I)			PORT_CHAR('I')	
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_CLOSEBRACE)	PORT_CHAR('\\')	
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_Y)			PORT_CHAR('Y')	
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_R)			PORT_CHAR('R')	
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_W)			PORT_CHAR('W')	
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_TAB)		PORT_CHAR('\t')

	PORT_START( "ROW5" )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_4_PAD)		PORT_CHAR(UCHAR_MAMEKEY(4_PAD)) 
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_OPENBRACE)	PORT_CHAR('[')	
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_O)			PORT_CHAR('O')	
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_NAME("Crsr Down Up") PORT_CODE(KEYCODE_PGDN) PORT_CHAR(UCHAR_MAMEKEY(DOWN)) PORT_CHAR(UCHAR_MAMEKEY(UP))	
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_U)			PORT_CHAR('U')	
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_T)			PORT_CHAR('T')	
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_E)			PORT_CHAR('E')	
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_Q)			PORT_CHAR('Q')	

	PORT_START( "ROW6" )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_3_PAD)		PORT_CHAR(UCHAR_MAMEKEY(3_PAD)) 
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_NAME("Shift (Right)") PORT_CODE(KEYCODE_RSHIFT) PORT_CHAR(UCHAR_SHIFT_1) 
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_DEL_PAD)	PORT_CHAR(UCHAR_MAMEKEY(DEL_PAD)) 
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_STOP)		PORT_CHAR('.') PORT_CHAR('>')
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_B)			PORT_CHAR('B')	
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_C)			PORT_CHAR('C')	
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_NAME("Shift (Left)") PORT_CODE(KEYCODE_LSHIFT)

	PORT_START( "ROW7" )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_2_PAD)		PORT_CHAR(UCHAR_MAMEKEY(2_PAD)) 
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_NAME("Repeat") PORT_CODE(KEYCODE_LALT)
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_0)			PORT_CHAR('0') PORT_CHAR(')')
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_COMMA)		PORT_CHAR(',') PORT_CHAR('<')
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_N)			PORT_CHAR('N')	
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_V)			PORT_CHAR('V')	
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_Z)			PORT_CHAR('Z')	

	PORT_START( "ROW8" )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_1_PAD)		PORT_CHAR(UCHAR_MAMEKEY(1_PAD)) 
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_SLASH)		PORT_CHAR('/') PORT_CHAR('?')
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_NAME("Home  Clr Screen") PORT_CODE(KEYCODE_HOME) PORT_CHAR(UCHAR_MAMEKEY(HOME)) 
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_M)			PORT_CHAR('M')	
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_SPACE)		PORT_CHAR(' ')	
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_X)			PORT_CHAR('X')	
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_NAME("Rvs Off") PORT_CODE(KEYCODE_INSERT)

	PORT_START( "ROW9" )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_MINUS)		PORT_CHAR(':') PORT_CHAR('*')
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_NAME("Stop Run") PORT_CODE(KEYCODE_END)
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_9)			PORT_CHAR('9') PORT_CHAR('(')
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_6)			PORT_CHAR('6') PORT_CHAR('\'')
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_3)			PORT_CHAR('3') PORT_CHAR('#')
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_NAME("\xE2\x86\x90") PORT_CODE(KEYCODE_TILDE) PORT_CHAR(0x2190)
INPUT_PORTS_END


INPUT_PORTS_START( pet_special )
	PORT_START( "SPECIAL" )		/* Special keys */ 
	PORT_DIPNAME( 0x80, 0x00, "Shift Lock (switch)") PORT_CODE(KEYCODE_CAPSLOCK) PORT_TOGGLE
	PORT_DIPSETTING(0x00, DEF_STR( Off ) )				
	PORT_DIPSETTING(0x80, DEF_STR( On ) )
INPUT_PORTS_END


INPUT_PORTS_START( pet_config )
    PORT_START("CFG")
    PORT_BIT( 0x8000, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_NAME("Quickload") PORT_CODE(KEYCODE_F8)
	PORT_DIPNAME( 0x180, 0x180, "Memory")					
	PORT_DIPSETTING(	0x000, "4 KByte" )					
	PORT_DIPSETTING(	0x080, "8 KByte" )					
	PORT_DIPSETTING(	0x100, "16 KByte" )					
	PORT_DIPSETTING(	0x180, "32 KByte" )					
	PORT_BIT( 0x08, 0x00, IPT_UNUSED ) /* no 8096 hardware */	
	PORT_BIT( 0x04, 0x00, IPT_UNUSED ) /* no superpet switch */
	PORT_DIPNAME( 0x02, 0x02, "IEEE488 Bus/Dev 8/Floppy Sim")
	PORT_DIPSETTING(	0x00, DEF_STR( No ) )				
	PORT_DIPSETTING(	0x02, DEF_STR( Yes ) )				
	PORT_DIPNAME( 0x01, 0x00, "IEEE488 Bus/Dev 9/Floppy Sim")
	PORT_DIPSETTING(	0x00, DEF_STR( No ) )				
	PORT_DIPSETTING(	0x01, DEF_STR( Yes ) )
INPUT_PORTS_END



/***************************** Commodore CBMB **************************************
 *
 *	- CBMB machines share Controls (in particular Lightpen) with C64
 *	- cbmb_keyboard: Keyboard used by all the models of this series 
 *	- cbmb_special: input port for the Shift Lock Switch
 *
 **********************************************************************************/

/*

CBMB Series Keyboard Layout (based on a CBM 610 keyboard)
---------------------------------------------------------

     F1    F2   F3   F4   F5   F6   F7   F8   F9  F10      DOWN  UP  LEFT  RIGHT     HOME/CLEAR   DEL/INST
  
                                                                            INS  
     ESC   1!   2"   3#   4$   5%   6^   7&   8*   9(   0)   -   =+   <-�   DEL          ?   CE    .    /
  
                                                                         ________   
     TAB     Q    W    E    R    T     Y    U    I    O    P    [    ]  | RETURN |       7    8    9    -
                                                                        |__      |
	  SHIFT                                                                |     |
	  LOCK     A    S    D    F     G     H    J    K    L   ;:   '"   Pi  |     |       4    5    6    +
																		   |_____|
                                                                                                        E
        SHIFT     Z    X    C    V    B     N    M    ,<   .>   /?   SHIFT   C=          1    2    3    n
                                                                                                        t
																		                                e
              CTRL               SPACEBAR                                              0      .    00   r


Notes: "C=" is a key with the Commodore logo, Shift+6 produces an arrow pointing up (''^'' above). 


*/

INPUT_PORTS_START( cbmb_keyboard )
	PORT_START("ROW0")
	PORT_BIT( 0x80, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_NAME("Stop  Run") PORT_CODE(KEYCODE_DEL)
	PORT_BIT( 0x40, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_NAME("RVS Off") PORT_CODE(KEYCODE_HOME)
	PORT_BIT( 0x20, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_NAME("Graph  Norm") PORT_CODE(KEYCODE_PGUP)
	PORT_BIT( 0x10, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_NAME("Home  Clr") PORT_CODE(KEYCODE_INSERT) PORT_CHAR(UCHAR_MAMEKEY(HOME))
	PORT_BIT( 0x08, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_UP)			PORT_CHAR(UCHAR_MAMEKEY(UP)) 
	PORT_BIT( 0x04, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_DOWN)			PORT_CHAR(UCHAR_MAMEKEY(DOWN)) 
	PORT_BIT( 0x02, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_F10)			PORT_CHAR(UCHAR_MAMEKEY(F10))
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_F9)			PORT_CHAR(UCHAR_MAMEKEY(F9))

	PORT_START("ROW1")
	PORT_BIT( 0x80, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_F8)			PORT_CHAR(UCHAR_MAMEKEY(F8))
	PORT_BIT( 0x40, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_F7)			PORT_CHAR(UCHAR_MAMEKEY(F7))
	PORT_BIT( 0x20, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_F6)			PORT_CHAR(UCHAR_MAMEKEY(F6))
	PORT_BIT( 0x10, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_F5)			PORT_CHAR(UCHAR_MAMEKEY(F5))
	PORT_BIT( 0x08, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_F4)			PORT_CHAR(UCHAR_MAMEKEY(F4))
	PORT_BIT( 0x04, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_F3)			PORT_CHAR(UCHAR_MAMEKEY(F3))
	PORT_BIT( 0x02, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_F2)			PORT_CHAR(UCHAR_MAMEKEY(F2))
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_F1)			PORT_CHAR(UCHAR_MAMEKEY(F1))

	PORT_START("ROW2")
	PORT_BIT( 0x80, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_ASTERISK)		PORT_CHAR(UCHAR_MAMEKEY(SLASH_PAD)) 
	PORT_BIT( 0x40, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_SLASH_PAD)		PORT_CHAR(UCHAR_MAMEKEY(ASTERISK)) 
	PORT_BIT( 0x20, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_NAME("Keypad CE") PORT_CODE(KEYCODE_NUMLOCK)
	PORT_BIT( 0x10, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_NAME("Keypad ?") PORT_CODE(KEYCODE_END)
	PORT_BIT( 0x08, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_LEFT)			PORT_CHAR(UCHAR_MAMEKEY(LEFT)) 
	PORT_BIT( 0x04, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_EQUALS)		PORT_CHAR('=') PORT_CHAR('+')
	PORT_BIT( 0x02, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_0)				PORT_CHAR('0') PORT_CHAR(')')
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_9)				PORT_CHAR('9') PORT_CHAR('(')

	PORT_START("ROW3")
	PORT_BIT( 0x80, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_8)				PORT_CHAR('8') PORT_CHAR('*')
	PORT_BIT( 0x40, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_7)				PORT_CHAR('7') PORT_CHAR('&')
	PORT_BIT( 0x20, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_5)				PORT_CHAR('5') PORT_CHAR('%')
	PORT_BIT( 0x10, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_4)				PORT_CHAR('4') PORT_CHAR('$')
	PORT_BIT( 0x08, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_3)				PORT_CHAR('3') PORT_CHAR('#')
	PORT_BIT( 0x04, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_2)				PORT_CHAR('2') PORT_CHAR('@')
	PORT_BIT( 0x02, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_1)				PORT_CHAR('1') PORT_CHAR('!')
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_ESC)			PORT_CHAR(UCHAR_MAMEKEY(ESC))

	PORT_START("ROW4")
	PORT_BIT( 0x80, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_MINUS_PAD)		PORT_CHAR(UCHAR_MAMEKEY(MINUS_PAD)) 
	PORT_BIT( 0x40, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_9_PAD)			PORT_CHAR(UCHAR_MAMEKEY(9_PAD)) 
	PORT_BIT( 0x20, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_8_PAD)			PORT_CHAR(UCHAR_MAMEKEY(8_PAD)) 
	PORT_BIT( 0x10, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_7_PAD)			PORT_CHAR(UCHAR_MAMEKEY(7_PAD)) 
	PORT_BIT( 0x08, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_RIGHT)			PORT_CHAR(UCHAR_MAMEKEY(RIGHT)) 
	PORT_BIT( 0x04, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_NAME("\xE2\x86\x90  \xC2\xA3") PORT_CODE(KEYCODE_TILDE) PORT_CHAR(0x2190) PORT_CHAR('\xA3')
	PORT_BIT( 0x02, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_MINUS)			PORT_CHAR('-')
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_O)				PORT_CHAR('o') PORT_CHAR('O')

	PORT_START("ROW5")
	PORT_BIT( 0x80, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_I)				PORT_CHAR('i') PORT_CHAR('I')
	PORT_BIT( 0x40, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_U)				PORT_CHAR('u') PORT_CHAR('U')
	PORT_BIT( 0x20, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_NAME("6  \xE2\x86\x91") PORT_CODE(KEYCODE_6) PORT_CHAR('6') PORT_CHAR(0x2191)
	PORT_BIT( 0x10, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_R)				PORT_CHAR('r') PORT_CHAR('R')
	PORT_BIT( 0x08, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_E)				PORT_CHAR('e') PORT_CHAR('E')
	PORT_BIT( 0x04, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_W)				PORT_CHAR('w') PORT_CHAR('W')
	PORT_BIT( 0x02, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_Q)				PORT_CHAR('q') PORT_CHAR('Q')
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_TAB)			PORT_CHAR('\t')

	PORT_START("ROW6")
	PORT_BIT( 0x80, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_PLUS_PAD)		PORT_CHAR(UCHAR_MAMEKEY(PLUS_PAD)) 
	PORT_BIT( 0x40, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_6_PAD)			PORT_CHAR(UCHAR_MAMEKEY(6_PAD)) 
	PORT_BIT( 0x20, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_5_PAD)			PORT_CHAR(UCHAR_MAMEKEY(5_PAD)) 
	PORT_BIT( 0x10, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_4_PAD)			PORT_CHAR(UCHAR_MAMEKEY(4_PAD)) 
	PORT_BIT( 0x08, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_NAME("Del  Ins") PORT_CODE(KEYCODE_BACKSPACE)	PORT_CHAR(8) PORT_CHAR(UCHAR_MAMEKEY(INSERT))
	PORT_BIT( 0x04, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_CLOSEBRACE)	PORT_CHAR(']')
	PORT_BIT( 0x02, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_P)				PORT_CHAR('p') PORT_CHAR('P')
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_L)				PORT_CHAR('l') PORT_CHAR('L')

	PORT_START("ROW7")
	PORT_BIT( 0x80, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_K)				PORT_CHAR('k') PORT_CHAR('K')
	PORT_BIT( 0x40, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_J)				PORT_CHAR('j') PORT_CHAR('J')
	PORT_BIT( 0x20, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_Y)				PORT_CHAR('y') PORT_CHAR('Y')
	PORT_BIT( 0x10, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_T)				PORT_CHAR('t') PORT_CHAR('T')
	PORT_BIT( 0x08, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_D)				PORT_CHAR('d') PORT_CHAR('D')
	PORT_BIT( 0x04, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_S)				PORT_CHAR('s') PORT_CHAR('S')
	PORT_BIT( 0x02, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_A)				PORT_CHAR('a') PORT_CHAR('A')
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_UNUSED )

	PORT_START("ROW8")
	PORT_BIT( 0x80, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_ENTER_PAD)		PORT_CHAR(UCHAR_MAMEKEY(ENTER_PAD)) 
	PORT_BIT( 0x40, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_3_PAD)			PORT_CHAR(UCHAR_MAMEKEY(3_PAD)) 
	PORT_BIT( 0x20, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_2_PAD)			PORT_CHAR(UCHAR_MAMEKEY(2_PAD)) 
	PORT_BIT( 0x10, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_1_PAD)			PORT_CHAR(UCHAR_MAMEKEY(1_PAD)) 
	PORT_BIT( 0x08, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_NAME("CBM") PORT_CODE(KEYCODE_RALT) PORT_CHAR(UCHAR_MAMEKEY(RALT))
	PORT_BIT( 0x04, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_NAME("Return") PORT_CODE(KEYCODE_ENTER) PORT_CHAR(13)
	PORT_BIT( 0x02, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_OPENBRACE)		PORT_CHAR('[')
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_COLON)			PORT_CHAR(';') PORT_CHAR(':')

	PORT_START("ROW9")
	PORT_BIT( 0x80, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_COMMA)			PORT_CHAR(',') PORT_CHAR('<')
	PORT_BIT( 0x40, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_M)				PORT_CHAR('m') PORT_CHAR('M')
	PORT_BIT( 0x20, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_H)				PORT_CHAR('h') PORT_CHAR('H')
	PORT_BIT( 0x10, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_G)				PORT_CHAR('g') PORT_CHAR('G')
	PORT_BIT( 0x08, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_F)				PORT_CHAR('f') PORT_CHAR('F')
	PORT_BIT( 0x04, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_X)				PORT_CHAR('x') PORT_CHAR('X')
	PORT_BIT( 0x02, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_Z)				PORT_CHAR('z') PORT_CHAR('Z')
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_LSHIFT) PORT_CODE(KEYCODE_RSHIFT) PORT_CHAR(UCHAR_SHIFT_1)

	PORT_START("ROW10")	
	PORT_BIT( 0x80, IP_ACTIVE_HIGH, IPT_UNUSED )
	PORT_BIT( 0x40, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_NAME("Keypad 00") PORT_CODE(KEYCODE_PGDN)
	PORT_BIT( 0x20, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_DEL_PAD)		PORT_CHAR(UCHAR_MAMEKEY(DEL_PAD)) 
	PORT_BIT( 0x10, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_0_PAD)			PORT_CHAR(UCHAR_MAMEKEY(0_PAD)) 
	PORT_BIT( 0x08, IP_ACTIVE_HIGH, IPT_UNUSED )
	PORT_BIT( 0x04, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_NAME("Pi") PORT_CODE(KEYCODE_BACKSLASH) PORT_CHAR(0x03C0)
	PORT_BIT( 0x02, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_QUOTE)			PORT_CHAR('\'') PORT_CHAR('"')
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_SLASH)			PORT_CHAR('/') PORT_CHAR('?')

	PORT_START("ROW11")	
	PORT_BIT( 0x80, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_STOP)			PORT_CHAR('.') PORT_CHAR('>')
	PORT_BIT( 0x40, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_SPACE)			PORT_CHAR(' ')
	PORT_BIT( 0x20, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_N)				PORT_CHAR('n') PORT_CHAR('N')
	PORT_BIT( 0x10, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_B)				PORT_CHAR('b') PORT_CHAR('B')
	PORT_BIT( 0x08, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_V)				PORT_CHAR('v') PORT_CHAR('V')
	PORT_BIT( 0x04, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_C)				PORT_CHAR('c') PORT_CHAR('C')
	PORT_BIT( 0x02, IP_ACTIVE_HIGH, IPT_UNUSED )
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_CODE(KEYCODE_LCONTROL) PORT_CHAR(UCHAR_SHIFT_2)
INPUT_PORTS_END


INPUT_PORTS_START( cbmb_special )
	PORT_START("SPECIAL")
	PORT_BIT( 0x8000, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_NAME("Quickload") PORT_CODE(KEYCODE_F8) 
	PORT_BIT( 0x200, 0x200, IPT_UNUSED ) /* ntsc */		
	PORT_BIT( 0x100, 0x000, IPT_UNUSED ) /* cbm600 */	
	PORT_DIPNAME( 0x04, 0x00, "Shift Lock (switch)") PORT_CODE(KEYCODE_CAPSLOCK) PORT_TOGGLE
	PORT_DIPSETTING(	0x00, DEF_STR( Off ) )			
	PORT_DIPSETTING(	0x04, DEF_STR( On ) )			
INPUT_PORTS_END


 /***************************** Commodore Vic 20 ***********************************
 *
 *	- vic_keyboard: basic Vic 20 keyboard
 *  - vic_special: input port for the Shift Lock Switch
 *	- vic_controls: joypads and paddles
 *	- vic_expansion: RAM expansions
 *	- vic_config: controllers, tape and serial configurations
 *	- VIC20 also has 2 lightpen ports, vic_lightpen_6560 & vic_lightpen_6561
 *			currently in vc20.c (they need visible area parameters for centering)
 *
 **********************************************************************************/

/*

VIC20 Keyboard Layout
---------------------

                                                                           CLR    INST
    <-   1!   2"   3#   4$   5%   6&   7'   8(   9)   0     +    -    �    HOME   DEL           f 1

 
    CTRL   Q    W    E    R    T     Y    U    I    O    P    @    *     UP    RESTORE          f 3

RUN   SHIFT
STOP  LOCK   A    S    D    F     G     H    J    K    L   :[   ;]    =      RETURN             f 5

                                                                           CRSR  CRSR
C=    SHIFT     Z    X    C    V    B     N    M    ,<   .>   /?   SHIFT   U/D    L/R           f 7


                                 SPACEBAR


Notes: �C=� is a key with the Commodore logo, �UP� is an arrow pointing up, the �CRSR� keys at the 
bottom-right corner are used to move the cursor on screen (Up/Down and Left/Right respectively).
Notice that this is exactly the same layout of C64 keyboard.
 
*/

INPUT_PORTS_START( vic_keyboard )
	PORT_START( "ROW0" )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_NAME("Del  Inst") PORT_CODE(KEYCODE_BACKSPACE) PORT_CHAR(8) PORT_CHAR(UCHAR_MAMEKEY(INSERT))
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_BACKSLASH2)		PORT_CHAR('\xA3')	
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_MINUS)			PORT_CHAR('+')
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_9)				PORT_CHAR('9') PORT_CHAR(')')	
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_7)				PORT_CHAR('7') PORT_CHAR('\'')	
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_5)				PORT_CHAR('5') PORT_CHAR('%')	
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_3)				PORT_CHAR('3') PORT_CHAR('#')	
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_1)				PORT_CHAR('1') PORT_CHAR('!')	

	PORT_START( "ROW1" )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_NAME("Return") PORT_CODE(KEYCODE_ENTER) PORT_CHAR(13)
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_CLOSEBRACE)		PORT_CHAR('*')	
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_P)				PORT_CHAR('P')	
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_I)				PORT_CHAR('I')	
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_Y)				PORT_CHAR('Y')	
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_R)				PORT_CHAR('R')	
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_W)				PORT_CHAR('W')	
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_NAME("\xE2\x86\x90") PORT_CODE(KEYCODE_TILDE) PORT_CHAR(0x2190)

	PORT_START( "ROW2" )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_NAME("Crsr Right Left") PORT_CODE(KEYCODE_RCONTROL) PORT_CHAR(UCHAR_MAMEKEY(RIGHT)) PORT_CHAR(UCHAR_MAMEKEY(LEFT))
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_QUOTE)			PORT_CHAR(';') PORT_CHAR(']')
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_L)				PORT_CHAR('L')	
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_J)				PORT_CHAR('J')	
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_G)				PORT_CHAR('G')	
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_D)				PORT_CHAR('D')	
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_A)				PORT_CHAR('A')	
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_TAB)			PORT_CHAR(UCHAR_SHIFT_2)

	PORT_START( "ROW3" )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_NAME("Crsr Down Up") PORT_CODE(KEYCODE_RALT) PORT_CHAR(UCHAR_MAMEKEY(DOWN)) PORT_CHAR(UCHAR_MAMEKEY(UP))
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_SLASH) 			PORT_CHAR('/') PORT_CHAR('?')
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_COMMA) 			PORT_CHAR(',') PORT_CHAR('<')
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_N)				PORT_CHAR('N')	
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_V)				PORT_CHAR('V')	
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_X)				PORT_CHAR('X')	
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_NAME("Shift (Left)") PORT_CODE(KEYCODE_LSHIFT)
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_NAME("Stop Run") PORT_CODE(KEYCODE_HOME)

	PORT_START( "ROW4" )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_F1)				PORT_CHAR(UCHAR_MAMEKEY(F1)) PORT_CHAR(UCHAR_MAMEKEY(F2))
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_NAME("Shift (Right)") PORT_CODE(KEYCODE_RSHIFT) PORT_CHAR(UCHAR_SHIFT_1)	
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_STOP) 			PORT_CHAR('.') PORT_CHAR('>')
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_M)				PORT_CHAR('M')	
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_B)				PORT_CHAR('B')	
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_C)				PORT_CHAR('C')	
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_Z)				PORT_CHAR('Z')	
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_SPACE)			PORT_CHAR(' ')	

	PORT_START( "ROW5" )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_F2)				PORT_CHAR(UCHAR_MAMEKEY(F3)) PORT_CHAR(UCHAR_MAMEKEY(F4))
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_BACKSLASH)		PORT_CHAR('=')	
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_COLON)			PORT_CHAR(':') PORT_CHAR('[')
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_K)				PORT_CHAR('K')	
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_H)				PORT_CHAR('H')	
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_F)				PORT_CHAR('F')	
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_S)				PORT_CHAR('S')	
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_NAME("CBM") PORT_CODE(KEYCODE_LCONTROL)

	PORT_START( "ROW6" )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_F3)				PORT_CHAR(UCHAR_MAMEKEY(F5)) PORT_CHAR(UCHAR_MAMEKEY(F6))
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_NAME("\xE2\x86\x91  Pi") PORT_CODE(KEYCODE_DEL) PORT_CHAR(0x2191) PORT_CHAR(0x03C0)
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_OPENBRACE) 		PORT_CHAR('@')	
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_O)				PORT_CHAR('O')	
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_U)				PORT_CHAR('U')	
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_T)				PORT_CHAR('T')	
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_E)				PORT_CHAR('E')	
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_Q)				PORT_CHAR('Q')	

	PORT_START( "ROW7" )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_F4)				PORT_CHAR(UCHAR_MAMEKEY(F7)) PORT_CHAR(UCHAR_MAMEKEY(F8))
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_NAME("Home  Clr") PORT_CODE(KEYCODE_INSERT) PORT_CHAR(UCHAR_MAMEKEY(HOME))
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_EQUALS)			PORT_CHAR('-')	
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_0)				PORT_CHAR('0')	
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_8)				PORT_CHAR('8') PORT_CHAR('(')
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_6)				PORT_CHAR('6') PORT_CHAR('&')
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_4)				PORT_CHAR('4') PORT_CHAR('$')
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_KEYBOARD ) PORT_CODE(KEYCODE_2)				PORT_CHAR('2') PORT_CHAR('"')
INPUT_PORTS_END


INPUT_PORTS_START( vic_special )
	PORT_START( "SPECIAL" )  /* special keys */	
    PORT_BIT( 0x02, IP_ACTIVE_HIGH, IPT_KEYBOARD ) PORT_NAME("Restore") PORT_CODE(KEYCODE_PRTSCR)	
	PORT_DIPNAME( 0x01, 0x00, "Shift Lock (switch)") PORT_CODE(KEYCODE_CAPSLOCK) PORT_TOGGLE		
	PORT_DIPSETTING(	0x00, DEF_STR( Off ) )														
	PORT_DIPSETTING(	0x01, DEF_STR( On ) )
INPUT_PORTS_END


/* Paddle buttons are read in the same bits as some joystick inputs */
static CUSTOM_INPUT( vic_custom_inputs )
{
	int bit_mask = (FPTR)param;
	UINT8 port = 0;
	
	if (input_port_read(field->port->machine, "CFG") & 0x40)
		port |= (input_port_read(field->port->machine, "FAKE0") & bit_mask) ? 1 : 0;

	if (input_port_read(field->port->machine, "CFG") & 0x80)
		port |= (input_port_read(field->port->machine, "FAKE1") & bit_mask) ? 1 : 0;

	return port;
}
	
INPUT_PORTS_START( vic_controls )
	PORT_START( "JOY" )
	PORT_BIT( 0x80, IP_ACTIVE_HIGH, IPT_SPECIAL ) PORT_CUSTOM(vic_custom_inputs, (void *)0x02)
	PORT_BIT( 0x40, IP_ACTIVE_HIGH, IPT_BUTTON1 ) PORT_NAME("Lightpen Signal") PORT_CODE(KEYCODE_LALT)	
	PORT_BIT( 0x20, IP_ACTIVE_HIGH, IPT_SPECIAL ) PORT_CUSTOM(vic_custom_inputs, (void *)0x01)
	PORT_BIT( 0x10, IP_ACTIVE_HIGH, IPT_JOYSTICK_LEFT ) PORT_8WAY			
	PORT_BIT( 0x08, IP_ACTIVE_HIGH, IPT_JOYSTICK_DOWN ) PORT_8WAY			
	PORT_BIT( 0x04, IP_ACTIVE_HIGH, IPT_JOYSTICK_UP ) PORT_8WAY				

	PORT_START( "FAKE0" )
	PORT_BIT( 0x02, IP_ACTIVE_HIGH, IPT_BUTTON2 ) PORT_NAME("Paddle 2 Button") PORT_CODE(KEYCODE_DEL)	
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_BUTTON1 ) PORT_NAME("Paddle 1 Button") PORT_CODE(KEYCODE_INSERT)	

	PORT_START( "FAKE1" )
	PORT_BIT( 0x02, IP_ACTIVE_HIGH, IPT_JOYSTICK_RIGHT ) PORT_8WAY			
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_BUTTON1 )

	PORT_START( "PADDLE0" )
	PORT_BIT( 0xff,128,IPT_PADDLE) PORT_SENSITIVITY(30) PORT_KEYDELTA(20) PORT_MINMAX(0,255) PORT_CODE_DEC(KEYCODE_HOME) PORT_CODE_INC(KEYCODE_PGUP) PORT_REVERSE

	PORT_START( "PADDLE1" )
	PORT_BIT( 0xff,128,IPT_PADDLE) PORT_SENSITIVITY(30) PORT_KEYDELTA(20) PORT_MINMAX(0,255) PORT_CODE_DEC(KEYCODE_END) PORT_CODE_INC(KEYCODE_PGDN) PORT_PLAYER(2) PORT_REVERSE
INPUT_PORTS_END


INPUT_PORTS_START( vic_expansion )
	PORT_START( "EXP" )
	PORT_DIPNAME( 0x07, 0x00, "RAM Cartridge")
	PORT_DIPSETTING(	0x00, DEF_STR( None ) )
	PORT_DIPSETTING(	0x01, "3k" )		
	PORT_DIPSETTING(	0x02, "8k" )		
	PORT_DIPSETTING(	0x03, "16k" )		
	PORT_DIPSETTING(	0x04, "32k" )		
	PORT_DIPSETTING(	0x05, "Custom" )	
	PORT_DIPNAME( 0x08, 0x00, "RAM at 0x0400")
	PORT_DIPSETTING(	0x00, DEF_STR( No ) )
	PORT_DIPSETTING(	0x08, DEF_STR( Yes ) )
	PORT_DIPNAME( 0x10, 0x00, "RAM at 0x2000")
	PORT_DIPSETTING(	0x00, DEF_STR( No ) )
	PORT_DIPSETTING(	0x10, DEF_STR( Yes ) )
	PORT_DIPNAME( 0x20, 0x00, "RAM at 0x4000")
	PORT_DIPSETTING(	0x00, DEF_STR( No ) )
	PORT_DIPSETTING(	0x20, DEF_STR( Yes ) )
	PORT_DIPNAME( 0x40, 0x00, "RAM at 0x6000")
	PORT_DIPSETTING(	0x00, DEF_STR( No ) )
	PORT_DIPSETTING(	0x40, DEF_STR( Yes ) )
	PORT_DIPNAME( 0x80, 0x00, "RAM at 0xa000")
	PORT_DIPSETTING(	0x00, DEF_STR( No ) )
	PORT_DIPSETTING(	0x80, DEF_STR( Yes ) )	
INPUT_PORTS_END


INPUT_PORTS_START( vic_config )
	PORT_START( "CFG" )
	PORT_DIPNAME( 0x80, 0x80, DEF_STR( Joystick ) )
	PORT_DIPSETTING(	0x00, DEF_STR( No ) )				
	PORT_DIPSETTING(	0x80, DEF_STR( Yes ) )				
	PORT_DIPNAME( 0x40, 0x40, "Paddles")					
	PORT_DIPSETTING(	0x00, DEF_STR( No ) )				
	PORT_DIPSETTING(	0x40, DEF_STR( Yes ) )				
	PORT_DIPNAME( 0x20, 0x00, "Lightpen")					
	PORT_DIPSETTING(	0x00, DEF_STR( No ) )				
	PORT_DIPSETTING(	0x20, DEF_STR( Yes ) )				
	PORT_DIPNAME( 0x10, 0x10, "Draw Pointer")				
	PORT_DIPSETTING(	0x00, DEF_STR( No ) )				
	PORT_DIPSETTING(	0x10, DEF_STR( Yes ) )				
	PORT_DIPNAME( 0x08, 0x08, "Tape Drive/Device 1")		
	PORT_DIPSETTING(	0x00, DEF_STR( No ) )				
	PORT_DIPSETTING(	0x08, DEF_STR( Yes ) )				
	PORT_DIPNAME( 0x04, 0x00, "Tape Sound")					
	PORT_DIPSETTING(	0x00, DEF_STR( No ) )				
	PORT_DIPSETTING(	0x04, DEF_STR( Yes ) )				
	PORT_DIPNAME( 0x02, 0x02, "Serial/Dev 8/VC1541 Floppy")	
	PORT_DIPSETTING(	0x00, DEF_STR( No ) )				
	PORT_DIPSETTING(	0x02, DEF_STR( Yes ) )				
	PORT_DIPNAME( 0x01, 0x01, "Serial/Dev 9/VC1541 Floppy")	
	PORT_DIPSETTING(	0x00, DEF_STR( No ) )				
	PORT_DIPSETTING(	0x01, DEF_STR( Yes ) )
INPUT_PORTS_END

