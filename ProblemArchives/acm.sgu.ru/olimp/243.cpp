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

int t[350][350];
char s[350];

vector<int> l;
vector<int> r;
vector<int> c;

int calc(int l,int r){
	if (l>r)
		return 0;
	int& ans=t[l][r];
	if (ans!=-1)
		return ans;
	for (;l<r && s[r]==s[l];--r);
	if (l==r)
		return ans=0;
	ans=1<<30;
	for (int i=l;i<=r;i++)
		if (s[i]==s[r])
			ans=min(ans,calc(l,i-1)+calc(i,r)+1);
	return ans;
}

void gen(int l,int r){
	if (l>r)
		return;
	int ans=calc(l,r);
	for (;l<r && s[r]==s[l];--r);
	if (l==r)
		return;
	for (int i=l;i<=r;i++)
		if (s[i]==s[r])
			if (ans == calc(l,i-1)+calc(i,r)+1){
				::l.pb(i);
				::r.pb(r);
				::c.pb(s[r]);
				gen(l,i-1);
				gen(i,r);
				return;
			}
	assert(false);
}


int main()
{                        
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	memset(t,-1,sizeof(t));
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++)
		scanf(" %c ",&s[i]);		
	cout<<(calc(0,n-1)+1)<<endl;
	l.pb(0);
	r.pb(n-1);
	c.pb(s[0]);
	gen(0,n-1);
	for (int i=0;i<l.size();i++)
		printf("%d %d %c\n",l[i]+1,r[i]+1,c[i]);		
    return 0;
}