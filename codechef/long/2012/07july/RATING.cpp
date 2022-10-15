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

multiset<int> a,b,c;

void norm(multiset<int>& a,multiset<int>& b){
    if (a.size() - b.size() > 1){
        b.insert(*--a.end());
        a.erase(--a.end());
    }
    if (a.size() && b.size() && *--a.end() > *b.begin()){
        b.insert(*--a.end());
        a.erase(--a.end());
        a.insert(*b.begin());
        b.erase(b.begin());
    }
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    int n;

    scanf("%d",&n);
    for (int i = 0; i < n; i++){
        int x;
        scanf("%d",&x);
        if (x == 1){
            scanf("%d",&x);
            a.insert(x);
            norm(a,b);
            norm(a,c);
            norm(b,c);
        }
        else {                                                       
            if (c.empty())
                printf("No reviews yet\n");
            else
                printf("%d\n",*c.begin());
        }
    }

  return 0;
}