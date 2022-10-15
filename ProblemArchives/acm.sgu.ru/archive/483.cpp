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

typedef long long int64;
typedef long double ld;

deque<int> ans;

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	int n,H;
	int64 num;
	scanf("%d %d",&n,&H);
	num=2;
	if (H==0)
		ans.push_back(1);
	for (int i=1;num<=n;i++){
		if (i-1>=H && num+H<=n)
			ans.push_front(num+H);
		num+=i;
		if (i-1>=H && num+H<=n)
			ans.push_back(num+H);
		num+=i;
		if (i==H)
			ans.push_front(num);
		num++;
	}
	for (int i=0;i<ans.size();i++)
		printf("%d ",ans[i]);
	printf("\n");
    return 0;
}