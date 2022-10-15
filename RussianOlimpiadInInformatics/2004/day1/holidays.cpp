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

int cnt[10000][2];
int cntd[10000];
int cntp[10000];

int c[10000];
int d[10000];
int a,b;
int n,m;

void mod(int start,int len,int coef){
	int ptr = 0;
	for (int i=1;i<=len;i++){
		cntd[start]+=coef;
		if (ptr < m && d[ptr] == i){
			cntp[start]+=coef;
			++ptr;
		}
		start=start+1;
		if (start == a)
			start=0;
	}
}

int main()
{
	freopen("holidays.in","r",stdin);
 	freopen("holidays.out","w",stdout);
	scanf("%d %d",&a,&b);
	scanf("%d",&n);
	for (int i=0;i<n;i++)
		scanf("%d",&c[i]);

	scanf("%d",&m);
	for (int j=0;j<m;j++)
		scanf("%d",&d[j]);
	int e;
	scanf("%d",&e);
	int ptr = 0;
	int start=0;
	for (int i=1;e>0;++i){
		if (ptr < n && c[ptr] == i){
			++ptr;
			if (e >= b+1)
				cnt[start][1]++;
			else
				mod(start,e,1);
			start=(start+b+1)%a;			
			e-=b+1;
		}
		else {
			if (e>=b)
				cnt[start][0]++;
			else
				mod(start,e,1);
			start = (start + b)%a;
			e-=b;
		}
	}
	
	
	for (int i=0;i<a;i++){
		mod(i,b,cnt[i][0]);
		mod(i,b+1,cnt[i][1]);
	}
	
	int sum = 0;
	for (int i=0;i<a;i++)
		sum += cntp[i];
	
	int best = -1;
	int bestd = -1;
	for (int i=0;i<a;i++){
		if (best < sum - cntp[i] + cntd[i]){
			bestd = i+1;
			best = sum - cntp[i] + cntd[i];
		}
	}
	cout << bestd << " "<< best << endl;;
 	return 0;
}