#include <vector>
#include <fstream>
#include <utility>
#include <iostream>
#include <string>
#define mp make_pair

using namespace std;

vector <vector<int>> tabl;
vector<vector<pair<int,int>>> mt;
vector <vector<bool>> used;
int n,m,p,mlast,k;
vector<vector<pair<pair<int,int>,pair<int,int>>>> answer;
string s;

bool kunn(pair<int,int> coord)
{
	int x=coord.first;
	int y=coord.second;
	if (x>n)
	   return false;
	if (y>m)
		return false;
	if ((x==n) && (y>mlast))
		return false;
	if (used[x][y])
		return false;
	used[x][y]=true;
	if ((x<n)&&((x!=n-1)|| (y<=mlast)) && (tabl[x+1][y]+tabl[x][y]==p))
	  if ((mt[x+1][y].first==-1) || (kunn(mt[x+1][y])))
	  {
	    	mt[x+1][y]=mp(x,y);
			return true;
	  }
    
	if ((x>0) && (tabl[x-1][y]+tabl[x][y]==p))
	  if ((mt[x-1][y].first==-1) || (kunn(mt[x-1][y])))
	  {
	    	mt[x-1][y]=mp(x,y);
			return true;
	  }
    if ((y>0) && (tabl[x][y-1]+tabl[x][y]==p))
	  if ((mt[x][y-1].first==-1) || (kunn(mt[x][y-1])))
	  {
	    	mt[x][y-1]=mp(x,y);
			return true;
	  }

  if ((((x<n) && (y<m))||((x==n) && (y<mlast))) && (tabl[x][y+1]+tabl[x][y]==p))
	  if ((mt[x][y+1].first==-1) || (kunn(mt[x][y+1])))
	  {
	    	mt[x][y+1]=mp(x,y);
			return true;
	  }
  return false;
}

void print()
{
	for (int i=0;i<answer.size();i++)
		printf("%d ",answer[i].size());
	printf("\n");
	for (int i=0;i<answer.size();i++)
	{
		for (int j=0;j<answer[i].size();j++)
			printf("%d,%d; %d,%d\n",answer[i][j].first.first+1,answer[i][j].first.second+1,answer[i][j].second.first+1,answer[i][j].second.second+1);
		printf("\n");
	}
}

void clear()
{
	for(int i=0;i<used.size();i++)
		used[i].assign(used[i].size(),false);
}
bool usemt()
{
	int l=answer.size();
	answer.resize(l+1);
	clear();;
	for (int i=0;i<n;i++)
		for (int j=1-i%2;j<=m;j+=2)
		if (mt[i][j].first!=-1)
		{
             used[i][j]=true;
			 used[mt[i][j].first][mt[i][j].second]=true;
			 answer[l].push_back(mp(mp(i,j),mt[i][j]));
			 k-=2;
		}
	for (int j=1-n%2;j<=mlast;j+=2)
		if (mt[n][j].first!=-1)
		{
             used[n][j]=true;
			 used[mt[n][j].first][mt[n][j].second]=true;
			 answer[l].push_back(mp(mp(n,j),mt[n][j]));
			 k-=2;
		}
	if (answer[l].size()==0)
	{
		int sum=0;
		for(int i=0;i<n;i++)
			for (int j=0;j<=m;j++)
				sum+=tabl[i][j];
		for(int i=0;i<=mlast;i++)
			sum+=tabl[n][i];
		sum--;
		sum%=(s.length());
		printf("%c\n",s[sum]);
		answer.resize(l);
		print();
		return false;

	}
	vector<int> newtabl;
	for (int i=0;i<n;i++)
		for(int j=0;j<=m;j++)
			if (!used[i][j])
				newtabl.push_back(tabl[i][j]);
	for (int i=0;i<=mlast;i++)
		if (!used[n][i])
			newtabl.push_back(tabl[n][i]);
	if (newtabl.size()==0)
	{
		printf("It is your best friend!\n");
		print();
		return false;
	}
	m=s.length();
	n=k/m;
	mlast=k%m;
	if (mlast!=0)
		n++;
	else
	   mlast=m;
	tabl.resize(n);
	mt.resize(n);
	used.resize(n);
	n--;
	for (int i=0;i<n;i++)
	{
		tabl[i].resize(m);
		mt[i].resize(m);
		used[i].resize(m);
		for (int j=0;j<m;j++)
			tabl[i][j]=newtabl[i*m+j];
	}
	tabl[n].resize(mlast);
	used[n].resize(mlast);
	mt[n].resize(mlast);
    for (int i=0;i<mlast;i++)
		tabl[n][i]=newtabl[n*m+i];
	m--,mlast--;
	for (int i=0;i<=n;i++)
		mt[i].assign(mt[i].size(),mp(-1,-1));
	return true;
}

int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	getline(cin,s);
	scanf("%d %d %d %d",&m,&n,&k,&p);
	mlast=k%m;
	n=k/m+(k%m==0?0:1);
	if (mlast==0)
		mlast=m;
	tabl.resize(n);
	mt.resize(n);
	used.resize(n);
	n--;
	for (int i=0;i<n;i++)
	{
		tabl[i].resize(m);
		mt[i].resize(m);
		used[i].resize(m);
	}
	tabl[n].resize(mlast);
	used[n].resize(mlast);
	mt[n].resize(mlast);
	m--;
	mlast--;
	for (int i=0;i<n;i++)
     for (int j=0;j<=m;j++)
		 scanf("%d",&tabl[i][j]);
    for (int i=0;i<=mlast;i++)
		scanf("%d",&tabl[n][i]);
	do
	{
	  for (int i=0;i<=n;i++)
		mt[i].assign(mt[i].size(),mp(-1,-1));
		for (int i=0;i<n;i++)
			for (int j=i%2;j<=m;j+=2)
			{
				clear();
				kunn(mp(i,j));
			};
		for(int i=n%2;i<=mlast;i+=2)
		{
			clear();
			kunn(mp(n,i));
		};
	}
	while (usemt());
	return 0;
}