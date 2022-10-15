#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cassert>
#include <queue>
#include <string>
#include <ctime>
#include <stack>

#define sqr(x) ((x)*(x))
#define sz(a) (int)a.size()
#define pb push_back
#define mp make_pair
#define zero(a) memset (a, 0, sizeof(a))



#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

#define taskname ""

const int inf = (int)1e9;

const int MAXN = 1100;

int mt[MAXN];
int res[MAXN];
int l[MAXN];
int r[MAXN];

int used[MAXN];

pair<int,int> room[MAXN];

vector<pair< pair<int,int>,int > > v; // start,end,num


void dfs(int v){
    if (used[v] == 1){
        printf("Ask Shiftman for help.\n");
        exit(0);
    }
    if (used[v] == 2)
        return;
    used[v] = 1;
    for (int i = l[v]; i < r[v]; i++)
        if (mt[i] != v)
            dfs(mt[i]);
    used[v] = 2;
}


int main (void){
#ifdef LOCAL
  freopen ("input.txt", "r", stdin);
    freopen ("output.txt", "w", stdout);
#endif
    int n;
    scanf("%d",&n);
    for (int i = 0; i < n; i++){
        scanf("%d",&room[i].first);
        room[i].second = i;
    }

    sort(room,room+n);

    for (int i = 0; i < n; i++){
        int l,r;
        scanf("%d %d",&l,&r);
        ::l[i] = lower_bound(room,room+n,mp(l,-(1<<30))) - room;
        ::r[i] = upper_bound(room,room+n,mp(r,(1<<30))) - room;
        v.pb(mp( mp( ::l[i], ::r[i]), i));
    }

    sort(v.begin(),v.end());

    set<pair<int,int> > s;

    int ptr = 0;

    for (int i = 0; i < n; i++) {
        
        for (;ptr < n  && v[ptr].first.first == i; ++ptr)
            s.insert(mp(v[ptr].first.second,v[ptr].second));
        

//       cerr << s.begin()->first <<" "<<i << endl;

        if (s.empty() || s.begin()->first <= i){
            printf("Let's search for another office.\n");
            return 0;
        }

        mt[i] = s.begin()->second;
        s.erase(s.begin());
    }

    for (int i = 0; i < n; i++)
        if (!used[i])
            dfs(i);

    printf("Perfect!\n");

    for (int i = 0; i < n ; i++)
        res[mt[i]] = room[i].second + 1;

    for (int i = 0; i < n; i++)
        printf("%d%c",res[i]," \n"[i==n-1]);
  return 0;  
}