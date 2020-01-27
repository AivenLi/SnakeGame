/*
 *   Author: Aiven.Li
 *   Time:   2019.10
 *   
 *   Filename: main.c
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
#include <string.h>
#include <time.h>
//  Socket
/*
#include <winsock2.h>
#include <windows.h>
#pragma comment(lib, "ws2_32.lib")
*/
#include "snake.h"
#include "loccon.h"

#define MENU_X 30
#define MENU_NUM 5

#define MENU_START_GAME   0
#define AUTO_SPEED_GAME   1
#define START_SPEED_GAME  2
#define MAP_SIZE_GAME     3
#define EXIT_GAME         4

#define S_ICON "¡ô"
#define N_ICON "     "

static void rel_res(sp_msg snake);

static int my_strlen(char const *str) {

	int i = 0;

	while ( *str != '\0' ) {
		
		i++;
		str++;
	}
	return i;
}

static void menu(sp_msg snake) {
	
	int i;
	int map_w;
	int map_h;

#if ( LEVEL_THE_WAY == LEVEL_INTE )
	int level;
#elif ( LEVEL_THE_WAY == LEVEL_LINK )
	int level;
#else
	int level;
#endif

	char *menu[MENU_NUM] = {
							"1. Start game",
							"2. Automatic speed increase: ",
							"3. Starting speed (0-999), 0 fastest: ",
							"4. Set the map size(x y): ",
							"5. Exit game"
							};

	for ( i = 0; i < MENU_NUM; i++ ) {
	
		printxy(MENU_X, i, menu[i]);
	}
	printxy(MENU_X+my_strlen(menu[1])+1, 1, snake->level_up ? "TRUE" : "FALSE");
//	printxy(MENU_X+my_strlen(menu[2])+1, 2, snake
	i = 0;
	printxy(MENU_X-2, 0,  S_ICON);
	
	while ( 1 ) {

		printxy(MENU_X-2, 10, NONE);
		if ( GetAsyncKeyState(VK_UP) ) {

			Sleep(500);
			printxy(MENU_X-2, i, NONE);
			i -= 1;
			if ( i < 0 ) {

				i = MENU_NUM-1;
			}
			printxy(MENU_X-2, i, S_ICON);
		} else if ( GetAsyncKeyState(VK_DOWN) ) {

			Sleep(500);
			printxy(MENU_X-2, i, NONE);
			i += 1;
			if ( i >= MENU_NUM ) {

				i = 0;
			}
			
			printxy(MENU_X-2, i, S_ICON);
		} else if ( GetAsyncKeyState(VK_SPACE) ) {

			Sleep(500);
			switch ( i ) {

				case MENU_START_GAME:
					system("cls");
					return;
				case AUTO_SPEED_GAME:
					snake->level_up = !(snake->level_up);
					printxy(MENU_X+my_strlen(menu[i])+1, i, N_ICON);
					printxy(MENU_X+my_strlen(menu[i])+1, i, snake->level_up ? "TRUE" : "FALSE");
					break;
				case START_SPEED_GAME:
					printxy(MENU_X+my_strlen(menu[i])+1, i, "");
					scanf("%d", &level);
					printxy(MENU_X+my_strlen(menu[i])+1, i, N_ICON);
					printxy(MENU_X+my_strlen(menu[i])+1, i, "OK");
#if ( LEVEL_THE_WAY == LEVEL_INTE )
					snake->level = level;
#elif ( LEVEL_THE_WAY == LEVEL_INTE )
					while ( snake->level->ms != level ) {

						snake->level = snake->level->next;
					}
#else
					snake->level = level;
#endif
					break;
				case MAP_SIZE_GAME:
					printxy(MENU_X+my_strlen(menu[i])+1, i, N_ICON);
					printxy(MENU_X+my_strlen(menu[i])+1, i, "");
					scanf("%d,%d", &map_w, &map_h);
					printxy(MENU_X+my_strlen(menu[i])+1, i, N_ICON);
					printxy(MENU_X+my_strlen(menu[i])+1, i, "OK");
					snake->width = map_w;
					snake->hight = map_h;
					break;
				case EXIT_GAME:
					rel_res(snake);
					exit(0);
					break;
			}
		}
	}
}

static void refresh_snake(int const headx, int const heady,
						  int const tailx, int const taily) {
	//
	//     The order of these two statements cannot be changed,
	// otherwise the snake body cannot be displayed in some cases.
	//
	printxy(tailx, taily, NONE);
	printxy(headx, heady, BODY);
}

static sp_body get_snake_tail(sp_body snake) {

	sp_body s;

	s = snake;
	while ( s->next != NULL ) {

		s = s->next;
	}
	return s;
}

