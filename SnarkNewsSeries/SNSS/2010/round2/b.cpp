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
#include <sstream>
#include <iterator>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

#define taskname "B"

using namespace std;

typedef long long int64;
typedef long double ld;

bool used[1000];
vector<int> g[1000];
bool done[1000];
vector<int> ans;

string pr;

int main(){
	#ifdef LOCAL
		#ifndef taskname
			#error taskname is not defined
		#else
			freopen(taskname".in","r",stdin);
			freopen(taskname".out","w",stdout);
		#endif
	#endif
	used[0]=true;
	int n,m;
	scanf("%d %d\n",&n,&m);
	for (int i=0;i<m;i++){
		string s;
		getline(cin,s);
		stringstream str(s);
		int a;
		for (;str>>a;)
		{
			--a;
			g[i].pb(a);
		}
	}
	for (int i=0;i<m;i++){
		bool q=false;
		for (int j=0;j<m;j++)
			if (!done[j]){
				int sz=g[j].size();
				for (int k=0;k<sz;++k)
					if (used[g[j][k]]){
						q=true;
						break;
					}
				if (q){
					for (int k=0;k<sz;k++)
						used[g[j][k]]=true;
					done[j]=true;
					ans.pb(j+1);
					break;
				}	
			}
		if (!q){
			printf("Impossible\n");
			return 0;
		}
	}
	for (int i=0;i<m;i++)
		printf("%d ",ans[i]);
	printf("\n");
	
	return 0;
} 