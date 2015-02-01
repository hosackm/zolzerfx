#include "Delay.h"
#include <string.h>

void delay_init(delay_s *_this)
{
	memset(_this, 0, sizeof(*_this));
	ringbuffer_init(&_this->buffer);
}

void delay_setDelay_ms(delay_s *_this, unsigned int ms)
{
    pthread_mutex_lock(&_this->mutex);

	ringbuffer_setdelay(&_this->buffer, ms);

    pthread_mutex_unlock(&_this->mutex);
}

void delay_setAmount(delay_s *_this, float amount)
{
    pthread_mutex_lock(&_this->mutex);

	if(amount < 0.0f)
	{
		amount = 0.0f;
	}
	if(amount > 1.0f)
	{
		amount = 1.0f;
	}

	_this->amount = amount;

    pthread_mutex_unlock(&_this->mutex);
}

void delay_process(	delay_s *_this
					,const float *input
					,float *output
					,unsigned long frameCount
					)
{
	int i;
	float temp[4];
    float wet, dry;

    pthread_mutex_lock(&_this->mutex);

    /* amount = 100% should correspond to 0.5 : 0.5 wet/dry */
    wet = _this->amount / 2;
    dry = 1.0f - wet;

	for(i = 0; i < frameCount; ++i)
	{
		temp[0] = *input++;
        temp[1] = *input++;

        ringbuffer_put(&_this->buffer, temp[0]);
        ringbuffer_put(&_this->buffer, temp[1]);
        
        ringbuffer_get(&_this->buffer, &temp[2]);
        ringbuffer_get(&_this->buffer, &temp[3]);
        
        *output++ = temp[0] * dry + temp[2] * wet;
        *output++ = temp[1] * dry + temp[3] * wet;
	}

    pthread_mutex_unlock(&_this->mutex);
}