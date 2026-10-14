//=======================================================================\\
//                                                                       \\
// Filename:    config.h                                                 \\
//                                                                       \\
// Description: All defines related to runtime system configuration.     \\
//              Modified with terminal/curses emulation controls.        \\
//                                                                       \\
// History:                                                              \\
//                                                                       \\
// 02/26/93  jmr  Created                                                \\
// 08/24/94  jmr  Readied for going online.                              \\
// 10/10/26  mod  Added ANSI/VT100 curses control macros.                \\
//                                                                       \\
//============== Copyright 1994 ===== Raymond Interactive Theatre, Ltd. =\\

// Revision numbers for interpreter and runtime library.
#define ENGINE_REV          "1.0"
#define LIBRARY_REV         "1.0"

// Undefine to disable
#define BETAMODE           TRUE

// System data
#define SYSTEM_DIR          "system/"
#define SYSTEM_OBJ           SYSTEM_DIR+"system"
#define TICKETWINDOW_OBJ     SYSTEM_DIR+"ticketwindow"
#define HTML_TICKETWINDOW_OBJ     SYSTEM_DIR+"html_ticketwindow"
#define MAP                  SYSTEM_DIR+"Map"
#define PRELOAD_LST          SYSTEM_DIR+"preload.lst"

// Libraries
#define LIBRARIES_DIR       "libraries/"
#define LIBRARIES            LIBRARIES_DIR + "libraries"

// Daemons
#define DAEMON_DIR           SYSTEM_DIR+"daemons/"
#define COMMONS_MGR          DAEMON_DIR+"commons_mgr"
#define NAVIGATE_OBJ         DAEMON_DIR+"navigate"
#define DIRECTOR_OBJ         DAEMON_DIR+"director"
#define ROUTING_TBL          DAEMON_DIR+"routing.tbl"

// Various info
#define INFO_DIR             SYSTEM_DIR + "info/"
#define MOTD                 INFO_DIR+"motd"
#define CREDITS              INFO_DIR+"Credits"

// Instances
#define INSTANCE_DIR        "instances/"
#define INSTANCE_BINARIES   INSTANCE_DIR + "bin/"
#define INANIMATE_OBJ_DIR   INSTANCE_DIR + "inanimate/"
#define INTRANSIENT_OBJ_DIR INANIMATE_OBJ_DIR + "intransients/"
#define TRANSIENT_OBJ_DIR   INANIMATE_OBJ_DIR + "transients/"

// Locations
#define LOCATION_DIR        "instances/inanimate/intransients/locations/"
#define DEFAULT_LOCATION     LOCATION_DIR+"nowhere"	// Should a location be destructed, it's contents go here */
#define LOCATION_PREFIX     "loc"

#ifdef BETAMODE
#define STARTING_LOCATION    LOCATION_DIR+LOCATION_PREFIX+"+2+1+0"
#else
#define STARTING_LOCATION    LOCATION_DIR+LOCATION_PREFIX+"+2+0+0"
#endif

#define GUEST_STARTING_LOCATION    LOCATION_DIR+LOCATION_PREFIX+"+2+1+0"

/*===============================================================*/
/* Extract a location number from it's filename  /47\  /53\      */
/*                                               \--/  \--/      */
/*                                                |/    |/       */
/* /instances/inanimate/intransients/locations/loc+n+n+n#        */
/* 0         1         2         3         4      V  5  V      6 */
/* 0123456789012345678901234567890123456789012345678901234567890 */
/*===============================================================*/
#define LOCATION_NUMBER(obj) extract(file_name(obj), 47, 53)

#define STAGE_DIR            LOCATION_DIR + "stages/"

// Doors
#define DOOR_DIR             INTRANSIENT_OBJ_DIR + "door/"

// Where the Ylastrum flask can be found.
#define FLASK_YLIASTRUM      TRANSIENT_OBJ_DIR + "flask/yliastrum"
#define ROOM_KEY             TRANSIENT_OBJ_DIR + "key/guest_room"

