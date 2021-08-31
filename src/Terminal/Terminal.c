#include "Terminal.h"

#include <stdio.h>

int Terminal_runMenu(Account *account)
{
    int escolha;
    printf("ESCOLHA UMA OPCAO: \n");
    printf("0. Sair\n");
    printf("1. Cadastrar nova conta\n");
    printf("2. Ver dados da conta\n");
    printf("> ");
    scanf("%d", &escolha);

    if (escolha == 0)
        return 0;
    else if (escolha == 1)
    {
        char *owner;
        printf("Digite o nome do dono da conta: ");
        scanf("%[^\n]s", &owner);
        setbuf(stdin, NULL);

        account->setOwner(&account, owner);

        return 1;
    }
    else if (escolha == 2)
    {
        printf("Nome do dono: %s\n", account->getOwner(&account));
        printf("Saldo: %f\n", account->getBalance(&account));

        return 2;
    }
}

void Terminal_printWelcome()
{
    printf("================================\n");
    printf("=========== OOP BANK ===========\n");
    printf("================================\n");
}

void Terminal_newTerminal(Terminal *this)
{
    this->printWelcome = &Terminal_printWelcome;
    this->runMenu = &Terminal_runMenu;
}