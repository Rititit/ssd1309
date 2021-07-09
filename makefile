main: main.cpp ssd1309.h
	g++ -o main main.cpp -pthread -lpigpio -lrt -w
