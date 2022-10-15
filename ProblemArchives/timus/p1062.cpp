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

const double eps = 1e-12;

struct point{
    double x,y;
    point(){}
    point(double x,double y):x(x),y(y){}
};

int sign(double x){
    if (x > eps) return 1;
    if (x > -eps) return 0;
    return -1;
}

struct line{
    double a,b,c;
    line(){}
    line(double a,double b,double c):a(a),b(b),c(c){
        norm();
    }
        
    void norm(){
        double nc = sqrt(a*a+b*b);
        //if (sign(nc) == 0) return;
        a /= nc;
        b /= nc;
        c /= nc; 
    }

    line (const point& p1,const point& p2){
        a = p1.y - p2.y;
        b = p2.x - p1.x;
        c = -a * p1.x - b*p1.y;
        norm();
    }

    int side(const point& p) const{
        return sign(a * p.x + b * p.y + c);
    }  
};

point operator&(const line& a,const line& b){   
    
    double d = a.a * b.b - a.b * b.a;
    assert(sign(d));
    point p(-(a.c * b.b - a.b * b.c)/d,-(a.a * b.c - a.c * b.a)/d);
    //assert(a.side(p) == 0);
    //assert(b.side(p) == 0);
    return p;
}

vector<point> poly;

void intersec(const line& l){
    vector<point> np;


    poly.pb(poly[0]);

    for (int i = 1; i < (int)poly.size(); i++){
        if (l.side(poly[i-1]) * l.side(poly[i]) < 0)
            np.pb(l & line(poly[i],poly[i-1]));

        if (l.side(poly[i]) >= 0)   
            np.pb(poly[i]);           
    }
    poly = np;
}

const int MAXN = 110;

double a[MAXN];
double b[MAXN];
double c[MAXN];
int n;


bool check(int id){
    if (a[id] < c[id]){
        for (int i = 0; i < n; i++)
            swap(a[i],c[i]);
    }
    if (b[id] < c[id]){
        for (int i = 0; i < n; i++)
            swap(b[i],c[i]);
    }
    poly.clear();

    poly.pb(point(0,0));
    poly.pb(point(9e9,0));
    poly.pb(point(9e9,9e9));
    poly.pb(point(0,9e9));

    for (int i = 0; i < n; i++)
        if (i != id){
            if (a[id] == a[i] && b[id] == b[i]){
                if (c[id] > c[i]) continue;
                return false;
            }
            intersec(line(- 1.0/a[id] + 1.0/a[i], - 1.0/b[id] + 1.0/b[i], - 1.0/c[id] + 1.0/c[i]));
        }

    double s = 0;

    poly.pb(poly[0]);

    for (int i = 0; i+1 < (int)poly.size(); i++)
        s += poly[i].x * poly[i+1].y - poly[i+1].x * poly[i].y;

    cerr.precision(20);


    return sign(s) != 0; 
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    cin >> n;

    for (int i = 0; i < n; i++)
        cin >> a[i] >> b[i] >> c[i];

    for (int i = 0; i < n; i++){
        if (check(i))
            printf("Yes\n");
        else
            printf("No\n");
    }

    return 0;
}