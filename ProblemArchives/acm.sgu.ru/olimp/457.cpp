#include <vector>
#include <fstream>
#include <iostream>
#include <cmath>
#include <set>
#include <utility>
#include <algorithm>
#include <map>
#define pii pair<int,int>
#define ppii pair<pii,pii>
#define mp make_pair
using namespace std;


set<int> reb;//cписок номеров ребер после сортировки.
map<pii,int> rebnum;//map<pair<номер вершины1,номер вершины 2>,номер ребра.>
vector< ppii> gr;//список ребер. vector<вершины,pair<вес ребрабномер ребра до сорт.>>
const int inf=1<<30;//а сам не догодаешься?))
class snmkr{//класс, реализующий кракала.
public:
	vector<int> p;// для снм
	int kol;//количество ребер.
	void setsize(int n)// инициализация
	{
		this->p.resize(n);
		for (int i=0;i<n;i++)
			this->p[i]=i;
		this->kol=0;
	}
	int root (int a)
	{
		if (this->p[a]==a)
			return a;
		return this->p[a]=root(this->p[a]);
	}
	void uni (int a,int b,int c) //третий аргумент - номер ребра.
	{
		a=this->root(a);
		b=this->root(b);
		if (a!=b)
		{
			reb.insert(c);//добавили ребро в список.
			++kol;
			if (rand()%2)
				this->p[a]=b;
			else
				this->p[b]=a;
		}
	}
};

class snmnorm:public snmkr{// класс для удаления лишних столичных ребер.
public:
	vector<vector<int>> g;// матрица смежности для компонент.
	vector<int> minreb;  //минимальное ребро в компоненту.
	vector<int> minnum;  //его номер
	vector<int> st;      //вес столичного ребра в компоненту. 
	vector<int> stnum;   //номер столичного ребра
	int size;
	void setsize(int n)//инициализайия размера.
	{
		this->p.resize(n);
		this->size=n;
		for (int i=1;i<n;i++)
			this->p[i]=i;
		this->minreb.assign(n,inf);
		this->st.assign(n,inf);
		this->stnum.resize(n);
		this->minnum.resize(n);
		this->g.resize(n);
		for (int i=0;i<n;i++)
			this->g[i].assign(n,inf);
	}
	void uni(int a,int b,int c,bool init=false)// объединение компонент с a и b. если init=fаlse, то замена столичного рера a на c.
	{
		a=this->root(a);
		b=this->root(b);		
		if (!init){reb.insert(c);reb.erase(this->stnum[a]);}//замена.
		if (rand()%2)//объединение
		{
			this->p[a]=b;
			int t=a;//пусть в a хранится новый представитель всегда.
			a=b;
			b=t;
		}
		else
		{
			this->p[b]=a;
			stnum[a]=stnum[b];//столичной ж ребро для a убрали.
			st[a]=st[b];
		}

		for (int i=1;i<size;i++)// теперь все ребра b - ребра a, значит и эти тоже.
			if (this->minnum[i]==b)
				this->minnum[i]=a;
		minreb[a]=inf;//пересчитаем минимум для a
		minnum[a]=0;
		for (int i=1;i<size;i++)
		if ((p[i]=i)&&(i!=a))
		{
			int t=this->minreb[a];
			this->minreb[a]=min(this->minreb[a],this->g[a][i]=this->g[i][a]=min(this->g[i][a],this->g[i][b]));// это минимум  из того что есть и g[i][a],g[i][b], заодно и обновим матрицу для a.
			if (t!=this->minreb[a])
				minnum[a]=i;
		}
	}
	void unimax()// поиск лучшей замены.
	{
		int m=-(inf);
		int mn=0;
		for (int i=1;i<this->size;i++)
			if (((this->st[i])-(this->minreb[i])>m)&&(p[i]==i))//если ребро улучшает и исходит из компоненты,то..
			{
				m=(this->st[i])-this->minreb[i];
				mn=i;
			};
		uni(mn,this->minnum[mn],rebnum[mp(mn,this->minnum[mn])]);//вызов объединения.
	}
	snmnorm(int n)//конструктор(автоматическа инииализация).
	{
		setsize(n);
		for (int i=0;i<gr.size();i++)//заполнение атрицы смежности
		{
			this->g[gr[i].first.first][gr[i].first.second]=g[gr[i].first.second][gr[i].first.first]=gr[i].second.first;
		};
		for (int i=1;i<size;i++)// поииск минимальных ребер.
			for (int j=1;j<size;j++)
				if (minreb[i]>g[i][j])
				{
					minreb[i]=g[i][j];
					minnum[i]=j;
				};
		for (set<int>::iterator iter=reb.begin();iter!=reb.end();++iter)// поиск столичных реьер.
		{
			int t=*iter;
			if ((gr[t].first.first==0)||(gr[t].first.second==0))
			{
				st[gr[t].first.first+gr[t].first.second]=gr[t].second.first;
				stnum[gr[t].first.first+gr[t].first.second]=t;
			}
		};
		for (set<int>::iterator iter=reb.begin();iter!=reb.end();++iter)// объединение в компоненты по нестоличным ребра.
		{
			int t=*iter;
			if ((gr[t].first.first!=0)&&(gr[t].first.second!=0))
				uni(gr[t].first.first,gr[t].first.second,t,true);
		}

	}
};

bool lessppiipii (ppii a,ppii b)//критерий сравнения для ребер.
{
	return a.second.first<b.second.first;
}
int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	int n,m,k;
	scanf("%d %d %d\n",&n,&m,&k);
	gr.resize(m);
	int stol=0;
	for (int i=0;i<m;i++)// считывание графа, подсчет количества стол ребер.
	{
		scanf("%d %d %d\n",&gr[i].first.first,&gr[i].first.second,&gr[i].second.first);
		gr[i].first.first--;//0-индексация.
		gr[i].first.second--;
		gr[i].second.second=i;
		if ((gr[i].first.first==0)||(gr[i].first.second==0))
			stol++;
	}
	sort(gr.begin(),gr.end(),lessppiipii);//сортировка
	for (int i=0;i<m;i++)	//заполение номеров ребер	
		rebnum[mp(gr[i].first.first,gr[i].first.second)]=rebnum[mp(gr[i].first.second,gr[i].first.first)]=i;
	snmkr a;//краскал
	a.setsize(n);
	for (int i=0;i<gr.size();i++)
    	if ((gr[i].first.first==0)||(gr[i].first.second==0))//сначала столичные реьра
		   a.uni(gr[i].first.first,gr[i].first.second,i);
	for (int i=0;i<gr.size();i++)//потом остальные
		   a.uni(gr[i].first.first,gr[i].first.second,i);
	if ((stol<k)||(a.kol<n-1))// если мало столичных ребер или граф не связный
	{
		printf("-1");
		return 1;
	}
	snmnorm b(n);// убираем ненужные ребра.
	for (;stol>k;stol--)//пока столичных не столько сколько надо
	{
		b.unimax();// делаем лушую замену.
	}
	printf("%d\n",n-1);
	for (set<int>::iterator iter=reb.begin();iter!=reb.end();++iter)//вывод
		printf("%d ",gr[*iter].second.second+1);
	return 0;
}