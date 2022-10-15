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


char s[1100000];
ll ans;
ll cnt;

int main()
{
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    scanf("%s",s);
    int n = strlen(s);
    cnt = 0;
    ans = 0;

    for (int i = 0; i < n; i++){
        if (s[i] == '0' || s[i] == '8')
            ans++;
        if (i && ((s[i-1]-'0')*10 + s[i]-'0') % 8 == 0 && s[i-1] != '0')
            ans++;
        cnt += (i > 1 && s[i-2] != '0');
        if (i > 1 && ((s[i-2]-'0')*100 + (s[i-1]-'0')*10 + s[i]-'0') % 8 == 0)
            ans += cnt;
    }

    cout << ans << endl;

  return 0;
}