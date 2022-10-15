#include <iostream>
#include <cmath>
#include <vector>
#define ld long double
#define _DEBUG_
using namespace std;


vector<ld> x;
vector<ld> y;
ld aac,bbc,ccc,ddc,ac,bc,cc,dc,abc,acc,adc,bcc,bdc,cdc,sv;
ld a,b,c,d;
const ld inf = 1E+07;
const ld eps = 1E-05;
int n;

ld result()
{
	ld res=0;
	res=a*a*aac;
	res+=b*b*bbc;
	res+=c*c*ccc;
	res+=d*d*ddc;
	res+=2*a*b*abc;
	res+=2*a*c*acc;
	res+=2*a*d*adc;
	res+=2*b*c*bcc;
	res+=2*b*d*bdc;
	res+=2*c*d*cdc;
	res+=2*a*ac;
	res+=2*b*bc;
	res+=2*c*cc;
	res+=2*d*dc;
	res+=sv;
	return res;
}

ld dcoef()
{
	ld res=0;
	res+=2*a*adc;
	res+=2*b*bdc;
	res+=2*c*cdc;
	res+=2*dc;
	return res;
}

ld trind()
{
	/*ld l=-inf;
	ld r=inf;
	while (r-l>eps)
	{
		ld p1=l+(r-l)/3;
		ld p2=r-(r-l)/3;
		d=p1;
		ld res1=result();
		d=p2;
		ld res2=result();
		if (res1<=res2)
			r=p2;
		else
			l=p1;
	}
	d=(l+r)/2;
	return result();*/
	d=-dcoef()/(2*ddc);
	//cerr<<d<<endl;
	return result();
}


ld trinc()
{
	ld l=-inf;
	ld r=inf;
	while (r-l>eps)
	{
		ld p1=l+(r-l)/3;
		ld p2=r-(r-l)/3;
		c=p1;
		ld res1=trind();
		c=p2;
		ld res2=trind();
		if (res1<=res2)
			r=p2;
		else
			l=p1;
	}
	c=(l+r)/2;
	return trind();
}

ld trinb()
{
	ld l=-inf;
	ld r=inf;
	while (r-l>eps)
	{
		ld p1=l+(r-l)/3;
		ld p2=r-(r-l)/3;
		b=p1;
		ld res1=trinc();
		b=p2;
		ld res2=trinc();
		if (res1<=res2)
			r=p2;
		else
			l=p1;
	}
	b=(l+r)/2;
	return trinc();
}

ld trina()
{
	ld l=-inf;
	ld r=inf;
	while (r-l>eps)
	{
		ld p1=l+(r-l)/3;
		ld p2=r-(r-l)/3;
		a=p1;
		ld res1=trinb();
		a=p2;
		ld res2=trinb();
		if (res1<=res2)
			r=p2;
		else
			l=p1;
	}
	a=(l+r)/2;
	//cout<<iter<<endl;
	return trinb();
}

int main()
{
	#ifdef _DEBUG_
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	#endif
	scanf("%d",&n);
	x.resize(n);
	y.resize(n);
	aac=bbc=ccc=ddc=0;
	abc=acc=adc=ac=0;
	bcc=bdc=bc=0;
	cdc=cc=0;
	dc=0;
	sv=0;
	for (int i=0;i<n;i++)
		cin>>x[i]>>y[i];
	ddc=n;
	for (int i=0;i<n;i++)
	{
		aac+=x[i]*x[i]*x[i]*x[i]*x[i]*x[i];
		bbc+=x[i]*x[i]*x[i]*x[i];
		ccc+=x[i]*x[i];
		sv+=y[i]*y[i];
		abc+=x[i]*x[i]*x[i]*x[i]*x[i];
		acc+=x[i]*x[i]*x[i]*x[i];
		adc+=x[i]*x[i]*x[i];
		bcc+=x[i]*x[i]*x[i];
		bdc+=x[i]*x[i];
		cdc+=x[i];
		ac-=y[i]*x[i]*x[i]*x[i];
		bc-=y[i]*x[i]*x[i];
		cc-=y[i]*x[i];
		dc-=y[i];
	}
	//cout<<trina()<<endl;;
	trina();
	printf("%.2f %.2f %.2f %.2f\n",(double)a,(double)b,(double)c,(double)d); 
	/*a=1.00;
	b=-2.00;
	c=-3.00;
	d=10.00;
	cout<<result();*/
}