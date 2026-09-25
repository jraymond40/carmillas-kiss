//=======================================================================\\
//                                                                       \\
// Filename:    html.h                                                   \\
//                                                                       \\
// Description: The defines common to HTML uses.                         \\
//                                                                       \\
// History:                                                              \\
//                                                                       \\
// 04/12/95  jmr  Original                                               \\
//                                                                       \\
//============== Copyright 1995 ===== Raymond Interactive Theatre, Ltd. =\\

#define THIS_URL "http://www.poetix.com/"
#define BOUNDARY "PageBoundary"
#define HEADER "Content-type: multipart/x-mixed-replace;boundary=" + \
               BOUNDARY + "\n" 
#define BOUNDARYSTR "\n--" + BOUNDARY + "\n"
#define ENDSTR BOUNDARYSTR + "--\n"
#define CTSTR "Content-type: text/html\n\n"
