#ifndef TERMINAL_H
#define TERMINAL_H

#include "../Account/Account.h"

typedef struct Terminal Terminal;

struct Terminal {
    Account *accountToUse;

    void (*printWelcome)();
    int (*runMenu)(Terminal *);
};

void Terminal_newTerminal(Terminal *this, Account *accountToUse);

#endif