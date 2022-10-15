#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <list>
#include <queue>
#include <stack>
#include <deque>
#include <iterator>

#define mp make_pair
#define pb push_back
#define sqr(a) ((a) * (a))
#define zero(a) memset (a, 0, sizeof(a))
#define sz(a) (int)(a.size())

#ifdef LOCAL
	#define LLD "%I64d"
#else 
	#define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef unsigned int uint;

#define taskname "e"

const int inf = 1000000000;
const ld eps = 1e-9;

double tt=clock();
map <string, int> M;
set <pair <int, string> > S, Ans;
long long D[10100][4];
char s[11000];
int len, A[4];

int main(){
  int i, j, cnt;
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  gets(s);
  len=strlen(s);
  srand(239017);
  for (cnt=0; cnt<100000; cnt++)
  {
    for (i=0; i<4; i++)
      A[i]=rand()%len;
    sort(A,A+4);
    //cerr<<"!!!"<<endl;
    //cerr<<A[0]<<" "<<A[1]<<" "<<A[2]<<" "<<A[3]<<endl;
    if (A[0]==A[1] || A[1]==A[2] || A[2]==A[3])
      continue;
    string tmps="";
    for (i=0; i<4; i++)
      tmps.pb(s[A[i]]);
    //cerr<<tmps<<endl;
    M[tmps]++;
  }
  for (map <string, int> :: iterator it=M.begin(); it!=M.end(); it++)
    S.insert(mp(-(it->second),it->first));
  set <pair <int, string> > :: iterator it=S.begin();
  cnt=0;
  long long tl=len;
  long long tcnt=(tl)*(tl-1ll)*(tl-2ll)*(tl-3ll);
  tcnt/=24ll;
  long long rest=tcnt;
  while (cnt<2500 && it!=S.end())
  {
    //cerr<<it->first<<" "<<it->second<<endl;
    memset(D,0,sizeof(D));
    for (i=0; i<len; i++)
    {
      for (j=0; j<4; j++)
      {
        D[i+1][j]=D[i][j];
        if (s[i]==(it->second)[j])
          (j==0)?(D[i+1][j]++):(D[i+1][j]+=D[i][j-1]);
      }
    }
    //cerr<<"!!!!"<<endl;
    D[len][3]*=100ll;
    if (D[len][3]>=tcnt)
      rest-=(D[len][3]/100ll), Ans.insert(mp(-(D[len][3]/tcnt),it->second));
    //cerr<<tcnt<<" "<<rest<<endl;
    it++, cnt++;
  }
  it=Ans.begin();
  //cerr<<"????"<<endl;
  while (it!=Ans.end())
    cout<<it->second, printf(" %d%%\n", -(it->first)), it++;
  //cerr<<rest<<endl;
  if (rest>0ll)
    puts("Others less than 1%");
  return 0;
}

