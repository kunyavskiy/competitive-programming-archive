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

#define taskname "C"

#ifdef _WIN32_ 
  #define LLD "%I64d"
#else
  #define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;

const int maxn=210000;

pair<int64,int64> row[maxn];
pair<int64,int64> col[maxn];
int64 before[maxn];

int main(){
#ifdef LOCAL
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
#endif
  int r,c;
  scanf("%d",&r);
  for (int i=0;i<r;i++)
    scanf(LLD" "LLD,&row[i].first,&row[i].second);
  scanf("%d",&c);
  for (int i=0;i<c;i++)
    scanf(LLD" "LLD,&col[i].first,&col[i].second);
  sort(row,row+r);
  sort(col,col+c);
  reverse(row,row+r);
  reverse(col,col+c);

  int64 bal=0;
  int ptr=c-1;
  int64 kolc,kolr;
  kolc=0;
  for (int i=0;i<c;i++)
    kolc+=col[i].second;
  kolr=0;
  for (int i=0;i<r;i++){
    bal-=row[i].first*row[i].second;
    int tmp=kolr;
    kolr+=row[i].second;
    for (;ptr>=0 && col[ptr].first<kolr;--ptr){
      bal+=col[ptr].second*(col[ptr].first-tmp);      
      kolc-=col[ptr].second;
    }
    bal+=kolc*kolr;
    if (bal<0){
      printf("0\n");
      return 0;
    }
  }
  if (bal!=0 || ptr!=-1)
  {
    printf("0\n");
    return 0;
  }
  printf("1\n");
  return 0;
}