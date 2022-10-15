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
#include <iterator>
#define mp make_pair
#define pb push_back                     
#define int64 long long
#define ld long double  
#define setval(a,v) memset(a,v,sizeof(a))
#define dbga(a) copy(a,a+n,ostream_iterator<int>(cerr," "));cerr<<endl
using namespace std;

const int MAXN=110000;

int a[MAXN];
int b[MAXN];
int c[MAXN];
int n;
int ans[3][MAXN];
int prev[MAXN];

void read(){
	scanf("%d",&n);
	for (int i=0;i<n;i++){
		scanf("%d",&a[i]);
		--a[i];
	}
	for (int i=0;i<n;i++){
		scanf("%d",&b[i]);
		--b[i];
		c[b[i]]=i;
	}
	for (int i=0;i<n;i++)
		a[i]=c[a[i]];
	for (int i=0;i<=n;i++){
		ans[0][i]=ans[1][i]=ans[2][i]=n;
		prev[i]=-1;
	}	
}

char res[MAXN];
char res2[MAXN];

int last[3];
const char col[3]={'R','G','B'};



int main()
{                        
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	read();
	last[0]=last[1]=last[2]=-1;
	for (int i=0;i<n;i++){
		for (int j=0;j<=3;j++){
			if (j==3){
				cout<<"NO\n";
				return 0;
			}
			if (last[j] < a[i]){
				last[j]=a[i];
				res[a[i]]=col[j];
				break;
			}
		}
//		cerr<<last[0]<<" "<<last[1]<<" "<<last[2]<<endl;
	}
	for (int i=0;i<n;i++)
		res2[b[i]]=res[i];
	for (int i=0;i<n;i++)
		printf("%c",res2[i]);
	printf("\n");
    return 0;
}