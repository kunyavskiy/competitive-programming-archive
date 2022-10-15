#include <iostream>
#include <fstream>
#include <cassert>
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

const string code[26] = {
".-",
"-...",
"-.-.",
"-..",
".",
"..-.",
"--.",
"....",
"..",
".---",
"-.-",
".-..",
"--",
"-.",
"---",
".--.",
"--.-",
".-.",
"...",
"-",
"..-",
"...-",
".--",
"-..-",
"-.--",
"--.."
};

char s[60];

ll dp[55];


      
int main(){
    #ifdef LOCAL
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif

    gets(s);

    unsigned long long _k;
    cin >> _k;           
    --_k;

    long long k = _k;

    int n = strlen(s);

    dp[n] = 1;
                       
    for (int i = n-1; i >= 0; i--){
        for (int j = 0; j < 26; j++)
            if (string(s+i,s+i+code[j].size()) == code[j])
                dp[i] += dp[i+code[j].size()];
    }

    if (dp[0] <= k){
        printf("0\n");
        return 0;
    }


    int i = 0;

    for (;i < n;){
        for (int j = 0; j <= 26; j++){
            assert(j != 26);
            if (string(s+i,s+i+code[j].size()) == code[j]){
                if (dp[i + code[j].size()] > k){
                    printf("%c",'A'+j);
                    i += code[j].size();
                    break;
                }
                k -= dp[i+code[j].size()];
            }
        }
    }         
     
    return 0;
} 