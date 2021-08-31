SOURCE = src/main.o \
		src/Account/Account.o src/Account/Account.h \
		src/Terminal/Terminal.o src/Terminal/Terminal.h

CC = gcc

bankPOO*: $(SOURCE)
	$(CC) -o bankPOO -Wall $(SOURCE)