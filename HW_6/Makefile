CXX = g++
CLINK = $(CXX)
CXXFLAGS = -Wall -g -std=c++11
OBJS = string.o field.o port.o ip.o

firewall.exe: main.o libfirewall.so libinput.so
	$(CLINK) $(CXXFLAGS) main.o -o firewall.exe -lfirewall -linput -L.

libfirewall.so: string.o field.o port.o ip.o
	$(CLINK) $(CXXFLAGS) -shared $(OBJS) -o libfirewall.so -L.

main.o: main.cpp string.h field.h port.h ip.h 
	$(CXX) $(CXXFLAGS) -c -fpic main.cpp

ip.o: ip.cpp ip.h string.h field.h
	$(CXX) $(CXXFLAGS)  -c -fpic ip.cpp

port.o: port.cpp port.h string.h field.h
	$(CXX) $(CXXFLAGS)  -c -fpic port.cpp 

field.o: field.cpp field.h string.h
	$(CXX) $(CXXFLAGS)  -c -fpic field.cpp
	
string.o: string.h string.cpp
	$(CXX) $(CXXFLAGS)  -c -fpic string.cpp 

clean:
	rm -rf *.o libfirewall.so
	