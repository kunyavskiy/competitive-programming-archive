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


char s[110000];
char t[110000];

void go(int pos,int val,bool f = true){
    //cerr << pos <<" "<<val << " "<<f<<endl;
    if (pos >= 0){
        if (s[pos] - '0' == 1-val){
            printf("Impossible\n");
            exit(0);
        }
        if (s[pos] != '?' && !f)
            return;
        s[pos] = '0'+val;
    }

    if (pos > 0 && t[pos] != '?')
        go(pos-1,val ^ (t[pos] - '0'),false);
    if (s[pos+1] && t[pos+1] != '?')
        go(pos+1,val ^ (t[pos+1] - '0'),false);    
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    gets(s);
    gets(t);
    go(-1,0);

    for (int i = 0; s[i]; i++)
        if (s[i] != '?')
            go(i,s[i]-'0');


    for (int i = 0; s[i]; i++)
        if (s[i] != '?' && (i == 0 || s[i-1] != '?')){
            if (t[i] == '?')
                t[i] = (((i?s[i-1]:'0')-'0') ^ (s[i] - '0'))+'0';
            assert((((i?s[i-1]:'0')-'0') ^ (s[i] - '0')) == t[i] - '0');
            
        }

    for (int i = 0; s[i]; i++)
        if (s[i] == '?'){
            printf("Ambiguity\n");
            return 0;
        }

    puts(s);
    puts(t);


    return 0;
}