#makefile COP4530_Project_5_Binary_Expression_Tree
#Created on 3/18/2024
#Reference from Dr. Gaitros' lecture on 1/24/2024

CC = g++ -std=c++11

main: proj5_driver.o bet.h bet.hpp
	$(CC) proj5_driver.o -o main

proj5_driver.o: proj5_driver.cpp
	$(CC) -c bet.h
	$(CC) -c proj5_driver.cpp

clean:
	rm -rf *o main
