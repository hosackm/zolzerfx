//
//  ringbuffer.h
//  DelayLine
//
//  Created by Matthew Hosack on 1/29/15.
//  Copyright (c) 2015 Matthew Hosack. All rights reserved.
//

#ifndef DelayLine_ringbuffer_h
#define DelayLine_ringbuffer_h

#define SAMPLE_RATE     (44100) // Hz
#define NUM_CHANNELS    (2)
#define MAX_DELAY_SEC   (1)
#define MAX_DELAY_MSEC  (1000 * MAX_DELAY_SEC)
#define MAX_BUF_SIZE    (SAMPLE_RATE * MAX_DELAY_SEC * NUM_CHANNELS)

typedef float dtype;

typedef struct
{
    dtype   buf[MAX_BUF_SIZE];
    int     head;
    int     tail;
    int     count;
}ringbuffer_s;

int ringbuffer_empty(ringbuffer_s *_this);
int ringbuffer_full(ringbuffer_s *_this);
void ringbuffer_init(ringbuffer_s *_this);
int ringbuffer_put(ringbuffer_s *_this, const dtype input);
int ringbuffer_get(ringbuffer_s *_this, dtype *output);
int ringbuffer_putn(ringbuffer_s *_this, dtype *input, unsigned int n);
void ringbuffer_setdelay(ringbuffer_s *_this, int delay_ms);
void ringbuffer_flush(ringbuffer_s *_this);

#endif
