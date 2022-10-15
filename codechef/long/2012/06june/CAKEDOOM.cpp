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

char s[110];

void solve(){
    int k;
    scanf("%d %s",&k,s);
    int n = strlen(s);

    if (n == 1){
        if (s[0] == '?')
            s[0] = '0';
        puts(s);
        return;
    }

    if (k == 1){
        printf("NO\n");
        return;
    }

    if (k == 2){
        if (n % 2 == 1){
            printf("NO\n");
            return;
        }

        for (int i = 0; i < 2*n; i++)
            if (s[i%n] != '?'){
                if ((s[(i+1)%n] ^ 1) != s[i%n] && s[(i+1)%n] != '?')
                {
                    printf("NO\n");
                    return;
                }    
                s[(i+1)%n] = (s[i%n] ^ 1);

                if ((s[(i+n-1)%n] ^ 1) != s[i%n] && s[(i+n-1)%n] != '?')
                {
                    printf("NO\n");
                    return;
                }    
                s[(i+n-1)%n] = (s[i%n] ^ 1);
            }

        if (s[0] == '?'){
            for (int i = 0; i < n; i++)
                s[i] = '0' + (i&1);
        }       
        puts(s);
        return;
    }
    for (int i = 0; i < n; i++)
        if (s[i] == s[(i+1)%n] && s[i] != '?'){
            printf("NO\n");
            return ;
        }

    for (int i = 0; i < n; i++){
        if (s[i] != '?')
            continue;
        s[i] = '0';
        while (s[i] == s[(i+n-1)%n] || s[i] == s[(i+1)%n])
            s[i]++;
    }
    puts(s);
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    int t;
    scanf("%d",&t);
    while (t-->0)
        solve();
  return 0;
}