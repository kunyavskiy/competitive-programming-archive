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

map<string,string> a;

char buf1[10000];
char buf2[11000];

int main (void){
#ifdef LOCAL
  freopen ("input.txt", "r", stdin);
    freopen ("output.txt", "w", stdout);
#endif

    for (int i = 0; i < 12; i++){
        string s;
        cin >> s;
        if (i < 4)
            a[s] = "gold";
      else if (i < 8)
        a[s] = "silver";
      else
        a[s] = "bronze";
    }

    int best = -1,cnt = 0;

    int k;
    cin >> k;

    for (; k --> 0;){
        int n;
        scanf("%d",&n); 
        int cur = 0;
        for (int j = 0; j < n; j++){
            scanf(" %s : %s",buf1,buf2);
            string t = buf2;
            if ( a.find(string(buf1)) != a.end() && a[string(buf1)] == t)
                cur++;
        }


        if (cur == best)
            cnt += 5;
        else if (cur > best){
            best = cur;
            cnt = 5;
        }
            
    }

    cout << cnt << endl;
        
    
  return 0;
  
}