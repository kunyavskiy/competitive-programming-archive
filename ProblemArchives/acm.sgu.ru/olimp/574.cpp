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

int f[50];


int main()
{                        
	freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	int n;
	cin>>n;
	for (int i=1;i<=n;i++)
		cout<<i<<" \n"[i==n];
	f[0]=1;
	f[1]=2;
	for (int i=0;i<n;i++){
		if (i>=2)
			f[i]=f[i-1]+f[i-2];
		cout<<f[i]<<" \n"[i==n-1];
	}
	return 0;
}