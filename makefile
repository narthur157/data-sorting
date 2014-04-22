EXECUTABLE = prj
all:
	g++ -std=c++0x -g -ggdb -Wfatal-errors -o $(EXECUTABLE) WikiSort.cpp Driver.cpp
clean:
	rm -rf *.o $(EXECUTABLE)
