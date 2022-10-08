// Sample input 3, in C.

#include <assert.h>

#include <stdbool.h>

long long NumberOfCards() {
  return 7LL;
}

bool IsBetter(long long i, long long j) {
  if (i == 0 && j == 0) return false;
  if (i == 0 && j == 1) return false;
  if (i == 0 && j == 2) return true;
  if (i == 0 && j == 3) return false;
  if (i == 0 && j == 4) return false;
  if (i == 0 && j == 5) return false;
  if (i == 0 && j == 6) return false;
  if (i == 1 && j == 0) return true;
  if (i == 1 && j == 1) return false;
  if (i == 1 && j == 2) return false;
  if (i == 1 && j == 3) return false;
  if (i == 1 && j == 4) return false;
  if (i == 1 && j == 5) return false;
  if (i == 1 && j == 6) return false;
  if (i == 2 && j == 0) return false;
  if (i == 2 && j == 1) return true;
  if (i == 2 && j == 2) return false;
  if (i == 2 && j == 3) return false;
  if (i == 2 && j == 4) return false;
  if (i == 2 && j == 5) return false;
  if (i == 2 && j == 6) return false;
  if (i == 3 && j == 0) return true;
  if (i == 3 && j == 1) return true;
  if (i == 3 && j == 2) return true;
  if (i == 3 && j == 3) return false;
  if (i == 3 && j == 4) return false;
  if (i == 3 && j == 5) return true;
  if (i == 3 && j == 6) return false;
  if (i == 4 && j == 0) return true;
  if (i == 4 && j == 1) return true;
  if (i == 4 && j == 2) return true;
  if (i == 4 && j == 3) return true;
  if (i == 4 && j == 4) return false;
  if (i == 4 && j == 5) return false;
  if (i == 4 && j == 6) return false;
  if (i == 5 && j == 0) return true;
  if (i == 5 && j == 1) return true;
  if (i == 5 && j == 2) return true;
  if (i == 5 && j == 3) return false;
  if (i == 5 && j == 4) return true;
  if (i == 5 && j == 5) return false;
  if (i == 5 && j == 6) return false;
  if (i == 6 && j == 0) return true;
  if (i == 6 && j == 1) return true;
  if (i == 6 && j == 2) return true;
  if (i == 6 && j == 3) return true;
  if (i == 6 && j == 4) return true;
  if (i == 6 && j == 5) return true;
  if (i == 6 && j == 6) return false;
  assert(0);
}
