#include <iostream>
#include <fstream>
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
#include <bitset>
#include <iterator>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

#define taskname "ranking"



using namespace std;

typedef long long int64;
typedef long double ld;

bool g[510][510];
bitset<500> g2[510];
bitset<500> g3[510];
int cnt[510];
int ans[510];

int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif
	int n;
	scanf("%d",&n);
	#ifdef MAXTEST
		n=500;
	#endif
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++){
			char c;
			scanf(" %c ",&c);
			#ifdef MAXTEST
				c='1';
			#endif			
			g[i][j]=c=='1';
			if (g[i][j]){
				g2[i].set(j);
				g3[i].set(j);
			}
		}
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++){
			if (g[i][j])
				g3[i]|=g2[j];
		}
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			g[i][j]=g3[i].test(j) && (i!=j);
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			cnt[i]+=g[i][j];
	for (int i=0;i<n;i++){
		ans[i]=-1;
		for (int j=0;j<n;j++)
			if (cnt[j] == n-i-1){
				cnt[j]=-1;
				ans[i]=j;
				break;
			}
		if (ans[i]==-1){
			cout<<"impossible"<<endl;
			return 0;
		}
		for (int j=0;j<n;j++)
				if (g[j][ans[i]])
					cnt[j]--;
	}		
	cerr<<"!!!"<<endl;
	for (int i=0;i<n;i++)
		cout<<ans[i]+1<<" \n"[i==n-1];
	return 0;
} 