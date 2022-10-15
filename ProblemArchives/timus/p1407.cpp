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
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

const string a[101] =  {"",
"2",
"12",
"112",
"2112",
"22112",
"122112",
"2122112",
"12122112",
"212122112",
"1212122112",
"11212122112",
"111212122112",
"1111212122112",
"11111212122112",
"211111212122112",
"1211111212122112",
"11211111212122112",
"111211111212122112",
"2111211111212122112",
"12111211111212122112",
"112111211111212122112",
"1112111211111212122112",
"11112111211111212122112",
"111112111211111212122112",
"2111112111211111212122112",
"22111112111211111212122112",
"122111112111211111212122112",
"1122111112111211111212122112",
"21122111112111211111212122112",
"121122111112111211111212122112",
"1121122111112111211111212122112",
"21121122111112111211111212122112",
"121121122111112111211111212122112",
"2121121122111112111211111212122112",
"12121121122111112111211111212122112",
"112121121122111112111211111212122112",
"1112121121122111112111211111212122112",
"21112121121122111112111211111212122112",
"121112121121122111112111211111212122112",
"2121112121121122111112111211111212122112",
"12121112121121122111112111211111212122112",
"212121112121121122111112111211111212122112",
"2212121112121121122111112111211111212122112",
"12212121112121121122111112111211111212122112",
"112212121112121121122111112111211111212122112",
"2112212121112121121122111112111211111212122112",
"12112212121112121121122111112111211111212122112",
"212112212121112121121122111112111211111212122112",
"2212112212121112121121122111112111211111212122112",
"22212112212121112121121122111112111211111212122112",
"122212112212121112121121122111112111211111212122112",
"1122212112212121112121121122111112111211111212122112",
"11122212112212121112121121122111112111211111212122112",
"111122212112212121112121121122111112111211111212122112",
"2111122212112212121112121121122111112111211111212122112",
"22111122212112212121112121121122111112111211111212122112",
"122111122212112212121112121121122111112111211111212122112",
"2122111122212112212121112121121122111112111211111212122112",
"12122111122212112212121112121121122111112111211111212122112",
"112122111122212112212121112121121122111112111211111212122112",
"1112122111122212112212121112121121122111112111211111212122112",
"21112122111122212112212121112121121122111112111211111212122112",
"221112122111122212112212121112121121122111112111211111212122112",
"2221112122111122212112212121112121121122111112111211111212122112",
"12221112122111122212112212121112121121122111112111211111212122112",
"212221112122111122212112212121112121121122111112111211111212122112",
"1212221112122111122212112212121112121121122111112111211111212122112",
"11212221112122111122212112212121112121121122111112111211111212122112",
"211212221112122111122212112212121112121121122111112111211111212122112",
"2211212221112122111122212112212121112121121122111112111211111212122112",
"22211212221112122111122212112212121112121121122111112111211111212122112",
"122211212221112122111122212112212121112121121122111112111211111212122112",
"2122211212221112122111122212112212121112121121122111112111211111212122112",
"22122211212221112122111122212112212121112121121122111112111211111212122112",
"122122211212221112122111122212112212121112121121122111112111211111212122112",
"1122122211212221112122111122212112212121112121121122111112111211111212122112",
"21122122211212221112122111122212112212121112121121122111112111211111212122112",
"121122122211212221112122111122212112212121112121121122111112111211111212122112",
"1121122122211212221112122111122212112212121112121121122111112111211111212122112",
"11121122122211212221112122111122212112212121112121121122111112111211111212122112",
"211121122122211212221112122111122212112212121112121121122111112111211111212122112",
"1211121122122211212221112122111122212112212121112121121122111112111211111212122112",
"11211121122122211212221112122111122212112212121112121121122111112111211111212122112",
"211211121122122211212221112122111122212112212121112121121122111112111211111212122112",
"1211211121122122211212221112122111122212112212121112121121122111112111211111212122112",
"21211211121122122211212221112122111122212112212121112121121122111112111211111212122112",
"121211211121122122211212221112122111122212112212121112121121122111112111211111212122112",
"1121211211121122122211212221112122111122212112212121112121121122111112111211111212122112",
"21121211211121122122211212221112122111122212112212121112121121122111112111211111212122112",
"221121211211121122122211212221112122111122212112212121112121121122111112111211111212122112",
"1221121211211121122122211212221112122111122212112212121112121121122111112111211111212122112",
"11221121211211121122122211212221112122111122212112212121112121121122111112111211111212122112",
"211221121211211121122122211212221112122111122212112212121112121121122111112111211111212122112",
"1211221121211211121122122211212221112122111122212112212121112121121122111112111211111212122112",
"11211221121211211121122122211212221112122111122212112212121112121121122111112111211111212122112",
"211211221121211211121122122211212221112122111122212112212121112121121122111112111211111212122112",
"1211211221121211211121122122211212221112122111122212112212121112121121122111112111211111212122112",
"11211211221121211211121122122211212221112122111122212112212121112121121122111112111211111212122112",
"211211211221121211211121122122211212221112122111122212112212121112121121122111112111211111212122112",
"1211211211221121211211121122122211212221112122111122212112212121112121121122111112111211111212122112"
};



int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    int n;
    cin >> n;
    cout << a[n] << endl;
    return 0;
}