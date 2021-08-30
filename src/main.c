#include <stdio.h>
#include "Account/Account.h"

int main(void)
{
    Account account;
    Account_newAccount(&account);

    // Testing the set and get for Owner
    printf("Name of Account Owner: %s\n", account.getOwner(&account));

    account.setOwner(&account, "Foo");
    printf("Name of Account Owner: %s\n", account.getOwner(&account));

    account.setOwner(&account, "Foo ooF");
    printf("Name of Account Owner: %s\n", account.getOwner(&account));

    return 0;
}