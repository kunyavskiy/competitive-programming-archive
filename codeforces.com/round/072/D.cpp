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


int a,b,k;


const int MAXN=1100000;
int p[MAXN];
vector<int> primes;
void precalc(){
	for (int i=2;i<MAXN;i++){
		if (p[i] == 0){
			primes.pb(i);
			p[i]=i;
		}
		for (int j=0;j< primes.size() && i*1LL*primes[j]<=MAXN && primes[j]<=p[i];j++)
			p[i*primes[j]]=primes[j];
	}
}

int meb(int a){
	int cnt = 1;
	for (int i=2;a>1;i++){
		if (a % (i*i) == 0)
			return 0;
		if (a%i == 0){
			a/=i;
			cnt*=-1;
		}
	}
	return cnt;
}

bool prime(int a){
	for (int i=2;i*i<=a;i++)
		if (a%i == 0)
			return false;
	return true;
}

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	int k;
	cin>>a>>b>>k;
	if (!prime(k)){
		printf("0\n");
		return 0;
	}
	if (k >= 2000){
		precalc();
		int cnt=0;
		for (int i=1;i*k<=b;i++){
			if (i*k >= a && (p[i] >= k || i==1))
				cnt++;
		}
		cout<<cnt<<endl;
		return 0;
	}
	
	b/=k;
	a=(a/k)+!!(a%k);
	if (a>b){
		printf("0\n");
		return 0;
	}
	int ans = b-a+1;
	for (int i=2;i<k;i++){
		int coef = meb(i);
		int la = a/i+!!(a%i);
		int ra = b/i;
		int len = max(0,ra-la+1);
		ans += coef*len;
	}
	cout<<ans<<endl;
	return 0;
}