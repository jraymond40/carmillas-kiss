//=======================================================================\\
//                                                                       \\  
// Filename:    std_defs.h                                               \\
//                                                                       \\
// Description: Standard definitions.                                    \\
//                                                                       \\
// History:                                                              \\
//                                                                       \\
// 02/12/93  jmr  Created                                                \\
//                                                                       \\
//============== Copyright 1994 ===== Raymond Interactive Theatre, Ltd. =\\

#define FALSE 0
#define TRUE  1

#define NULL 0

#define OFF   0
#define ON    1
#define START 2
#define PAUSE 3

#define FAIL    0
#define SUCCEED 1

#define SHORT  1
#define MEDIUM 2
#define LONG   3

#define OPEN   0
#define CLOSED 1
#define LOCKED 2

#define NONE   0
#define LOW    1
//      MEDIUM 2 // - it's already def'd above
#define HIGH   3

#define INFINITE -1

// Physical forms.
#define GAS    0
#define LIQUID 1
#define SOLID  2
#define EFFECT 3   // ie. fire 

// Object Rigidity.
#define LIMP     0
#define FLEXIBLE 1
#define RIGID    2

// Human types.
#define LOGON         0 // The default.
#define GUEST         1
#define PLAYER        2
#define ADMINISTRATOR 3
#define NPC           4
#define NPC_AI        5

// Object types.
#define STAGE       1
#define LOCATION    2
#define LIVING      4
#define INANIMATE   8
 
// Object attributes.
#define INTRANSIENT 16
#define TRANSIENT   32 
#define STATIC      64
#define DYNAMIC     128

#define HOLDER      256
#define ENCLOSURE   512
#define CLOSABLE    1024

#define ALL         65535   // Flip all object bits defined so far

// Masking modes.
#define OR  0
#define AND 1



// Range types
//
// This is for the range of an effect, and for defining objects relative
// to an individual (ie object_list), these functions should be more closely 
// integrated, and are || together...  
// Future use of these can use negative numbers to define a radial range 
// the user.
//
#define OUTSIDE		16	// Outside this location
#define GLOBAL		8	// Everywhere
#define LOCAL		4	// Everything in this location (self-included)
#define IMMEDIATE 	4	// Same as local
#define INVENTORY	2	// Those things I'm carrying
#define INDIV		1	// The individual only

// When we want to return a failure msg, here's the SUCCEED key.
#define SUCCEED_STR "SUCCEED"

// Misc.
#define MASTER_KEY_STR "MASTER KEY"
#define ROOM_KEY_STR   "Key to room #"

#define EOF "\D"
