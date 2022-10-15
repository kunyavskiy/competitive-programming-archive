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


int a[100][100];





int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    int n;
    cin >> n;
    int ptr1,ptr2;
    ptr1 = 1;
    ptr2 = n*n;
//    assert(n != 5);
    for (int ipj = 0; ipj <2*n-1; ipj++)
        for (int i = 0; i < n; i++){
            int j = ipj-i;
            if (j < 0 || j >= n)
                continue;
            if (ipj & 1)
                a[i][j] = ptr1++;
            else
                a[i][j] = ptr2--;
        }

    cout << n*n+n/2+1 << endl;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            printf("%d%c",a[i][j]," \n"[j==n-1]);

    return 0;
}