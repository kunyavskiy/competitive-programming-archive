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

typedef vector<int> tlong;
const int base=10000;
const int blen=4;

istream& operator>> (istream& ist,tlong& t){
	string s;
	getline(ist,s);
	t.clear();
	for (int i=((int)s.size())-blen;i>-blen;i-=blen)
		t.pb(atoi(string(s.begin()+max(0,i),s.begin()+i+blen).data()));
	return ist;
}

int operator% (const tlong& a,int b){
	int res=0;
	for (int i=(int)a.size()-1;i>=0;--i)
		res=(res*base+a[i])%b;
	return res;
}

void div(tlong& a,int b){
	int c=0;
	for (int i=(int)a.size()-1;i>=0;--i){
		c=c*base+a[i];
		a[i]=c/b;
		c%=b;
	}
	for (;a.back()==0;a.pop_back());
}

int st[1100];
tlong t;

int gcd(int a,int b){
	if (!a) return b;
	if (!b) return a;
	return gcd(b,a%b);
}

int main()
{                        
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
	cin>>t;
	//cerr<<t[0]<<endl;
	for (int i=2;i<=1000;i++){
		while (t%i==0)
			{
				st[i]++;
				div(t,i);
			//	cerr<<t[0]<<endl;
			}
	}
//	cerr<<"!!!"<<endl;
	int g=0;
	for (int i=0;i<=1000;i++)
		g=gcd(g,st[i]);
	for (int i=1000;i>=0;--i)
		if (g%i==0){
			g=i;
			break;
		}
	int a=1;
	for (int i=0;i<=1000;i++){
		for (;st[i]>0;st[i]-=g)
			a*=i;			
	}
	cout<<a<<" "<<g<<endl;
  return 0;
}