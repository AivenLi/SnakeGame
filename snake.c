/*
 *   Author: Aiven.Li
 *   Time:   2019.10
 *   
 *   Filename: snake.c
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
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "snake.h"
#include "loccon.h"

//
// Function:     Initialize the snake.
// Parameter:    None.
// Return Value: s_msg(snake).
// Describe:     
//     This function mainly initializes some basic parameters of 
// the game, the length of the snake body, and the difficulty of
// the game (the speed of the snake movement).
//            
//
s_msg init_snake(void) {

	s_msg   snake;
	sp_body temp;
	sp_body body;
	int     snake_x;
	int     i;
	//
	//  This piece of code is dedicated to "lazy players".
	//
	snake_x      = DEFAULT_SNAKE_X;
	snake.level_up = TRUE;
	snake.maxlength = ( ( DEFAULT_WALL_WIDTH-1 ) * ( DEFAULT_WALL_HIGHT-1 ) ) ;
	snake.length = DEFAULT_SNAKE_LENGTH;
	snake.width  = DEFAULT_WALL_WIDTH;
	snake.hight  = DEFAULT_WALL_HIGHT;
	snake.direction = right;
#if   ( LEVEL_THE_WAY == LEVEL_LINK )
	snake.level = create_level();
#elif ( LEVEL_THE_WAY == LEVEL_INTE )
	snake.level = LEVEL_TIMES / 2;
#else
	snake.level = LEVEL_TIMES / 2;
#endif
	//
	//    These two nodes are used to record the snake head 
	// and the snake tail respectively, which is much faster
	// when the snake is refreshed after the game starts.
	//
	snake.s_head = create_body(0, 0);
	snake.s_tail = create_body(0, 0);

	body = create_body(snake_x, DEFAULT_SNAKE_Y);
	snake.snake = body;
	temp = body;
	snake_x -= 2;
	for ( i = 0; i < snake.length-1; i++ ) {

		body = create_body(snake_x, DEFAULT_SNAKE_Y);
		temp->next = body;
		temp = temp->next;
		snake_x -= 2;
	}
	snake.food = (sp_food)malloc(sizeof(s_food));
	if ( snake.food == NULL ) {

		perror("I can't create food");
		exit(-1);
	}
	return snake;
}
//
// Function:     Create four walls for this snake.
// Parameter:    A snake, wall size: width and hight.
// Return Value: None.
// Describe:     
//     Set the size of the wall according to the parameters 
// width and hight.      
//
void set_wall(sp_msg snake, int const width, int const hight) {

	int x;
	int y;
	sp_body body;

	if ( width > WALL_MAX_WIDTH ) {

		snake->width = WALL_MAX_WIDTH;
	} else if ( width < WALL_MIN_WIDTH ) {

		snake->width = WALL_MIN_WIDTH;
	} else {

		snake->width = width;
	}
	if ( hight > WALL_MAX_HIGHT ) {

		snake->hight = WALL_MAX_HIGHT;
	} else if ( hight < WALL_MIN_HIGHT ) {

		snake->hight = WALL_MIN_HIGHT;
	} else {

		snake->hight = hight;
	}
	x = DEFAULT_SNAKE_X;
	y = snake->hight / 2;
	body = snake->snake;

	while ( body != NULL ) {

		body->x = x;
		body->y = y;
		x -= 2;
		body = body->next;
	}
	snake->maxlength = ( snake->width-1 ) * ( snake->hight-1 );
}
//
// Look at the function name.
//
void init_map(int width, int hight) {

	int w;
	int h;
	//
	// The width of the wall must be even, otherwise it will coincide.
	//
	if ( width & 0x00000001 ) {

		width += 1;
	}
	// Show the top and bottom wall.
	for ( w = 0; w < width; w += 2 ) {
		
		printxy(w, 0, WALL);
		printxy(w, hight, WALL);
	}
	// Show the left and right wall.
	
	for ( h = 0; h < hight; h++ ) {

		printxy(0, h, WALL);
		printxy(width, h, WALL);
	}
	printxy(width, hight, WALL);
}
//
// The food that first appeared (fixed position).
//
void init_food(sp_msg const snake) {

	snake->food->x = snake->width - 10;
	snake->food->y = snake->hight / 2;
	printxy(snake->width - 10, snake->hight / 2, FOOD);
}

#if ( LEVEL_THE_WAY == LEVEL_LINK )
sp_level create_level(void) {

	sp_level head;
	sp_level p;
	sp_level n;
	int i = 0;
	int ms = LEVEL_TIMES / 2;

	n = (sp_level)malloc(sizeof(s_level));
	if ( n == NULL ) {

		perror("Create snake level failed");
		system("pause");
		exit(-1);
	}
	head = n;
	p = n;
	n->ms = ms++;
	ms = ms % LEVEL_TIMES;
	while ( ++i < LEVEL_TIMES ) {

		n = (sp_level)malloc(sizeof(s_level));
		if ( n == NULL ) {

			perror("Create snake level failed");
			system("pause");
			exit(-1);
		}
		n->ms = ms++;
		ms = ms % LEVEL_TIMES;
		n->prev = p;
		p->next = n;
		p = n;
	}
	p->next = head;
	head->prev = p;
	return head;
}
void free_level(sp_level level) {

	sp_level head;
	sp_level temp;

	head  = level;
	temp  = level->next;
	level = temp->next;

	while ( head != temp ) {

		free(temp);
		temp = level;
		level = level->next;
	}
	free(head);
}
#elif ( LEVEL_THE_WAY == LEVEL_INTE )

#else

#endif

sp_body create_body(int const x, int const y) {

	sp_body body;

	body = (sp_body)malloc(sizeof(s_body));
	if ( body == NULL ) {

		perror("Create snake's body failed");
		exit(-1);
	}
	body->x = x;
	body->y = y;
	body->next = NULL;

	return body;
}
void free_body(sp_body snake) {

	sp_body s = snake;
	
	while ( s != NULL ) {

		s = snake->next;
		free(snake);
		snake = s;
	}
}
void free_head(sp_body head) {

	free(head);
}
void free_tail(sp_body tail) {

	free(tail);
}
//
//    The secondary function only prints snakes that have 
// not started yet, and will not call the function again.
//
void print_snake(sp_body const snake) {

	sp_body body = snake;
	
	while ( body != NULL ) {

		printxy(body->x, body->y, BODY);
		body = body->next;
	}
}

void create_food(sp_msg snake) {

	int x;
	int y;
	_bool flag = FALSE;
	sp_body s;

	srand( (unsigned)time(NULL) );
	//
	//     The x coordinate must be an even number 
	// because one food occupies two output positions.
	// And he position where the food appears cannot 
	// also coincide with the body of the snake.    
	//
	while ( !flag ) {

		snake->food->x = rand() % ( snake->width-2 ) + 2;
		if ( snake->food->x & 1 ) {

			continue;
		}
		snake->food->y = rand() % ( snake->hight-1 ) + 1;
		s = snake->snake;
		flag = TRUE;
		while ( s != NULL ) {

			if ( s->x == snake->food->x && s->y == snake->food->y ) {
				
				flag = FALSE;
				break;
			}
			s = s->next;
		}
	}
}

void free_food(sp_food food) {

	free(food);
}

void move_snake(sp_msg snake) {
	//
	//      Every time we move the snake, we need to 
	// determine its current direction of movement to
	// calculate the next coordinates of the snake head.
	//
#if ( MOVE_SNAKE_VERSION == VERSION_1 )

	void move_up    (sp_msg snake);
	void move_down  (sp_msg snake);
	void move_left  (sp_msg snake);
	void move_right (sp_msg snake);
	//
	// Use a better version and remove those redundant code (repetitive).
	//
	switch ( snake->direction ) {

		case up:
			move_up(snake);
			break;
		case down:
			move_down(snake);
			break;
		case left:
			move_left(snake);
			break;
		case right:
			move_right(snake);
			break;
		default:
			system("cls");
			printf("Error: An unknown error has occurred. Please contact the administrator to submit a bug.\n");
			system("pause");
			exit(-1);
	}
	snake->s_head->x = snake->snake->x;
	snake->s_head->y = snake->snake->y;

#elif ( MOVE_SNAKE_VERSION == MOVE_VERSION_2 )

	void save_tail_coordinate(sp_msg snake);
	sp_body s;
	int x;
	int y;

	save_tail_coordinate(snake);
	
	x = snake->snake->x;
	y = snake->snake->y;
	switch ( snake->direction ) {

		case up:
			//x = snake->snake->x;
			y = snake->snake->y-1;
			break;
		case down:
			//x = snake->snake->x;
			y = snake->snake->y+1;
			break;
		case left:
			x = snake->snake->x-2;
			break;
		case right:
			x = snake->snake->x+2;
			break;
		default:
			system("cls");
			printf("Error: An unknown error has occurred. Please contact the administrator to submit a bug.\n");
			system("pause");
			exit(-1);
	}
	s = create_body(x, y);
	snake->s_head->x = x;
	snake->s_head->y = y;
	s->next      = snake->snake;
	snake->snake = s;
	
#else
	//
	// Version 3, not yet implemented.
	//
#endif
}

#if ( MOVE_SNAKE_VERSION == VERSION_1 )

void move_up(sp_msg snake) {

	sp_body s     = snake->snake;
	sp_body s_end = s->next;
	//
	// Find for snake tail.
	//
	while ( s_end->next != NULL ) {

		s = s_end;
		s_end = s_end->next;
	}
	snake->s_tail->x = s_end->x;
	snake->s_tail->y = s_end->y;
	free(s_end);
	s->next = NULL;
	//
	//      We should judge whether the creation of the node is 
	// successful, but I think it should not fail if the tail 
	// node is first released. In theory, this is true, but 
	// I have not tested it.
	//
	s = create_body( snake->snake->x, snake->snake->y-1 );
	s->next      = snake->snake;
	snake->snake = s;
	//
	//    In fact, only the snake head and the snake tail have 
	// changed, and the rest of the nodes are pushed forward.
	//    This is very simple, we only need to create a new 
	// node as a snakehead, release the tail node.
	//
}

void move_down(sp_msg snake) {
	
	//
	//    When I started implementing this function, 
	// it seems to be similar to the code of the previous
	// function(move_up), so I think I need to change the strategy.
	//    But as a lesson, I should keep this ugly version.
	//
	sp_body s     = snake->snake;
	sp_body s_end = s->next;

	while ( s_end->next != NULL ) {

		s = s_end;
		s_end = s_end->next;
	}
	snake->s_tail->x = s_end->x;
	snake->s_tail->y = s_end->y;
	free(s_end);
	s->next = NULL;

	s = create_body( snake->snake->x, snake->snake->y+1 );
	s->next      = snake->snake;
	snake->snake = s;
}

void move_left(sp_msg snake) {

	sp_body s     = snake->snake;
	sp_body s_end = s->next;

	while ( s_end->next != NULL ) {

		s = s_end;
		s_end = s_end->next;
	}
	snake->s_tail->x = s_end->x;
	snake->s_tail->y = s_end->y;
	free(s_end);
	s->next = NULL;
	s = create_body( snake->snake->x-2, snake->snake->y );
	s->next      = snake->snake;
	snake->snake = s;
}

void move_right(sp_msg snake) {

	sp_body s     = snake->snake;
	sp_body s_end = s->next;

	while ( s_end->next != NULL ) {

		s = s_end;
		s_end = s_end->next;
	}
	snake->s_tail->x = s_end->x;
	snake->s_tail->y = s_end->y;
	free(s_end);
	s->next = NULL;
	s = create_body( snake->snake->x+2, snake->snake->y );
	s->next      = snake->snake;
	snake->snake = s;
}

#elif ( MOVE_SNAKE_VERSION == MOVE_VERSION_2 )

void save_tail_coordinate(sp_msg snake) {

	sp_body s     = snake->snake;
	sp_body s_end = s->next;

	while ( s_end->next != NULL ) {

		s = s_end;
		s_end = s_end->next;
	}
	snake->s_tail->x = s_end->x;
	snake->s_tail->y = s_end->y;
	free(s_end);
	s->next = NULL;
	s_end = NULL;
}

#else
	//
	// Version 3, not yet implemented.
	//
#endif

_bool eaten_food(sp_msg snake) {

	if ( ( snake->s_head->x == snake->food->x ) &&
		 ( snake->s_head->y == snake->food->y ) ) {

		snake->food->x = 0;
		snake->food->y = 0;
		return TRUE;
	} 
	return FALSE;
}

_bool is_death(sp_msg snake) {

	sp_body s;
	//
	// Hit the wall.
	//
	if ( ( snake->snake->x <= 0 ) ||
		 ( snake->snake->x >= snake->width ) ||
		 ( snake->snake->y <= 0 ) ||
		 ( snake->snake->y >= snake->hight ) ) {
		//printf("Hit Yes\n");
		return TRUE;
	}
	//
	// Eat yourself.
	//
	s = snake->snake->next->next;
	while ( s != NULL ) {

		if ( ( s->x == snake->snake->x ) &&
			 ( s->y == snake->snake->y ) ) {
			//printf("Eat Yes\n");
			return TRUE;
		}
		s = s->next;
	}
	return FALSE;
}