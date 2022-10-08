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



const int MAXSQ = 500;

int a[MAXSQ][MAXSQ];
pair<int,int> b[MAXSQ][MAXSQ];
int dlt[MAXSZ][MAXSZ];
int64 val[MAXSZ];
int64 sum[MAXSQ];
int BSZ;



void push(int num){
	for (int i=1;i<BSZ;i++)
		dlt[num][i] += dlt[num][i-1];
	for (int i=0;i<BSZ;i++){
		sum[num] -= dlt[i] * b[i].first;
		val[b[i].second] -= dlt[i] * b[i].first;
	}	
}

void add(int to,int col){
	
}

void addnew(int pos,int x){	
	
}




int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	
	return 0;
}