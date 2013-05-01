#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include "attrlib2.h"

using namespace std;
main()
{
    double lamin=0.1548;
    double lamax=0.15484;
    double lastep=0.00001;
    double x;
    double f1fixedpoint=0.1;
    int all_iterations=3E7;
    int iterations_to_show=1E3;
    int trajectories=10;
    int period=1;
    int denom=(1<<period)-1;
    int numerator;
    double b;

    char filename[256];
    const int components=3;
    ofstream periodicattr[components];
    ofstream nonperiodicattr[components];
    double xs[components]={0.,0.5,1.};
    double curx[components];
    double pastb;
    double la;
    int i,j,k;
    
    for(la=lamin;la<lamax;la+=lastep)
    {
	for(k=0; k<components; k++)
	{
	    sprintf(filename,"periodic-%.5f-%i.data",la,k);
	    periodicattr[k].open(filename);
	    periodicattr[k].precision(8);
	    sprintf(filename,"nonperiodic-%.5f-%i.data",la,k);
	    nonperiodicattr[k].open(filename);
	    nonperiodicattr[k].precision(8);
	}
	for(i=0;i<denom;i++)
	{
	    numerator=i;
	    for(k=0;k<components;k++)
	    {
		x=xs[k];
		for(j=0;j<all_iterations;j++)
		{
		    b=double(numerator)/double(denom);
		    x=f(digit(b),x,la,f1fixedpoint);
		    numerator=((numerator*2)%denom);
		    if(j>all_iterations-period)
		    {
			periodicattr[k] << double(numerator)/double(denom) << ", " << x << endl;
		    }
		}
	    }
	}
	for(i=0;i<trajectories;i++)
	{
	    b=drand(1);
	    for(k=0;k<components;k++)
	    {
		curx[k]=xs[k];
	    }
	    pastb=int(b*2)*0.5;
	    for(j=0;j<all_iterations;j++)
	    {
		for(k=0;k<components;k++)
		{
		    curx[k]=f(digit(b),curx[k],la,f1fixedpoint);
		}
		b=mod1(b*2+drand(1E-10));
		pastb=pastb/2.+int(b*2)*0.5;
		for(k=0;k<components;k++)
		{
		    if(j>all_iterations-iterations_to_show)
		    {
			    nonperiodicattr[k] <<  pastb << ", " << curx[k] << ", " << b << endl;
		    }
		}
	    }
	}
	for(k=0;k<components;k++)
	{
	    periodicattr[k].close();
	    nonperiodicattr[k].close();
	}
    }
}
