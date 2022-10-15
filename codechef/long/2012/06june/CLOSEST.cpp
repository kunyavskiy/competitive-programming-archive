// WHAT'S WRONG WITH YOU GUYS??? WTF IS PENTIUM 3??? PLEASE UPGRADE SERVERS! IT'S RIDICULOUS TO TEST SOLUTIONS ON 9-YEAR OLD SYSTEM!"
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
    #define myrand() ((rand()<<15)|rand())
#else
    #define LLD "%lld"
    #define myrand() rand()
#endif

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

#ifdef LOCAL
    ld START = clock();
#endif


struct point{
    int x,y,z;
    int id;
};     

inline ull dist(const point& a,const point& b){
    return (ull)((a.x-b.x)*1LL*(a.x-b.x)) + (ull)((a.y-b.y)*1LL*(a.y-b.y)) + (ull)((a.z-b.z)*1LL*(a.z-b.z));
}

int vx,vy,vz;

inline bool pcmp(const point& a,const point& b){
    return (a.x-b.x)*1LL*vx + (a.y-b.y)*1LL*vy + (a.z-b.z)*1LL*vz < 0;
}
       
int ans[50010];
ull val[50010];

point _ab[100010];
point* a;
point* b;

int v[100010];
int n,m;


inline bool cmp(int a,int b){
    return pcmp(_ab[a], _ab[b]);
}


inline void update(int x,int y){
    ull tmp = dist(b[x], a[y]);
    if (val[x] > tmp) ans[x] = y, val[x] = tmp;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    srand(239017);

    scanf("%d",&n);
    a = _ab;
    b = _ab + n;
    for (int i = 0; i < n; i++)
        scanf("%d %d %d",&a[i].x,&a[i].y,&a[i].z), v[i] = i;

    scanf("%d",&m);

    for (int i = 0; i < m; i++)
        scanf("%d %d %d",&b[i].x,&b[i].y,&b[i].z), v[i+n] = i+n, val[i] = (ull)(1.4e19);

    for (int i = 0; i < n; i++)
       update(0,i);
                        
    vector<int> last;

    for (int i = 0; i < 1; i++){
        vx = myrand(), vy =myrand(), vz = myrand();
        sort(v,v+n+m,cmp);

        last.clear();
                          
        for (int j = 0; j < n+m; j++)
            if (v[j] < n)
                last.pb(v[j]);
            else {
                for (vector<int>::iterator iter = last.begin()+max(0,(int)last.size()-350); iter != last.end(); ++iter)
                    update(v[j] - n,*iter);
            }

        reverse(v,v+n+m);

        last.clear();
                                     
        for (int j = 0; j < n+m; j++)
            if (v[j] < n)
                last.pb(v[j]);
            else {
                for (vector<int>::iterator iter = last.begin()+max(0,(int)last.size()-350); iter != last.end(); ++iter)
                    update(v[j]-n,*iter);
            }
    }     

    for (int i = 0; i < m; i++)
        printf("%d\n",ans[i]);

    #ifdef LOCAL
        cerr << (clock()-START)/CLOCKS_PER_SEC << endl;
    #endif


    return 0;
}