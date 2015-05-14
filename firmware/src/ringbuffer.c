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


#include "ringbuffer.h"


void ringbuffer_putc(ringbuffer_t *buffer, char c)
{
    uint8_t nextPos = (buffer->head+1) % RINGBUFFER_SIZE;
    if(nextPos != buffer->tail){
        buffer->data[buffer->head] = c;
        buffer->head = nextPos;
    }
}

char ringbuffer_getc(ringbuffer_t *buffer)
{
    if (buffer->tail != buffer->head){
        char c = buffer->data[buffer->tail];
        buffer->tail = (buffer->tail + 1) % RINGBUFFER_SIZE;
        return c;
    }
    return 0;
}

bool ringbuffer_isFull(ringbuffer_t *buffer)
{
    uint8_t nextPos = (buffer->head+1) % RINGBUFFER_SIZE;
    return (nextPos == buffer->tail);
}

bool ringbuffer_isEmpty(ringbuffer_t *buffer)
{
    return (buffer->head == buffer->tail);
}

