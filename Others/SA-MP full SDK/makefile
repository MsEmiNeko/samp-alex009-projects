OUTFILE = "SDK.so"
 
COMPILE_FLAGS=-m32 -c -O3 -w -DLINUX -I./SDK/amx/

all:
	gcc $(COMPILE_FLAGS) SDK/amx/*.c
	g++ $(COMPILE_FLAGS) SDK/*.cpp
	g++ $(COMPILE_FLAGS) *.cpp
	g++ -m32 -O -pthread -unistd -fshort-wchar -shared -o $(OUTFILE) *.o
	rm *.o