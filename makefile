all:main_cmd

main_cmd: main_cmd.o
	g++ -std=c++11 -g main_cmd.o -o main_cmd

main_cmd.o: main_cmd.cpp ctree.cpp ctree.h node.h
	g++ -std=c++11 -g -c main_cmd.cpp

clean:
	rm *.o *~ main_cmd
