#include <iostream>
#include <cassert>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <set>
#include <vector>
#include <memory.h>

#define pb push_back
#define mp make_pair

using namespace std;

typedef long long int64;
typedef long double ld;

vector<pair<int,int> > ans;
int p,q;
int n;

bool a[100000];


int main(){
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  cin>>p>>q>>n;
  if (p>q)
    swap(p,q);
  for (int i=1;i<=n;i++){
     if (a[i]) continue;
     assert(!a[i+p+q]);
     a[i]=a[i+p+q]=true;
     if (!a[i+p])
        {
            a[i+p]=true;
            ans.pb(mp(i,p));
        }
     else{
        assert(!a[i+q]);
        a[i+q]=true;
        ans.pb(mp(i,q));
     }        
  }
  printf("%d\n",(int)ans.size());
  for (int i=0;i<ans.size();i++)
    printf("%d %d %d\n",ans[i].first,ans[i].first+ans[i].second,ans[i].first+p+q);
  return 0;
}
            