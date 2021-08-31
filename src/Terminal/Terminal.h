#ifndef TERMINAL_H
#define TERMINAL_H

#include "../Account/Account.h"

typedef struct Terminal Terminal;

struct Terminal {
    void (*printWelcome)();
    int (*runMenu)(Account *);
};

void Terminal_newTerminal(Terminal *);

#endif