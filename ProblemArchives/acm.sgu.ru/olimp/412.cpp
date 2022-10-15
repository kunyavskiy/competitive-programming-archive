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

#define mp make_pair
#define pb push_back

#define taskname "B"

#ifdef LOCAL 
  #define LLD "%I64d"
#else
  #define LLD "%lld"
#endif

#define abs(x) (((x)>0)?(x):(-(x)))

using namespace std;

typedef long long int64;
typedef long double ld;

int read(){
  string s;
  cin>>s;
  int h,m;
  sscanf(s.data(),"%d:%d",&h,&m);
  return h*60+m;
}

int a[100];

int main(){
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);

  int n;
  scanf("%d\n",&n);
  ++n;
  for (int i=0;i<n;i++)
    a[i]=read();
  int tec=a[0];
  for (int i=0;i<n-1;i++){
    tec=max(tec,a[i]);
    tec+=5;
  }
  if (tec>a[n-1]){
    printf("-1\n");
    return 0;
  }

  tec=a[0];
  ld ans=1e+100;

  for (int i=0;i<n-1;i++){

    
    a[i]=max(a[i],tec);

    ld tmp=(a[n-1]-a[i])*1.0/(n-i-1);

    if (tmp-5<(-(1e-09)))
      break;

    bool q=true;

    ld intec=a[i];

    for (int j=i+1;j<n-1;j++){
       if (intec+tmp<a[j]-(1e-09))
          {
            q=false;
            break;
          }
       intec=intec+tmp;
          
       //cerr<<"!!"<<j<<" "<<q<<endl;
    }

    //cerr<<tmp<<" "<<q<<endl;

    if (q)
      ans=min(ans,tmp);
                        
    tec+=5;


   // cerr<<ans<<endl;
  }
  cout.precision(14);
  assert(ans<1e+10);
  cout<<fixed<<ans<<endl;
  return 0;
}