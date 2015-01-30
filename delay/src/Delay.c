#include "Delay.h"
#include <string.h>

void delay_init(delay_s *_this)
{
	memset(_this, 0, sizeof(*_this));
	ringbuffer_init(&_this->buffer);
}

void delay_setDelay_ms(delay_s *_this, unsigned int ms)
{
	ringbuffer_setdelay(&_this->buffer, ms);
}

void delay_setAmount(delay_s *_this, float amount)
{
	if(amount < 0.0f)
	{
		amount = 0.0f;
	}
	if(amount > 1.0f)
	{
		amount = 1.0f;
	}

	_this->amount = amount;
}

void delay_process(	delay_s *_this
					,const float *input
					,float *output
					,unsigned long frameCount
					)
{
	int i;
	float temp[4];

	for(i = 0; i < frameCount; ++i)
	{
		temp[0] = *input++;
        temp[1] = *input++;

        ringbuffer_put(&_this->buffer, temp[0]);
        ringbuffer_put(&_this->buffer, temp[1]);
        
        ringbuffer_get(&_this->buffer, &temp[2]);
        ringbuffer_get(&_this->buffer, &temp[3]);
        
        *output++ = temp[0] * 0.5 + temp[2] * 0.5;
        *output++ = temp[1] * 0.5 + temp[3] * 0.5;
	}
}