#ifndef DELAY_EFFECT_H_
#define DELAY_EFFECT_H_

#include "ringbuffer.h"

#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	ringbuffer_s	buffer;
	float			amount;
    pthread_mutex_t mutex;
}delay_s;

void delay_init(delay_s *_this);
void delay_setDelay_ms(delay_s *_this, unsigned int ms);
void delay_setAmount(delay_s *_this, float amount);
void delay_process(	delay_s *_this
					,const float *input
					,float *output
					,unsigned long frameCount
					);

#ifdef _cplusplus
}
#endif
#endif //DELAY_EFFECT_H_