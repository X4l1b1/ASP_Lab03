/**
 * FILE: react_game.h
 *
 * @author Julien Baeriswyl                (julien.baeriswyl@heig-vd.ch)
 * @author Arthur Benjamin Simon Passuello (arthur.passuello@heig-vd.ch)
 * @since  2017-04-20
 */
#ifndef ASP_A_BAERISWYL_PASSUELLO_REACT_GAME_H_
#define ASP_A_BAERISWYL_PASSUELLO_REACT_GAME_H_

#include "students_defs.h"
#include "timer_toolbox.h"

#define REACT_GAME_PENALTY_MTIME 100

/* Game data structure definition */
struct ReactScore
{
    ulong nbGames;
    Time  last,
          best,
          worst,
          time_sum;
    ulong pen_sum;
};

struct ReactGame
{
    ulong timer;
    ulong penalties;
    bool  started;
    bool  intc_wait;
    bool  intc_done;
    struct ReactScore score;
};

/**
 * Reset state of game, statistics included.
 */
void react_game_reset (void);

/**
 * Prepare new game.
 */
void react_game_init (void);

/**
 * Start new game.
 */
void react_game_start (void);

/**
 * Stop current game.
 */
void react_game_stop (void);

/**
 * Display result with updated statistics.
 */
void react_game_result (void);

/**
 * Subroutine called by interruption handler.
 */
void react_game_isr (void);

/**
 * Ask user if he wants to continue to play game.
 */
int  react_game_continue (void);

#endif /* ASP_A_BAERISWYL_PASSUELLO_REACT_GAME_H_ */
