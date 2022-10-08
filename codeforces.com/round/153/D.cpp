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


const int MAXN = 110000;

ll a[MAXN];
ll a0[MAXN];
ll mask[MAXN];
int ans[MAXN];
ll val[100];
ll used[100];
int id[100];

int n;
ll allx;
ll curx;

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  cin >> n;
  for (int i = 0; i < n; i++){
  	cin >> a[i];
  	allx ^= a[i];
  	a0[i] = a[i];
  }

  curx = 0;

  int ptr = 0;

  for (int i = 62; i >= 0; i--){
  	 bool need = false;
  	 if (allx & (1LL<<i))
  	 	need = (curx & (1LL<<i));
  	 else 
  	 	need = !(curx & (1LL<<i));

  	 //cerr << need << " "<<ptr << endl;

  	 int found = -1;

  	 for (int j = 0; j < n; j++){
  	 	if (a[j] & (1LL<<i)){
  	 		found = j;
  	 		break;
  	 	}
  	 }

  	 if (found == -1)
  	 	continue;

  	 val[ptr] = found;
  	 used[ptr] = need;
  	 for (int j = 0; j < ptr; j++)
  	 	if (mask[found] & (1LL<<j))
  	 		used[j] ^= need;
  	 if (need) curx ^= a[found];
                 

     ll temp = a[found];

     mask[found] ^= (1LL<<ptr);
     a[found] = 0;


  	 for (int j = 0; j < n; j++)
  	 	if (a[j] & (1LL<<i)){
  	 		mask[j] ^= mask[found];
  	 		a[j] ^= temp;
  	 	}  	 	

  	 ptr++;
  }

  for (int i = 0; i < ptr; i++)
		if (used[i]){
			ans[val[i]] = 1;
			curx ^= a0[val[i]];
		}

  #ifdef LOCAL
  	assert(curx ==  0);
  #endif

  for (int i = 0; i < n; i++)
  	printf("%d ",2 - ans[i]);

      
  return 0;
}