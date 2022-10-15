#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
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


const int dx[4] = {0,-1,0,1};
const int dy[4] = {1,0,-1,0};
const char name[5] = "ENWS";

char _s[510][510];
int s[510][510];
bool used[510][510];

char st[500*500+10];
int ptr;
int n,m;

bool dfs(int x,int y,int tox,int toy,int rot){
    if (x < 0 || x >= n || y < 0 || y >= m)
        return false;
    if (used[x][y])
        return false;
    if (x == tox && y == toy)
        return true;

    used[x][y] = true;
    rot += !!(s[x][y]&16);

    for (int i = 0; i < 4; i++){
        if (s[x][y] & (1<<i)){
            st[ptr++] = name[(i+rot)&3];
            if (dfs(x + dx[i], y + dy[i], tox,toy,rot))
                return true;
            --ptr;
        }
    }
    return false;
}

void solve(){
    scanf("%d %d",&m,&n);

    int sx,sy,ex,ey;
    scanf("%d %d %d %d ",&sy,&sx,&ey,&ex);
    for (int i = 0; i < n; i++){
        scanf(" %s",_s[i]);
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            s[i][j] = (isdigit(_s[i][j])?(_s[i][j]-'0'):(_s[i][j] - 'A' + 10)), used[i][j] = 0;

    ptr = 0;
    assert(dfs(sx,sy,ex,ey,0));
    st[ptr++] = 0;
    puts(st);
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