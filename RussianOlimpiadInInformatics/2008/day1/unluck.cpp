#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <queue>
#include <memory.h>
#include <stack>
#define mp make_pair
#define pb push_back                     
#define int64 long long
#define ld long double  
#define setval(a,v) memset(a,v,sizeof(a))
using namespace std;

struct tlong{
	vector<int> c;
	tlong(){
		c.pb(0);
	}
	tlong(int a){
		c.clear();
		if (a==0)	
			c.pb(0);
		for (;a;){
			c.pb(a%10);
			a/=10;
		}
	}
	int& operator[](int a){
		return c[a];
	}
	int size() const
	{
		return c.size();
	}
	void resize(int n){
		int tec=c.size();		
		c.resize(n);
		for (int i=tec;i<n;i++)
			c[i]=0;
	}
	int back(){
		return c.back();
	}
	void pop_back(){
		c.pop_back();
	}
};


ostream& operator<< (ostream& ost, tlong a){
	//cerr<<"!"<<endl;
	for (int i=a.size()-1;i>=0;i--)
	{
		printf("%d",a[i]);
		assert(a[i]<10);
	}
	return ost;
}

tlong operator+(tlong a,tlong b){
	int rs=max(a.size(),b.size())+10;
	tlong res;
	res.resize(rs);
	int per=0;
	for (int i=0;i<rs-1;i++){
		if (i<a.size())
			per+=a[i];
		if (i<b.size())
			per+=b[i];
		res[i]=per%10;
		per/=10;
	}
	for (;res.size()!=1 && res.back()==0;)
		res.pop_back();
	return res;
}

tlong operator*(tlong a,tlong b){
	tlong res;
	res.resize(a.size()+b.size()+10);
	for (int i=0;i<a.size();i++)
		for (int j=0;j<b.size();j++)
			{
				res[i+j]+=a[i]*b[j];
				res[i+j+1]+=res[i+j]/10;
				res[i+j]%=10;
			}
	for (;res.size()!=1 && res.back()==0;)
		res.pop_back();
	return res;
}

tlong operator-(tlong a,tlong b){
	tlong res;
	res.resize(a.size());
	int per=0;
	for (int i=0;i<a.size();i++){
		res[i]+=a[i]+per;
		if (i<b.size())
			res[i]-=b[i];
		if (res[i]<0){
			res[i]+=10;
			per=-1;
		}
		else
			per=0;
	}
	for (;res.size()!=1 && res.back()==0;)
		res.pop_back();
	return res;
}

int size(int mask){
	int res=0;
	for (;mask;){
		res+=mask&1;
		mask/=2;
	}
}

bool gm[1<<10];
int k;
tlong gl[101];
tlong fact[101];
tlong rasl[101][101];

void perebor(int sum1,int sum2,int tec,int len,int n,tlong vars,tlong& res){
	if (len>n)
		return;
	if (tec==k && len==n)
		{
			if (sum1==sum2)
				res+=vars;
			return;				
		}
	if (len==n)
		return;
	for (int i=0;i+len<=n;i++){
		perebor(sum1+i*tec,sum2,tec+1,len+i,n,vars*rasl[len+1][i],res);
		if (len!=0)
			perebor(sum1,sum2+i*tec,tec+1,len+i,n,vars*rasl[len+1][i],res);
	}
	return;
}




int main()
{
	int n;
	scanf("%d %d",&n,&k);
	perebor(0,0,0,0,0);
	fact[0]=1;
	for (int i=1;i<=100;i++)
		fact[i]=fact[i-1]*i;	
	for (int j=0;j<=n+1;j++)
		rasl[0][j]=1;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n+1;j++)
		{
			rasl[i][j]=0;
			for (int l=0;l<=i;l++)
				rasl[i][j]=resl[i][j]+rasl[i-l][j-1];
		}
	for (int i=0;i<=n;i++)
	{
		gl[i]=0;
		perebor(0,0,1,0,i,1,gl[i]);
	}
	return 0;
}