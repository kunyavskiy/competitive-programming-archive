#include <iostream>
#include <vector>
#include <memory.h>
#include <cstdio>
#include <cstdlib>
using namespace std;

bool a[2010];
bool d[2][2010];
bool d1[2][2010];
bool dr[2][2010];
bool dr1[2][2010];

char s[5000];
int ptr;

bool next(){
	for (;s[ptr]==' ';++ptr);
	return s[ptr++]=='+';
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
  int n;
  scanf("%d\n",&n);	
  bool c;
  int ans[2];
  ans[0]=ans[1]=0;
  int tmp;
  for (int i=1;i<=n;i++){
  	gets(s);ptr=0;
  	for (int j=0;j<i;j++){
  		c=next();
  		for (int k=0;k<2;k++){
	  		d1[k][j]^=d[k][j];
  			d1[k][j]^=dr[k][j];
  			dr1[k][j+1]^=dr[k][j];  			
	  		tmp=d[k][j]^dr[k][j]^c;
	  		if (tmp!=k){
	  			++ans[k];
	  			d1[k][j]^=1;
	  			dr1[k][j+1]^=1;
	  		}
  		}
  	}
  	
  	for (int j=0;j<=i;j++)
  		for (int k=0;k<2;k++){
  			d[k][j]=d1[k][j];
  			d1[k][j]=0;
  			dr[k][j]=dr1[k][j];
  			dr1[k][j]=0;
  		}  	
  }
  cout<<min(ans[0],ans[1])<<endl;
}