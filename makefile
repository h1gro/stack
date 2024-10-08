all: exe clean

flag = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

exe: main.exe
	.\main.exe

main.exe: main.o push_pop.o C_Dtor.o checks.o output.o
	g++ main.o push_pop.o C_Dtor.o checks.o output.o $(flag) -o main

main.o: main.cpp
	g++ -c $(flag) main.cpp

push_pop.o: push_pop.cpp
	g++ -c $(flag) push_pop.cpp

C_Dtor.o: C_Dtor.cpp
	g++ -c $(flag) C_Dtor.cpp

checks.o: checks.cpp
	g++ -c $(flag) checks.cpp

output.o: output.cpp
	g++ -c $(flag) output.cpp

clean:
	rm -rf *.o *.exe
