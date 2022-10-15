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
#include <stack>
#define mp make_pair
#define pb push_back                     
#define int64 long long
#define ld long double
#define fileinout
using namespace std;

pair<int,int> a[4];

bool cmp2(pair<int,int> a,pair<int,int> b){
	return a.second<b.second;
}

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  int c;
  scanf("%d",&c);
  for (;c;--c){
  	for (int i=0;i<4;i++)
  	{
  		scanf("%d",&a[i].first);
  		a[i].second=i;
  	}
  	sort(a,a+4);
  	int tmp=a[0].first;
 		if (a[1].first==tmp && a[2].first==tmp){
 			printf("Robert wins.\n");
 			if (c!=1)
 				printf("\n");
 			continue;
 		}
 		printf("Julia wins.\n");
 		sort(a,a+4,cmp2);
		int kol=0;
		for (int i=0;i<4;i++)
			if (kol<2 && a[i].first!=tmp){
				kol++;
				printf("%d ",a[i].first-tmp);
			}
		else
				printf("0 ");
		printf("\n");
		if (c!=1)
			printf("\n");
 	}  		
  return 0;
}