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

string s[1100];
int p[1100];

char _s[1100];

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int n,q;
  scanf("%d",&n);

  for (int i = 0; i < n; i++){
     scanf(" %s %d",_s,&p[i]);
     s[i] = _s;
  }

  scanf("%d",&q);

  for (int i = 0; i < q; i++){
    scanf(" %s",_s);
    string t = _s;

    int id = -1;

    for (int j = 0; j < n; j++)
        if (s[j].size() >= t.size() && string(s[j].begin(),s[j].begin()+t.size()) == t)
            if (id == -1 || p[id] < p[j])
                id = j;

    if (id == -1)
        puts("NO");
    else
        puts(s[id].data());

  }

  return 0;
}

