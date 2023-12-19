#ifndef __MESSAGES_H__
#define __MESSAGES_H__

#define ERROR_NO_SPACE        "error: insufficient stack space to push %.10f\n"
#define ERROR_BINARY_OPERATOR "error: not enough values on stack for binary operator\n"
#define ERROR_UNARY_OPERATOR  "error: not enough values on stack for unary operator\n"
#define ERROR_BAD_CHAR        "error: unknown operation '%c'\n"
#define ERROR_BAD_STRING      "error: unknown operation \"%s\"\n"

#define USAGE                                                                                      \
    "usage: %s [-mh]\n"                                                                            \
    "    -m: use libm trig function implementations instead of custom ones.\n"                     \
    "    -h: show help\n"

#endif
