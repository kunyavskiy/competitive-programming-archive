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
#include <iterator>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

const int dx[4] = {0,1,0,-1};
const int dy[4] = {1,0,-1,0};

double dp[15][15];
double dp2[15][15];
double cnt[15][15];

inline bool good(int x,int y,int n,int m){
	return 0 < x && x <= n && 0 < y && y <= m;
}

void solve(){
	int n,m;
	int x,y;
	int tox,toy;
	int p;
	scanf("%d %d %d %d %d %d %d",&n,&m,&x,&y,&tox,&toy,&p);
	x++,y++;
	tox++,toy++;

	memset(dp2,0,sizeof(dp2));
	dp2[x][y] = 1;

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++){
			int c = 0;
			for (int k = 0; k < 4; k++)
				c += good(i + dx[k], j + dy[k],n , m);
			cnt[i][j] = 1.0 / c;
		}
				
	double ans = 0;

	for (int it = 0; it < p; it++){
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				dp[i][j] = dp2[i][j], dp2[i][j] = 0;
			
		ans += dp[tox][toy];
		dp[tox][toy] = 0;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				for (int k = 0; k < 4; k++)
					dp2[i+dx[k]][j+dy[k]] += dp[i][j] * cnt[i][j];


	}

	cout.precision(15);
	cout << fixed << ans + dp2[tox][toy] << endl;

}

int main(){
    #ifdef LOCAL
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif

    int t;
    scanf("%d",&t);

    while (t-->0)
    	solve();


    return 0;
} 