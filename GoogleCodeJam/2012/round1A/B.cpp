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
#include <iterator>
#include <cstdio>
#include <cstdlib>
#include <memory.h>
#include <stack>
#define mp make_pair
#define pb push_back   
#define setval(a,v) memset(a,v,sizeof(a))
using namespace std;

typedef long long ll;
typedef long double ld;

const string TASKNAME = "B";
const string TASKMOD = "large";
const string INFILE = TASKNAME+"-"+TASKMOD+".in";
const string OUTFILE = TASKNAME+"-"+TASKMOD+".out";



void PreCalc(){
}

int n;
pair<int,int> s[2100];

pair<int,pair<int,int> > cnt[2100];

bool used[2100];



void solve(){
    scanf("%d",&n);
    //cerr <<"!!!"<<n<<endl;

    for (int i = 0; i < n; i++){
        scanf("%d %d",&s[i].first,&s[i].second);
        cnt[2*i] = mp(s[i].first,mp(i,1));
        cnt[2*i+1] = mp(s[i].second,mp(i,0));
    }
    sort(cnt,cnt+2*n);

    //cerr << cnt[0].first <<" "<<cnt[1].first <<" "<<cnt[2].first <<" "<<cnt[3].first << endl;

    for (int i = 0; i < 2*n; i++)
        if (cnt[i].second.second == 1)
            s[cnt[i].second.first].first = i;
        else
            s[cnt[i].second.first].second = i;

    //cerr << s[0].first <<" "<<s[0].second << endl;
    //cerr << s[1].first <<" "<<s[1].second << endl;

    for (int i = 0; i < n; i++)
        for (int j = s[i].second+1; j < 2*n; j++)
            cnt[j].first-=2;

    memset(used,0,sizeof(used));

    int ans = n;

    for (int i = 0; i < 2*n; i++)
        while (cnt[i].first > 0 && cnt[i].second.second == 0){
            int id = -1;
            for (int k = 0; k < n; k++)
                if (!used[k] && s[k].first < i && s[k].second >= i && cnt[s[k].first].first <= 0)
                    if (id == -1 || s[k].second > s[id].second)
                        id = k;

            if (id == -1){
                printf("Too Bad\n");
                return;
            }

            used[id] = true;
            ans++;

            for (int j = s[id].first; j <= s[id].second; j++)
                  cnt[j].first--;
        }

   cout << ans << endl;
        
}

int main(){
    freopen(INFILE.data(),"r",stdin);
    freopen(OUTFILE.data(),"w",stdout);
    PreCalc();
    int t;
    cin>>t;
    for (int i=1;i<=t;i++)
        {
            printf("Case #%d: ",i);
            solve();
            if (i>t-20 || i%10==0)
                cerr<<"SOLVED:"<<i<<endl;
        }

  return 0;
}