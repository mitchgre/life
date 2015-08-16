# Makefile for Week8's assignments

# Author:		Gregory Mitchell
# Date Created:		11/23/14
# Last Modified:	11/23/14
# Filename:		Makefile
# Overview:		Makes the project implementation and the exercise for Week8.

all: 		logger quartiles merge getInt gameOfLife gameOfLife-ncurses-menu 

logger: 	logger.cpp
		g++ logger.cpp -o logger

quartiles: 	quartiles.cpp
		g++ quartiles.cpp -o quartiles

merge:	 	merge.cpp
		g++ merge.cpp -o merge

getInt: 	getInt.cpp
		g++ getInt.cpp -o getInt

gameOfLife: 	gameOfLife.cpp gameOfLife-week7 gameOfLife-ncurses-menu
		g++ gameOfLife.cpp -o gameOfLife

gameOfLife-week7: 	gameOfLife-week7.cpp
			g++ gameOfLife-week7.cpp -o gameOfLife-week7

gameOfLife-ncurses-menu: gameOfLife-ncurses-menu.cpp
		g++ gameOfLife-ncurses-menu.cpp -o gameOfLife-ncurses-menu -lncurses -lmenu

clean: 
		rm logger quartiles merge getInt gameOfLife gameOfLife-ncurses-menu gameOfLife-week7






