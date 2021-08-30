SOURCE = src/main.o \
		src/Account/Account.o src/Account/Account.h

CC = gcc

bankPOO*: $(SOURCE)
	$(CC) -o bankPOO -Wall $(SOURCE)