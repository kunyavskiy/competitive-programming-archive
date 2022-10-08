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

typedef long long ll;
typedef long double ld;

const ld eps = 1e-9;



struct point{
    int x;
    ld y;
    point (int x,ld y):x(x),y(y){
    }
};

bool operator<(const point& a,const point& b){
    if (a.x != b.x)
        return a.x < b.x;
    return a.y < b.y - eps;
}

point intersect(const point& a,const point& b,int x){
    assert(a.x <= x && x <= b.x);
    if (x == b.x) return b;
    if (x == a.x) return a;
    return point(x,(b.y - a.y)/(b.x - a.y) * (x - a.x));
}

ld dist(const point& a,const point& b){
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)); 
}


set<point> curs;

point pts[110000];
int n;

namespace Graph{
    vector<int> g[310000];
    vector<ld> len[310000];

    map<point,int> id;

    struct DoubleComparer{
        bool operator()(const pair<ld,int>& a,const pair<ld,int>& b){
            if (abs(a.first - b.first) > eps)
                return a.first < b.first;
            return a.second < b.second;
        }
    }

    double d[310000];

    int getid(const point& a){
        if (id.find(a) != id.end())
            return id[a];
        int cnt = id.size();
        id[a] = cnt;
        return cnt;
    }

    void add(const point& a,const point& b){       
        int id1 = getid(a);
        int id2 = getid(b);
        ld len = dist(a,b);
        g[id1].pb(id2);
        g[id2].pb(id1);
        Graph::len[id1].pb(len);
        Graph::len[id2].pb(len);
    }

    double deijkstra(const point& a,const point& b){
        int from = getid(a);
        int to = getid(b);

        set<pair<double,int>,DoubleComparer> s;

        int n = id.size();

        for (int i = 0; i < n; i++)
            d[i] = 1e100;

        d[from] = 0;
        s.insert(mp(0.0,from));

        while (!s.empty()){
            int id = s.begin()->second;
            if (id == to)
                return s.begin()->first;
            s.erase(s.begin());

            for (int i = 0; i < (int)g[id].size(); i++){
                int to = g[id][i];
                ld len = d[id] + Graph::len[id][i];

                if (d[to] > len + 2*eps){
                   s.erase(mp(d[to],to));
                   d[to] = len + 2*eps;
                   s.insert(mp(d[to],to));
                }
            }
        }
        assert(false);
    }

}

void GenGraph(){
    rotate(pts,min_element(pts,pts+n),pts+n);

    pts[n] = pts[0];

    set<point> s;

    s.insert(pts[0]);

    for (int i = 0; i < n; i++){
         if (pts[i+1].x > pts[i].x){
            while (true){
                
            }
         }
    }


}





int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    scanf("%d",&n);
    for (int i = 0; i < n; i++)
        cin >> pts[i].x >> pts[i].y;

    int _s,_e;

    point s = pts[_s];
    point e = pts[_e];

    GenGraph();

    cout.precision(15);
    cout << fixed << Graph::dijkstra(s,e) << endl;
    return 0;
}