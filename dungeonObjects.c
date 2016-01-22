#include "dungeonObjects.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

Dungeon_Space_Rock *Dungeon_Space_Rock_create(int density)
{
  Dungeon_Space_Rock *rock = malloc(sizeof(Dungeon_Space_Rock));
  rock->density = density;
  return rock;
}

Dungeon_Space_Room *Dungeon_Space_Room_create(int width, int height)
{
  Dungeon_Space_Room *room = malloc(sizeof(Dungeon_Space_Room));
  room->width = width;
  room->height = height;
  room->x = -1;
  room->y = -1;
  return room;
}

Dungeon_Space_Corridor *Dungeon_Space_Corridor_create(Dungeon_Space_Room from, Dungeon_Space_Room to)
{
  Dungeon_Space_Corridor *corridor = malloc(sizeof(Dungeon_Space_Corridor));
  corridor->previous = from;
  corridor->next = to;
  return corridor;
}

Dungeon_Space_Struct *Dungeon_Space_Struct_create(Dungeon_Space_Type space_type, ...)
{
  va_list ap;
  va_start(ap, space_type);
 
  Dungeon_Space_Struct *dungeon_space = malloc(sizeof(Dungeon_Space_Struct));
  dungeon_space->space_type = space_type;

  switch(space_type)
    {
    case ROCK:
      dungeon_space->rock = va_arg(ap, Dungeon_Space_Rock);
      break;
    case ROOM:
      dungeon_space->room = va_arg(ap, Dungeon_Space_Room);
      break;
    case CORRIDOR:
      dungeon_space->corridor = va_arg(ap, Dungeon_Space_Corridor);
      break;
    }

  va_end(ap);

  return dungeon_space;
}

void Dungeon_Space_Rock_destroy(Dungeon_Space_Rock *rock)
{
  free(rock);
}

void Dungeon_Space_Room_destroy(Dungeon_Space_Room *room)
{
  free(room);
}

void Dungeon_Space_Corridor_destroy(Dungeon_Space_Corridor *corridor)
{
  free(corridor->previous);
  free(corridor->next);
  free(corridor);
}

void Dungeon_Space_Struct_destroy(Dungeon_Space_Struct *dungeon_space)
{
  switch(dungeon_space->space_type)
    {
    case ROCK:
      free(dungeon_space->rock);
      break;
    case ROOM:
      free(dungeon_space->room);
      break;
    case CORRIDOR:
      free(dungeon_space->corridor);
      break;
    }

  free(dungeon_space);
}
