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

string s[1000];

int main()
{                        
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++)
		cin>>s[i];
	sort(s,s+n);
	int ans=0;
	for (int i=0;i<n;){
		int j=i;
		for (;s[i]==s[j];j++);
		ans=max(ans,j-i);
		i=j;
	}
	cout<<ans<<endl;;
    return 0;
}