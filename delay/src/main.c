//
//  main.c
//  Delay Line
//
//  Created by Matthew Hosack on 1/26/15.
//  Copyright (c) 2015 Matthew Hosack. All rights reserved.
//
#include "portaudio.h"
#include "ringbuffer.h"

#define NUM_SECONDS     (3)
#define SAMPLE_RATE     (44100)

ringbuffer_s rbuf;

static int callback(const void *input
                    ,void *output
                    ,unsigned long frameCount
                    ,const PaStreamCallbackTimeInfo* timeInfo
                    ,PaStreamCallbackFlags statusFlags
                    ,void *userData)
{
    int i;
    float temp[4];
    float *in = (float*)input;
    float *out = (float*)output;
    ringbuffer_s *p_rbuf = (ringbuffer_s*)userData;

    for(i = 0; i < frameCount; ++i)
    {
        temp[0] = *in++;
        temp[1] = *in++;
        ringbuffer_put(p_rbuf, temp[0]);
        ringbuffer_put(p_rbuf, temp[1]);
        
        ringbuffer_get(p_rbuf, &temp[2]);
        ringbuffer_get(p_rbuf, &temp[3]);
        
        *out++ = temp[0] * 0.5 + temp[2] * 0.5;
        *out++ = temp[1] * 0.5 + temp[3] * 0.5;
    }

    return 0;
}

int main(int argc, const char * argv[])
{
    PaStream* stream;
	PaError err;
    ringbuffer_s *p_rbuf;
    
    p_rbuf = &rbuf;
    ringbuffer_init(p_rbuf);
    ringbuffer_setdelay(p_rbuf, 300);
    
	err = Pa_Initialize();
	if (err != paNoError){
        return -1;
	}
    
	err = Pa_OpenDefaultStream(&stream
                               ,2
                               ,2
                               ,paFloat32
                               ,SAMPLE_RATE
                               ,256
                               ,callback
                               ,p_rbuf);
	if (err != paNoError){
		return -1;
	}
    
	err = Pa_StartStream(stream);
	if (err != paNoError){
		return -1;
	}
    
    //RUN FOREVER
	for(;;);
    
	err = Pa_CloseStream(stream);
	if (err != paNoError){
		return -1;
	}
    
	err = Pa_Terminate();
	if (err != paNoError){
		return -1;
	}
    
    return 0;
}

