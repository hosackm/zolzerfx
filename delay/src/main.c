//
//  main.c
//  Delay Line
//
//  Created by Matthew Hosack on 1/26/15.
//  Copyright (c) 2015 Matthew Hosack. All rights reserved.
//
#include "portaudio.h"
#include "Delay.h"

#define NUM_SECONDS     (3)
#define SAMPLE_RATE     (44100)

delay_s delay;

static int callback(const void *input
                    ,void *output
                    ,unsigned long frameCount
                    ,const PaStreamCallbackTimeInfo* timeInfo
                    ,PaStreamCallbackFlags statusFlags
                    ,void *userData)
{
    unsigned long i;
    float temp[4];
    float *in = (float*)input;
    float *out = (float*)output;
	delay_s *d = (delay_s*)userData;

	delay_process(d, in, out, frameCount);

    return 0;
}

int main(int argc, const char * argv[])
{
    PaStream* stream;
	PaError err;
	delay_s *d;

	d = &delay;
	delay_setAmount(d, 1.0f);
    delay_setDelay_ms(d, 25);
    
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
							   ,d);

	if (err != paNoError){
		return -1;
	}
    
	err = Pa_StartStream(stream);
	if (err != paNoError){
		return -1;
	}
    
    //RUN FOREVER
	for(;;);
	//Pa_Sleep(NUM_SECONDS * 1000);
    
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

