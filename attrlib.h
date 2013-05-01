#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#ifndef ATTRLIB_H
#define ATTRLIB_H
inline double f(int i, double x, double la)
{
    if(i==0)
    {
	return x-(x-0.2)*(x-0.5)*(x-0.7);
    }
    else if(i==1)
    {
	return x-(x-0.1)*(x-la)*(x-0.9); // la have to be close to 0.7
    }
    assert(false);
}
inline int digit(double x)
{
    return int(x*2);
}
inline double drand(double x)
{
	return rand()/(((double)RAND_MAX + 1) / x);
}
inline double mod1(double x)
{
	if(x>=0 && x<1)
	{
		return x;
	}
	if(x>=1)
	{
		return x-int(x);
	}
	if(x<1)
	{
		return x-int(x)+1;
	}
}
#endif
