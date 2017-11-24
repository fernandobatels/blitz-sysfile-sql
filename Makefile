LIBS_FLAGS = -lUnitTest++

build:
	
	g++ -c ./src/result-status.cpp -o ./dist/result-status.o $(LIBS_FLAGS)
	g++ -c ./src/result-data-group.cpp -o ./dist/result-data-group.o $(LIBS_FLAGS)
	g++ -c ./src/result-data.cpp -o ./dist/result-data.o $(LIBS_FLAGS)
	g++ -c ./src/interpreter.cpp -o ./dist/interpreter.o $(LIBS_FLAGS)
	g++ -c ./src/main.cpp -o ./dist/main.o $(LIBS_FLAGS)
	
	ld -r ./dist/*.o -o ./dist/tmp.o
	
	g++ ./dist/tmp.o -o ./dist/blitz-sysfile-sql $(LIBS_FLAGS)
	
	rm ./dist/*.o
	
