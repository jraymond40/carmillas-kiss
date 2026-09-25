/*
//=======================================================================\\
//                                                                       \\  
// Filename:    location.c                                               \\
//                                                                       \\
// Description: Functions and attributes for an aggregation of objects.  \\
//                                                                       \\
// History:                                                              \\
//                                                                       \\
// 08/30/93    jmr    Complete rewrite of the old "place" functions      \\
//                                                                       \\
//==================== Copyright 1993 ===== Raymond Interactive Theatre =\\
//                                                                       \\
// initialize()                                                          \\
// init()                                                                \\
// direction_cmds()                                                      \\
// query_adjacent_locations()                                            \\
// query_possible_directions()                                           \\
// set_adjacent_locations()                                              \\
// query_long()                                                          \\
//                                                                       \\
//=======================================================================\\
*/

#include <config.h>
#include <std_defs.h>
#include <english.h>

// Prototypes
varargs void initialize(object one, object two);

inherit "/classes/inanimate/intransients/inanm_intrns_holder";
inherit "/classes/sharer";

private string *adjacent_locations;  // Locations adjacent to this one.    
private string *possible_directions; // Possible directions one can move.  
private string *associated_doors;    // The door associated w/ moving that way. 
private string *npc_list;            // The NPC's inited at this location.
private string *npcai_list;          // The NPCAI's inited at this location.

void 
set_adjacent_locations(string *locs, string *dirs, string *doors) 
{ 
   adjacent_locations  = locs;
   possible_directions = dirs;
   associated_doors    = doors;   
}

void
create()
{
   inanm_intrns_holder::create();

  // Defaults that can be overridden by each instance.
   set_light(ON);
   set_max_bearable (INFINITE);
   set_flammability (NONE);
   set_burn_duration(0);
   set_form         (SOLID);
   set_rigidity     (RIGID);
   set_object_type(LOCATION);
   set_manner_held("here");
   set_adjacent_locations(({""}),({""}), ({""})); // By default, unconnected.
}

//
// Initialize this location w/ doors, NPC's and inanimate objects.
//
varargs
void 
initialize(object stage, object loc)
{
   int    i;
   string result;
   string error;
   string str;
   object obj;

   inanm_intrns_holder::initialize(stage);

   if (associated_doors)
   {
      for (i = 0; i < sizeof(associated_doors); i++)
      {
         // Is there a door to worry about?
         if (associated_doors[i] != "")
         {
            str =  DOOR_DIR + associated_doors[i] + ".c";
            obj = find_object(str);
            if (obj) add_shared_object(obj); // This is an object we're sharing
            else
            {
               error = catch(obj = clone_object(str));

               if ((!obj || error) && LOCATION_DEBUG)
                  write_file(LOCATION_LOG, this_object()->query_short() + 
                     " couldn't clone: " + str + "\n");
               else if (obj) obj->initialize((loc ? loc : this_object()));
            }
         } 
      }
   }
   if (npc_list)
   {
      for (i = 0; i < sizeof(npc_list); i++)
      {
         str =  NPCS_DIR + npc_list[i] + ".c";

         error = catch(obj = clone_object(str));

         if ((!obj || error) && LOCATION_DEBUG)
            write_file(LOCATION_LOG, this_object()->query_short() + 
            " couldn't clone: " + str + "\n");
         if (obj) obj->initialize((loc ? loc : this_object())); 
      }
   }
   if (npcai_list)
   {
      for (i = 0; i < sizeof(npcai_list); i++)
      {
         str =  NPCAIS_DIR + npcai_list[i] + ".c";

         error = catch(obj = clone_object(str));

         if ((!obj || error) && LOCATION_DEBUG)
            write_file(LOCATION_LOG, this_object()->query_short() + 
            " couldn't clone: " + str + "\n");

         if (obj) obj->initialize((loc ? loc : this_object()));
      }
   }
}

// Location's can be initialized as already having NPC's in them.
void 
set_npc_list(string *list)
{
   npc_list = list;
}

void 
set_npcai_list(string *list)
{
   npcai_list = list;
}

int 
exit(string str) 
{
   int    i, err;
   object tp, dest, door;

   i  = member_array(str, possible_directions);
   tp = this_player();
   if (! valid_action(tp))
   {
      notify_fail("    You can't seem to move.\n");
      return FAIL;
   }
   if (i == -1) 
   {
      notify_fail("    You can't move that way.\n");
      return FAIL;
   }

   dest = find_object(LOCATION_DIR + adjacent_locations[i]);
   if (!dest)
   {  // Location may not have been loaded yet, so try it now.
      err = catch(call_other(LOCATION_DIR + adjacent_locations[i], "??"));
      if (err != 0)
         write_file(LOCATION_LOG, (string) this_object()->query_short() + 
            "'s 'exit' function was unable to find it's adjacent_location: " +
            LOCATION_DIR + adjacent_locations[i] + ".\n");
      dest = find_object(LOCATION_DIR + adjacent_locations[i]);
      if (!dest) 
      {
         notify_fail(
            "    The area you headed to is still under construction, and " +
            "are unable to get there currently.\n");
         return FAIL;
      }
      dest->initialize(0);
   }
   
   door = find_object(DOOR_DIR + associated_doors[i] + ".c");

   if (door)
   {
      if((int) door->query_closed() == TRUE)
      {
         notify_fail("   The " + door->query_short() + " in that direction " +
            forms_of_Be(THIRD_PERSON, PRESENT, door->query_aggregate() + 1)
            + " closed.\n");
         return FAIL;
      }
   }
   // If no door specified, or engine couldn't find door, 
   // or pass_through okay, then proceed.
   tp->move(dest, str);

   return SUCCEED;
}

string *query_adjacent_locations()   { return adjacent_locations;  }
string *query_possible_directions()  { return possible_directions; }
string *query_associated_doors()     { return associated_doors; }

// 
// There needs to be light here to see description::query_long() 
//
string query_long() 
{
   /* If the number of lights == 0, then it's dark... */
   if (set_light(0) <= 0) 
      return "It is dark here and impossible to make out any details.";
   else
      return (inanm_intrns_holder::query_long());
}

string query_pronoun()    { return "this area"; }
string query_possessive() { return "this area's"; }
string query_objective()  { return "this area"; }

void 
add_light()          
{ 
   set_light(set_light(0) + 1); 
}

void 
remove_light()       
{ 
   int lights;
   lights = set_light(0); // How many lights?
   set_light((lights <= 1 ? -1 : --lights)); 
}
