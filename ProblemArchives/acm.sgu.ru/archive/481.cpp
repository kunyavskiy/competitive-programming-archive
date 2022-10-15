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

using namespace std;

typedef long long int64;
typedef long double ld;

typedef vector<int> tlong;

const int base=1000000000;
const string format="%09d";


void norm(tlong& a){	
	for (;a.size()>1 && a.back()==0;a.pop_back());
}

void print(FILE* F,tlong& a){
	norm(a);
	fprintf(F,"%d",a.back());
	for (int i=int(a.size())-2;i>=0;i--)
		fprintf(F,format.data(),a[i]);
	fprintf(F,"\n");
}


void mull(tlong& a,int64 b){
//	print(stderr,a);
//	cerr<<"*"<<b<<endl;
	int64 c=0;
	int sz=a.size();
	for (int i=0;i<sz || c;i++){
		if (i==sz){
			a.pb(0);
			++sz;
		}
		c+=a[i]*b;
		a[i]=c%base;
		c/=base;
	}
//	print(stderr,a);
	norm(a);	
}

void div(tlong& a,int b){
	int64 c=0;
	for (int i=int(a.size())-1;i>=0;i--){
		c+=a[i];
		a[i]=c/b;
		c%=b;
		c*=base;
	}
	assert(c==0);
	norm(a);
}

void add(tlong& a,const tlong& b){
	int c=0;
	int sza=a.size();
	int szb=b.size();
	for (int i=0;i<szb || c;i++){
		if (sza==i){
			a.pb(0);
			sza++;
		}
		c+=a[i];
		if (i<szb)
			c+=b[i];
		a[i]=c%base;
		c/=base;
	}
	norm(a);
}


int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	int n;
	cin>>n;
	tlong ans,cur;
	ans.pb(0);
	cur.pb(1);
	for (int i=1;i<n;i++)
		mull(cur,i);
	div(cur,2);
	add(ans,cur);
	for (int k=n;k>3;k--){
		mull(cur,n);
		div(cur,n-k+1);
		add(ans,cur);
//		cerr<<k<<endl;
	}
//	return 0;
	print(stdout,ans);
	return 0;
}