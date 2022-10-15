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
    #undef assert
    #define assert(x) if (!(x)) throw 1
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

int ans[37];
bool cur[37];

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    char c;
    while (scanf("%c",&c) != EOF){
        for (int i = 2; i <= 10; i++){
            if (!('0' <= c && c < '0'+i)){
                ans[i] += cur[i];
                cur[i] = false;
            }
            else    
                cur[i] = true;
        }
        for (int i = 11; i <= 36; i++){
            if (!('0' <= c && c <= '9') && !('A' <= c && c < 'A'+i-10)){
                ans[i] += cur[i];
                cur[i] = false;
            }
            else
                cur[i] = true;
        }
    }

    for (int i = 2; i < 37; i++)
        ans[i] += cur[i];

    cout << max_element(ans+2,ans+37)-ans <<" "<<*max_element(ans+2,ans+37) << endl;
        

    return 0;
}