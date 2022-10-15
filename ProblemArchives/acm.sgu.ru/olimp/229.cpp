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

const int base=1000*1000*1000;

void norm(tlong& a){
	for (;a.back()==0 && a.size()>1;a.pop_back());
}

tlong operator+ (const tlong& a,const tlong& b){
	tlong res(max(a.size(),b.size())+10);
	for (int i=0;i<res.size()-1;i++){
		if (i<a.size()) res[i]+=a[i];
		if (i<b.size()) res[i]+=b[i];
		res[i+1]+=res[i]/base;
		res[i]%=base;
	}
	norm(res);
	return res;
}

tlong operator- (const tlong& a,const tlong& b){
	tlong res(a.size());
	for (int i=0;i<a.size();i++){
		res[i]+=a[i];
		if (i<b.size()) res[i]-=b[i];
		if (res[i]<0){
			res[i+1]--;
			res[i]+=base;			
		}
	}
	norm(res);
	return res;
}

tlong operator* (const tlong& a,const tlong& b){
	tlong res(a.size()+b.size()+5);
	for (int i=0;i<a.size();i++)
		for (int j=0;j<b.size();j++){
			int64 tmp=res[i+j]+a[i]*1LL*b[j];
			res[i+j]=tmp%base;
			res[i+j+1]+=tmp/base;
		}
	norm(res);
	return res;
}

tlong get(int a){
	tlong res;
	for (;a;a/=base)
		res.pb(a%base);
	if (res.size()==0)
		res.pb(0);
	return res;
}

void print(const tlong& a){
	printf("%d",a.back());
	for (int i=(int)a.size()-2;i>=0;i--)
		printf("%09d",a[i]);
	printf("\n");
	return;
}

tlong t[300][300];
tlong c[300][300];
tlong st2[20000];

int main()
{                        
   // freopen("input.txt","r",stdin);
//    freopen("output.txt","w",stdout);
    int n;
    cin>>n;
	st2[0]=get(1);
	for (int i=1;i<=n*(n-1)/2;i++)
		st2[i]=st2[i-1]*get(2);
	for (int i=0;i<=n;i++)
		c[i][0]=get(1);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=i;j++)
			c[i][j]=c[i-1][j-1]+c[i-1][j];
	t[1][1]=get(1);
	for (int i=2;i<=n;i++){
		for (int j=i;j>=1;j--){
			if (j!=1){
				t[i][j]=get(0);
				for (int k=1;k<=i;k++)
					t[i][j]=t[i][j]+c[i-1][k-1]*t[k][1]*t[i-k][j-1];				
			}
			else {
				t[i][j]=st2[i*(i-1)/2];
				for (int k=2;k<=i;k++)
					t[i][j]=t[i][j]-t[i][k];
			}
		}
		cerr<<i<<endl;	
	}
	print(t[n][1]);
    return 0;
}