#include "Account.h"

#include <string.h>
#include <stdlib.h>

char *Account_getOwner(Account *self)
{
    return self->owner;
}

void Account_setOwner(Account *self, char *owner)
{
    self->owner = malloc(strlen(owner) + 1);
    self->owner = owner;
}

void Account_newAccount(Account *self)
{
    self->owner = "";
    self->balance = 0;

    self->getOwner = &Account_getOwner;
    self->setOwner = &Account_setOwner;
}

void Account_destroyAccount(Account *self)
{
    free(self->owner);
}