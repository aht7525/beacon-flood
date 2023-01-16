LDLIBS += -lpcap

all: beacon-flood

airodump: beacon-flood.cpp

clean:
	rm -f beacon-flood *.o
