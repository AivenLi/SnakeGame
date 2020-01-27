/*
 *   Author: Aiven.Li
 *   Time:   2019.10
 *   
 *   Filename: snake.h
 *	 This file is licensed under the MIT License as stated below
 *
 *   Copyright (c) 2019-2020 Aiven Li
 *
 *   Permission is hereby granted, free of charge, to any person obtaining a copy
 *   of this software and associated documentation files (the "Software"), to deal
 *   in the Software without restriction, including without limitation the rights
 *   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *   copies of the Software, and to permit persons to whom the Software is
 *   furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all
 *   copies or substantial portions of the Software.
 * 
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *   SOFTWARE.
 *   Describe:
 *             Snake game based on windows console.
 */
#ifndef _SNAKE_H_
#define _SNAKE_H_

typedef char _bool;
#define TRUE  1
#define FALSE 0
//
// Snake move.
//
#define MOVE_VERSION_1 1
#define MOVE_VERSION_2 2
#define MOVE_VERSION_3 3

#define MOVE_SNAKE_VERSION MOVE_VERSION_2
//
// Snake level.
//
#define LEVEL_INTE 4
#define LEVEL_LINK 5
#define LEVEL_NONE 6

#define LEVEL_THE_WAY LEVEL_INTE

#define LEVEL_TIMES 1000
// Model.
#define MANU_SET_LEVEL 100
#define AUTO_SET_LEVEL 1

//
// We need a rule to limit the scope of the snake's activity.
//
#define WALL_MIN_WIDTH 30
#define WALL_MAX_WIDTH 90
#define WALL_MIN_HIGHT 12
#define WALL_MAX_HIGHT 28
//
//    Of course, some players want to start playing directly, 
// so we also need to set some default values.
//
#define DEFAULT_WALL_WIDTH    50
#define DEFAULT_WALL_HIGHT    28
#define DEFAULT_SNAKE_LENGTH  3
#define DEFAULT_SNAKE_X       6
#define DEFAULT_SNAKE_Y ( DEFAULT_WALL_HIGHT / 2 )
//
//      Next is to define the various properties of the snake.
//  Yes,the representative pointer with "p", I know that this
//  name is not reasonable, but this is the way I can think of
//  now.
//
typedef struct snake_food      *sp_food;
typedef struct snake_body      *sp_body;
typedef struct snake_msg       *sp_msg;
typedef enum   snake_direction se_dir;
typedef struct snake_food      s_food;
typedef struct snake_body      s_body;
typedef struct snake_msg       s_msg;

#if ( LEVEL_THE_WAY == LEVEL_LINK )
typedef struct snake_level     *sp_level;
typedef struct snake_level     s_level;
struct snake_level {

	int ms;
	sp_level next;
	sp_level prev;
};
#elif ( LEVEL_THE_WAY == LEVEL_INTE )
	
#else

#endif

//
//     The current direction of the snake.
//     The lack of the snake's mobile algorithm version 1 is obvious, 
// version 2 is slightly better, I am thinking about the version 3 algorithm.
//
#if ( MOVE_SNAKE_VERSION == MOVE_VERSION_1 )

enum snake_direction {

	up,
	down,
	left,
	right
};
#elif ( MOVE_SNAKE_VERSION == MOVE_VERSION_2 )

enum snake_direction {

	up,
	down,
	left,
	right
};
#else

#endif

struct snake_food {

	int x;
	int y;
};

struct snake_body {

	int x;
	int y;
	sp_body next;
};


struct snake_msg {

	_bool level_up;
	int maxlength;
	int length;
	int width;
	int hight;
#if   ( LEVEL_THE_WAY == LEVEL_INTE )
	int level;
#elif ( LEVEL_THE_WAY == LEVEL_LINK )
	sp_level level;
#else
	// do something.
	int level;
#endif
	sp_food food;
	sp_body snake;
	sp_body s_head;
	sp_body s_tail;
	se_dir direction;
};



void     set_wall    (sp_msg        snake, int const width, int const hight );
void     init_map    (int           width, int       hight);
void     print_snake (sp_body const snake);
void     init_food   (sp_msg  const snake);
void     create_food (void);
void     free_food   (sp_food);
void     move_snake  (sp_msg snake);
#if ( LEVEL_THE_WAY == LEVEL_LINK )
sp_level create_level(void);
void     free_level  (sp_level level);
#endif
_bool    eaten_food  (sp_msg snake);
_bool    is_death    (sp_msg snake);
s_msg    init_snake  (void);

sp_body  create_body (int const x, int const y);
void     free_body   (sp_body snake);
void     free_head   (sp_body head);
void     free_tail   (sp_body tail);


#endif