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
           

const int MAXN = 10000000;

bool p[MAXN];
vector<int> pr;

void find(){
    for (int i = 2; i < MAXN; i++){
        if (!p[i])
            pr.pb(i);
        for (int j = i; i*1LL*j < MAXN; j++)
            p[i*j] = true;
    }
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  find();

  //int cnt = 60000;
  int cnt;
  cin >> cnt;
  /*for (int i = 0; i < (int)pr.size() && cnt; i++){
    for (int j = i; j < (int)pr.size() && 5*pr[i] >= pr[j] && cnt; j++)
        for (int k = j; k < (int)pr.size() && 5*pr[j] >= pr[k] && cnt; k++){
            if (((pr[i] + pr[j])*1LL*(pr[i] + pr[j]) - 1)%pr[k])
                continue; 
            if (((pr[j] + pr[k])*1LL*(pr[j] + pr[k]) - 1)%pr[i])
                continue;
            if (((pr[k] + pr[i])*1LL*(pr[k] + pr[i]) - 1)%pr[j])
                continue;
            printf("%d %d %d\n",pr[i],pr[j],pr[k]);
            cnt--;
            //if (cnt % 1000 == 0)
            //    cerr << cnt << " "<<pr[i] << " " <<pr[j] <<" "<<pr[k]<<endl;
        }
  } */

  for (int i = 2; i < MAXN/2-1 && cnt; ++i){
    
    if (!p[i] && !p[2*i-1]){
        //printf("%d %d %d\n",i,i,2*i-1);
        --cnt;
        if (cnt == 0){
            cout << i <<" "<<i<<" "<<2*i-1<<endl;
            return 0;
        }        
    }   
    if (!p[i] && !p[2*i+1]){
        //printf("%d %d %d\n",i,i,2*i+1);
        --cnt;
        if (cnt == 0){
            cout << i <<" "<<i<<" "<<2*i+1 << endl;
            return 0;
        }
    }         
  }
  return 0;
}