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

struct rect{
    int l1,l2;
    int r1,r2;

    rect(){
    }

    rect(int x,int y,int r){
        l1 = x-r;
        r1 = x+r;
        l2 = y-r;
        r2 = y+r;
    }

    void intersec(rect r){
        l1 = max(l1,r.l1);
        l2 = max(l2,r.l2);
        r1 = min(r2,r.r1);
        r2 = min(r2,r.r2);
    }

    bool any(){
        return l1 <= r1 && l2 <= r2;
    }

    bool empty(){return !any();}

};

struct gnome{
  int x,y;
  int cl;
};

gnome a[110000];
gnome b[110000];
int n,k;

bool cmpx(const gnome& a,const gnome& b){
    return a.x < b.x;
}

bool cmpy(const gnome& a,const gnome& b){
    return a.y < b.y;
}

bool cmpcl(const gnome& a,const gnome& b){
    return a.cl < b.cl;
}

namespace SQRT{
    const int BSZ = 400;
    int y[110000];
    int y1[110000];
    int x[110000];
    int lst;
    int n;

    void init(gnome* v,int n){
        SQRT::n = n;
        sort(v,v+n,cmpx);
        for (int i = 0; i < n; i++)
            x[i] = v[i].x,y[i] = v[i].y;

        while (n % BSZ != 0){
            x[n] = 1<<30;
            y[n] = 1<<30;
            n++;
        }   

        memcpy(y1,y,sizeof(y));

        for (int i = 0; i < n; i+= BSZ)
            sort(y1+i,y1+i+BSZ);
    }

    int get(int l,int r,int y){
        l = lower_bound(x,x+n,l) - x;
        r = upper_bound(x,x+n,r) - x;
        
        int ans = 1<<30;

        for (;l%BSZ && l < r; l++)
            ans = min(ans,abs(y - SQRT::y[l]));
        for (;r%BSZ && l < r; r--)
            ans = min(ans,abs(y - SQRT::y[r-1]));

        for (;l < r; l += BSZ){
            int id = lower_bound(y1+l,y1+l+BSZ,y) - y1;
            if (id != l+BSZ) ans = min(ans,abs(y-y1[id]));
            if (id != l) ans = min(ans,abs(y-y1[id-1]));
        }

        return ans;
    }

    int any(int l,int r,int yl,int yr){
        l = lower_bound(x,x+n,l) - x;
        r = upper_bound(x,x+n,r) - x;
        
        for (;l%BSZ && l < r; l++)
            if (yl <= SQRT::y[l] && SQRT::y[l] <= yr)
                return true;
        for (;r%BSZ && l < r; r--)               
            if (yl <= SQRT::y[r-1] && SQRT::y[r-1] <= yr)
                return true;

        for (;l < r; l += BSZ){
            int id = lower_bound(y1+l,y1+l+BSZ,yl) - y1;
            int id1 = upper_bound(y1+l,y1+l+BSZ,yr) - y1;
            if (id != id1)
                return true;
        }

        return false;
    }

};

rect suff[110000];

int dist(int x,int y){
     int l = -1;
     int r = 1<<29;

     for (;r - l > 1;){
         int m = (l+r)/2;

         if (SQRT::get(x - m, x + m, y) <= m)
            r = m;
         else
            l = m;
     }
  return r;
}


bool check(int t){                        
    if (t >= a[n-1].cl)
        return true;

    rect cur = rect(0,0,(int)1e9);

    for (int i = n-1; i >= 0; i--){
        cur.intersec(rect(a[i].x,a[i].y,t));

        if (cur.empty())
            return false;
        int e = (t - (i?a[i-1].cl:0));
        if (i && SQRT::any(cur.l1-e,cur.r1+e,cur.l2-e,cur.r2+e))
            return true;
    }

    if (cur.any())
        return true;

    return false;
       
}



int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  scanf("%d %d",&n,&k);
  for (int i = 0; i < n; i++){
    int x,y;
    scanf("%d %d",&x,&y);
    a[i].x = x+y;
    a[i].y = x-y;
    a[i].cl = 1<<30;
  }

  for (int i = 0; i < k; i++){
    int x,y;
    scanf("%d %d",&x,&y);
    b[i].x = x+y;
    b[i].y = x-y;
    b[i].cl = 1<<30;
  }

  SQRT::init(b,k);

  for (int i = 0; i < n; i++){
     a[i].cl = dist(a[i].x,a[i].y);
  }

  sort(a,a+n,cmpcl);

  int l = -1;
  int r = (1<<29);

  while (r - l > 1){
    int m = (l+r)/2;

    if (check(m))
       r =  m;
    else
       l = m; 
  }

  cout << r << endl;

  return 0;
}

