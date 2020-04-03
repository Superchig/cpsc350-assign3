CPPFLAGS=-Wall -g
CXX=g++

all: assignment3.exe

assignment3.exe: main.cpp
	$(CXX) $(CPPFLAGS) $^ -o $@

# test: test_stack.cpp
# 	$(CXX) $(CPPFLAGS) $^ -o $@
# 	./test

clean:
	[ -f assignment3.exe ] && rm assignment3.exe
