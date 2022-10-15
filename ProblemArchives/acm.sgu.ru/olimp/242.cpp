#include <iostream>
using namespace std;

short t[31][31];
char s[31];

int l[31];
int r[31];
int c[31];

short calc(int l,int r){
	if (l>r)
		return 0;
	short& ans=t[l][r];
	if (ans!=-1)
		return ans;
	for (;l<r && s[r]==s[l];--r);
	if (l==r)
		return ans=0;
	ans=127;
	for (int i=l;i<=r;i++)
		if (s[i]==s[r]){
			short tmp=calc(l,i-1)+calc(i,r)+1;
			if (ans > tmp)
				ans=tmp;
		}
	return ans;
}

void gen(int l,int r){
	if (l>r)
		return;
	short ans=calc(l,r);
	for (;l<r && s[r]==s[l];--r);
	if (l==r)
		return;
	for (int i=l;i<=r;i++)
		if (s[i]==s[r])
			if (ans == calc(l,i-1)+calc(i,r)+1){
				::l[::l[0]++]=i;
				::r[::r[0]++]=r;
				::c[::c[0]++]=s[r];
				gen(l,i-1);
				gen(i,r);
				return;
			}
}


int main()
{                        
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	memset(t,-1,sizeof(t));
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++)
		scanf(" %c ",&s[i]);		
	printf("%d\n",calc(0,n-1)+1);
	l[0]=r[0]=c[0]=1;
	l[l[0]++]=0;
	r[r[0]++]=n-1;
	c[c[0]++]=s[0];
	gen(0,n-1);
	for (int i=1;i<l[0];i++)
		printf("%d %d %c\n",l[i]+1,r[i]+1,c[i]);		
    return 0;
}