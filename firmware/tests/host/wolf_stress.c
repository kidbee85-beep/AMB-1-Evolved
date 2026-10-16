/* Bunkai Wolf host stress test; GPL-3.0-only. No hardware timing claims. */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "amb.h"
static struct { uint32_t before; int32_t samples[256]; uint32_t after; } out;
static unsigned stress_second;
#define BAD() do { fprintf(stderr,"FAIL line %d at second %u\n",__LINE__,stress_second); exit(1); } while(0)
static uint32_t rng=0x574f4c46u, midi;
static uint32_t random32(void){rng^=rng<<13;rng^=rng>>17;rng^=rng<<5;return rng;}
void en_midi_out(uint32_t st,uint32_t d1,uint32_t d2){if(st>255||d1>127||d2>127){fprintf(stderr,"MIDI st=%u note=%u value=%u\n",st,d1,d2);BAD();}midi++;}
int main(int argc,char **argv){
 unsigned seconds=argc>1?(unsigned)atoi(argv[1]):600,s,b,j;int p;uint64_t frames=0;int32_t peak=0;
 en_init();en_play(1);
 for(s=0;s<seconds;s++){
  stress_second=s;
  /* Cycle 100 scale/generator pairs; keep DSP running through all transitions. */
  en_gen_mode((s/20)%EN_NGENMODES);en_set(P_MODE,s%EN_NMODES);en_pool(EN_MODE_POOL[s%EN_NMODES]);
  for(p=0;p<P_NPARAMS;p++){const en_param_t *q=en_param_info(p);int v=(s%3==0)?q->hi:(s%3==1)?q->lo:q->lo+(int)(random32()%(q->hi-q->lo+1));en_set(p,v);}
  en_set(P_MIDI,1);en_set(P_TEMPO, en_param_info(P_TEMPO)->hi);
  if(s%13==0)en_freeze(1);if(s%13==3)en_freeze(0);
  if(s%17==0)en_next();if(s%37==0)en_regrow();
  if(s%53==0){en_panic();en_play(1);}if(s%71==0){en_play(0);}if(s%71==1)en_play(1);
  /* Flood command queue to check its bounded overflow behaviour. */
  if(s%29==0)for(p=0;p<200;p++)en_set(P_BRIGHT,p%101);
  for(b=0;b<345;b++){
   if(s%10<3 && b%14==0)en_clock(EN_CLK_TICK);
   out.before=0x13579bdfu;out.after=0x2468ace0u;
   en_render(out.samples,128,4096);frames+=128;
   if(out.before!=0x13579bdfu||out.after!=0x2468ace0u)BAD();
   for(j=0;j<256;j++){int32_t x=out.samples[j];if(x< -8388608||x>8388607)BAD();int32_t a=x<0?-x:x;if(a>peak)peak=a;}
   if(!isfinite(en_pad_level)||!isfinite(en_bass_level)||!isfinite(en_arc)||!isfinite(en_drift))BAD();
   for(j=0;j<EN_NLOOP;j++)if(en_loop_pos[j]>=EN_LOOP_LEN[j]||!isfinite(en_loop_glow[j]))BAD();
  }
  if(s%300==299){printf("progress %u seconds, peak %d\n",s+1,peak);fflush(stdout);}
 }
 printf("PASS Wolf stress: %llu frames, %.2f simulated seconds, MIDI %u, peak %d; extremes, queue floods, freeze, stop/start, regrow, clock transitions, buffer guards.\n",(unsigned long long)frames,(double)frames/44100.0,midi,peak);
 return 0;
}
