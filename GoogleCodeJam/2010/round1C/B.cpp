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
#define int64 long long
#define ld long double  
#define setval(a,v) memset(a,v,sizeof(a))
using namespace std;

int main()
{
  //freopen("input.txt","r",stdin);
  //freopen("output.txt","w",stdout);

	

	
	int tkol;
	scanf("%d",&tkol);

	int64	l,r,c;
	
	for (int test=1;test<=tkol;++test){
		int ans=0;
		cin>>l>>r>>c;
		int64 tmp=c;
		for (;l*tmp<r;ans++)
			tmp=tmp*tmp;
		printf("Case #%d: %d\n",test,ans);
	}
  
  return 0;
}