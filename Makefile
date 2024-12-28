all: compile link execute clean

compile:
	gcc -c -I "./include" ./src/logger.c -o ./bin/logger.o
	gcc -c -I "./include" ./src/file_operations.c -o ./bin/file_operations.o
	gcc -c -I "./include" ./src/directory_ops.c -o ./bin/directory_ops.o
	gcc -c -I "./include" ./src/permissions.c -o ./bin/permissions.o
	gcc -c -I "./include" ./src/main.c -o ./bin/main.o
	
link:
	gcc ./bin/logger.o ./bin/file_operations.o ./bin/directory_ops.o ./bin/permissions.o ./bin/main.o -o ./bin/program

execute:
	./bin/program
