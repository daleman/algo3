#include "time.h"
#include <stdio.h>

struct timespec requestStart, requestEnd;

void iniciarTimer(){
        clock_gettime(CLOCK_REALTIME, &requestStart);
}

double finalizarTimer(int n){
        clock_gettime(CLOCK_REALTIME, &requestEnd);
        double accum = ( requestEnd.tv_sec - requestStart.tv_sec ) + ( requestEnd.tv_nsec - requestStart.tv_nsec ) / 1E9;
       // printf( "%d %lf\n", n, accum );
        return accum;
}

