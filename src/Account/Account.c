#include "Account.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *Account_getOwner(Account *this)
{
    return this->_private_owner;
}

void Account_setOwner(Account *this, const char *value)
{
    this->_private_owner = realloc(this->_private_owner, strlen(value) + 1);
    strcpy(this->_private_owner, value);
}

void Account_executeWithdraw(Account *this, float valueToWithdraw)
{
    this->balance = this->balance - valueToWithdraw;
}

void Account_executeDeposit(Account *this, float valueToDeposit)
{
    this->balance = this->balance + valueToDeposit;
}

void Account_printData(Account *this)
{
    printf("Nome do dono: %s\n", this->getOwner(this));
    printf("Saldo: %.2f\n", this->balance);
}

void Account_askForOwnerName(Account *this, const char *msg)
{
    printf("%s", msg);
    scanf("%s", this->_private_owner);

    this->setOwner(this, this->_private_owner);
}

void Account_newAccount(Account *this)
{
    this->_private_owner = malloc(1);

    this->getOwner = &Account_getOwner;
    this->setOwner = &Account_setOwner;

    this->askForOwnerName = &Account_askForOwnerName;
    this->printData = &Account_printData;
    this->executeDeposit = &Account_executeDeposit;
    this->executeWithdraw = &Account_executeWithdraw;

    this->setOwner(this, "");
    this->balance = 0;
}

void Account_destroyAccount(Account *this)
{
    free(this->_private_owner);
}