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
                 
#define taskname "stars"


ll f[129][129][129];
int n;

ll get(int a,int b,int c){
	ll ans = 0;
	for (int i = a; i; i -= (i&-i))
		for (int j = b; j; j -= (j&-j))
			for (int k = c; k; k -= (k&-k)){
				ans += f[i][j][k];
				//cerr << i << " "<<j<<" "<<k<<endl;
			}
	return ans;		
}

ll get(int x1,int x2,int y1,int y2,int z1,int z2){
	return   (get(x2,y2,z2) - get(x1 - 1,y2,z2) - get(x2,y1 - 1,z2) + get(x1 - 1, y1 - 1, z2)) -
			 (get(x2,y2,z1-1) - get(x1 - 1,y2,z1-1) - get(x2,y1 - 1,z1-1) + get(x1 - 1, y1 - 1, z1-1));
			 
}


void upd(int a,int b,int c,int d){
	for (int i = a; i <= n; i += (i&-i))
		for (int j = b; j <= n; j += (j&-j))
			for (int k = c; k <= n; k += (k&-k)) 
				f[i][j][k] += d;			
}



int main(){                          
  scanf("%d",&n);                    

  for (int i = 0;; i++){
  	int t;
  	scanf("%d",&t);
  	if (t == 1){
  		int a,b,c,d;
  		scanf("%d %d %d %d",&a,&b,&c,&d);
  		++a,++b,++c;
  		upd(a,b,c,d);
  	}
  	else if (t == 2){
  		int x1,x2,y1,y2,z1,z2;
  		scanf("%d %d %d %d %d %d",&x1,&y1,&z1,&x2,&y2,&z2);
  		++x1,++x2,++y1,++y2,++z1,++z2;
  		printf(LLD"\n",get(x1,x2,y1,y2,z1,z2));
  	}
  	else
  		break;
  }

  return 0;
}

