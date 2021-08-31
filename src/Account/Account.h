#ifndef ACCOUNT_H
#define ACCOUNT_H

typedef struct Account Account;

struct Account
{
    char *owner;
    float balance;

    void (*askForOwnerName)(Account *, const char *);

    char *(*getOwner)(Account *);
    void (*setOwner)(Account *, const char *);

    float (*getBalance)(Account *);
    void (*setBalance)(Account *, float);
};

void Account_newAccount(Account *);
void Account_destroyAccount(Account *);

#endif