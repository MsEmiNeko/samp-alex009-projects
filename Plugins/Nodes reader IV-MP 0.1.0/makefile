OUTFILE = "Release/Nodes.so"
 
COMPILE_FLAGS=-m32 -c -O3 -w -DLINUX -I./plugin/SDK/amx/

all:
	g++ $(COMPILE_FLAGS) plugin/SDK/*.cpp
	g++ $(COMPILE_FLAGS) plugin/*.cpp
	g++ -m32 -O -unistd -fshort-wchar -shared -o $(OUTFILE) *.o
	rm *.o
