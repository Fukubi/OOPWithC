#include "Terminal.h"

#include <stdio.h>

int Terminal_executeWithdrawInAccount(Terminal *this)
{
    float depositValue;
    printf("Digite o valor para sacar: ");
    scanf("%f", &depositValue);

    this->accountToUse->executeWithdraw(this->accountToUse, depositValue);

    return 4;
}

int Terminal_executeDepositInAccount(Terminal *this)
{
    float depositValue;
    printf("Digite o valor para depositar: ");
    scanf("%f", &depositValue);

    this->accountToUse->executeDeposit(this->accountToUse, depositValue);

    return 3;
}

int Terminal_showAccountData(Terminal *this)
{
    this->accountToUse->printData(this->accountToUse);

    return 2;
}

int Terminal_registerNewAccount(Terminal *this)
{
    char *owner;
    this->accountToUse->askForOwnerName(this->accountToUse, "Digite o nome do dono da conta: ");

    return 1;
}

int Terminal_runMenu(Terminal *this)
{
    int escolha;
    printf("ESCOLHA UMA OPCAO: \n");
    printf("0. Sair\n");
    printf("1. Cadastrar nova conta\n");
    printf("2. Ver dados da conta\n");
    printf("3. Realizar deposito bancario\n");
    printf("4. Realizar saque bancario\n");
    printf("> ");
    scanf("%d", &escolha);

    if (escolha == 0)
        return 0;
    else if (escolha == 1)
        return Terminal_registerNewAccount(this);
    else if (escolha == 2)
        return Terminal_showAccountData(this);
    else if (escolha == 3)
        return Terminal_executeDepositInAccount(this);
    else if (escolha == 4)
        return Terminal_executeWithdrawInAccount(this);
}

void Terminal_printWelcome()
{
    printf("================================\n");
    printf("=========== OOP BANK ===========\n");
    printf("================================\n");
}

void Terminal_newTerminal(Terminal *this, Account *accountToUse)
{
    this->printWelcome = &Terminal_printWelcome;
    this->runMenu = &Terminal_runMenu;
    this->accountToUse = accountToUse;
}