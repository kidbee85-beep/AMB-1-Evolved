/* GPL-3.0-only. Production-DSP preset verification / PCM preview generator. */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "amb.h"
void en_midi_out(uint32_t s,uint32_t a,uint32_t b){assert(s<=255&&a<128&&b<128);}
int main(int argc,char **argv){int layer=atoi(argv[1]),patch=atoi(argv[2]),i,j;int32_t out[512];uint64_t hash=1469598103934665603ULL;double energy=0;int peak=0;FILE *pcm=argc>3?fopen(argv[3],"wb"):0;
 en_init();
 if(layer<0){int16_t par[P_NPARAMS];uint16_t pool;en_piece(patch,par,&pool);for(i=0;i<P_NPARAMS;i++){assert(par[i]>=en_param_info(i)->lo&&par[i]<=en_param_info(i)->hi);en_set(i,par[i]);}en_pool(pool);}
 else {assert(layer<4&&patch<16);for(i=0;i<4;i++)en_set(i,i==layer?80:0);for(i=0;i<3;i++)en_set(EV_PATCH_PARAM[layer][i],EV_PATCH_VALUE[layer][patch][i]);en_set(P_PADPATCH+layer,patch);en_set(P_DENSITY,100);en_set(P_HITS,100);en_set(P_ECHO,0);en_set(P_REVERB,0);en_set(P_EVOLVE,0);en_set(P_TEMPO,100);}
 en_play(1);
 for(i=0;i<4000;i++){en_render(out,256,4096);for(j=0;j<512;j++){int32_t v=out[j];assert(v>=-8388608&&v<=8388607);hash=(hash^(uint32_t)v)*1099511628211ULL;double x=v/8388608.0;energy+=x*x;if(abs(v)>peak)peak=abs(v);
 // Preview: exactly four seconds after a two-second warm-up, little-endian signed16 PCM.
 uint64_t frame=(uint64_t)i*256+j/2;if(pcm&&frame>=88200&&frame<264600){int16_t s=(int16_t)(v/256);unsigned char bytes[2]={(unsigned char)s,(unsigned char)((uint16_t)s>>8)};fwrite(bytes,1,2,pcm);}
 }}if(pcm)fclose(pcm);printf("{\"hash\":\"%016llx\",\"energy\":%.8f,\"peak\":%d}\n",(unsigned long long)hash,energy,peak);return 0;}
