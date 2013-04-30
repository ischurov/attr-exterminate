from math import sin,pi

class SkewProduct:
    la=0.1
    f1fixedpoint=0.1
    def f(self,i,x):
	if i=='0':
	    return x-0.1*sin(2.3*pi*x-0.2*pi)
	elif i=='1':
	    return (x-self.f1fixedpoint)*(1-la)+self.f1fixedpoint
	else:
	    assert False, "Shouldn't be here"
    def comp(self,word):
	def ret(x):
	    for i in word:
		x=self.f(i,x)
	    return x
	return ret
def is_admissible(str):
    return '11' not in str


def frange2(start, end=None, inc=None):
    "A range function, that does accept float increments..."

    if end == None:
        end = start + 0.0
        start = 0.0
    else: start += 0.0 # force it to be a float

    if inc == None:
        inc = 1.0

    count = int((end - start) / inc)
    if start + count * inc != end:
        # need to adjust the count.
        # AFAIKT, it always comes up one short.
        count += 1

    L = [None,] * count
    for i in xrange(count):
        L[i] = start + i * inc

    return L

def writefunctofile(filename,f,xmin,xmax,xstep):
    datafile=open(filename,'w')
    for x in frange2(xmin,xmax,xstep):
	datafile.write("{0:.5f}, {1:.9f}\n".format(x,f(x)))
    datafile.close()

def findfixedpoints(f,xmin,xmax,xstep):
    state=f(xmin)>xmin
    ret=[]
    for x in frange2(xmin,xmax,xstep):
	if (f(x)>x)!=state:
	    ret.append(bisect(lambda x: f(x)-x,x-xstep,x,xstep*0.001))
	    state= not state
    return ret

def bisect(f,xmin,xmax,delta):
    a=xmin
    b=xmax
    assert(b>a)
    assert(f(a)*f(b)<0)
    while True:
	c=(b+a)/2.
	if f(a)*f(c)<0:
	    b=c
	else:
	    a=c
	if b-a<delta:
	    break
    return (a+b)/2.



returns=['0','01','10']
transitions=['0','1','01','10']
sp=SkewProduct()
xstep=0.01
fixedpoints=[]
for la in frange2(0,0.5,0.001):
    sp.la=la
    for word in returns:
	f=sp.comp(word)
	filename='ret-{0:.3f}-{1}.data'.format(la,word)
	writefunctofile(filename,f,0.,1.,0.01)
	fixedpoints=findfixedpoints(f,0,1,0.001)
	fp=open('fixedpoints-{0}.data'.format(word),'a')
	fp.write(", ".join(map(str,[la]+fixedpoints))+"\n")
	fp.close()
	for tr in transitions:
	    if is_admissible(word+tr):
		fp=open('fixedpoints-comp-{0}-{1}.data'.format(word,tr),'a')
		ftrans=sp.comp(tr)
		fp.write(", ".join([str(la)]+[str(ftrans(x)) for x in fixedpoints])+"\n")
		fp.close()
