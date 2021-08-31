#include "Account.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Account_askForOwnerName(Account *this, const char *msg)
{
    printf("%s", msg);
    scanf("%s", this->owner);

    this->setOwner(this, this->owner);
}

char *Account_getOwner(Account *this)
{
    return this->owner;
}

void Account_setOwner(Account *this, const char *value)
{
    this->owner = realloc(this->owner, strlen(value) + 1);
    strcpy(this->owner, value);
}

float Account_getBalance(Account *this)
{
    return this->balance;
}

void Account_setBalance(Account *this, float value)
{
    this->balance = value;
}

void Account_newAccount(Account *this)
{
    this->owner = malloc(1);

    this->getOwner = &Account_getOwner;
    this->setOwner = &Account_setOwner;

    this->getBalance = &Account_getBalance;
    this->setBalance = &Account_setBalance;

    this->askForOwnerName = &Account_askForOwnerName;

    this->setOwner(this, "");
    this->setBalance(this, 0);
}

void Account_destroyAccount(Account *this)
{
    free(this->owner);
}