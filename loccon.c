/*
 *   Author: Aiven.Li
 *   Time:   2019.10
 *   
 *   Filename: loccon.c
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
#include "loccon.h"
#include "snake.h"

static c_pos pos;

void printxy(int const x, int const y, char const *str) {

	pos.coord.X = x;
	pos.coord.Y = y;
	pos.handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(pos.handle, pos.coord);
	printf(str);
}

void print_level(sp_msg const snake) {

	char *slevel  = "Current  level: ";
	
	printxy(snake->width + 4, snake->hight / 4, slevel);
#if ( LEVEL_THE_WAY == LEVEL_LINK )
	printf("%d ms/t", snake->level->ms);
#elif ( LEVEL_THE_WAY == LEVEL_INTE )
	printf("%d ms/t", snake->level);
#else

#endif
}

void print_length(sp_msg const snake) {

	char *slength = "Current length: ";
	printxy(snake->width + 4, ( snake->hight / 4 ) + 1, slength);
	printf("%d", snake->length);
}
