#include <fstream>
#include <vector>
#include <algorithm>
#define forc(i,s,e) for(int i=s;i<=e;i++)
#define scan(p) scanf("%d",&p);
using namespace std;

vector<vector<int>> t,from;
vector<int> ras;
vector<int> len;
int n,m;

int best(int l,int r)
{
	if (t[l][r])
	  {
		  return t[l][r];
	  }
	if (r-l==1)
	  {
		  t[l][r]=0;
		  return 0;
	  }
	if (r-l==2)
	  {
		    t[l][r]=len[l+1];
			return t[l][r];
	  }
	int sum=ras[r]-ras[l];
	int res=1<<30;
	forc(i,l+1,r-1)
	{
		int temp=sum+best(l,i)+best(i,r);
		if (res>temp)
		  {
			  res=temp;
			  from[l][r]=i;
	      }
	}
	t[l][r]=res;
	return res;
}

void printanswer(int l,int r)
{
	if (r-l==1)
	  {
		  return;
	  }
	if (r-l==2)
	  {
		    printf("%d ",ras[l+1]);
			return;
	  }
	printf("%d ",ras[from[l][r]]);
	printanswer(l,from[l][r]);
	printanswer(from[l][r],r);
}

int main()
{
	freopen("input.txt","rt",stdin); 
	freopen("output.txt","wt",stdout);
	scan(n);
	scan(m);
	ras.push_back(0);
	len.push_back(0);
    forc(i,1,m)
	  {
		  int a;
		  scan(a);
		  ras.push_back(a);
	  }
	sort(ras.begin(),ras.end());
	ras.push_back(n);
	forc(i,1,m)
		len.push_back(ras[i+1]-ras[i-1]);
	len.push_back(0);
	t.resize(m+2);
	forc(i,0,m+1)
		t[i].resize(m+2);
	from.resize(m+2);
	forc(i,0,m+1)
		from[i].resize(m+2);
	forc(i,0,m+1)
		forc(j,0,m+1)
		  t[i][j]=0;
	int p=best(0,m+1);
	printf("%d\n",p);
    printanswer(0,m+1);
	return 0;
}