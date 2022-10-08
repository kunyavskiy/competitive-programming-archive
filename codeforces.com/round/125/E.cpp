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

const int MAXN = 251000;
const int BSZ = 450;

#ifdef LOCAL
ld START = clock();
#endif

ll d[MAXN];
int m[MAXN];
int p[MAXN];
ll r[MAXN];
bool used[MAXN];

queue<int> q;


struct mComparer{
    bool operator()(int a,int b){
        if (m[a] != m[b])
            return m[a] < m[b];
        return a < b;
    }
};


struct dComparer{
    bool operator()(int a,int b){
        if (d[a] != d[b])
            return d[a] < d[b];
        return a < b;
    }
};


set<int,mComparer> s[MAXN/BSZ+5];

int ids[MAXN];
int n;



int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    int x,y;
    r[0] = 0;
    q.push(0);
    used[0] = true;
    int tmp;
    scanf("%d %d %d %d %d",&x,&y,&p[0],&tmp,&n);
    r[0] = tmp*1LL*tmp;
    ++n;

    for (int i = 1; i < n; i++){
        int tx,ty,r;
        scanf("%d %d %d %d %d",&tx,&ty,&m[i],&p[i],&r);
        tx -= x, ty-= y;
        d[i] = tx*1LL*tx +ty*1LL*ty;
        ::r[i] = r * 1LL * r;
        ids[i] = i;
    }

    sort(ids,ids+n,dComparer());

    for (int i = 0; i < n; i += BSZ){                
        for (int j = max(i,1); j < i+BSZ && j < n; j++)
            s[i/BSZ].insert(ids[j]);
    } 

    int ans = -1;


    for (;q.size();){
        ans++;
        
        //cerr << ans << endl;

        int x = q.front();
        q.pop();

        d[n] = r[x];
        m[n] = p[x];
        int rb = upper_bound(ids,ids+n,n,dComparer()) - ids - 1;
        if (rb == -1) continue;
        int bl = rb/BSZ;

                           
        for (;(rb+BSZ) % BSZ != BSZ-1; rb--)
            if (!used[ids[rb]] && d[ids[rb]] <= d[n] && m[ids[rb]] <= m[n]){
                used[ids[rb]] = true;
                s[bl].erase(ids[rb]);
                q.push(ids[rb]);
            }

        for (bl--; bl >= 0; bl--){
            while (true){
                set<int>::iterator iter = s[bl].upper_bound(n);
                if (iter == s[bl].begin())
                    break;
                --iter;
                used[*iter] = true;
                q.push(*iter);
                s[bl].erase(iter);
            }
        }

        /*#ifdef LOCAL
        for (int i = 0; i < n; i++)
            assert(used[i] || d[i] > d[n] || m[i] > m[n]);
        #endif */                   
    }                                   

    printf("%d\n",ans);

    #ifdef LOCAL
        cerr << (clock()-START)/CLOCKS_PER_SEC << endl;
    #endif
    return 0;
}