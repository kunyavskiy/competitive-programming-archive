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
#define forn(i,n) for(int i=0;i<(n);++i)
#define ford(i,n) for(int i=(n)-1;i>=0;--i)

#if ( _WIN32 || __WIN32__ )
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long long ll;
typedef long double ld;

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
 	int n,m;
 	cin>>m>>n;
 	if (n>=2*m){
 		printf("1\n");
 		return 0; 	
 	}
 	
 	if (n==1){
		printf("-1");
 		return 0;
 	}
 
 	if (n==2){
 		if (m>3){
 			printf("-1");
 			return 0;
 		}
 		if (m==3)
 			printf("11");
 		else if (m==1)
 			printf("1");
 		else if (m==2)
 			printf("5");
 		printf("\n");
 		return 0;			
 	}
 	if (n==3){
 		if (m==2){
 			printf("3");
 			return 0;
 		}
 		if (m==3){
 			printf("5");
 			return 0;
 		}
 		if (m==4){
 			printf("7");
 			return 0;
 		}
		printf("-1");
		return 0;
 	}
 	int k=n/2-1;
 	int tmp=(m-k-1)/k+1;
 	cout<<tmp<<endl;
	return 0;
}