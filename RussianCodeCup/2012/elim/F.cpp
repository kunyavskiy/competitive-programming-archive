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

void merge(vector<pair<int,int> > & v){
    vector<pair<int,int> > event;
    for (int i = 0; i < (int)v.size(); i++){
        event.pb(mp(v[i].first,1));
        event.pb(mp(v[i].second,-1));
    }

    sort(event.begin(),event.end());

    v.clear();
    int bal;
    int start;

    bal = start = 0;

    for (int i = 0; i < (int)event.size(); i++){
        if (bal == 0)
            start = event[i].first;
        bal += event[i].second;
        if (bal == 0)
            v.pb(mp(start,event[i].first));         
    }
}

int l[1100];
int r[1100];
int lt[1100];
int rt[1100];
int n,x;

vector<int> evs;
int ans;

vector<pair<int,int> > v;


void erase(vector<pair<int,int> > & v,pair<int,int> bad){
    vector<pair<int,int> > v1;
    for (int i = 0; i < (int)v.size(); i++){
        if (v[i].second <= bad.first || bad.second <= v[i].first){
            v1.pb(v[i]);
            continue;
        }
        if (bad.first < v[i].first && v[i].second < bad.second)
            continue;
        if (v[i].first <= bad.first && bad.second <= v[i].second){
            v1.pb(mp(v[i].first,bad.first));
            v1.pb(mp(bad.second,v[i].second));
            continue;
        }
        if (bad.first < v[i].first && v[i].first <= bad.second){
            v1.pb(mp(bad.second,v[i].second));
            continue;
        }
        if (bad.first <= v[i].second && v[i].second < bad.second){
            v1.pb(mp(v[i].first,bad.first));
            continue;
        }
        assert(false);           
    }
    v = v1;
    merge(v);
}


void doit(int start,int t){
    vector<pair<int,int> > bad;

    for (int i = 0; i < n; i++)
        if (lt[i] <= start && start < rt[i])
            bad.pb(mp(l[i],r[i]));

    merge(bad);


    for (int i = 0; i < n; i++)
        if (start == lt[i])
            erase(v,mp(l[i],r[i]));



    for (int it = 0; it < 2; it++){

       int ptr1,ptr2;
       ptr1 = ptr2 = 0;

       for (; ptr2 < (int)v.size();){
           if (ptr1 == (int)bad.size() || v[ptr2].first <= bad[ptr1].first){
               int temp;
               if (ptr1 == 0)
                  temp = v[ptr2].first - t;
               else
                  temp = max(v[ptr2].first - t, bad[ptr1-1].second);
               if (temp <= x && v[ptr2].first > x)
                  ans = min(ans, start + (v[ptr2].first - x));
               v[ptr2++].first = temp;
           }  
           else 
              ptr1++;
       }

       merge(v);
       
       for (int i = 0; i < (int)bad.size(); i++){
          swap(bad[i].first,bad[i].second);
          bad[i].first *= -1;
          bad[i].second *= -1; 
       }


       for (int i = 0; i < (int)v.size(); i++){
          swap(v[i].first,v[i].second);
          v[i].first *= -1;
          v[i].second *= -1; 
       }

       merge(v);
       merge(bad);


       x *= -1;      
          
    }
}



int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    ans = 1<<30;

    scanf("%d %d",&n,&x);
    for (int i = 0; i < n; i++){
        scanf("%d %d %d %d",&lt[i],&rt[i],&l[i],&r[i]);
        rt[i] += lt[i];
        evs.pb(lt[i]);
        evs.pb(rt[i]);
    }            
    evs.pb(0);
    evs.pb(1<<28);

    sort(evs.begin(),evs.end());
    evs.erase(unique(evs.begin(),evs.end()),evs.end());

    v.pb(mp(0,0));

    for (int i = 1; i < (int)evs.size() && (ans == (1<<30)); i++){
        doit(evs[i-1], evs[i] - evs[i-1]);

        /*cerr << evs[i] << endl;
        for (int j = 0; j < (int)v.size(); j++)
            cerr << "["<<v[j].first <<", "<<v[j].second <<"]"<<" ";
        cerr << endl << endl;*/
    }

    if (ans == (1<<30))
        printf("Impossible\n");
    else
        printf("%d\n",ans);

    return 0;
}