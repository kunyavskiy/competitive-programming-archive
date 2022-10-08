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

set<int> ans[50010];

set<int> small;
set<int> big;

int res[210000];


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    int n,m,k;
    scanf("%d %d %d",&m,&n,&k);

    for (int i = 0; i < n; i++)
        small.insert(i);

    int id = 0;

    for (int i = 0; i < m; i++){
        char c;
        scanf(" %c",&c);
        if (c == '-'){
            int id;
            scanf("%d",&id);
            int from = res[id];
            if (big.empty()){
                small.swap(big);
            }
            if (big.find(from) != big.end()){
                ans[from].erase(id);
                big.erase(from);
                small.insert(from);
                continue;
            }
            ans[from].erase(id);
            set<int>::iterator iter = big.lower_bound(from);
            int temp;
            if (iter == big.begin()){
                temp = *iter;
            } else if (iter == big.end()){
                temp = *(--iter);
            }
            else {
                set<int>::iterator iter2 = iter;
                iter2--;
                if (abs(*iter-from) < abs(*iter2-from))
                    temp = *iter;
                else
                    temp = *iter2;
            }
            big.erase(temp);
            small.insert(temp);

            id = *ans[temp].begin();
            ans[temp].erase(id);
            ans[from].insert(id);
            res[id] = from;            
        }
        else {
           ++id;
           if (small.empty()){
              small.swap(big);
           } 
           int to = *small.begin();
           ans[to].insert(id);
           small.erase(to);
           big.insert(to); 
           res[id] = to;
        }
    }

    for (int i = 0; i < n; i++,printf("\n")){
        printf("%d",ans[i].size());
        for (set<int>::iterator iter = ans[i].begin(); iter != ans[i].end(); ++iter)
            printf(" %d",*iter);
    }

    return 0;
}