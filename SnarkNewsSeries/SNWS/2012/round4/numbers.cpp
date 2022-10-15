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

#ifdef LOCAL
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

#define taskname "numbers"

using namespace std;

typedef long long int64;
typedef long double ld;

const int MAXV = 100000;

int c[15];
int cost[4][15];
int s,e;
int n;

int d[MAXV+10];

int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif
        scanf("%d %d %d",&s,&e,&n);

        for (int i = 0; i < n; i++)
            scanf("%d",&c[i]);
        for (int j = 0; j < n; j++)
            for (int i = 0; i < 4; i++)
                scanf("%d",&cost[i][j]);

        memset(d,63,sizeof(d));

        d[s] = 0;
        set<pair<int,int> > st;
        st.insert(mp(0,s));


        for (;;){
            int v = st.begin()->second;
            //cerr << v << " "<<d[v] <<endl;
            st.erase(st.begin());
            if (v == e){
                printf("%d\n",d[e]);
                return 0;
            }
            
            for (int i = 0; i < n; i++){
                if (v+c[i] <= MAXV){
                    if (d[v+c[i]] > d[v] + cost[0][i]){
                      //  cerr << "!"<<v<<"+"<<c[i]<<" "<<d[v]+cost[0][i]<<endl;
                        st.erase(mp(d[v+c[i]],v+c[i]));
                        d[v+c[i]] = d[v] + cost[0][i];
                        st.insert(mp(d[v+c[i]],v+c[i]));
                    }
                }

                if (v-c[i] >= 0){
                    if (d[v-c[i]] > d[v] + cost[1][i]){
                        //cerr << "!"<<v<<"-"<<c[i]<<" "<<d[v]+cost[1][i]<<endl;
                        st.erase(mp(d[v-c[i]],v-c[i]));
                        d[v-c[i]] = d[v] + cost[1][i];
                        st.insert(mp(d[v-c[i]],v-c[i]));
                    }
                }



                if (v*1LL*c[i] <= MAXV){
                    if (d[v*c[i]] > d[v] + cost[2][i]){
                      //  cerr << "!"<<v<<"*"<<c[i]<<" "<<d[v]+cost[2][i]<<endl;
                        st.erase(mp(d[v*c[i]],v*c[i]));
                        d[v*c[i]] = d[v] + cost[2][i];
                        st.insert(mp(d[v*c[i]],v*c[i]));
                    }
                }
                    if (d[v/c[i]] > d[v] + cost[3][i]){
                       // cerr << "!"<<v<<"/"<<c[i]<<" "<<d[v]+cost[3][i]<<endl;
                        st.erase(mp(d[v/c[i]],v/c[i]));
                        d[v/c[i]] = d[v] + cost[3][i];
                        st.insert(mp(d[v/c[i]],v/c[i]));
                    }
            }
        }



    	return 0;
} 