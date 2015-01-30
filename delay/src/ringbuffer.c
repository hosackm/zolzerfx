//
//  ringbuffer.c
//  DelayLine
//
//  Created by Matthew Hosack on 1/29/15.
//  Copyright (c) 2015 Matthew Hosack. All rights reserved.
//

#include <string.h>
#include "ringbuffer.h"

int ringbuffer_empty(ringbuffer_s *_this)
{
    return (_this->count == 0);
}

int ringbuffer_full(ringbuffer_s *_this)
{
    return (_this->count >= MAX_BUF_SIZE);
}

void ringbuffer_init(ringbuffer_s *_this)
{
    memset(_this, 0, sizeof(*_this));
}

int ringbuffer_put(ringbuffer_s *_this, const dtype input)
{
    int ret;
    
    if (!ringbuffer_full(_this)) {
        _this->buf[_this->head] = input;
        _this->head++;
        _this->head %= MAX_BUF_SIZE;
        _this->count++;
        ret = 0;
    }
    else
    {
        ret = -1;
    }
    
    return ret;
}

int ringbuffer_get(ringbuffer_s *_this, dtype *output)
{
    int ret;
    
    if(!ringbuffer_empty(_this))
    {
        *output = _this->buf[_this->tail];
        _this->tail++;
        _this->tail %= MAX_BUF_SIZE;
        _this->count--;
        ret = 0;
    }
    else
    {
        ret = -1;
    }
    
    return ret;
}

void ringbuffer_flush(ringbuffer_s *_this)
{
    memset(_this, 0, sizeof(*_this));
}

int ringbuffer_putn(ringbuffer_s *_this, dtype *input, unsigned int n)
{
    int i, ret;
    
    if(n > MAX_BUF_SIZE || n > _this->count)
    {
        ret = -1;
    }
    else
    {
        ret = 0;
        for(i = 0; i < n; i ++)
        {
            ret = ringbuffer_put(_this, *input++);
        }
    }
    
    return ret;
}

void ringbuffer_setdelay(ringbuffer_s *_this, int delay_ms)
{
    if (delay_ms >= (MAX_DELAY_MSEC)) {
        /**  Tail must be one sample from behind head
        *   otherwise we have no delay
        **/
        delay_ms = MAX_DELAY_MSEC - 1;
    }
    
    _this->tail = _this->head - (NUM_CHANNELS * SAMPLE_RATE * delay_ms / 1000);
    
    while (_this->tail < 0) {
        _this->tail += MAX_BUF_SIZE * NUM_CHANNELS;
    }
}
