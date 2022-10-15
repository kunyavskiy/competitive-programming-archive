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

char convert(int temp){
    if (temp <= 9)
        return '0'+temp;
    return 'A'+temp-10;
}

void printint(int val,int base){
    string s = "";
    while (val)
       s += convert(val%base), val /= base;
    if (s == "")
        s = "0";
    reverse(s.begin(),s.end());
    printf("%s",s.data()); 
}

int used[10000];


bool solve(){
    int a,b,base;
    scanf("%d %d %d",&a,&b,&base);
    if (b == 0)
        return 0;

    printint(a/b,base);
    a %= b;
    if (a == 0){
        printf("\n");
        return 1;
    }
    memset(used,-1,sizeof(used));
    string s;
    printf(".");

    for (int i = 0; a; i++){
        if (used[a] != -1){
            s = string(s.begin(),s.begin()+used[a]) + '(' + string(s.begin()+used[a],s.end())+')';
            break;
        }
        used[a] = i;
        a = a*base;
        s += convert(a/b);
        a %= b;
    }

    puts(s.data());
    return 1;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    while (solve());
    return 0;
}