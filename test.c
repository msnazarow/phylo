#include <sys/time.h>
#include <stdio.h>

struct timeval tv1,tv2,dtv;
struct timezone tz;
int mafin() 
{
    gettimeofday(&tv1, NULL);
    printf("%ld %d\n", tv1.tv_sec, tv1.tv_usec);
    return 0;
}
