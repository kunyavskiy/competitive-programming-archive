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
#include <queue>
#include <stack>
#define mp make_pair
#define pb push_back                     
#define int64 long long
#define ld long double
#define fileinout
using namespace std;

bool prime(int x)
{
  if (x<2)
    return false;
  for (int i=2;i*i<=x;i++)
    if (x%i==0)
      return false;
  return true;
}

int val1=0;
int val2=0;

void print(int x)
{
  int tmp=x/10;
  if (tmp!=0)
    {
      printf(">");
      for (;val1>tmp;val1--)
        printf("-");
      for (;val1<tmp;val1++)
        printf("+");
      printf(".");
      printf("<");
    }
  tmp=x%10;
 // printf("<");
  for (;val2>tmp;val2--)
     printf("-");
  for (;val2<tmp;val2++)
     printf("+");
  printf(".");
  if (x!=97)
    printf("<.>");
  printf("\n");
  return;
}

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif     
  for (char c=0;c<'0';c++)
    printf("+");    
  printf("[->+>+>+<<<]>---->");
    printf("\n");
  for (int i=0;i<100;i++)
    if (prime(i))
      print(i); 
  return 0;
}