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

int n;

bool check(int mask){
	for (int i=0;i*2<=n;i++){
		if (mask& (1<<i)){
			if (mask & (1<<(2*i)))
				return false;
			if (i*3 <= n)
				if (mask & (1<<(3*i)))
					return false;
		}
	}
	return true;
}

void solve(int n){
	::n=n;
	int ans=0;
	for (int i=0;i<(1<<n);i++)
		ans+=check(i);
	cout<< ans << endl;
}

int main()
{                        
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	for (int i=1;i<25;i++)
		solve(i);
    return 0;
}