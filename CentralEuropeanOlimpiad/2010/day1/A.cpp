#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include <fstream>
#include <queue>
#include <memory.h>    
#include <stack>
#include <deque>

#define mp make_pair
#define pb push_back

#define taskname "A"

#ifdef LOCAL 
  #define LLD "%I64d"
#else
  #define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;

const int dx[4]={1,0,-1,0};
const int dy[4]={0,1,0,-1};
const int obr[4]={2,3,0,1};

bool used[71][71][4]; 
int bal[71][71];
int type[71][71];
int usedv[71][71];
int n,m;

bool dfs(int x,int y,int nap,bool last){
  if (x>=n || x<0 || y>=m || y<0 || type[x][y]==0)
    return false;  

 // cout<<x<<" "<<y<<" "<<nap<<" "<<last<<endl;

  if (type[x][y]==2){

    if (usedv[x][y]==nap || (nap!=-2 && usedv[x][y]==obr[nap]) || usedv[x][y]==5)
      return false;
    if (nap!=-2 && used[x][y][obr[nap]] && last){     


       if (usedv[x][y]==-1)
         usedv[x][y]=nap;
       else
         usedv[x][y]=5;

      if (dfs(x+dx[obr[nap]],y+dy[obr[nap]],nap,last^1)){
        used[x][y][nap]^=1;
        used[x][y][obr[nap]]^=1;
        return true;
      }
    }

    usedv[x][y]=5;

    if (bal[x][y]>0 && nap!=-2 && last){
      used[x][y][nap]=true;
      bal[x][y]--;
      return true;
    }

   // cerr<<"!"<<endl;
    if (last){
      for (int i=0;i<4;i++)
        if (i!=nap && (nap==-2 || i!=obr[nap]) && used[x][y][i])
          if (dfs(x+dx[i],y+dy[i],obr[i],last^1)){
              if (nap!=-2)
                used[x][y][nap]^=1;
              else
                bal[x][y]--;
              used[x][y][i]^=1;
              return true;                         
          }
          //else
           //   cout<<"B"<<x<<" "<<y<<" "<<nap<<" "<<last<<endl;
    }
    else{


     for (int i=0;i<4;i++)
        if (i!=nap && !used[x][y][i] && (!used[x][y][obr[i]] || obr[i]==nap)) 
          if (dfs(x+dx[i],y+dy[i],obr[i],last^1)){
              if (nap!=-2)
                used[x][y][nap]^=1;
              else
                bal[x][y]--;
              used[x][y][i]^=1;
              return true;
          }
      //    else
        //      cout<<"B"<<x<<" "<<y<<" "<<nap<<" "<<last<<endl;

    }
    return false;
  }

  if (usedv[x][y]!=-1)
    return false;

  usedv[x][y]=5;
  
  if (bal[x][y]>0 && nap!=-2 && last){
    used[x][y][nap]=true;
    bal[x][y]--;
    return true;
  }

  for (int i=0;i<4;i++)
    if (i!=nap && (!used[x][y][i]^last))
      if (dfs(x+dx[i],y+dy[i],obr[i],last^1)){
          if (nap!=-2)
            used[x][y][nap]^=1;
          else
            bal[x][y]--;
          used[x][y][i]^=1;
          return true;
      }     
     // else
     //     cout<<"B"<<x<<" "<<y<<" "<<nap<<" "<<last<<endl;
  return false;
}

void print(int x){
  for (int i=0;i<m;i++){
    printf(".");
    printf("%c",".X"[used[x][i][2]]);
    printf(".");
  }
  printf("\n");


  for (int i=0;i<m;i++){
    printf("%c",".X"[used[x][i][3]]);
    printf("%c","O."[type[x][i]==0]);
    printf("%c",".X"[used[x][i][1]]);
  }
  printf("\n"); 

  for (int i=0;i<m;i++){
    printf(".");
    printf("%c",".X"[used[x][i][0]]);
    printf(".");
  }
  printf("\n");        
}

int main(){
#ifdef LOCAL
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
#endif
  scanf("%d %d",&n,&m);
  for (int i=0;i<n;i++)
    for (int j=0;j<m;j++){
      scanf("%d",&type[i][j]);
      bal[i][j]=type[i][j];
    }
  for (int i=0;i<n;i++)
    for (int j=0;j<m;j++)
      for (;bal[i][j]!=0;){

        /*#ifdef LOCAL
          cout<<i<<" "<<j<<" "<<type[i][j]<<endl;
        #endif*/
        memset(usedv,-1,sizeof(usedv));
        if (!dfs(i,j,-2,0)){
          printf("Impossible!\n");
          return 0;
        }


       /* #ifdef LOCAL
          cout<<"<DEBUG>"<<endl;                                

          for (int i=0;i<n;i++)
            print(i);
    
          cout<<"</DEBUG>"<<endl;
        #endif*/

      }         
  for (int i=0;i<n;i++)
    print(i);

  return 0;
}