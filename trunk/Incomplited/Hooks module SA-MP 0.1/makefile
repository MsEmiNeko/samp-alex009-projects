OUTFILE = "Release/Hooks.so"
 
COMPILE_FLAGS=-m32 -c -O3 -w -DLINUX

all:
	g++ $(COMPILE_FLAGS) plugin/*.cpp
	g++ -m32 -O -unistd -fshort-wchar -shared -o $(OUTFILE) *.o
	rm *.o
