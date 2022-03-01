
all clean distclean: 
	make -C ./src $@
	mkdir -p ./include && cp -f ./src/stun.h ./include
	mkdir -p ./lib && cp -f ./src/*.so ./src/*.a ./lib
	$(STRIP) ./lib/*
