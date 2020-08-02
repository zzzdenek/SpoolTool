spt_test: Spooler FileHandler ArgsHandler Arguments src/test_main.cpp
	g++ -std=c++14 -Wall -o bin/spt_test.out bin/FileHandler.o bin/Spooler.o bin/ArgsHandler.o bin/Arguments.o src/test_main.cpp

Spooler: src/Spooler.cpp src/Spooler.h
	g++ -c -std=c++14 -Wall -o bin/Spooler.o src/Spooler.cpp

FileHandler: src/FileHandler.cpp src/FileHandler.h
	g++ -c -std=c++14 -Wall -o bin/FileHandler.o src/FileHandler.cpp

ArgsHandler: src/ArgsHandler.cpp src/ArgsHandler.h
	g++ -c -std=c++14 -Wall -o bin/ArgsHandler.o src/ArgsHandler.cpp

Arguments: src/Arguments.cpp src/Arguments.h
	g++ -c -std=c++14 -Wall -o bin/Arguments.o src/Arguments.cpp
	
#################################################################################

spool_tool: spool_tool.cpp
	g++ -Wall -o spool_tool.out spool_tool.cpp

# clean
clean:
	rm bin/*.o
	rm bin/*.out