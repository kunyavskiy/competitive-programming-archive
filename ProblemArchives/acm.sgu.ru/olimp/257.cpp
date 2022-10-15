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


struct cube{
	bool a[6];
	static int pv[6];
	static int ph[6];
	static int pin[6];
	void read(){
		char c;
		for (int i=0;i<6;i++){
			scanf(" %c ",&c);
			a[pin[i]]=(c=='0');
		}
	}
	void rotatev(){
		int b[6];
		for (int i=0;i<6;i++)
			b[pv[i]]=a[i];
		for (int i=0;i<6;i++)
			a[i]=b[i];
	}
	
	void rotateh(){
		int b[6];
		for (int i=0;i<6;i++)
			b[ph[i]]=a[i];
		for (int i=0;i<6;i++)
			a[i]=b[i];
	}
	bool check(){	
		return a[0];
	}
};

int cube::pin[6]={5,0,1,2,3,4};
int cube::ph[6] ={4,1,0,3,5,2};
int cube::pv[6] ={1,5,2,0,4,3};

cube a[31][31];
int n;
char buf[10];
vector<string> ans;

void rotatev(int y){
	sprintf(buf,"V %d",y+1);
	ans.pb(string(buf));
	for (int i=0;i<n;i++)
		a[i][y].rotatev();
}

void rotateh(int x){
	sprintf(buf,"H %d",x+1);
	ans.pb(string(buf));
	for (int i=0;i<n;i++)
		a[x][i].rotateh();
}

void solvever(int y){
	bool used[30];
	for (int i=0;i<n;i++){
		used[i]=false;
	}
	for (int it=0;it<4;it++){	
		for (int i=0;i<n;i++)
			if (a[i][y].check() && !used[i]){
				used[i]=true;
				rotateh(i);
			}
		rotatev(y);
	}
	for (int i=0;i<n;i++)
		if (used[i]){
			rotateh(i);
			rotateh(i);
			rotateh(i);
			assert(a[i][y].check());
		}
}

void solvehor(int x){
	bool used[30];
	for (int i=0;i<n;i++){
		used[i]=false;
	}
	for (int it=0;it<4;it++){	
		for (int i=0;i<n;i++)
			if (a[x][i].check() && !used[i]){
				used[i]=true;
				rotatev(i);
			}
		rotateh(x);
	}
	for (int i=0;i<n;i++)
		if (used[i]){
			rotatev(i);
			rotatev(i);
			rotatev(i);
			assert(a[x][i].check());
		}
}



int main()
{                        
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	scanf("%d",&n);
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			a[i][j].read();
	for (int i=0;i<n;i++)
		solvever(i);	
	for (int i=0;i<n;i++)
		solvehor(i);	
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			if (!a[i][j].check()){	
				cout<<"NO"<<endl;
				return 0;
			}
	printf("YES\n");
	printf("%d\n",int(ans.size()));
	for (int i=0;i<ans.size();i++)
		puts(ans[i].data());
	
    return 0;
}