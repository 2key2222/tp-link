all: vethd

clean:
	rm -f vethd

vethd: vethd.c
	$(CC) $(CFLAGS) -o vethd vethd.c

install: all
	install -s -m 750 ./vethd $(INSTALL_DIR)
