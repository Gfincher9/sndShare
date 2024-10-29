CXX=g++
CC=gcc
CXXFLAGS=$(-O3, -fomit-frame-pointer, -Werror, -Wall -g)

SendRecv:
	$(CXX) $(CXXFLAGS) send.cpp -o send
	$(CXX) $(CXXFLAGS) recv.cpp -o recv
send:
	$(CXX) $(CXXFLAGS) send.cpp -o send
recv:
	$(CXX) $(CXXFLAGS) recv.cpp -o recv
clean:
	rm -f recv send 
