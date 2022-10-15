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

int gcd(int a,int b){
	if (b==0) return a;
	return gcd(b,a%b);
}

int main()
{                        
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	int n;
	cin>>n;
	int ans = 1;
	for (int i=1;i<=n;i++)
		ans = ans * i /gcd(ans,i);
	cout << ans+1 << endl;
    return 0;
}