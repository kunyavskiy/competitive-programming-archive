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

#define taskname "oil"

using namespace std;

typedef long long int64;
typedef long double ld;

int cost[110][110];
int n,m,f,k;
int d[110][110][210];
const int dx[4] = {0,1,0,-1};
const int dy[4] = {1,0,-1,0};

bool good(int a,int b){
    return 0 <= a && a < n && 0 <= b && b < m;
}

void solve(){
    scanf("%d %d %d %d",&n,&m,&f,&k);
    memset(cost,63,sizeof(cost));
    memset(d,63,sizeof(d));
    int V0 = d[0][0][0];
    for (int i = 0; i < k; i++){
        int a,b;
        scanf("%d %d",&a,&b);
        --a,--b;
        double c;
        scanf("%lf",&c);
        cost[a][b] = min(cost[a][b],int(c*100+(1e-9)));
    }
    f = min(f,200);
    d[0][0][f] = 0;
    deque<int> qx,qy,qf;
    qx.pb(0),qy.pb(0),qf.pb(f);

    int ans = V0;

    for (;!qx.empty();){
        int x = qx.front();qx.pop_front();
        int y = qy.front();qy.pop_front();
        int f = qf.front();qf.pop_front();

        if (d[x][y][f] > ans)
            continue;

        if (x == n-1 && y == m-1)
            ans = min(ans,d[x][y][f]);         

        if (f){
            for (int i = 0; i < 4; i++){
                if (good(x+dx[i],y+dy[i]) && d[x+dx[i]][y+dy[i]][f-1] > d[x][y][f]){
                    d[x+dx[i]][y+dy[i]][f-1] = d[x][y][f];
                    qx.push_front(x+dx[i]);
                    qy.push_front(y+dy[i]);
                    qf.push_front(f-1);
                }                                   
            }
        }

        if (cost[x][y] < 100000 && f != ::f){
            if (d[x][y][f+1] > d[x][y][f] + cost[x][y]){
/*                if (d[x][y][f+1] != V0){
                    qx.push_front(x);
                    qy.push_front(y);
                    qf.push_front(f+1);
                }
                else {*/
                    qx.push_back(x);
                    qy.push_back(y);
                    qf.push_back(f+1);
//                }                    
                d[x][y][f+1] = d[x][y][f] + cost[x][y];
            }
        }
    }


    if (ans == V0)
        printf("-1\n");
    else
        printf("%.2lf\n",ans/100.0);
}

int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif
        int t;
        scanf("%d",&t);
        for (int i = 0; i < t; i++)
            solve();    
    	return 0;
} 