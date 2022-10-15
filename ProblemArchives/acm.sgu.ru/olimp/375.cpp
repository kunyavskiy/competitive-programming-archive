#include <fstream>
#include <vector>
using namespace std;
int main()
{
  freopen("input.txt","rt",stdin);
  freopen("output.txt","wt",stdout);
  int n,m;
  scanf("%d %d\n",&n,&m);
  vector<vector<int>> a(n+1);
  int i,j;
  for (i=1;i<=n;i++)
	  a[i].resize(m+1);
  int xmax=0,ymax=0,vmax=0;
  for (int i=1;i<=n;i++)
  {
	  for (int j=1;j<m;j++)
		  scanf("%d ",&a[i][j]);
	  scanf("%d\n",&a[i][m]);
  }

  for (i=1;i<=n;i++)
	  for (j=1;j<=m;j++)
		  if (a[i][j]>=vmax)
		  {
			  vmax=a[i][j];
              xmax=i;
			  ymax=j;
		  }
  int ymin=0,xmin=0,vmin=2147483647;
  for (i=1;i<=m;i++)
    if (a[xmax][i]<=vmin)
	{
		ymin=i;
		vmin=a[xmax][i];
	}
  vmin=2147483647;
  for (i=1;i<=n;i++)
    if (a[i][ymax]<=vmin)
	{
		xmin=i;
		vmin=a[i][ymax];
	}
  printf("%d",a[xmin][ymin]);
  return 0;
}