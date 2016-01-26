dungeonGenerator: dungeonObjects.o dungeonRoomGenerator.o dungeonLevelGenerator.o dungeonGenerator.o
	gcc dungeonObjects.o dungeonRoomGenerator.o dungeonLevelGenerator.o dungeonGenerator.o -o dungeonGenerator -lm

dungeonObjects.o: dungeonObjects.h dungeonObjects.c
	gcc -g -Wall -Werror dungeonObjects.c -c

dungeonRoomGenerator.o: dungeonRoomGenerator.h dungeonRoomGenerator.c
	gcc -g -Wall -Werror dungeonRoomGenerator.c -c

dungeonLevelGenerator.o: dungeonLevelGenerator.h dungeonLevelGenerator.c
	gcc -g -Wall -Werror dungeonLevelGenerator.c -c

dungeonGenerator.o: dungeonGenerator.c
	gcc -g -Wall -Werror dungeonGenerator.c -c

clean:
	rm -f *.o dungeonGenerator
