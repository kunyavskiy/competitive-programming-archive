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

bool g[500][500];


int main()
{                        
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	int n,m;
	scanf("%d %d",&n,&m);
	for (int i=0;i<m;i++){
		int a,b;
		scanf("%d %d",&a,&b);
		--a,--b;
		g[a][b]=g[b][a]=1;
	}
	int64 sum = 0;
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++){
			if (i==j)
				continue;
			int cnt = 0;
			for (int k=0;k<n;k++)
				if (g[i][k] && g[j][k])
					cnt++;
			sum+=cnt*(cnt-1);
		}
	sum /= 8;
	cout<<sum<<endl;
    return 0;
}