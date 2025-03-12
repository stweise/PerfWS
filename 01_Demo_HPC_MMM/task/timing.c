#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
void timing (double * wcTime)
{
        struct timeval tv;
        gettimeofday (&tv,NULL);
        *wcTime = tv.tv_sec + tv.tv_usec/ 1.0e6;
}
