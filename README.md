COM S 327, Spring 2015
Programming Project 1.09
PC Equipment and Updated Combat
Now we’ve got a dungeon full of super-powered monsters, but our combat semantics haven’t changed
to reflect that, so everything—monsters and PC—still dies in one round. Let’s pick up and use (some of)
those items and update the combat so it goes multiple rounds.
Characters have been updated with hitpoints and damage (if you put these in npc, you need to move
them to character). Give the PC a default number of hitpoints; you may use whatever value you like. The
PC’s default speed will remain at 10. It will also get a default damage dice, something small, like 0+1d4,
since this is bare-handed damage and will be augmented by equipment.
The PC gets equipment slots, one each for WEAPON, OFFHAND, RANGED, ARMOR, HELMET, CLOAK, GLOVES,
BOOTS, AMULET, LIGHT, and two for RING, ‘numbered’ a–l. The PC also gets 10 carry slots, numbered 0–
9. Equipped items do not impact carry. When the PC walks over an item, if it has an open carry slot, it
automatically picks the item up; else the item is ignored.
The following commands are added:
Command Meaning
w Wear an item. Prompts the user for a carry slot. If an item of that type is already
equipped, items are swapped.
t Take off an item. Prompts for equipment slot. Item goes to an open carry slot.
d Drop an item. Prompts user for carry slot. Item goes to floor.
x Expunge an item from the game. Prompts the user for a carry slot. Item is permanently
removed from the game
i List PC inventory
e List PC equipment
I Inspect an item. Prompts user for a carry slot. Item’s description is displayed
In all cases, failures should be handled gracefully. You may decide what that means, but it does not
mean, i.e., crashing the game, leaking memory, adding an extra carry slot, or expunging an item that the
user didn’t want expunged. The prompt should include a list of all appropriate slots including their slot
numbers and the name of the item in that slot. The user may abort the command by entering the escape
character.
Speed bonuses from equipment are applied additively to the PC’s base speed. Damage bonuses are
applied additively to the PC’s damage, e.g., all damage dice for all equipped items are rolled and added
together.
Combat is updated as follows:
• NPCs do not attack other NPCs. When an NPC attempts to move to a cell containing another NPC,
the current occupant is displaced to any open cell neighboring the occupant’s slot.
• Combat between PC and NPCs is initiated by attempts to move into the cell of the respective character.
The attack uses a character turn, so no move will occur, only the attack.
• All attempted attacks connect.
• When an attack connects, the damage of the attack is calculated by rolling all applicable damage
dice (NPCs have only one set; the PC has a base (bare-handed) set which is rolled only if nothing is
equipped in the weapon slot, to which is added rolls for all equipped items).
• Character hitpoints are reduced by the calculated damage. If hitpoints fall below zero1
, the character
is removed from the game. As always, if the PC dies, the game ends.
1Note that if you have HP as an unsigned type, it will never fall below zero. You will need to update it to a signed type.