CC = g++

all: task1 task2 task3

lint:
	clang-format --style Google -n *.cpp

format:
	clang-format --style Google -i *.cpp

task1:
	echo "Starting Method #1"
	$(CC) method1.cpp
	./a.out

task2:
	echo "Starting Method #2"
	$(CC) method2.cpp
	./a.out

task3:
	echo "Starting Method #3"
	$(CC) method3.cpp
	./a.out

clean:
	rm ./a.out