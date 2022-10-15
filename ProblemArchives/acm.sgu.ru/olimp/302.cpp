#include <fstream>
#include <vector>
#include <utility>

#define ppi pair<int,int>
#define mp make_pair
using namespace std;

int n1,tec;
int p1,p2,m1,m2;
vector<char> t;


bool good(int plus,int minus)
{
	return ((minus<=m2) && (m1<=minus) && (plus<=p2) && (p1<=plus));
}

int generatenext(int mask,int size)
{
	return ((mask^(mask>>1)) & ((1<<size)-1));
}

ppi generate(int size,int mask)
{
   
   if ((size==1) && (mask==0))
	   return mp(1,0);
   if ((size==1) && (mask==1))
	   return mp(0,1);
   ppi a=generate(size-1,generatenext(mask,size-1));
   a.first+=(size-(int)t[mask]);
   a.second+=(int)t[mask];
   return a;
}
int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	scanf("%d\n%d %d %d %d",&n1,&p1,&p2,&m1,&m2);
	int res=0;
	t.resize(1<<n1);
	t[0]=0;
	for (int i=1;i<(1<<n1);i++)
		t[i]=t[i & (i-1)]+1;
	//if (good(t[1][0])) res++;
	//if (good(t[1][1])) res++;
	//if (n1!=1)
	//t[2].resize(4);
	for (int i=1;i<=n1;i++)
	{
		for (int j=0;j<(1<<i);j++)
	       {
			   ppi a=generate(i,j);
			   if (good(a.first,a.second))
				   res++;
	       }
	}
   //if (n1!=1)
 //  for (int j=0;j<(1<<n1);j++)
	       //{
			   //tr tr1=genetate(n1,j);
			   //if (good(tr1))
				   //res++;
	       //}
   printf("%d",res);
	return 0;
}