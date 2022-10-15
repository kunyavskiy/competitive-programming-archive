#ifndef LOCAL
    #pragma comment(linker, "/STACK:33554432")
#endif

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



#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
	#define M_PI 3.1415926535897932384626433832795
    #define prev prev_dsfdfgfhgfh
    #define next next_mkdlsmfdgkl
    #define hash hash_mdfdsgdhgfm
    #undef assert
    #define assert(x) if (!(x)) throw 1
    #define sqrt(x) sqrt((double)(x))
#endif

using namespace std;

typedef long long ll;
typedef long double ld;


char s[4][4];

int go(int x){
    for (int i = 0;i < 3; i++){
        bool q = (s[i][0] != '#');
        for (int j = 0; j < 3; j++)
            q &= s[i][j] == s[i][0];
        if (q)
            return 0;
    }
    for (int i = 0;i < 3; i++){
        bool q = (s[0][i] != '#');
        for (int j = 0; j < 3; j++)
            q &= s[j][i] == s[0][i];
        if (q)
            return 0;
    }

    if (s[0][0] == s[1][1] && s[0][0] == s[2][2] && s[0][0] != '#')
        return 0;
    if (s[2][0] == s[1][1] && s[2][0] == s[0][2] && s[2][0] != '#')
        return 0;                      

    if (x == 3)
        return 1;

    int res = 0;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++){
            if (s[i][j] != '#')
                continue;
            s[i][j] = 'X'*(!(x&1)) + 'O'*(x&1);
            res = max(res, 2- go(x+1));
            s[i][j] = '#';
        }
    return res;
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            scanf(" %c",&s[i][j]);

    int res = go(0);

    if (res == 2)
        printf("Crosses win\n");
    else if (res == 1)
        printf("Draw\n");
    else
        printf("Ouths win\n");

    return 0;
}