#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <memory.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <iterator>

#define mp make_pair
#define pb push_back
#define taskname "D"

#ifdef LOCAL
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;

int kol[110][1100];
int t[110][600];

void readstation(int num){
	string s;
	getline(cin,s);
	stringstream str(s);
	int a;
	for (;str>>a;)
		kol[num][a]++;
	for (int i=1000;i>=0;i--)
		kol[num][i]+=kol[num][i+1];
}

int main(){
	#ifdef LOCAL
		#ifndef taskname
			#error taskname is not defined
		#else
			freopen(taskname".in","r",stdin);
			freopen(taskname".out","w",stdout);
		#endif
	#endif
	int n;
	scanf("%d\n",&n);
	for (int i=n-1;i>=1;i--)
		readstation(i);
	int maxv=500;
	for (int i=0;i<=maxv;i++)
		t[0][i]=0;
	for (int i=1;i<n;i++){
		for (int j=0;j<=maxv;j++){
			if (j!=0)
				t[i][j]=t[i][j-1];
			t[i][j]=max(t[i][j],j*kol[i][j]+t[i-1][j]);
		}
	}
/*	for (int i=0;i<n;i++)
		for (int j=0;j<=maxv;j++)
			cerr<<t[i][j]<<" \n"[j==maxv]; */
	int maxx=0;
	for (int i=0;i<=maxv;i++)
		maxx=max(maxx,t[n-1][i]);
	cout<<maxx<<endl;

	return 0;
} 