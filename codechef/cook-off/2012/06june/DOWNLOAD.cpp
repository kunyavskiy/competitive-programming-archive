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
#include <bitset>
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


struct event{
    int type;
    int x,y;
    bool operator<(const event& a) const{
        if (a.x != x)
            return x < a.x;
        return type < a.type;
    }
};

vector<event> evs;
vector<int> ys;

int n;

int ans[5100];

int fen[110000];

int get(int x){
    //cerr <<"!" << x <<" : ";
    x = upper_bound(ys.begin(),ys.end(),x)-ys.begin()-1;

  //  cerr << "Get " << x ;

    int res = 0;
    for (;x != -1; x = (x&(x+1))-1)
        res += fen[x];
   // cerr << " : " << res << endl; 
    return res;
}

void update(int x){
    x = upper_bound(ys.begin(),ys.end(),x)-ys.begin()-1;

   // cerr << "upd "<< x << endl;

    for (;x < (int)ys.size(); x = (x|(x+1)))
        fen[x]++;
}




int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    scanf("%d",&n);
    for (int i = 0; i < n; i++){
        int x,y;
        scanf("%d %d",&x,&y);
        ys.pb(y);
        evs.pb(event());
        evs.back().type = -1;
        evs.back().x = -x;
        evs.back().y = y;
    }

    sort(ys.begin(),ys.end());
    ys.erase(unique(ys.begin(),ys.end()),ys.end());

    int q;
    scanf("%d",&q);

    for (int i = 0; i < q; i++){
        ans[i] = n;

        int k;
        scanf("%d",&k);

        vector<int> t(k);
        for (int j = 0; j < k; j++)
           scanf("%d",&t[j]);

        t.pb(0);
        t.pb((int)1e9+10);
        sort(t.begin(),t.end());

        for (int j = 1; j <= k+1; j++){   
            evs.pb(event());
            evs.back().type = i;
            evs.back().x = -(t[j-1]+1);
            evs.back().y = t[j]-1;
        }        
    }

    sort(evs.begin(),evs.end());

    for (int i = 0; i < (int)evs.size(); i++){
       //cerr << evs[i].type <<" "<<evs[i].x <<" "<<evs[i].y << endl;
       if (evs[i].type == -1)
          update(evs[i].y);
       else
          ans[evs[i].type] -= get(evs[i].y);
    }

    for (int i = 0; i < q; i++)
        printf("%d\n",ans[i]);

     return 0;
}