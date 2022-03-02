LDFLAGS = $(TARGET_LDFLAGS)
#CFLAGS = $(TARGET_CFLAGS) -Wall -Werror
CFLAGS = $(TARGET_CFLAGS)

SRC_C = $(wildcard *.c)
SRC_H = $(wildcard *.h)
OBJS = $(patsubst %.c,%.o,$(SRC_C))

BIN = ividns

all: $(BIN)

$(OBJS): %.o: %.c $(SRC_H)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BIN): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) $(BIN)
