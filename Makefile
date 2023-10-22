all: compile link

compile:

	cd game/compiled && g++ -c ../gameState/*.cpp
	g++ -c main.cpp

link:

	g++ game/compiled/*.o main.o -o main -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system