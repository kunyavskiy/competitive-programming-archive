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

struct _node;
typedef _node* node;

const int MAXN=1000000+100;

int p[MAXN];
vector<int> primes;
int last[MAXN];
bool used[MAXN];
int ptr;

void erotosfen(){
	p[0]=p[1]=0;
	for (int i=2;i<MAXN;i++){
		if (p[i]==0){
			p[i]=i;
			primes.pb(i);
		}
		for (int j=0;j<primes.size() && primes[j]<=p[i] && primes[j]*i<MAXN;j++)
			p[i*primes[j]]=primes[j];
	}
}

inline int next(int v){
	for (;v*last[v] <MAXN && used[v*last[v]];last[v]++);
	return v*last[v];
}

int main()
{                        
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	erotosfen();
	used[0]=used[1]=true;
	int val=1;
	int n;
	scanf("%d",&n);
	if (n==1){
		cout<<1<<endl;
		return 0;			
	}
	--n;
	val=2;
	ptr=0;
	for (--n;n;--n){
		used[val]=1;
		int tmp=val;
		val=1<<30;
		for (;tmp>=2;tmp/=p[tmp])
			val=min(val,next(p[tmp]));				
	}
	cout<<val<<endl;
    return 0;
}