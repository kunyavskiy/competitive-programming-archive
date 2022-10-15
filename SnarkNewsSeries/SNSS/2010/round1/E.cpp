#include <iostream>
#include <cassert>
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
#include <iterator>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

#define taskname "E"

using namespace std;

typedef long long int64;
typedef long double ld;

void norm(bool a[][4]){
	for (;;){
		bool q=false;
		for (int i=0;i<4;i++)
			q|=a[0][i];
		if (q) break;
		for (int i=0;i<3;i++)
			for (int j=0;j<4;j++)
				a[i][j]=a[i+1][j];
		for (int j=0;j<4;j++)
			a[3][j]=0;
	}
	for (;;){
		bool q=false;
		for (int i=0;i<4;i++)
			q|=a[i][0];
		if (q) break;
		for (int i=0;i<4;i++)
			for (int j=0;j<3;j++)
				a[i][j]=a[i][j+1];
		for (int j=0;j<4;j++)
			a[j][3]=0;
	}             
}

void rotate(bool a[][4]){
	bool tmp[4][4];
	for (int i=0;i<4;i++)
		for (int j=0;j<4;j++)
			tmp[3-j][i]=a[i][j];
	for (int i=0;i<4;i++)
		for (int j=0;j<4;j++)
			a[i][j]=tmp[i][j];
	norm(a);
}

void gen(bool res[][4],int f,int a){
	for (int i=0;i<4;i++)
		for (int j=0;j<4;j++)
			res[i][j]=0;
	switch (f){
		case 0:
			for (int i=0;i<4;i++)
				res[0][i]=1;
		break;
		case 1:
	   	 	res[0][1]=1;
			for (int i=1;i<4;i++)
				res[1][i]=1;
		break;
		case 2:
			res[0][3]=1;
			for (int i=1;i<4;i++)
				res[1][i]=1;
		break;
		case 3:
			for (int i=0;i<2;i++)	
				for (int j=2;j<4;j++)
					res[i][j]=1;
		break;
		case 4:
			res[0][3]=res[0][2]=res[1][2]=res[1][1]=1;
		break;
		case 5:
			res[0][2]=1;
			for (int i=1;i<4;i++)
				res[1][i]=1;
		break;
		case 6:
			res[1][3]=res[1][2]=res[0][2]=res[0][1]=1;
		break;			
	}      
	norm(res);   
//	cerr<<"!!"<<endl;
	for (;a;a-=90){
//		cerr<<a<<endl;
		rotate(res);
	}
}

bool a[110][110];
bool tec[4][4];
int n,m;

void print(){
	for (int i=n-1;i>=0;i--){
		for (int j=0;j<m;j++)
			if (a[i][j])
				printf("*");
			else
				printf(".");
	printf("\n");
	}		
}

bool get(int x,int y){
	if (x<0)
		return true;
	if (x>=n)
		return false;
	if (y>=m)
		return false;
	return a[x][y];
}

void setv(int x,int y){
	if (x>=n)
		{
			printf("Overflow\n");
			print();
			exit(0);
		}
	a[x][y]=1;
}

bool check(int x,int y){
	for (int i=0;i<4;i++)
		for (int j=0;j<4;j++)
			if (tec[i][j] && get(x-i,y+j))
				return false;
	return true;
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
	int k,t;
	scanf("%d %d %d %d",&n,&m,&k,&t);
	for (int i=0;i<k;i++){
		int x,y;
		scanf("%d %d",&x,&y);
		--x;--y;
		a[x][y]=true;
	}

/*	for (int i=0;i<7;i++){
		for (int j=0;j<360;j+=90){
			gen(tec,i,j);
			cout<<i<<" "<<j<<endl;
			for (int k=0;k<4;k++)
				for (int l=0;l<4;l++)
					cout<<tec[k][l]<<" \n"[l==3];
			cout<<endl<<endl;
		}
	}*/

	//print();
	//cout<<endl<<endl;
	for (;t;--t){
		int p,f,ang;
		scanf("%d %d %d",&p,&f,&ang);
	//	cout<<p<<" "<<f<<" "<<ang<<endl;
		--p;
		gen(tec,f,ang);
	//	for (int i=0;i<4;i++)
	//		for (int j=0;j<4;j++)
	//			cout<<tec[i][j]<<" \n"[j==3];
		int x=n+5;
		for (;check(x,p);--x);
		++x;
	//	cout<<"TO:"<<x<<endl;
		for (int i=3;i>=0;i--)
			for (int j=0;j<4;j++)
				if (tec[i][j]){
					assert(p+j<m);
					setv(x-i,p+j);
				}

		//print();
		//cout<<endl<<endl;
	}
	printf("Ok\n");
	print();
	return 0;
} 