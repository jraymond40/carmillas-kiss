//=======================================================================\\
//                                                                       \\  
// Filename:    ticketwindow.h                                           \\
//                                                                       \\
// Description: ticketwindow defines.                                    \\
//                                                                       \\
// History:                                                              \\
//                                                                       \\
// 08/17/94  jmr  Created                                                \\
//                                                                       \\
//============== Copyright 1994 ===== Raymond Interactive Theatre, Ltd. =\\
#include <config.h>
#include <std_defs.h>
#include <curses.h>
#include <pgui.h>
#include <corporate.h>
#include <timing.h>

#define TICKETWINDOW_DEBUG        FALSE
#define TIMEOUT_TIME       120
#define MAX_FAILURES       5

#define STG_WELCOME        0
#define STG_LOGIN          1
#define STG_VERIFY_PASSWD  2
#define STG_SET_PASSWD     3
#define STG_INFO_MENU      4
#define STG_MENU_SELECT    5
#define STG_MORE_PAYMENT_METHODS 6
#define STG_SHOW_IN_PROGRESS 7
#define STG_CLOSED           8
#define STG_ADD_PLAYER       9
#define STG_SWITCH        16

#define PASSWORD_PROMPT_X     10
#define PASSWORD_PROMPT_Y     22

#define TICKETHOLDER_PROMPT_X 15
#define TICKETHOLDER_PROMPT_Y 21

#define CLOCK_UPDATE 15 // Update the Closed window clock this often
#define CLOSED_CLOCK_Y      23
#define CLOSED_CLOCK_X       2
#define CLOSED_STR          "Minutes until Window reopens: "
#define OPEN_CLOCK_Y      23
#define OPEN_CLOCK_X       5
#define OPEN_STR          "Minutes until Showtime: "
