/*
// Curses.h
//
// For lib use only.
*/

#ifndef CURSES_H
#define CURSES_H

#define ERR      -1
#define OK        0
#define stdscr    getstdscr()
#define curscr    getcurscr()
#define chtype    int

/*
//    Macros
*/
#define wrefresh(w)                (wnoutrefresh(w)!= ERR ? doupdate() : ERR)
#define prefresh(p)                (pnoutrefresh(p)!= ERR ? doupdate() : ERR)

#define addch(c)                   waddch(stdscr, (c))
#define addstr(str)                waddstr(stdscr, (str))
#define attrset(attr)              wattrset(stdscr, (attr))
#define attron(attr)               wattron(stdscr, (attr))
#define attroff(attr)              wattroff(stdscr, (attr))
#define clear()                    wclear(stdscr)
#define clrtoeol()                 wclrtoeol(stdscr)
#define clrtobot()                 wclrtobot(stdscr)
#define crmode()                   cbreak()
#define delch()                    wdelch(stdscr)
#define deleteln()                 wdeleteln(stdscr)
#define erase()                    werase(stdscr)
#define inch()                     winch(stdscr)
#define insch(c)                   winsch(stdscr, (c))
#define insertln()                 winsertln(stdscr)
#define getch()                    wgetch(stdscr)
#define getstr()                   wgetstr(stdscr)
#define getyx(win,y,x)             ((y) = getcury(win), (x) = getcurx(win))
#define getbegyx(win,y,x)          ((y) = getbegy(win), (x) = getbegx(win))
#define getmaxyx(win,y,x)          ((y) = getmaxy(win), (x) = getmaxx(win))
#define getparyx(win,y,x)          ((y) = getpary(win), (x) = getparx(win))
#define getcury(win)               ((win)->_cury)
#define getcurx(win)               ((win)->_curx)
#define getbegy(win)               ((win)->_begy)
#define getbegx(win)               ((win)->_begx)
#define getmaxy(win)               ((win)->_maxy)
#define getmaxx(win)               ((win)->_maxx)
#define getpary(win)               ((win)->_pary)
#define getparx(win)               ((win)->_parx)
#define getbkgd(win)               ((win)->_bkgd)
#define getattrs(win)              ((win)->_attrs)
#define move(line, col)            wmove(stdscr, (line), (col))
#define mvdelch(y, x)              (move((y), (x)), delch())
#define mvwdelch(win, y, x)        (wmove((win),(y),(x)),wdelch((win)))
#define mvgetch(y, x)              (move((y), (x)), getch())
#define mvwgetch(win, y, x)        (wmove((win),(y),(x)),wgetch((win)))
#define mvgetstr(y, x, ptr)        (move((y), (x)), getstr((ptr)))
#define mvwgetstr(win, y, x, ptr)  (wmove((win), (y), (x)), \
                                     wgetstr((win), (ptr)))
#define mvinsch(y, x, c)           (move((y), (x)), insch((c)))
#define mvwinsch(win, y, x, c)     (wmove((win), (y), (x)), \
                                     winsch((win), (c)))
#define mvinch(y, x)               (move((y), (x)), inch())
#define mvwinch(win, y, x)         (wmove((win), (y), (x)),winch((win)))
#define mvaddch(y, x, c)           (move((y), (x)), addch((c)))
#define mvwaddch(win, y, x, c)     (wmove((win), (y), (x)), \
                                     waddch((win), (c)))
#define mvaddstr(y, x, str)        (move((y), (x)), addstr((str)))
#define mvwaddstr(win, y, x, str)  (wmove((win), (y), (x)), \
                                     waddstr((win), (str)))

#define nocrmode()                 nocbreak()
#define refresh()                  wrefresh(stdscr)
#define noutrefresh()              wnoutrefresh(stdscr)
#define setscrreg(top, bottom)     wsetscrreg(stdscr, (top), (bottom))
#define standend()                 wstandend(stdscr)
#define standout()                 wstandout(stdscr)

/*
 *    Video Attributes.
 */
#define A_NORMAL      0
#define A_STANDOUT    65536      // 8^5 * 2
#define A_UNDERLINE   131072     // 8^5 * 4
#define A_REVERSE     262144     // 8^6
#define A_BLINK       524288     // 8^6 * 2
#define A_DIM         1048576    // 8^6 * 4
#define A_BOLD        2097152    // 8^7
#define A_ALTCHARSET  16777216   // 8^8
#define _STANDOUT     A_STANDOUT /* for compatibility with old curses */
#define A_CLRPART     7
#define A_ATRPART     504 

/*
// Key definitions
*/
#define KEY_BACKSPACE   8       /* Backspace */
#define KEY_RETURN      10      /* Return */
#define KEY_ESC         27      /* The escape key */
#define KEY_DC          127     /* Delete character */
#define KEY_UP          259     /* The up arrow key */
#define KEY_DOWN        258     /* The down arrow key */
#define KEY_LEFT        260     /* The left arrow key */
#define KEY_RIGHT       261     /* The right arrow key */
#define KEY_SHIFT_UP    267     /* Shifted up arrow key */
#define KEY_SHIFT_DOWN  266     /* Shifted down arrow key */
#define KEY_SHIFT_RIGHT 268     /* Shifted right arrow key */
#define KEY_SHIFT_LEFT  272     /* Shifted right arrow key */
#define KEY_CTRL_A      1       // Trigger HTML mode in Ticketwindow
#define KEY_CTRL_C      3       // Cancel certain functions
#define KEY_CTRL_I      9       // Info Screen 
#define KEY_HELP        363     // help key  - info
#define KEY_SHELP       390     // shifted help key  - info
#define KEY_REFRESH     373     // Screen Refresh
#define KEY_CTRL_L      12      // Screen Refresh - Unix style
#define KEY_CTRL_R      18      // Screen Refresh
#define KEY_CTRL_N      14      // North
#define KEY_CTRL_T      20      // North - rosette
#define KEY_CTRL_S      19      // South
#define KEY_CTRL_V      22      // South - rosette
#define KEY_CTRL_E      5       // East
#define KEY_CTRL_G      7       // East - rosette
#define KEY_CTRL_W      23      // West
#define KEY_CTRL_F      6       // West - rosette
#define KEY_CTRL_U      21      // Up
#define KEY_CTRL_D      4       // Down

#endif /* CURSES_H */
