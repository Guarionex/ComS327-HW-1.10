#ifndef DUNGEON_OBJECTS_H
#define DUNGEON_OBJECTS_H

typedef enum
{
  ROCK,
  ROOM,
  CORRIDOR
} Dungeon_Space_Type;

typedef struct
{
  int density;
} Dungeon_Space_Rock;

typedef struct
{
  int x;
  int y;
  int width;
  int height;
} Dungeon_Space_Room;

typedef struct
{
  Dungeon_Space_Room previous;
  Dungeon_Space_Room next;
} Dungeon_Space_Corridor;
typedef struct
{
  Dungeon_Space_Type space_type;
  Dungeon_Space_Rock rock;
  Dungeon_Space_Room room;
  Dungeon_Space_Corridor corridor;
} Dungeon_Space_Struct;

Dungeon_Space_Rock *Dungeon_Space_Rock_create(int density);
Dungeon_Space_Room *Dungeon_Space_Room_create(int width, int height);
Dungeon_Space_Corridor *Dungeon_Space_Corridor_create(Dungeon_Space_Room from, Dungeon_Space_Room to);
Dungeon_Space_Struct *Dungeon_Space_Struct_create(Dungeon_Space_Type space_type, ...);

#endif
