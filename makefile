compilar : src/main.cpp
	g++ -o bin/main src/main.cpp -Iinclude -Llib -lsymengine

run : bin/main.exe
	./bin/main.exe

test : 
	g++ -o bin/main-test src/test.cpp -Iinclude
	./bin/main-test.exe