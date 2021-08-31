#ifndef ACCOUNT_H
#define ACCOUNT_H

typedef struct Account Account;

struct Account
{
    char *_private_owner;

    float balance;

    void (*askForOwnerName)(Account *, const char *);
    void (*printData)(Account *);
    void (*executeDeposit)(Account *, float);
    void (*executeWithdraw)(Account *, float);

    char *(*getOwner)(Account *);
    void (*setOwner)(Account *, const char *);
};

void Account_newAccount(Account *);
void Account_destroyAccount(Account *);

#endif