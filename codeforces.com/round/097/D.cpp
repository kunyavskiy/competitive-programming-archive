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

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

char s[1100][1100];

int used[1100][1100];
int ptr;
int anyx,anyy;
bool ok;
int n,m;

vector<pair<int,int> > v;


void dfs(int x,int y){
    if (x < 0 || y < 0 || x >= n || y >= m){
        anyx = anyy = -2;
        return;
    }
    if (s[x][y] == '0' && used[x][y] == ptr)
        return;
    if (s[x][y] == '1'){
        used[x][y] = ptr;
        if (anyx == -1)
            anyx = x,anyy = y;
        v.pb(mp(x,y));
        return;
    }

    used[x][y] = ptr;

    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            dfs(x+i,y+j);    
}

const int dx[4] = {0,1,0,-1};
const int dy[4] = {1,0,-1,0};

int dfs2(int x,int y){
    if (x < 0 || y < 0 || x >= n || y >= m){
        return 0;
    }
    if (s[x][y] == '0')
        return 0;
    if (used[x][y] != ptr-1)
        return 0;

    used[x][y] = ptr;
    int ans = 1;
    int cnt = 0;

    for (int i = 0; i < 4; i++){
        int x1 = x + dx[i];
        int y1 = y + dy[i];
        if (x < 0 || y < 0 || x >= n || y >= m || s[x1][y1] == '0')
            continue;
        cnt += (used[x1][y1] == ptr) || (used[x1][y1] == ptr-1);
        ans += dfs2(x1,y1);
    }

//    cerr << x <<" "<<y<<" "<<cnt << endl;

    if (cnt != 2)
        ok = false;
    return ans;
}

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    gets(s[0]);
    sscanf(s[0],"%d %d",&n,&m);

    int ans = 0;

    for (int i = 0; i < n; i++)
        gets(s[i]);

    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < m-1; j++)
            if (s[i][j] == '1' && s[i][j+1] == '1' && s[i+1][j] == '1' && s[i+1][j+1] == '1')
                ans = 4;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (used[i][j] == 0 && s[i][j] == '0'){
                anyx = anyy = -1;
                ++ptr;
                dfs(i,j);
                if (anyx == -2)
                    continue;
                ok = true;
                ++ptr;                
                int temp = dfs2(anyx,anyy);
                for (int i = 0; i < v.size(); i++)
                    ok &= used[v[i].first][v[i].second] == ptr;
                v.clear();
                if (ok)
                    ans = max(ans,temp);
            }

    cout << ans << endl;
    return 0;
}