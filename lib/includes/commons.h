//=======================================================================\\
//                                                                       \\  
// Filename:    commons.h                                                \\
// Description: All defines specific to the commons simulation           \\
//                                                                       \\
// History:                                                              \\
//                                                                       \\
//    1/19/93    jmr    Created                                          \\
//   08/24/94    jmr    Readied to go online.                            \\
//                                                                       \\
//============== Copyright 1994 ===== Raymond Interactive Theatre, Ltd. =\\

#include <timing.h>

#define COOPERATE  5
#define EXPLOIT    1
#define POLICE     2
#define REWARD     3
#define WITHDRAW   4
#define SIP        COOPERATE
#define GULP       EXPLOIT
#define INHALE     POLICE
#define BLOW_INTO  REWARD
#define DO_NOTHING WITHDRAW
#define VAMPIRE    EXPLOIT
#define HUNTER     POLICE

#define ELIXIR_EFFECT_LENGTH   82      // How long does the effect last?
#define COMMONS_STARTING_LEVEL 5000    // The commons level at start 
#define COMMONS_MAX_LEVEL      10000   // Maximum pop. commons can reach
#define COMMONS_GROWTH_COEFF   0.0000001666666 // Growth coeff per second.
#define COMMONS_SAFE_HARVEST   0.015   // A percentage of the population that
                                       // that can be harvested with _NO_ 
                                       // effect on the population.

#define EXPLOITERS_HARVEST     COMMONS_MAX_LEVEL/60
#define MAX_BITERS_REWARD      EXPLOITERS_HARVEST
#define BONUS_MULTIPLIER       5 // Make the bonus tangible.

  /////////////////////////
 // Calculating Returns //
/////////////////////////
//
// COOPERATE role gain/loss:
//      The cooperaters base yield with this commons level (SAFE_HARVEST)
//
#define COOPERATERS_RETURN(level)        (level * COMMONS_SAFE_HARVEST)

//
// EXPLOIT role gain/loss:
//
// If no policing, then:-
// +    The EXPLOITERS_HARVEST + SAFE_HARVEST
// ====================================
//      The unpoliced exploiters return
//
// Else its policed and:
//       The base fine is number of players dependant. 
#define EXPLOITERS_RETURN(policed, level, players) \
        (policed ? (-19 - players) : EXPLOITERS_HARVEST + COMMONS_SAFE_HARVEST * level)

/*
// POLICE role loss:
//    (General Police Costs: Numbers of players * per player cost (players -1))
//  /   The total number of police that round
// =====================================
//      Cost per policer 
//
*/
#define POLICERS_RETURN(policers, players)   ((-players * (players - 1)) / policers)

/*
// REWARDERS role loss:
//      Basic cost of rewarding action/ number of rewarders
// =====================
//      Cost per rewarder
*/
#define REWARDERS_RETURN(players, rewarders) ((-players * (players - 1)) / rewarders)
#define REWARDERS_REWARD(players)            (33.571428 - (players * 0.7142857))
 
//
// WITHDRAW role gain:
//
#define WITHDRAWERS_RETURN(players)         (36 - players)
