#include <iostream>
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
    double lamin=0.15;
    double lamax=0.16;
    double lastep=0.01;
    double precision=1E-9;
    double x;
    double f1fixedpoint=0.1;
    double la;
    int all_iterations=1E9;
    int i;
    double xthreshold=0.2;
    bool destroyed;
    double b;

    while(lamax-lamin>precision)
    {
	destroyed=false;
	la=(lamin+lamax)/2.;
	b=drand(1);
	x=1;
	for(i=0;i<all_iterations;i++)
	{
	    x=f(digit(b),x,la,f1fixedpoint);
	    b=mod1(b*2+drand(1E-10));
	    if(x<0.2)
	    {
		destroyed=true;
		break;
	    }
	}
	cout.precision(16);
	cout << "Lambda = " << la;
	if(destroyed)
	{
	    cout << ", destroyed" << endl;
	    lamax=la;
	}
	else
	{
	    cout << ", attractor persists" << endl;
	    lamin=la;
	}
    }
    la=(lamax+lamin)/2.;
    cout.precision(16);
    cout << "Lambda critical = " << la << " (with precision " << precision << ")" << endl;
    return 0;
}
