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

pair<int,int> a[110];
bool used[110];
int b[110];

set<vector<int> > v;

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    int n,k;
    cin >> n >> k;
    int inone = n/k;

    for (int i = 0; i < n; i++)
    	cin >> a[i].first, a[i].second = i,b[i] = a[i].first;
    sort(a,a+n);

    int q;
    cin >> q;

    int minn,maxx;
    minn = 1<<30,maxx = -(1<<30);

    for (int i = 0; i < q; i++){
    	int sum = 0;

    	vector<int> temp;
    	temp.clear();

    	for (int j = 0; j < inone; j++){
    		int x;
    		cin >> x;
    		--x;
    		used[x] = true;
    		sum += b[x];
    		temp.pb(x);
    	}

    	sort(temp.begin(),temp.end());
    	v.insert(temp);

    	minn = min(minn,sum);
    	maxx = max(maxx,sum);    		
    }

//  cerr << minn <<" "<<maxx << endl; 

  if ((v.size()+1)*inone <= n){
  	int sum = 0;
  	int cnt = inone;
  	for (int i = 0; i < n; i++)
  		if (cnt && !used[a[i].second])
  			sum += a[i].first,cnt--;

  	assert(cnt == 0);

  	minn = min(minn,sum);
   	maxx = max(maxx,sum);

	sum = 0,cnt = inone;	

  	for (int i = n-1; i >= 0; i--)
  		if (cnt && !used[a[i].second])
  			sum += a[i].first,cnt--;

  	assert(cnt == 0);   

  	minn = min(minn,sum);
   	maxx = max(maxx,sum);    		

  }


  cout.precision(15);
  cout << fixed << ((ld)minn)/inone <<" "<<((ld)maxx)/inone << endl;
  return 0;
}