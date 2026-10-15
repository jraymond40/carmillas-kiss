/*
// pgui.h
//
// includes, defines and prototypes for pgui.c
// FOR LIB USE ONLY
*/
/* Shortcuts */
#define portrefresh(p)      (portnoutrefresh(p) != ERR ? doupdate() : ERR)

/* Various port types */
#define MENU_PORT            1   /* Scrolling, selectable type        */
#define SCROLL_PORT          2   /* A scrolling window                */
#define LINE_PORT            3   /* A command line port, 1 line only  */
#define OUTPUT_PORT          4   /* Just a plain ol' port, so far.... */

#define MAX_ENTRIES      20 /* A menu can't have more than this many entries */
#define MAX_ENTRY_LENGTH 20 /* Maximum length an entry str can be */
#define MAX_PORTS        20
#define MAX_PORT_WIDTH   80 /* Maximum width any port can be */

