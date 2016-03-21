dungeonGenerator: dungeonObjects.o dungeonRoomGenerator.o dungeonLevelGenerator.o dungeonIO.o binheap.o Dijkstra.o Graph.o CharacterController.o GameStateManager.o dungeonGenerator.o
	gcc dungeonObjects.o dungeonRoomGenerator.o dungeonLevelGenerator.o dungeonIO.o binheap.o Dijkstra.o Graph.o CharacterController.o  GameStateManager.o dungeonGenerator.o -o dungeonGenerator -lm -lcurses

dungeonObjects.o: dungeonObjects.h dungeonObjects.c
	gcc -g -Wall -Werror dungeonObjects.c -c

dungeonRoomGenerator.o: dungeonRoomGenerator.h dungeonRoomGenerator.c
	gcc -g -Wall -Werror dungeonRoomGenerator.c -c

dungeonLevelGenerator.o: dungeonLevelGenerator.h dungeonLevelGenerator.c
	gcc -g -Wall -Werror dungeonLevelGenerator.c -c

dungeonIO.o: dungeonIO.h dungeonIO.c
	gcc -g -Wall -Werror dungeonIO.c -c
	
binheap.o: binheap.h binheap.c
	gcc -g -Wall -Werror binheap.c -c
	
Dijkstra.o: Dijkstra.h Dijkstra.c
	gcc -g -Wall -Werror Dijkstra.c -c

Graph.o: Graph.h Graph.c
	gcc -g -Wall -Werror Graph.c -c
	
CharacterController.o: CharacterController.h CharacterController.cpp
	g++ -g -Wall -Werror CharacterController.cpp -c

GameStateManager.o: GameStateManager.h GameStateManager.c
	gcc -g -Wall -Werror GameStateManager.c -c

dungeonGenerator.o: dungeonGenerator.c
	gcc -g -Wall -Werror dungeonGenerator.c -c

clean:
	rm -f *.o dungeonGenerator
