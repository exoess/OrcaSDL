CC=gcc
NAME=orca

orca: orca.o
	$(CC) -o orca orca.o -lSDL2 -lportmidi

orca.o: orca.c
	$(CC) -c orca.c

install:
	install $(NAME) /usr/local/bin

uninstall:
	rm -f /usr/local/bin/$(NAME)
