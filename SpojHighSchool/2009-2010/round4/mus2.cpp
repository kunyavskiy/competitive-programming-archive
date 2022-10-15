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
#include <bitset>
#include <queue>
#include <stack>
#define mp make_pair
#define pb push_back                     
#define int64 long long
#define ld long double
#define assert(val) ;
#define fileinout
using namespace std;

struct ver{     
  bool l,r,u,d;
  ld a;
  ver(){ l=r=u=d=1;a=0;}
} pole[1222][1222];
ld d[1222][1222];
enum nap {_no=0,_lf=1,_rg=2,_up=3,_down=4};
nap from[1222][1222];

struct pos{
  int x,y;
  pos(){x=y=0;}
  pos(int _x,int _y){x=_x; y=_y;}
  void read(){
     scanf(" (%d, %d), ",&y,&x);    
  }
};

const ld eps=1e-09;

bool operator< (const pos& a,const pos& b)
{
  return ((a.x<b.x) || ((a.x==b.x) && (a.y<b.y)));
}

bool operator== (const pos& a,const pos& b)
{
  return ((a.x==b.x) && (a.x==b.x));
}


bool good(int x,int y)
{
	if (x<0)
		return false;
	if (x>=1222)
		return false;
	if (y<0)
		return false;
	if (y>=1222)
		return false;
	return true;
}


struct vect
{
  int x,y;
  vect()
  {
    x=y=0;
  }
  vect(int _x,int _y)
  {
     x=_x;
     y=_y;
  } 
  void read()
  {
     scanf(" [%d, %d], ",&y,&x);    
  }                             
};

pos operator+(pos a,vect b)
{
  return pos(a.x+b.x,a.y+b.y);
}           


pos operator-(pos a,pos b)
{
  return pos(a.x-b.x,a.y-b.y);
}

pos operator+(pos a,pos b)
{
  return pos(a.x+b.x,a.y+b.y);
}



void minimize(pos& a,pos b)
{
  a.x=min(a.x,b.x);
  a.y=min(a.y,b.y);
}

pos sdvig;

void newline(pos& p,vect v)
{
	assert(good(p.x,p.y));
  for (int i=0;i<v.y;i++)
  {
    pole[p.x][p.y+i].d=false;
    pole[p.x-1][p.y+i].u=false;
  }
  for (int i=-1;i>=v.y;i--)
  {
    pole[p.x][p.y+i].d=false;
    pole[p.x-1][p.y+i].u=false;
  }
  for (int i=0;i<v.x;i++)
  {
    pole[p.x+i][p.y].l=false;
    pole[p.x+i][p.y-1].r=false;
  }
  for (int i=-1;i>=v.x;i--)
  {
    pole[p.x+i][p.y].l=false;
    pole[p.x+i][p.y-1].r=false;
  }
  p=p+v;
}

void read_figure()
{
  pos st;
  int k;
  scanf("%d",&k);
  st.read();
  st=st+sdvig;
  pos tp=st;
  vect v;
  for (int i=0;i<k;i++)
  {                                              
    v.read();                                    
    newline(st,v);
    assert(good(st.x,st.y));
  }               
  assert(tp==st);
}


void read_figure(bool)
{
  pos st;
  int k;
  scanf("%d",&k);
  st.read();
  pos minp=st;
  pos tp=st;
  vector<vect> f(k);
  for (int i=0;i<k;i++)
  {
    f[i].read();
    tp=tp+f[i];
    minimize(minp,tp);
  }
  assert(tp==st);
  sdvig=pos(100,100)-minp;
  st=st+sdvig;                           
  for (int i=0;i<k;i++)
  {
    newline(st,f[i]); 
    assert(good(st.x,st.y));
  }
}
  
void readsensor()
{
  pos p;
  p.read();
  p=p+sdvig;
  newline(p,vect(0,1));
  newline(p,vect(1,0));
  newline(p,vect(0,-1));
  newline(p,vect(-1,0));
  int c;
  scanf("%d",&c);
  ld val=100;
  for (int i=0;i<c;i++)
  {
  	ld tv=(int)(val+0.5);
  	tv/=100;
  	assert(tv<=1);
    for (int x=-i;x<=i;x++)
     {
     	int nx=p.x+x;
     	int ny=p.y+(i-abs(x));     
     	if (good(nx,ny))   
	      pole[nx][ny].a=max(pole[nx][ny].a,tv);
     	ny=p.y-(i-abs(x));
     	if (good(nx,ny))   
	      pole[nx][ny].a=max(pole[nx][ny].a,tv);
    }
    val-=100.0/c;
  }
}

int cx,cy;

