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

int x[1100];
int y[1100];

int d[1100][1100];
int n,k;
int used[1100];
int used2[1110],used2ptr;
int deg[1100];
int cnt;
vector<int> g[1100];


int calc2(){
    ++used2ptr;
    int temp = 0;
    for (int it = 1; it < 3; it++){
        for (int i = 0; i < n; i++)
            if (deg[i] == it){
                if (used[i] || used2[i] == used2ptr)
                    continue;
                int num = 1;
                for (int j = i; ; num++){
                    used2[j] = used2ptr;
                    int id = -1;
                    for (int k = 0,sz = g[j].size(); k < sz; k++)
                        if (!used[g[j][k]] && used2[g[j][k]] != used2ptr){
                            id = g[j][k];
                            break;
                        }
                    if (id == -1)
                        break;
                    if (id == i){
                        num++;
                        break;
                    }
                }
                temp += num/2;
                if (temp > cnt)
                    return temp;
            }
  }   

  return temp;

}

set<pair<int,int> > s;

void use(int v){
    used[v]++;
    if (used[v] == 1){
        s.erase(mp(deg[v],v));
        cnt--;    
        for (int i = 0,sz = g[v].size(); i < sz; i++)
            if (!used[g[v][i]]){
                s.erase(mp(deg[g[v][i]],g[v][i]));
                deg[g[v][i]]--;        
                if (deg[g[v][i]])
                    s.insert(mp(deg[g[v][i]],g[v][i]));
            }
    }
}

void unuse(int v){
    used[v]--;
    if (used[v] == 0){         
        cnt++;
        deg[v] = 0;
        for (int i = 0,sz = g[v].size(); i < sz; i++)
            if (!used[g[v][i]]){
               s.erase(mp(deg[g[v][i]],g[v][i]));
               deg[g[v][i]]++;
               if (!used[g[v][i]])
                   s.insert(mp(deg[g[v][i]],g[v][i]));
            }
            else
               deg[v]++;
        s.insert(mp(deg[v],v));
    }
}

bool go(){
//    cerr << v << " "<<cnt << endl;
  //  cerr << deg[0] <<" "<<deg[2] <<" "<<deg[3] <<" "<< deg[1] <<" "<<deg[6] << endl;
 
    cerr << "Sz = "<<s.size() << endl;
    if (s.empty() ||  (--s.end())->first == 2){

        int temp = calc2();
        return temp <= cnt;
    }
    int v;

  
    if (s.begin()->first == 1)
        v = s.begin()->first;
    else
        v = (--s.end())->first;

    cerr << v << endl;

    for (int i = 0,sz = g[v].size(); i < sz; i++)
       use(g[v][i]);

    if (cnt >= 0){
        cerr <<"!!"<<endl;
        if (go())
            return true;
    }

    for (int i = 0,sz = g[v].size(); i < sz; i++)
       unuse(g[v][i]);



    if (deg[v] != 1){
        use(v);
        if (cnt >= 0)
           if (go())
               return true;
        unuse(v);
    }
    
    return false;
}

bool check(int m){
    memset(used,0,sizeof(used));
    memset(deg,0,sizeof(deg));
    cnt = k;
    for (int i = 0; i < n; i++)
        for (int j = i+1; j < n; j++)
            if (d[i][j] > m){
                deg[i]++,deg[j]++;
  //              cerr <<"!!!"<<i <<" "<<j<<endl;
            }

    for (int i = 0; i < n; i++){
        if (deg[i] > cnt){
    //        cerr <<"!!!!"<<i<<endl;
            for (int j = 0; j < n; j++)
                if (d[i][j] > m)
                    deg[j]--;
            used[i] = 1;
            cnt--;
            if (cnt < 0)
                return 0;
        }
    }
    //cerr << endl;

    for (int i = 0; i < n; i++){
        if (used[i])
            continue;
        g[i].clear();
        for (int j = 0; j < n; j++)
            if (d[i][j] > m && !used[j]){
  //              cerr <<"!!"<<i<<" "<<j<<endl;
                g[i].pb(j);
            }
    }
    
    for (int i = 0; i < n; i++)
        if (!used[i] && deg[i])
            s.insert(mp(deg[i],i));

    return go();        
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  scanf("%d %d",&n,&k);
  for (int i = 0; i < n; i++)
    scanf("%d %d",&x[i],&y[i]);

  int l = -1;
  int r = 2100000000;

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      d[i][j] = (x[i] - x[j])*(x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);


//  check(49);
//  return 0;
//  assert(check(r));


  while (r - l > 1){
    int m = (l+r)/2;
//    cerr << m <<" "<<check(m) << endl;
    if (check(m))
        r = m;
    else
        l = m;
  }

//  cerr <<"!!!!"<<r<<endl;

  assert(check(r));

  int cnt = 0;

//  cout << r << endl;

  for (int i = 0; i < n; i++)
    if (used[i])
        printf("%d ",i+1),cnt++;

  for (int i = 0; i < n && cnt < k; i++)
    if (!used[i])
        printf("%d ",i+1),cnt++;
    

  return 0;
}

