#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <memory.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iterator>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

char s[2][1010];

inline bool bad(char c){
    return c == '+' || c == '-' || c == '|';
}

int main(){
    #ifdef LOCAL
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif

    gets(s[0]);

    int res = 0;

    for (int i = 1; ; i = 1 - i){
        if (!gets(s[i]))
            break;

        for (int j = 1; s[i][j]; j++)
            if (!bad(s[i][j]) && bad(s[i][j-1]) && bad(s[i^1][j]))
                res++;
            
        
    }

    cout << res << endl;


    return 0;
} 