/**
 * FILE: react_game.c
 *
 * @author Julien Baeriswyl                (julien.baeriswyl@heig-vd.ch)
 * @author Arthur Benjamin Simon Passuello (arthur.passuello@heig-vd.ch)
 * @since  2017-04-20
 */
#include "react_game.h"

#include "bits.h"
#include "lcd.h"
#include "lcd_toolbox.h"
#include "gpio_toolbox.h"
#include "timer_toolbox.h"
#include "students_tools.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct ReactGame game;

LCDWindow wgame_run = (LCDWindow) {
    .title    = "Current game",
    .position = {
        .a = {
            .x = 0,
            .y = 0
        },
        .b = {
            .x = PIXELS_PER_ROW - 1,
            .y = PIXELS_PER_COL / 2 - 1
        }
    },
    .bgcolor = BLUE,
    .fgcolor = BRIGHT_YELLOW,
    .border  = BRIGHT_CYAN
};

LCDWindow wgame_score = (LCDWindow) {
    .title    = "Game scores",
    .position = {
        .a = {
            .x = 0,
            .y = PIXELS_PER_COL / 2
        },
        .b = {
            .x = PIXELS_PER_ROW - 1,
            .y = PIXELS_PER_COL - 1
        }
    },
    .bgcolor = BLACK,
    .fgcolor = BRIGHT_GREEN,
    .border  = BRIGHT_RED
};

Time random_ticks;

/**
 * Wait pressure of either SW0 (= no) or SW1 (= yes).
 */
static int wait_yes_no (void)
{
    struct GPIODetect sw0 = GPIO_DETECT_INIT(5, 12),
                      sw1 = GPIO_DETECT_INIT(5, 14);
    do
    {
        GPIO_DETECT_SAVE(sw0);
        GPIO_DETECT_SAVE(sw1);

        if (GPIO_DETECT_RISE(sw0))
        {
            return 0;
        }

        if (GPIO_DETECT_RISE(sw1))
        {
            return 1;
        }
    } while (1);

    return 0;
}

/**
 * Compute updated statistics based on last game, and display them.
 * 
 * @param newtime  [in] time of last game 
 */
static void react_game_update_score (Time newtime)
{
    char s[LCD_CHAR_PER_LINE + 1];
    
    // compute new stats
    ++game.score.nbGames;
    game.score.last      = newtime;
    game.score.best      = MIN(game.score.best,  game.score.last);
    game.score.worst     = MAX(game.score.worst, game.score.last);
    game.score.time_sum += game.score.last;
    game.score.pen_sum  += game.penalties;
    
    // Display window
    fb_window_disp(&wgame_score);
    
    // Display stats
    snprintf(s, LCD_CHAR_PER_LINE, "Number of games  : %10lu", game.score.nbGames);
    fb_window_print2(&wgame_score, s, 0);
    
    snprintf(s, LCD_CHAR_PER_LINE, "Last time    [ms]: %10lu", game.score.last);
    fb_window_print2(&wgame_score, s, 1);
    
    snprintf(s, LCD_CHAR_PER_LINE, "Best time    [ms]: %10lu", game.score.best);
    fb_window_print2(&wgame_score, s, 2);
    
    snprintf(s, LCD_CHAR_PER_LINE, "Worst time   [ms]: %10lu", game.score.worst);
    fb_window_print2(&wgame_score, s, 3);
    
    snprintf(s, LCD_CHAR_PER_LINE, "Average time [ms]: %10lu", game.score.time_sum / game.score.nbGames);
    fb_window_print2(&wgame_score, s, 4);
    
    snprintf(s, LCD_CHAR_PER_LINE, "Penalties average: %10lu", game.score.pen_sum / game.score.nbGames);
    fb_window_print2(&wgame_score, s, 5);
}

void react_game_reset (void)
{
    game = (struct ReactGame) {
        .started   = false,
        .intc_wait = false,
        .intc_done = false,
        .penalties = 0,
        .timer     = 0,
        .score     = (struct ReactScore) {
            .nbGames  = 0,
            .last     = 0,
            .best     = -1,
            .worst    = 0,
            .time_sum = 0,
            .pen_sum  = 0
        }
    };
    
    srand(time(NULL));
}

void react_game_init (void)
{
    struct GPIODetect sw1_detect = GPIO_DETECT_INIT(5, 14);
    
    ClearOutput(5, BIT15);
    game.started   = false;
    game.intc_wait = false;
    
    fb_window_disp(&wgame_run);
    fb_window_print2(&wgame_run, "To start game, press SW1:", 0);
    
    random_ticks = rand() % 320000; // ticks between 0 and 320000 (between 0 and 10 seconds)
    
    do
    {
        GPIO_DETECT_SAVE(sw1_detect);
    } while (!GPIO_DETECT_RISE(sw1_detect));
}

void react_game_start (void)
{
    fb_window_print2(&wgame_run, "GAME STARTED, wait LED0 to turn on !", 1);
    
    write_timer_value(0);
    game.timer     = 0;
    game.penalties = 0;
    game.intc_done = false;
    game.started   = true;
    start_timer();
    
    while (read_timer_value() <= random_ticks); // random delay

    SetOutput(5, BIT15);                        // turn on LED0
    game.intc_wait = true;
}

void react_game_stop (void)
{
    while (!game.intc_done);
    game.intc_wait = false;
    game.started   = false;
    stop_timer();
}

void react_game_result (void)
{
    Time response_time = (game.timer - random_ticks) / TIMER_TICKS_PER_MS;
    Time penalty_time  = game.penalties * REACT_GAME_PENALTY_MTIME;

    char s[LCD_CHAR_PER_LINE + 1];
    snprintf(s, LCD_CHAR_PER_LINE, "Your time [ms]: %lu + %lu (%lu penalties)", response_time, penalty_time, game.penalties);

    if (response_time < 1000 && game.penalties == 0) // if less than 1 second, no penalties
    {
        fb_window_print1(&wgame_run, s, 3, BRIGHT_GREEN);
    }
    else
    {
        fb_window_print1(&wgame_run, s, 3, BRIGHT_RED);
    }
    
    react_game_update_score(response_time + penalty_time);
}

void react_game_isr (void)
{
    if (game.intc_wait)
    {
        game.timer = read_timer_value();
        stop_timer();
        game.intc_done = true;
    }
    else if (game.started)
    {
        ++game.penalties;
    }
}

int react_game_continue (void)
{
    fb_window_print1(&wgame_run, "Do you want to continue ? (yes = SW1, no = SW0)", 5, BRIGHT_WHITE);
    return wait_yes_no();
}
