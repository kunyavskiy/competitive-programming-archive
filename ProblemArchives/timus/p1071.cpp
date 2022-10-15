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
    #undef assert
    #define assert(x) if (!(x)) throw 1
#endif

using namespace std;

typedef long long ll;
typedef long double ld;


bool check(int b,int x,int y){
    while (y){
        while (x >= y && x % b != y % b)
            x /= b;
        if (x < y)
            return false;
        x /= b;
        y /= b;
    }
    return true;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    int x,y;
    cin >> x >> y;


    for (int i = 2; i <= x+5; i++){
        if (check(i,x,y)){
            cout << i << endl;
            return 0;
        }
    }

    printf("No solution\n");
    return 0;
}