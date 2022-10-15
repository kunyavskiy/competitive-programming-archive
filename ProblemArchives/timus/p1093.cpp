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
                     
const ld eps = 1e-10;

void HIT(){
    printf("HIT");
    exit(0);
}

         
void MISS(){
    printf("MISSED");
    exit(0);
}



ld cx,cy,cz;
ld nx,ny,nz;
ld r;
ld sx,sy,sz;
ld vx,vy,vz;

void check(ld t){
    ld x = sx + vx*t;
    ld y = sy + vy*t;
    ld z = sz + vz*t - 5*t*t;

    //assert(abs((x-cx)*nx + (y-cy)*ny + (z-cz)*nz) < eps);

    if (t < eps)
        return;

    ld d = sqrt((x-cx) * (x-cx) + (y-cy) * (y-cy) + (z-cz)*(z-cz));

    if (d < r - eps)
        HIT();    
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    cin >> cx >> cy >> cz;
    cin >> nx >> ny >> nz;
    cin >> r;
    cin >> sx >> sy >> sz;
    cin >> vx >> vy >> vz;


    ld A = nx, B = ny, C = nz;
    ld D = -A*cx -B*cy -C*cz;


    ld c = A*sx + B*sy + C*sz + D;
    ld b = A*vx + B*vy + C*vz;
    ld a = -5*C;

    if (abs(a) < eps){
        if (abs(b) < eps)
            MISS();
        check(-c/b);
        MISS();       
    }

    ld disc = b*b - 4*a*c;

    if (disc < -eps)
        MISS();

    //ld temp = (-b-sqrt(disc))/(2*a);

    check((-b-sqrt(disc))/(2*a));
    check((-b+sqrt(disc))/(2*a));
    MISS();

    return 0;
}