#include <stdio.h>
#include <stdlib.h>
#include "amb.h"
static int32_t block[256];
void en_midi_out(uint32_t st,uint32_t d1,uint32_t d2){(void)st;if(d1>127||d2>127){fprintf(stderr,"MIDI range\n");exit(1);}}
static void render(int seconds){int n,j;for(n=0;n<seconds*44100/128;n++){en_render(block,128,4096);for(j=0;j<256;j++)if(block[j]<-8388608||block[j]>8388607){fprintf(stderr,"sample range\n");exit(1);}}}
int main(void){int mode,scale,steps[12];for(mode=0;mode<EN_NGENMODES;mode++){for(scale=0;scale<EN_NMODES;scale++){int count=en_scale(EN_MODE_POOL[scale],steps);if(count<3||count>12)return 2;en_init();en_set(P_MODE,scale);en_pool(EN_MODE_POOL[scale]);en_set(P_EVOLVE,100);en_set(P_TEMPO,120);en_gen_mode(mode);en_play(1);render(scale==1?35:1);if(en_genmode!=mode)return 3;} }puts("PASS: 100 C scale/generator pairs, 270s rendered; ASan/UBSan, sample/MIDI bounds");return 0;}
