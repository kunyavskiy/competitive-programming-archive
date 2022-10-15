#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <memory.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iterator>

#define mp make_pair
#define pb push_back

#define y1 y1_ndsfg

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

ld x2,y2,z2;
ld x1,y1,z1;


void load(ld& x,ld& y,ld&z){
    ld ang1,ang2;
    cin >> ang1 >> ang2;
    ang1 = ang1 / 180.0 * M_PI;
    ang2 = ang2 / 180.0 * M_PI;

    z = sin(ang1);
    x = cos(ang1)*cos(ang2);
    y = cos(ang1)*sin(ang2);
}

ld f(ld t){
    ld x = x1 * t + x2 * (1 - t);
    ld y = y1 * t + y2 * (1 - t);
    ld z = z1 * t + z2 * (1 - t);

    ld nc = sqrt(x*x + y*y + z*z);
    x /= nc;
    y /= nc;
    z /= nc;

    z = asin(z);
/*    if (z > M_PI/2.0 + (1e-9))
        z -= M_PI; */
    return z;
}

ld tern_max(){
    ld l = 0;
    ld r = 1;
    for (int i = 0; i < 1000; i++){
        ld x1 = l + (r-l)/3;
        ld x2 = r - (r-l)/3;
        ld f1 = f(x1);
        ld f2 = f(x2);

        //cerr << x1 <<" "<<x2 << endl;


        if (f1 < f2)
            l = x1;
        else
            r = x2;
    }


    return f(l);
}


ld tern_min(){
    ld l = 0;
    ld r = 1;
    for (int i = 0; i < 1000; i++){
        ld x1 = l + (r-l)/3;
        ld x2 = r - (r-l)/3;
        ld f1 = f(x1);
        ld f2 = f(x2);

        //cerr << x1 <<" "<<x2 << endl;

        if (f1 > f2)
            l = x1;
        else
            r = x2;
    }

    return f(l);
}



int main(){
    //cerr << round(-0.3) <<" "<<round(0.3) << " "<<round(-0.6) <<" "<<round(0.6) << endl;
    #ifdef LOCAL
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif

    load(x2,y2,z2);
    load(x1,y1,z1);


    //for (int i = 0; i < 100; i++)
    //    cerr << f(i*0.01) << endl;


    ld ans1 = tern_max();
    ld ans2 = tern_min();

    //cerr << ans1 <<" "<<ans2 << endl;

    ans1 = ans1 * 180 / M_PI;
    ans2 = ans2 * 180 / M_PI;

    /*if (ans1 > 90)
        ans1 -= 180;
    if (ans2 > 90)
        ans2 -= 180;*/

    int Ans1 = round(ans1);
    int Ans2 = round(ans2);

    cout << Ans1 <<" "<<Ans2 << endl;

    return 0;
} 