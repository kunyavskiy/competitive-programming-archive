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
#define setval(a,v) memset(a,v,sizeof(a))

#if ( _WIN32 || __WIN32__ )
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

#ifdef LOCAL
	#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
	#define eprintf(...) ;
#endif

using namespace std;

typedef long long int64;
typedef long double ld;

typedef vector<int> tlong;

void norm(tlong& a){
	for (;a.size()>1 && a.back()==0;a.pop_back());
}

const int base=10000;

tlong operator+(const tlong& a,const tlong& b){
	tlong res(max(a.size(),b.size())+10);
	int c=0;
	int asz=a.size(),bsz=b.size(),rsz=res.size();
	for (int i=0;i<rsz;i++){
		if (i<asz)
			c+=a[i];
		if (i<bsz)
			c+=b[i];
		res[i]=c%base;
		c/=base;
	}
	norm(res);
	return res;
}

tlong operator*(const tlong& a,int b){
	tlong res(a.size()+10);
	int c=0;
	int asz=a.size(),rsz=res.size();
	for (int i=0;i<rsz;i++){
		if (i<asz)
			c+=a[i]*b;
		res[i]=c%base;
		c/=base;
	}
	norm(res);
	return res;
}

tlong operator*(const tlong& a,const tlong& b){
	tlong res(a.size()+b.size()+10);
	for (int i=0;i<a.size();i++)
		for (int j=0;j<b.size();j++){
			res[i+j]+=a[i]*b[j];
			for (int k=0;res[i+j+k]>=base;++k){
				res[i+j+k+1]+=res[i+j+k]/base;
				res[i+j+k]%=base;
			}
		}
	norm(res);
	return res;
}

tlong operator/(tlong a,int b){
	int c=0;
	for (int i=int(a.size())-1;i>=0;--i){
		c+=a[i];
		a[i]=c/b;
		c%=b;
		c*=base;
	}
	norm(a);
	return a;
}

bool lseql(const tlong& a,const tlong& b){
	if (a.size()!=b.size())
		return a.size() < b.size();
	for (int i=int(a.size())-1;i>=0;--i)
		if (a[i]!=b[i])
			return a[i] < b[i];
	return true;
}

bool check(const tlong& a,const tlong& b,int p){
	return lseql(b*p,a*100);
}

int n,b,w,p;

tlong val[100];

tlong zn;

tlong c(int n,int k){	
	tlong val;
	if (n<k || k<0){
		val.pb(0);
		return val;
	}
	val.pb(1);
	
	for (int i=k+1;i<=n;i++)
		val=val*i;
	for (int i=1;i<=n-k;i++)
		val=val/i;
	return val;
}

#ifdef LOCAL
	#define debug(x) cerr<< #x << " = " ;_debug(x)
	#define dbgi(x) cerr << #x <<"  = " << x << " ";

void _debug(const tlong& a){
	eprintf("%d",a.back());
	for (int i=int(a.size())-2;i>=0;--i)
		eprintf("%04d",a[i]);
	eprintf("\n");
}

#else
	#define debug(x) ;
	#define dbgi(x) ;
#endif



int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  
  	tlong tmp,tmp2;
	cin>>n>>b>>w>>p;
	zn.pb(0);
	for (int i=0;i<=n;i++){
		val[i]=c(i,b)*c(n-i,w);	
		dbgi(i)
		debug(val[i]);
		zn=zn+val[i];
	}
//	zn=zn*(n+1);	
	debug(zn);
	int l=0,r=n;
	for (int i=0;i<=n;i++){
		tlong v;
		v.pb(0);
		for (int j=i;j<=n;j++){
			v=v+val[j];
			dbgi(i);
			dbgi(j);
			debug(v);
			if (check(v,zn,p)){
				if (j-i < r-l){
					l=i;
					r=j;
				}
				break;					
			}				
		}
	}
	cout<<l<<" "<<r<<endl;
	return 0;
}