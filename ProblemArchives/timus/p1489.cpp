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
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

int A,B,C;


void readpoint(ld& x,ld& y,ld& z){
    cin >> x >> y;
    if (y < B){
        x -= C;
        y = B-y;
        z = C;
        return;
    }

    y -= B;
    if (y < C){
       x -= C;
       z = C - y;
       y = 0;
       return;
    }

    y -= C;
    if (y > B){   
       x -= C;
       z = y - B;
       y = B;
       return;
    }

    if (x < C){
        z = C-x;
        x = 0;
        return;
    }

    x -= C;

    if (x > A){
        z = x - A;
        x = A;
        return;
    }

    z = 0;
    return;
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    cin >> A >> B >> C;
    ld x,y,z;
    ld x1,y1,z1;
    readpoint(x,y,z);
    readpoint(x1,y1,z1);

//    cerr << x <<" "<<y <<" "<<z<<"\n"<<x1<<" "<<y1<<" "<<z1<<endl;

    cout.precision(15);
    cout << fixed << sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1)+(z-z1)*(z-z1)) << endl;

    return 0;
}