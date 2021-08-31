#include <stdio.h>

#include "Account/Account.h"
#include "Terminal/Terminal.h"

int main(void)
{
    Account account;
    Account_newAccount(&account);

    Terminal terminal;
    Terminal_newTerminal(&terminal);

    terminal.printWelcome();

    while (1)
    {
        if (terminal.runMenu == 0)
            break;
    }

    Account_destroyAccount(&account);
    return 0;
}