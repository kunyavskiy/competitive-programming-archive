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

int t[3100];
int a[3100];
int n;


int main()
{                        
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d",&n);
	for (int i=0;i<n;i++)
		scanf("%d",&a[i]);
	int ans = 0;
	for (int i=0;i<n;i++){
		t[i]=1;
		for (int j=0;j<i;j++)
			if (a[j]*2==a[i])
				t[i]=max(t[i],t[j]+1);		
		ans = max(ans,t[i]);
	}
	cout<<ans<<endl;
	return 0;
}