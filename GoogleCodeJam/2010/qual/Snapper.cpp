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

int main()
{
	int t;
	cin>>t;
	for (int test=1;test<=t;test++){
		int64 n,k;
		cin>>n>>k;
		int64 tmp=1;
		tmp=tmp<<n;
		k%=tmp;
		if (k==tmp-1)
			printf("Case #%d: ON\n",test);
		else
			printf("Case #%d: OFF\n",test);
	 }
	 return 0;
}