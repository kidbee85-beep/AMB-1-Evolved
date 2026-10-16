/* Regression: drum accent * arc can produce MIDI velocity above 127. GPL-3.0-only. */
#include <assert.h>
#include "../../firmware/src/dsp/amb.c"
static unsigned last_velocity;
void en_midi_out(uint32_t st,uint32_t a,uint32_t b){assert(a<=127&&b<=127);if(st==0x99)last_velocity=b;}
int main(void){en_init();par[P_MIDI]=1;for(int i=1;i<=2000;i++){drum_fire(i%3,(float)i/1000.0f);assert(last_velocity>=1&&last_velocity<=127);}drum_fire(0,1.38f);assert(last_velocity==127);return 0;}
