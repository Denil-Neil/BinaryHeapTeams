# Volleyball Team Generator
This project implements a priority queue data structure with an underlying binary heap implementation and uses it to construct a greedy algorithm to pick fair 2-person teams from a list of Volleyball players.

## Requirements
To compile and run this project, you will need:

* A C++ compiler that supports C++11 standard
* The nlohmann/json library (included in the project)

## Usage
### Priority Queue
The '*PriorityQueue*' class is implemented in the '*priorityqueue.h*' and '*priorityqueue.cpp*' files. It is a minimum priority queue implemented as an array-based binary heap with the root node at index 1 of the array.

To use the '*PriorityQueue*', include the '*priorityqueue.h*' header file in your program and create an instance of the '*PriorityQueue*' class. You can then use the '*insert*' and '*removeMin*' member functions to add and remove elements from the queue.

### Build Heap
The '*buildheap*' program reads a JSON file of heap operations (insert and removeMin), executes the heap operations from the JSON file, and prints the priority queue as a JSON object to stdout.

To run the '*buildheap*' program, compile the '*buildheap.cxx*' file and pass the input JSON file as a command-line argument:

* $ g++ -std=c++11 -o buildheap buildheap.cxx priorityqueue.cpp
* $ ./buildheap input.json

### Create Teams
The '*createteams*' program uses the '*PriorityQueue*' to construct a greedy algorithm to pick fair 2-person teams from a list of Volleyball players. It reads a JSON file containing the win percentages of all 2-person teams, and outputs a JSON object containing the list of fair teams.

To run the '*createteams*' program, compile the '*createteams.cxx*' file and pass the input JSON file and the number of teams to create as command-line arguments:

* $ g++ -std=c++11 -o createteams createteams.cxx priorityqueue.cpp
* $ ./createteams input.json 4

### ALTERNATIVELY
To build the executable files, run the command '*make*' in the project directory. This will compile the C++ files and generate the following executables:

* '*buildheap.exe*': reads a JSON file of heap operations (insert and removeMin), executes the heap operations, and prints the priority queue as a JSON object to stdout.
* '*createteamdata.exe*': generates random data for n teams with win percentages between 40% and 60%.
* '*createteams.exe*': uses the priority queue to construct n "fair" 2-person teams from a list of volleyball players with past 2-person teams win percentages, and prints the teams as a JSON object to stdout.
* '*createheapoperationdata.exe*': generates random heap operations (insert and removeMin) and prints them as a JSON array to stdout.

To clean the project directory and remove all generated files, run the command '*make clean*'.

## Dependencies
This project requires a C++14 compiler and the JSON library "json.hpp". The library is included in the project directory and is already linked in the makefile.