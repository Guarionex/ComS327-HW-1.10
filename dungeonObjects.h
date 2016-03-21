#ifndef DUNGEON_OBJECTS_H
#define DUNGEON_OBJECTS_H

#include <stdarg.h>
#include <stdint.h>

typedef enum
{
	FALSE,
	TRUE
} boolean;

typedef struct position
{
	int x;
	int y;
} pos_t;

extern const pos_t NULL_POS;

typedef enum stair_direction
{
	DOWNSTAIRS,
	UPSTAIRS
} stair_direction_t;

typedef struct stair
{
	pos_t location;
	stair_direction_t direction;
} stair_t;

typedef enum
{
  ROCK,
  ROOM,
  CORRIDOR
} Dungeon_Space_Type;

typedef struct
{
  uint8_t density;
} Dungeon_Space_Rock;

typedef struct
{
  int x;
  int y;
  int width;
  int height;
  uint8_t density;
} Dungeon_Space_Room;

typedef struct
{
  //char *id;
  uint8_t density;
  //Dungeon_Space_Room previous;
  //Dungeon_Space_Room next;
} Dungeon_Space_Corridor;

typedef union
{
  Dungeon_Space_Rock rock;
  Dungeon_Space_Room room;
  Dungeon_Space_Corridor corridor;
} Dungeon_Space_Union;

typedef struct
{
  Dungeon_Space_Type space_type;
  Dungeon_Space_Union space_union;
} Dungeon_Space_Struct;

Dungeon_Space_Rock Dungeon_Space_Rock_create(int density);
Dungeon_Space_Room Dungeon_Space_Room_create(int width, int height);
Dungeon_Space_Corridor Dungeon_Space_Corridor_create(/*char *id, Dungeon_Space_Room from, Dungeon_Space_Room to*/);
Dungeon_Space_Union Dungeon_Space_Union_create(Dungeon_Space_Type space_type, va_list ap);
Dungeon_Space_Struct Dungeon_Space_Struct_create(Dungeon_Space_Type space_type, ...);

/*
void Dungeon_Space_Rock_destroy(Dungeon_Space_Rock rock);
void Dungeon_Space_Room_destroy(Dungeon_Space_Room room);
void Dungeon_Space_Corridor_destroy(Dungeon_Space_Corridor corridor);
void Dungeon_Space_Union_destroy(Dungeon_Space_Type space_type, Dungeon_Space_Union dungeon_space);
void Dungeon_Space_Struct_destroy(Dungeon_Space_Struct dungeon_space);
*/


#endif
