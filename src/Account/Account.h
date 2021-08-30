#ifndef ACCOUNT_H
#define ACCOUNT_H

typedef struct Account Account;

struct Account
{
    char *owner;
    float balance;

    char *(*getOwner)(Account *);
    void (*setOwner)(Account *, char *);

    void (*getBalance)(Account *);
    void (*setBalance)(Account *, double);
};

void Account_newAccount(Account *);
void Account_destroyAccount(Account *);

#endif