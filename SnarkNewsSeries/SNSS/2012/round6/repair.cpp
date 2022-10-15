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

int c[1100][1100];

const unsigned int MOD = (1LL<<31)-1;

map<string,int> id;

void PreCalc(){
    c[0][0] = 1;
    for (int i = 0; i < 1100; i++)
        for (int j = 0; j < 1100; j++){
            unsigned int t = 0;
            if (i) t += c[i-1][j];
            if (i && j) t += c[i-1][j-1];
            if (t >= MOD) t -= MOD;
            if (i || j)
            c[i][j] = t;
        }
}


char buf[200];

vector<vector<int> > v;

void solve(){
    v.clear();
    id.clear();
    int n,k;
    scanf("%d %d",&n,&k);
    for (int i = 0; i < n; i++){
        scanf(" %s",buf);
        id[buf] = i;
    }

    v.pb(vector<int>());
    for (int i = 0; i < n; i++)
        v[0].pb(i);
    
    ll ans = 0;

    for (int i = 0; i < k; i++){
        int c;
        scanf("%d",&c);
        vector<int> cur;
        for (int i = 0; i < c; i++){
            scanf(" %s",buf);
            int id = ::id[buf];
            cur.pb(id);
        }

        sort(cur.begin(),cur.end());

        ll curans = 1;

        int sz = v.size();
        for (int i = 0; i < sz; i++){
            vector<int> nv;
            nv.resize(v[i].size());
            nv.erase(set_intersection(cur.begin(),cur.end(),v[i].begin(),v[i].end(),nv.begin()),nv.end());
            
            if (nv.size()){
                curans = (curans * ::c[v[i].size()][nv.size()]) % MOD;
                if (ans >= MOD) ans -= MOD;
                vector<int> temp(v[i].size());
                temp.erase(set_difference(v[i].begin(),v[i].end(),cur.begin(),cur.end(),temp.begin()),temp.end());
                v[i] = temp;
                v.pb(nv);
            }
        }

        ans = (ans + curans) % MOD;

        /*for (int i = 0; i < (int)v.size(); i++,cerr<<endl)
            for (int j = 0; j < (int)v[i].size(); j++)
                cerr << v[i][j] <<" ";

        cerr<<endl<<endl;*/

    }

    cout << ans << endl;
}

int main(){
    PreCalc();
    #ifdef LOCAL
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif

    int t;
    scanf("%d",&t);
    for (int i = 0; i < t; i++){
        solve();
    }


    return 0;
} 