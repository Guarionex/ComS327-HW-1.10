all:

dungeonObjects: dungeonObjects.h dungeonObjects.c
	gcc -g -Wall -Werror dungeonObjects.c -o dungeonObjects
