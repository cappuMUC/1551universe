/*
 * Copyright (c)2015 by Bernhard Rohloff <rohloff.bernhard@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License (either version 2 or
 * version 3) as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * For more information on the GPL, please go to:
 * http://www.gnu.org/copyleft/gpl.html
 */

/* 
 * File:   ringbuffer.h
 * Author: bernhard
 *
 * Created on 30. Juli 2014, 20:00
 */

#ifndef RINGBUFFER_H
#define	RINGBUFFER_H

#include "stdint.h"
#include "stdbool.h"

#define RINGBUFFER_SIZE 64

typedef struct RINGBUFFER_T{
    char data[RINGBUFFER_SIZE];
    char head;
    char tail;
}ringbuffer_t;

void ringbuffer_putc(ringbuffer_t *buffer, char c);

char ringbuffer_getc(ringbuffer_t *buffer);

bool ringbuffer_isFull(ringbuffer_t *buffer);

bool ringbuffer_isEmpty(ringbuffer_t *buffer);

#endif	/* RINGBUFFER_H */

