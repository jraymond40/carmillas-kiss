/* Terminal Sensory Controls */
#define TERM_BELL            "\x07"
#define CSI                 "\x1b"+"["
#define TERM_FLASH           CSI+"?5h"+CSI+"?5l"       // Screen flash (reverse video toggle)
#define TERM_INVERT_ON       CSI+"?5h"
#define TERM_INVERT_OFF      CSI+"?5l"

#define TERM_ROWS           24
#define TERM_COLS           80

/* Key constants for emulation */
#define KEY_UP              1001
#define KEY_DOWN            1002
#define KEY_LEFT            1003
#define KEY_RIGHT           1004
#define KEY_RETURN          "\n"

/* --- ANSI Curses Macros --- */
#define DEFAULT_TERM_WIDTH  80
#define DEFAULT_TERM_HEIGHT 24
#define CURS_CLEAR          "\x1b"+"[2J"
#define CURS_HOME           "\x1b"+"[H"
#define CURS_SET_SCROLL(t,b) sprintf("\x1b[%d;%dr", t, b)
#define CURS_RESET_SCROLL   "\x1b"+"[r"
#define CURS_MOVE(r,c)      sprintf("\x1b[%d;%dH", r, c)
#define CURS_SAVE           "\x1b"+"7"
#define CURS_RESTORE        "\x1b"+"8"
#define CURS_REVERSE        "\x1b"+"[7m"
#define CURS_RESET          "\x1b"+"[0m"
#define CURS_CLEAR_TO_EOL   "\x1b"+"[K"
