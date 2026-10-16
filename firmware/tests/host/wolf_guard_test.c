#include <assert.h>
#include "../../firmware/src/app/wolf_guard.h"
int main(void){uint32_t s=0;for(int i=0;i<100000;i++){s=wolf_deadline_next(s,5000,5804);assert(s==0);}for(int i=0;i<7;i++)s=wolf_deadline_next(s,6000,5804);assert(s==7);s=wolf_deadline_next(s,2000,5804);assert(s==0);for(int i=0;i<8;i++)s=wolf_deadline_next(s,5804,5804);assert(s==8);assert(wolf_deadline_next(s,1,5804)==8);return 0;}
