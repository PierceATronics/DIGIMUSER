#include "Reverb.h"


void Reverb::update(void){

    audio_block_t *x;
    audio_block_t *delayed;
    //audio_block_t *y = (audio_block_t*)malloc(sizeof(audio_block_t));
    
    x = receiveWritable();

    int32_t *px;
    int32_t *pd; 
    int32_t *pc;
    int32_t *pg; 
    
    int32_t inputs, mult;
    uint32_t packed_consts;

    if(x){
        //Dereference the 16-bit constant C as a 32-bit constant
        //pc = (int32_t*)(&this->C);
        //pg = (int32_t*)(&this->g);
        //packed_consts = pack_16t_16t(*pc, *pg);

        delayed = this->delayed_blocks[this->delayed_block_pos];
        
        for(int i=0; i < AUDIO_BLOCK_SAMPLES; i++){

            //Dereference the 16-bit x value as a 32-bit constant
            //px = (int32_t*)(&x->data[i]);
            //pd = (int32_t*)(&delayed->data[i]);
            //inputs = pack_16t_16t(*px, *pd);

            //Performs y[n] = C * x[n] - g * y[n - M]
            //mult = multiply_16tx16t_add_16bx16b((uint32_t)(packed_consts), (uint32_t)(inputs));
            int32_t mult1 = (int32_t)(x->data[i]) * (int32_t)(this->C);
            int32_t mult2 = (int32_t)(delayed->data[i]) * (int32_t)(this->g);
            int32_t ad = mult1 + mult2;
            x->data[i] = (int16_t)(ad >> 15);
        }

        //Save the current y audio block to be used for delay.
        _copy_audio_block_t(x, this->delayed_blocks[this->delayed_block_pos]);

        if(this->delayed_block_pos < NUM_DELAYED_BLOCKS - 1)
            this->delayed_block_pos++;
        else
            this->delayed_block_pos = 0;

        Reverb::transmit(x);
        //Reverb::release(y);
        Reverb::release(x);
        //Reverb::release(delayed);

    }

}

Reverb::Reverb() : Reverb::AudioStream(1, input_queue_array){

    //Allocate the memory for the delayed blocks.
    _init_delayed_blocks();

}
void Reverb::_init_delayed_blocks(){

    for(int j=0; j < NUM_DELAYED_BLOCKS; j++){
        this->delayed_blocks[j] = (audio_block_t*) malloc(sizeof(audio_block_t));
    }

}

void Reverb::_copy_audio_block_t(audio_block_t *src, audio_block_t *dst){

    for(int i=0; i < AUDIO_BLOCK_SAMPLES; i++){
        dst->data[i] = src->data[i];
    }

}

Reverb::~Reverb(){

    //Free up the memory
    for(int j=0; j < NUM_DELAYED_BLOCKS; j++){
        free(this->delayed_blocks[j]);
    }
    
}