static void scan_key(sp_msg snake) {

#if   ( LEVEL_THE_WAY == LEVEL_LINK )
	int i = MANU_SET_LEVEL;
#elif ( LEVEL_THE_WAY == LEVEL_INTE )

#else

#endif
	if ( GetAsyncKeyState(VK_UP) && snake->direction != down ) {

		snake->direction = up;
	} else if ( GetAsyncKeyState(VK_DOWN) && snake->direction != up ) {

		snake->direction = down;
	} else if ( GetAsyncKeyState(VK_LEFT) && snake->direction != right ) {

		snake->direction = left;
	} else if ( GetAsyncKeyState(VK_RIGHT) && snake->direction != left ) {

		snake->direction = right;
	} else if ( GetAsyncKeyState(VK_SPACE) ) {
			
		Sleep(500);
		while ( !GetAsyncKeyState(VK_SPACE) );
	} else if ( GetAsyncKeyState(VK_ADD) ) {
#if ( LEVEL_THE_WAY == LEVEL_LINK )
		while ( i-- ) {

			snake->level = snake->level->prev;
		}
		i = MANU_SET_LEVEL;
#elif ( LEVEL_THE_WAY == LEVEL_INTE )
		snake->level -= 100;
		if ( snake->level < 0 ) {

			snake->level = LEVEL_TIMES;
		}
#else
		snake->level -= 100;
		if ( snake->level < 0 ) {

			snake->level = LEVEL_TIMES;
		}
#endif
		print_level(snake);
	} else if ( GetAsyncKeyState(VK_SUBTRACT) ) {
#if ( LEVEL_THE_WAY == LEVEL_LINK )
		while ( i-- ) {

			snake->level = snake->level->next;
		}
		i = MANU_SET_LEVEL;
#elif ( LEVEL_THE_WAY == LEVEL_INTE )
		snake->level += 100;
		if ( snake->level >= LEVEL_TIMES ) {

			snake->level = 0;
		}		
#else
		snake->level += 100;
		if ( snake->level >= LEVEL_TIMES ) {

			snake->level = 0;
		}	
#endif
		print_level(snake);
	}
}

int main(void) {

	s_msg snake; // Create a snake.
	sp_body s;
	sp_body s_tail;
//	_bool eaten = FALSE;
	
	//printf("Initializing...");
play_again:
	snake = init_snake();
	system("cls");
	
	menu(&snake);
	set_wall(&snake, snake.width, snake.hight);
	init_food(&snake);
	init_map(snake.width, snake.hight);
	print_snake(snake.snake);
	print_level(&snake);
	print_length(&snake);
	
	while ( 1 ) {

		//create_food(&snake);
		scan_key(&snake);
		move_snake(&snake);
		
		if ( eaten_food(&snake) ) {

			if ( snake.length >= snake.maxlength ) {

				system("cls");
				printf("You win!!!\n");
				system("pause");
				rel_res(&snake);
				goto play_again;
			}
			create_food(&snake);
			snake.length += 1;
			print_length(&snake);
			s = create_body(snake.s_tail->x, snake.s_tail->y);
			refresh_snake(snake.s_head->x, snake.s_head->y,
			    snake.s_tail->x, snake.s_tail->y);
			printxy(s->x, s->y, BODY);
			printxy(snake.food->x, snake.food->y, FOOD);
			s_tail = get_snake_tail(snake.snake);
			s_tail->next = s;
#if ( LEVEL_THE_WAY == LEVEL_LINK )
			if ( snake.level_up ) {

				snake.level = snake.level->prev;
			}
#elif ( LEVEL_THE_WAY == LEVEL_INTE )
			if ( snake.level_up ) {
			
				snake.level -= AUTO_SET_LEVEL;
				if ( snake.level < 0 ) {

					snake.level = LEVEL_TIMES;
				}
			}
#else
			if ( snake.level_up ) {

				snake.level -= AUTO_SET_LEVEL;
				if ( snake.level < 0 ) {
				
					snake.level = LEVEL_TIMES;
				}
			}
#endif
			print_level(&snake);
			//snake.level = level
		} else {

			refresh_snake(snake.s_head->x, snake.s_head->y,
						  snake.s_tail->x, snake.s_tail->y);
		}
		if ( is_death(&snake) ) {

			system("cls");
			printf("You failed!!!\n");
			system("pause");
			goto play_again;
		}
		printxy(snake.width+2, snake.hight+1, NONE);
#if ( LEVEL_THE_WAY == LEVEL_LINK )
		Sleep(snake.level->ms);
#elif ( LEVEL_THE_WAY == LEVEL_INTE )
		Sleep(snake.level);
#else

#endif
	}
	
	//printf("\n");
	return 0;
}

static void rel_res(sp_msg snake) {

	free_body(snake->snake);
	free_body(snake->food);
	free_head(snake->s_head);
	free_tail(snake->s_tail);
#if ( LEVEL_THE_WAY == LEVEL_LINK )
	free_level(snake->level);
#endif
}
