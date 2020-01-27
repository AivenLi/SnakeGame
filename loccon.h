/*
 *   Author: Aiven.Li
 *   Time:   2019.10
 *   
 *   Filename: loccon.h
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
#ifndef _LOCCON_H_
#define _LOCCON_H_

#include <windows.h>
#include "snake.h"

#define BODY "¡ö"
#define WALL BODY
#define FOOD "¡ñ"
#define NONE "  "

#define SNAKE_LEVEL_X  ( WALL_WIDTH + 4    )
#define SNAKE_LEVEL_Y  ( WALL_HIGHT >> 2   )
#define SNAKE_LENGTH_X ( SNAKE_LEVEL_X     )
#define SNAKE_LENGTH_Y ( SNAKE_LEVEL_Y + 1 )

typedef struct console_position c_pos;
struct console_position {

	COORD coord;
	HANDLE handle;
};

void printxy(int const x, int const y, char const *str);
void print_level(sp_msg const snake);
void print_length(sp_msg const snake);

#endif