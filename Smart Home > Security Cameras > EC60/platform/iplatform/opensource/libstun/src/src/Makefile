
ifeq ($(CC), )
$(error ERROR: CC not defined)
endif
C++ := $(CC)

CCFLAGS := $(CXXFLAGS) -fPIC -Wall -levent -levent_core -levent_extra

OBJS = stun.o stun_async.o

all: libstun.so libstun.a

stun.o: stun.cpp stun.h stunone.h
	$(C++) $(CCFLAGS) $(LDFLAGS) $< -c

stun_async.o: stun_async.c stun.h stunone.h
	$(C++) $(CCFLAGS) $(LDFLAGS) $< -c

libstun.so: $(OBJS)
	$(C++) $(CCFLAGS) $(LDFLAGS) -shared -o $@ $^

libstun.a: $(OBJS)
	$(AR) -rcs $@ $^

clean:
	rm -f *.o *.so *.a

distclean: clean
