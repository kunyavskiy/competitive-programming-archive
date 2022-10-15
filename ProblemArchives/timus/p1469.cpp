#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include <fstream>
#include <queue>
#include <memory.h>
#include <stack>
#include <deque>
#include <cmath>
#include <iterator>

#define mp make_pair
#define pb push_back

#define dbg(x) cerr<< #x <<" : ";copy(x.begin(),x.end(),ostream_iterator<int>(cerr," "));cerr<<endl 

#undef assert
#define assert(x) ((void)0)

#define taskname "A"

#ifdef LOCAL 
  #define LLD "%I64d"
#else
  #define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;

const int MAXN=230000;
                           
template<typename T>
inline T sqr(T x){
    return x*x;
}

template<typename T>
inline int sign(T x){
    if (x>0) return 1;
    if (x==0) return 0;
    return -1;
}                                 

template<typename T>
inline bool betweenlr(T l,T v,T r){
    return min(l,r)<=v && v<=max(l,r);
}

template<typename T>
inline bool betweenl(T l,T v,T r){
    return min(l,r)<=v && v<max(l,r);
}

template<typename T>
inline bool betweenr(T l,T v,T r){
    return min(l,r)<v && v<=max(l,r);
}

template<typename T>
inline bool between(T l,T v,T r){
    return min(l,r)<v && v<max(l,r);
}

struct point{
    int x,y;
    point(){};
    point(int X,int Y){
        x=X;y=Y;
    }
};

int dest2(const point& a,const point& b){
    return sqr(a.x-b.x) + sqr(a.y-b.y);
}

ld dest(const point& a,const point& b){
    return sqrt((ld)dest2(a,b));
}

bool operator<(const point& a,const point& b){
    if (a.x!=b.x) return a.x<b.x;
    return a.y<b.y;
}

bool operator==(const point& a,const point& b){
    return (a.x==b.x) && (a.y==b.y);
}
                                                   
struct segment{
    point p1,p2;
    segment(){};
    segment(const point& P1,const point& P2){
        p1=P1;
        p2=P2;
        if (p2 < p1)
            swap(p1,p2);
    }
    bool on(const point&) const;
};

bool operator==(const segment& a,const segment& b){
    return a.p1==b.p1 && a.p2==b.p2;
}

struct line{
    int a,b,c;
    line(){};
    line(const point& p1,const point& p2){
        a=p1.y-p2.y;
        b=p2.x-p1.x;
        c=-p1.x*a-p1.y*b;
    }
    line(const segment& s){
        a=s.p1.y-s.p2.y;
        b=s.p2.x-s.p1.x;
        c=-s.p1.x*a-s.p1.y*b;    
    }               
    int dest(const point& p) const{
        return a*p.x+b*p.y+c;
    }
    bool on(const point& p) const{
        return dest(p)==0;
    }
    int sdest(const point& p) const{
        return sign(dest(p));
    }
    ld gety(ld x) const{
        assert(b);
        return (-c-a*x)/((ld)b);
    }
};

bool segment::on(const point& p) const{
    line l(*this);
    if (!l.on(p)) return false;
    if (!betweenlr(p1.x,p.x,p2.x))
        return false;
    if (!betweenlr(p1.y,p.y,p2.y))
        return false;
    return true;
}

bool intersec(const segment& a,const segment& b){
    if (a.on(b.p1)) return true;
    if (a.on(b.p2)) return true;
    if (b.on(a.p1)) return true;
    if (b.on(a.p2)) return true;
    line l(a);
    if (l.sdest(b.p1)*l.sdest(b.p2) >= 0) return false;
    line l1(b);
    if (l1.sdest(a.p1)*l1.sdest(a.p2) >=0) return false;
    return true;
}

segment segs[MAXN];

struct segcmp{   
    static int x;
    bool cmp(const segment& a,const segment& b){
        ld y1,y2;
        if (a.p1.x!=a.p2.x)
            y1=line(a).gety(x);
        else
            y1=a.p1.y;
        if (b.p1.x!=b.p2.x)
            y2=line(b).gety(x);
        else
            y2=b.p1.y;
        return y1<y2;
    }
    bool operator()(int a,int b){
        if (a != b && intersec(segs[a],segs[b])){
            printf("YES\n%d %d\n",a+1,b+1);
            exit(0);
        }            
        return cmp(segs[a],segs[b]);
    }
};

int segcmp::x = 0;

typedef set<int,segcmp> myset;
typedef myset::iterator myiter;

myset s;

struct event{
    int x,num;
    bool add;
    event(){}
    event(int X,int Num,bool Add){
        x=X;
        num=Num;
        add=Add;
    }
};

bool operator<(const event& a,const event& b){
    if (a.x!=b.x) return a.x<b.x;
    if (b.add) return false;
    if (a.add) return true;
    return false;
}

event evs[MAXN*2];
int n;

void checkintersec(myiter iter,int num){
    myiter iter2=iter;
    for (int it=0;it<2;++it){
        if (iter!=s.end()){                
            int tmp=*iter;
            if (num!=tmp && intersec(segs[num],segs[tmp])){
                cout<<"YES\n"<<num+1<<" "<<tmp+1<<endl;
                exit(0);
            }
        }
        if (iter==s.begin())
           break;
        --iter;        
    }
    iter=iter2;
    for (int it=0;it<2;++it){
        if (iter!=s.end()){
            int tmp=*iter;
            if (num!=tmp && intersec(segs[num],segs[tmp])){
                cout<<"YES\n"<<num+1<<" "<<tmp+1<<endl;
                exit(0);
            }         
            ++iter;
        }
   }
}

void solve(){
    int ptr=0;
    for (int i=0;i<n;i++){
        evs[ptr++]=event(segs[i].p1.x,i,true);
        evs[ptr++]=event(segs[i].p2.x,i,false);
    }
    sort(evs,evs+ptr);
    segcmp::x=evs[0].x;
    for (int i=0;i<ptr;i++){             
        int v=evs[i].num;                
        if (evs[i].add){     
            myiter iter=s.lower_bound(v);
            checkintersec(iter,v);
            segcmp::x=evs[i].x;
            s.insert(v);
        }
        else {
            myiter iter=s.find(v);
            checkintersec(iter,v);            
            segcmp::x=evs[i].x;
            s.erase(iter);
        }
    }                      
    printf("NO\n");
}

int main(){
#ifdef LOCAL
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
#endif
  scanf("%d",&n);
  for (int i=0;i<n;i++){
    int x1,y1,x2,y2;
    scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
    segs[i]=segment(point(x1,y1),point(x2,y2));
  }
  solve();
  return 0;
}