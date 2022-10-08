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

typedef long long int64;
typedef long double ld;


int count(int64 a){
    //cerr <<"CNT["<<a<<"] = ";
    int cnt = 0;
    for (;a;a/=10)
        cnt += (a%10==4) || (a%10 == 7);
  //  cerr << cnt << endl;
    return cnt;        
}


bool check(int64 a,int64 b,int64 l){
    for (int i = 0; i < l; i++)
        if (count(a+i) != count(b+i))
            return false;
    return true;
}


int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    int64 a,l;
    cin >> a >> l;
    int64 st10 = 1;

    while (st10 < l)
        st10 *= 10;

    st10 /= 100;
    st10 = max(st10,1LL);

    int md = a%st10;

    int64 l2 = (a + l - 1) / st10 - a / st10 + 1;

    a /= st10;

    int64 b = a+1;

//    cerr << a <<" "<<b <<" "<<l2 << endl;

    while (!check(a,b,l2))
        b++;

    b = b * st10 + md;

    cout << b << endl;


    return 0;
}