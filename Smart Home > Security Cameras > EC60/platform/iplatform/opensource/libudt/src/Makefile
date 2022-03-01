
all clean distclean: 
	make -e os=LINUX arch=UNKNOWN -C ./src/src $@
	mkdir -p ./lib
	cp -f ./src/src/*.so ./lib
	cp -f ./src/src/*.a ./lib
	$(STRIP) ./lib/*