void print(int tx,int ty,int sx,int sy,int kol)
{
//	cerr<<tx<<" "<<ty<<endl;
	assert(good(tx,ty));
  if ((tx==sx) && (ty==sy))
  {
    printf("%d\n",kol);
    cx=sx;
    cy=sy;
    return;
  }
  if (from[tx][ty]==_down)
  {
    print(tx-1,ty,sx,sy,kol+1);
    printf("U");
    cx++;
    return;
  }
  if (from[tx][ty]==_up)
  {
    print(tx+1,ty,sx,sy,kol+1);
    printf("D");
    cx--;
    return;
  }
  if (from[tx][ty]==_rg)
  {
    print(tx,ty+1,sx,sy,kol+1);
    printf("L");
    cy--;
    return;
  }
  if (from[tx][ty]==_lf)
  {
    print(tx,ty-1,sx,sy,kol+1);
    printf("R");
    cy++;
    return;
  }
  assert(false);
}
                      
int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif                              
  pos spos,epos;
  spos.read();                                 
  epos.read();
  for (int i=0;i<1222;i++)
  {
    for(int j=0;j<1222;j++)
    {
    	pole[i][j]=ver(); 
    }             
  }
  read_figure(true);          
  spos=spos+sdvig;
  epos=epos+sdvig;
  int k;
  scanf("%d",&k);
  for (int i=0;i<k;i++)
    read_figure();
  scanf("%d",&k);
  for (int i=0;i<k;i++)
    readsensor();  
 // const ld inf1=1.0*(1<<30)*(1<<30);
  const ld inf2=1.0*(1<<30)*(1<<30)*(1<<30);
  for (int i=0;i<1222;i++)
  {
    for(int j=0;j<1222;j++)
    {
 //     if (abs(pole[i][j].a)<eps)
   //     pole[i][j].a=inf1;
     // else
       // pole[i][j].a=-logl(pole[i][j].a);
      d[i][j]=inf2;                          
      assert(pole[i][j].a>=0 && pole[i][j].a<=1);
    }             
  }
  d[spos.x][spos.y]=pole[spos.x][spos.y].a;
  set<pair<ld,pos> > s;
  s.insert(mp(pole[spos.x][spos.y].a,pos(spos.x,spos.y)));
  for (;!s.empty();)
  {
    pos from=(--s.end())->second;
    s.erase(--s.end());
    int fx=from.x;
    int fy=from.y;
   // cerr<<fx<<" "<<fy<<" "<<d[fx][fy]<<endl;
    assert(good(fx,fy));                      
    ld tmp;
    if (pole[fx][fy].d)
    {
      tmp=d[fx][fy]+pole[fx-1][fy].a-d[fx][fy]*pole[fx-1][fy].a;
      if ((d[fx-1][fy]>tmp) && good(fx-1,fy))
      {
        s.erase(mp(d[fx-1][fy],pos(fx-1,fy)));
        d[fx-1][fy]=tmp;
        ::from[fx-1][fy]=_up;
        s.insert(mp(d[fx-1][fy],pos(fx-1,fy)));
      }
    }
    if (pole[fx][fy].u)
    {tmp=d[fx][fy]+pole[fx+1][fy].a-d[fx][fy]*pole[fx+1][fy].a;
      if ((d[fx+1][fy]>tmp) && good(fx+1,fy))
      {
        s.erase(mp(d[fx+1][fy],pos(fx+1,fy)));
        d[fx+1][fy]=tmp; 
        ::from[fx+1][fy]=_down;
        s.insert(mp(d[fx+1][fy],pos(fx+1,fy)));
      }
    }
    if (pole[fx][fy].l)
    {
	tmp=d[fx][fy]+pole[fx][fy-1].a-d[fx][fy]*pole[fx][fy-1].a;
      if ((d[fx][fy-1]>tmp) && good(fx,fy-1))
      {
        s.erase(mp(d[fx][fy-1],pos(fx,fy-1)));
        d[fx][fy-1]=tmp; 
        ::from[fx][fy-1]=_rg;
        s.insert(mp(d[fx][fy-1],pos(fx,fy-1)));
      }
    }
    if (pole[fx][fy].r)
    {
	tmp=d[fx][fy]+pole[fx][fy+1].a-d[fx][fy]*pole[fx][fy+1].a;
      if ((d[fx][fy+1]>tmp) && good(fx,fy+1))
      {
        s.erase(mp(d[fx][fy+1],pos(fx,fy+1)));
        d[fx][fy+1]=tmp; 
        ::from[fx][fy+1]=_lf;
        s.insert(mp(d[fx][fy+1],pos(fx,fy+1)));
      }
    }          
  }                          
  assert(d[epos.x][epos.y]!=inf2);
  print(epos.x,epos.y,spos.x,spos.y,0);
  printf("\n");
  assert(cx==epos.x && cy==epos.y);
  return 0;
}