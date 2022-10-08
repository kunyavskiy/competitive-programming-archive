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

int64 kol[1000];
int64 ans[1000];
int num[1000];

int main()
{
 	int t;
	scanf("%d",&t);
	for (int test=1;test<=t;++test){
		int r,k,n;
		scanf("%d %d %d",&r,&k,&n);
		int64 SUM=0;
		for (int i=0;i<n;i++)
		{
			cin>>kol[i];
			SUM+=kol[i];
		}
		if (k>=SUM)
		{
			int64 res=SUM*r;			
			cout<<"Case #"<<test<<": "<<res<<endl;
			continue;
		}
		setval(ans,-1);
		int ptr=0;
		int64 res=0;
		for (;r>0;--r){
			int64 sum=0;
			for (;sum+kol[ptr]<=k;ptr=(ptr+1)%n)
				sum+=kol[ptr];
			res+=sum;
		//	cerr<<sum<<endl;
			if (ans[ptr]==-1){
				ans[ptr]=res;
				num[ptr]=r;
			}
			else{
				int times=num[ptr]-r;
				int64 add=res-ans[ptr];
				int64 tmp=(r-1)/times;
			//	cerr<<r<<" "<<times<<" "<<add<<" "<<tmp<<" "<<res<<endl;
				res=res+add*tmp;
				r=r-times*tmp;
			//	cerr<<res<<endl;
			}
		}
		cout<<"Case #"<<test<<": "<<res<<endl;
	}
  return 0;
}