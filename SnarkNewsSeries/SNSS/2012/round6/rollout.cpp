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

char s[500][500];
int d[500][500];
int n,m;

const int dx[4] = {0,1,0,-1};
const int dy[4] = {-1,0,1,0};

bool good(int x,int y){
    return 0 <= x && x < n && 0 <= y && y < m && s[x][y] != 'X';
}

void solve(){
    scanf("%d %d",&n,&m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf(" %c",&s[i][j]);

    memset(d,63,sizeof(d));

    queue<int> qx;
    queue<int> qy;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (s[i][j] == 'L'){
                qx.push(i);
                qy.push(j);
                d[i][j] = 0;
            }

    for (;!qx.empty();){
        int x = qx.front();qx.pop();
        int y = qy.front();qy.pop();

        for (int i = 0; i < 4; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (good(nx,ny) && d[nx][ny] > d[x][y] + 1){
                d[nx][ny] = d[x][y] + 1;
                qx.push(nx);
                qy.push(ny);
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (s[i][j] == 'B'){
                if (d[i][j] > n*m){
                    printf("-1\n");
                    return;
                }
                ans += 2 * d[i][j];
            }

    cout << ans << endl;
    return ;
}

int main(){
    #ifdef LOCAL
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif

    int t;
    scanf("%d",&t);

    while (t-->0){
        solve();
    }


    return 0;
} 