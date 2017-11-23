LIBS_FLAGS = 

build:
	
	g++ -c ./src/result-status.cpp -o ./dist/result-status.o $(LIBS_FLAGS)
	g++ -c ./src/result-files.cpp -o ./dist/result-files.o $(LIBS_FLAGS)
	g++ -c ./src/result-file.cpp -o ./dist/result-file.o $(LIBS_FLAGS)
	g++ -c ./src/interpreter.cpp -o ./dist/interpreter.o $(LIBS_FLAGS)
	g++ -c ./src/main.cpp -o ./dist/main.o $(LIBS_FLAGS)
	
	ld -r ./dist/*.o -o ./dist/tmp.o
	
	g++ ./dist/tmp.o -o ./dist/blitz-sysfile-sql $(LIBS_FLAGS)
	
	rm ./dist/*.o
	
