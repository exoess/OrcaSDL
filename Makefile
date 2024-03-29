CC=gcc
CFLAGS=-Wall
LDFLAGS=-lSDL2 -lportmidi

SRC=src
OUT=orca

all: $(OUT)

$(OUT): $(SRC)/*.c
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

clean:
	rm -f $(OUT)
