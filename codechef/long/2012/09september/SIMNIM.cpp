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
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

                       
int color[1100];
int best[1100];
int ans;

ll mask[100];
int id[100];
int bid[100];
ll used[100]; 
int cnt;

int colorid;

bool cmpsz(const vector<int>& a,const vector<int>& b){
    return a.size() < b.size();
}

struct TestCase{
   pair<ll,int> val[1100];
   int n;

   vector<vector<int> > groups;

   void init(){
       cnt = 0;
   }

   bool add(ll mask,int id){
       assert(cnt <= 63);
       ll mask0 = mask;
       ll used = 0;
       for (int i = 0; i < cnt; i++){
           if (mask & (1LL<<bid[i])){
               mask ^= ::mask[i];
               used ^= ::used[i];
           }
       }
       if (mask){
           ::mask[cnt] = mask;
           ::id[cnt] = id;
           bid[cnt] = 63 - __builtin_clzll(mask);
           ::used[cnt] = used ^ (1LL << cnt);
           ++cnt;
           return false;
       }
       else {
           vector<int> group;
           ++colorid;
           for (int i = 0; i < cnt; i++)
               if (used & (1LL << i)){
                   group.pb( ::id[i]);
                   color[ ::id[i]] = colorid;
                   mask0 ^= ::mask[i];
               }
           group.pb(id);
           color[id] = colorid;
           if (group.size() <= 10)
               groups.pb(group);
           return true;
       }
   }


   void solveonce(int type){
       int n = this->n;
       colorid = 0;
       for (int i = 0; i < n; i++)
           color[i] = -1;
       while (n){
           init();
           if (type == 0)
               random_shuffle(val,val+n);
           for (int j = n - 1; ; j--){
               assert(j >= 0);
               if (add(val[j].first, val[j].second)){
                   for (int i = n-1; i >= j; i--)
                       if (color[val[i].second] != -1){
                           swap(val[i],val[n-1]);
                           --n;
                       }
                   break;
               }
           }
       }
   }

   void load(){
      scanf("%d",&n);

      ll tot = 0;
      for (int i = 0; i < n; i++){
         scanf(LLD,&val[i].first);
         val[i].second = i; 
         tot ^= val[i].first;
      }
      assert(!tot);
   }

   void updateAns(){
        int curans = *max_element(color,color+n);
        if (curans > ans){
            ans = curans;
            memcpy(best,color,sizeof(int)*n);
        }
   }


   void solve2(int tp){
      if (tp == 0) sort(groups.begin(),groups.end(), cmpsz);
      else random_shuffle(groups.begin(),groups.end());

      for (int i = 0; i < n; i++)
        color[i] = -1;

      colorid = 0;

      for (int i = 0; i < (int)groups.size(); i++){
          bool q = true;
          for (int j = 0; j < (int)groups[i].size() && q; j++)
            q &= color[groups[i][j]] == -1;
          if (q){
              ++colorid;
              for (int j = 0; j < (int)groups[i].size() && q; j++)
                  color[groups[i][j]] = colorid;
          }
      }

      for (int i = 0; i < n; i++)
        if (color[i] == -1){
            ++colorid;
            for (int j = 0; j < n; j++)
                if (color[j] == -1)
                    color[j] = colorid;
        }
   }
 

   void solve(double TL){
       double start = clock();
       ans = 0;
       
       sort(val,val+n);
       solveonce(1);
       reverse(val,val+n);
       solveonce(1);

       for (;clock() - start < TL * CLOCKS_PER_SEC * 0.75;){
           solveonce(0);
           updateAns(); 
       }

       solve2(0);
       updateAns();

       for (;clock() - start < TL * CLOCKS_PER_SEC;){
           solve2(1);                            
           updateAns(); 
       }

       for (int i = 0; i < n; i++)
           printf("%d%c",best[i]," \n"[i == n-1]);    
   }

};

TestCase T[10];

#ifndef LOCAL
const double TTL = 3.7;
#else
const double TTL = 0.8;
#endif

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int t;
  scanf("%d",&t);

  int TN = 0;

  for (int i = 0; i < t; i++){
    T[i].load();
    TN += T[i].n;
  }
  for (int i = 0; i < t; i++)
    T[i].solve(TTL / TN * T[i].n);

  return 0;
}