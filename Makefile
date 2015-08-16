# Makefile for Week8's assignments

# Author:		Gregory Mitchell
# Date Created:		11/23/14
# Last Modified:	08/16/1
# Filename:		Makefile
# Overview:		Makes the project implementation and the exercise for Week8.

all: 		gameOfLife gameOfLife-ncurses-menu 

gameOfLife: 	gameOfLife.cpp gameOfLife-noAnim gameOfLife-ncurses-menu
		g++ gameOfLife.cpp -o gameOfLife

gameOfLife-noAnim: 	gameOfLife-noAnim.cpp
			g++ gameOfLife-noAnim.cpp -o gameOfLife-noAnim

gameOfLife-ncurses-menu: gameOfLife-ncurses-menu.cpp
		g++ gameOfLife-ncurses-menu.cpp -o gameOfLife-ncurses-menu -lncurses -lmenu

clean: 
		rm  gameOfLife gameOfLife-ncurses-menu gameOfLife-week7






