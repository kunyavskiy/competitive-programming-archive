#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <memory.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iterator>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;


struct Stack{
	vector<pair<int,int> > v;

	void push(int x){
		v.pb(mp(x,min(x,v.back().second)));
	}

	int getmin(){
		return v.back().second;
	}                          
	int pop(){
		int t = v.back().first;
		v.pop_back();
		return t;
	}
	int size(){
		return v.size() - 1;
	}
	Stack(){
		v.pb(mp(0x3f3f3f3f,0x3f3f3f3f));
	}
};

struct Queue{
	Stack a,b;

	void push(int x){
		a.push(x);
	}

	int pop(){
		if (!b.size()){
			while (a.size())
				b.push(a.pop());
		}
		return b.pop();
	}
	int getmin(){
		return min(a.getmin(),b.getmin());
	}
	int size(){
		return a.size() + b.size();
	}
};

int dp[10010];
int dp2[10010];

void solve(){
	int n,m;
	scanf("%d %d",&n,&m);
	memset(dp,0x3f,sizeof(dp));
	dp[0] = 0;

	Queue  s;

	for (int i = 0; i < m; i++){
	   int a,b,c;
	   scanf("%d %d %d",&a,&b,&c);

	   for (int j = 0; j <= n; j++){
	   	   s.push(dp[j] - j * b);
	   	   dp2[j] = dp[j] - j * b;
	   	   dp[j] = min(dp[j],s.getmin() + j * b + c);
	   	   if (j >= a)
	   	   	 s.pop();
	   }
	   while (s.size())
	   	s.pop();
	}

	cout << dp[n] << endl;
}

int main(){
    #ifdef LOCAL
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif

    int t;
    scanf("%d",&t);
    while (t-->0)
    	solve();
    return 0;
} 