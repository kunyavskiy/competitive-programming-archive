#ifndef LOCAL
    #pragma comment(linker, "/STACK:33554432")
#endif

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
#define setval(a,v) memset(a,v,sizeof(a))

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;


int n,m,k;

bool used1[1100];
bool used2[1100];
bool dp[1100][1100];


pair<char,int> plan1[1100];
pair<char,int> plan2[1100];


void solve(){
	memset(used1,0,sizeof(used1));
	memset(used2,0,sizeof(used2));
	memset(dp,0,sizeof(dp));
	scanf("%d%d%d",&n,&m,&k);
	for (int i = 0; i < n; i++)
		scanf(" %c %d",&plan1[i].first,&plan1[i].second);
	for (int i = 0; i < m; i++)
		scanf(" %c %d",&plan2[i].first,&plan2[i].second);

	dp[0][0] = 1;

	for (int i = 0; i < n; i++){
		memcpy(used2,used1,sizeof(used1));
		for (int j = 0; j < m; j++){
			if (dp[i][j]){
//				cerr << i << " "<<j << " "<<used2[1]<<" "<<used2[2] <<endl;
				bool can = false;
				if (plan1[i].first == '-' || !used2[plan1[i].second])
					dp[i+1][j] = can = true;
				if (plan2[j].first == '-' || !used2[plan2[j].second])
					dp[i][j+1] = can = true;
				if (!can){
					printf(":-(\n");
					return;
				}
			}
			used2[plan2[j].second] ^= 1;
		}
		used1[plan1[i].second] ^= 1;
	}
	printf(":-)\n");
//	cerr << endl << endl;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  int t;
  scanf("%d",&t);
  for (int i = 0; i < t; i++)
     solve();
  return 0;
}