// The directory where living classes are found
#define LIVING_DIR          "/classes/living/"
#define HUMAN_DIR            LIVING_DIR+"human/"
#define USERS_DIR            HUMAN_DIR+"users/"
#define NPCS_DIR             HUMAN_DIR+"npcs/"
#define NPCAIS_DIR           NPCS_DIR

// The directory where user type classes are found
#define GUEST_OBJ            USERS_DIR+"guest/guest.lpc"
#define PLAYER_OBJ           USERS_DIR+"players/player.lpc"
#define ADMIN_OBJ            USERS_DIR+"admin/admin.lpc"
#define HTML_GUEST_OBJ       USERS_DIR+"guest/html_guest.lpc"
#define HTML_PLAYER_OBJ      USERS_DIR+"players/html_player.lpc"
#define HTML_ADMIN_OBJ       USERS_DIR+"admin/html_admin.lpc"

// The directory where user type instances are found
#define USERS_INST_DIR       INSTANCE_DIR + "users/"
#define GUEST_INSTANCE       USERS_INST_DIR+"guest/guest"
#define PLAYER_INSTANCE      USERS_INST_DIR+"players/"
#define ADMIN_INSTANCE       USERS_INST_DIR+"admin/admin"

// Where action_object instances are found
#define ACTION_INST_DIR     "/instances/actions/"

// Flags for writing logfiles for debugging(>0) and trace level.
#define NPC_DEBUG            1
#define LOCATION_DEBUG       0
#define HOLDER_DEBUG         0

// The name/location of the various logfiles
#define LOG_DIR              SYSTEM_DIR+"log/"
#define LOCATION_LOG         LOG_DIR+"location.log"
#define ERROR_LOG            LOG_DIR+"error.log"
#define SHUTDOWN_LOG         LOG_DIR+"shutdown.log"

// The possible directions to head in from any one place
#define MAX_NUM_DIRECTIONS   6
#define CARDINAL_DIRECTIONS  ({"north", "south", "west", "east", "up", "down"})

// MAX_TEXT is the maximum input buffer size, this should
// mirror comm.h's MAX_TEXT.
#define MAX_TEXT             1024

// What is the standard maximum evaluation limit?
#define STD_MAX_EVAL_LIMIT   50000

// What is the fewest possible number of players whom can play?
#define MIN_REQUIRED_PLAYERS 3

// How long should a guest walk about the game? (in seconds)
#define GUEST_DURATION       600 // How about 10 minutes?

// Maximum number of characters a player can flood the system with before
// we move onto the next user for input.
#define MAX_CHAR_INPUT       20

/* =============================================================== */
/* Curses & ANSI Terminal Emulation Definitions                    */
/* =============================================================== */

#define CSI                  "\033["

/* Terminal Clearing & Screen Controls */
#define CURS_CLEAR           CSI "2J"
#define CURS_HOME            CSI "H"
#define CURS_SAVE            CSI "s"
#define CURS_RESTORE         CSI "u"

/* Scrolling Region (DECSTBM: DEC Set Top and Bottom Margins) */
#define CURS_SET_SCROLL(t,b) sprintf(CSI "%d;%dr", (t), (b))
#define CURS_RESET_SCROLL    CSI "r"

/* Direct Coordinate Movement & Clearing (1-indexed: row, col) */
#define CURS_MOVE(r, c)      sprintf(CSI "%d;%dH", (r), (c))
#define CURS_CLEAR_LINE      CSI "2K"
#define CURS_CLEAR_TO_EOL    CSI "K"

/* Text Attributes */
#define CURS_RESET           CSI "0m"
#define CURS_BOLD            CSI "1m"
#define CURS_DIM             CSI "2m"
#define CURS_UNDERLINE       CSI "4m"
#define CURS_REVERSE         CSI "7m"

/* Default Terminal Geometry */
#define DEFAULT_TERM_WIDTH   80
#define DEFAULT_TERM_HEIGHT  24