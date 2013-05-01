#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#ifndef ATTRLIB_H
#define ATTRLIB_H
inline double f(int i, double x, double la, double f1fixedpoint)
{
    if(i==0 or i==2 or i==3)
    {
	return x-0.1*sin(2.3*M_PI*x-0.2*M_PI);
    }
    else if(i==1)
    {
	return (x-f1fixedpoint)*(1-la)+f1fixedpoint; 
    }
    assert(false);
}
inline int digit(double x)
{
    return int(x*4);
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
