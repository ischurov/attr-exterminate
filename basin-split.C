#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include "attrlib.h"

using namespace std;
main()
{
    double lamin=0.6;
    double lamax=0.7;
    double lastep=0.01;
    double x;
    double xmin,xmax;
    int all_iterations=1E6;
    int bpoints=250;
    int pastpoints=250;
    double bisect_precision=1E-4;
    int period=1;
    int denom=(1<<period)-1;
    int numerator;
    double b;
    double saveb;

    char filename[256];
    ofstream nonperiodicattr;
    double pastb;
    double la;
    int i,j,k;
    double xmid;
    
    for(la=lamin;la<lamax;la+=lastep)
    {
	sprintf(filename,"basin-%.5f.data",la);
	nonperiodicattr.open(filename);
	nonperiodicattr.precision(8);
	for(i=0;i<bpoints;i++)
	{
	    saveb=drand(1);
	    xmin=0;
	    xmax=1;
	    
	    while(xmax-xmin>bisect_precision)
	    {
		b=saveb;
		x=xmid=(xmax+xmin)/2.;
		for(j=0;j<all_iterations;j++)
		{
		    x=f(digit(b),x,la);
		    b=mod1(b*2+drand(1E-10));
		}
		if(x>0.5)
		{
		    xmax=xmid;
		}
		else
		{
		    xmin=xmid;
		}
	    }
	    x=(xmax+xmin)/2.;
	    for(j=0;j<pastpoints;j++)
	    {
		nonperiodicattr << drand(1) << ", " << x << ", " << saveb << endl;
	    }
	}
	nonperiodicattr.close();
    }
}
