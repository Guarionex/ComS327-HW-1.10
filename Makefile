dungeonGenerator: dungeonObjects.o dungeonRoomGenerator.o dungeonLevelGenerator.o dungeonIO.o binheap.o Dijkstra.o Graph.o CharacterController.o GameStateManager.o dice.o dungeonGenerator.o
	g++ dungeonObjects.o dungeonRoomGenerator.o dungeonLevelGenerator.o dungeonIO.o binheap.o Dijkstra.o Graph.o CharacterController.o  GameStateManager.o dice.o dungeonGenerator.o -o dungeonGenerator -lm -lcurses

dungeonObjects.o: dungeonObjects.h dungeonObjects.cpp
	g++ -g -Wall -Werror dungeonObjects.cpp -c

dungeonRoomGenerator.o: dungeonRoomGenerator.h dungeonRoomGenerator.cpp
	g++ -g -Wall -Werror dungeonRoomGenerator.cpp -c

dungeonLevelGenerator.o: dungeonLevelGenerator.h dungeonLevelGenerator.cpp
	g++ -g -Wall -Werror dungeonLevelGenerator.cpp -c

dungeonIO.o: dungeonIO.h dungeonIO.cpp
	g++ -g -Wall -Werror dungeonIO.cpp -c
	
binheap.o: binheap.h binheap.cpp
	g++ -g -Wall -Werror binheap.cpp -c
	
Dijkstra.o: Dijkstra.h Dijkstra.cpp
	g++ -g -Wall -Werror Dijkstra.cpp -c

Graph.o: Graph.h Graph.cpp
	g++ -g -Wall -Werror Graph.cpp -c
	
CharacterController.o: CharacterController.h CharacterController.cpp
	g++ -g -Wall -Werror CharacterController.cpp -c

GameStateManager.o: GameStateManager.h GameStateManager.cpp
	g++ -g -Wall -Werror GameStateManager.cpp -c

dice.o: dice.h dice.cpp
	g++ -g -Wall -Werror dice.cpp -c
	
dungeonGenerator.o: dungeonGenerator.cpp
	g++ -g -Wall -Werror dungeonGenerator.cpp -c

clean:
	rm -f *.o dungeonGenerator
