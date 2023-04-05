#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <cstdlib>
#include <cstdio>
#include <iterator>
#include <functional>
#include <bitset>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char* what) : what(what){};
  __timestamper(const string& what) : what(what){};
  ~__timestamper(){
    TIMESTAMPf("%s", what.data());
	}
} __TIMESTAMPER("end");
#else 
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

uint8_t mem[(1 << 16) + 1];
uint16_t reg[16];
vector<string> ops;
#ifdef LOCAL
vector<function<void()>> ops_fun;
#endif

void add_op(string text_op, function<void()> fun_op) {
  ops.push_back(text_op);
#ifdef LOCAL
  ops_fun.push_back(fun_op);
  fun_op();
#endif
}

void set_to_const(int r, uint16_t value) {
  add_op("imm r" + to_string(r) + ", " + to_string(value), [=] { reg[r] = value;});
}

void load_to_reg(int reg_to, int reg_addr) {
  add_op("ld r" + to_string(reg_to) + ", r" + to_string(reg_addr), [=] {
    reg[reg_to] = ((uint16_t)mem[reg[reg_addr] + 1] << 8) | mem[reg[reg_addr]];
  });
}

int GLOB_J;
int GLOB_I;
int GLOB_N;

void dump(int l, int r, bool regs = true) {
#ifdef LOCAL
  if (regs) {
    for (int i = 0; i < 16; i++) {
      eprintf("R[%d] = %d\n", i, (int)reg[i]);
    }
  }
  for (int i = l; i < r; i++) {
    eprintf("%d ", mem[i]);
  }
  eprintf("\n");
#endif
}


void save_to_mem(int reg_from, int reg_addr) {
  add_op("st r" + to_string(reg_addr) + ", r" + to_string(reg_from), [=] {
    mem[reg[reg_addr]] = reg[reg_from] & 0xff;
    mem[reg[reg_addr] + 1] = reg[reg_from] >> 8;
    /*if (reg[reg_addr] < 2 * GLOB_N && reg[reg_addr] % 2 == 0 && mem[reg[reg_addr]] % 2 == 0) {
      eprintf("GLOB_I = %d, GLOB_J = %d, reg_addr = %d, val = %d\n", GLOB_I, GLOB_J, reg[reg_addr], mem[reg[reg_addr]]);
      dump(reg[reg_addr] - 10, reg[reg_addr] + 10);

//      assert(false);
    }*/
  });
}

const uint16_t OFF_BASE = (1 << 14);
const uint16_t OFF_MULT = OFF_BASE;
const uint16_t OFF_ARRAY_GET = OFF_BASE + 16;
const uint16_t OFF_LOAD8 = OFF_BASE + 32;
const uint16_t OFF_IF = OFF_BASE + 256;
const uint16_t OFF_TEMP_MUL = OFF_BASE + 256 * 2;
const uint16_t OFF_TEMP_N = OFF_BASE + 256 * 3;
const uint16_t ID_ARR_OFFSET = (1 << 15) / 256;
const uint16_t BITS_ARR_OFSET_FIRST = ID_ARR_OFFSET + 1;
const uint16_t ADD_POW2_ARR_OFFSET_FIRST = BITS_ARR_OFSET_FIRST + 8;
const uint16_t ZERO_ARR_OFFSET = ADD_POW2_ARR_OFFSET_FIRST + 8;
const uint16_t CARRY_ARR_OFFSET_FIRST = ZERO_ARR_OFFSET + 1;
const uint16_t N_PTR_ARR_OFFSET = CARRY_ARR_OFFSET_FIRST + 8;

// mem16[addr] = reg[r];
void save16(uint16_t addr, int r) {
  set_to_const(15, addr);
  save_to_mem(r, 15);
}


// reg[r] = mem16[addr]
void load16(uint16_t addr, int r) {
  set_to_const(15, addr);
  load_to_reg(r, 15);
}

void copy16(uint16_t src, uint16_t dest) {
  load16(src, 14);
  save16(dest, 14);
}


// reg[r] &= 0xff
void clean_hi(int r) {
  save16(OFF_LOAD8, r);
  set_to_const(14, 0);
  save16(OFF_LOAD8 + 1, 14);
  load16(OFF_LOAD8, r);
}

// reg[r] = mem8[addr]
void load8(uint16_t addr, int r) {
  copy16(addr, OFF_LOAD8);
  set_to_const(14, 0);
  save16(OFF_LOAD8 + 1, 14);
  load16(OFF_LOAD8, r);
}

// reg[to_reg] = mem8[reg[array_reg] * 256 + reg[offset_reg]]
void array_get16(int array_reg, int offset_reg, int to_reg) {
  save16(OFF_ARRAY_GET + 1, offset_reg);
  save16(OFF_ARRAY_GET + 2, array_reg);
  set_to_const(to_reg, OFF_ARRAY_GET + 1);
  load_to_reg(to_reg, to_reg);
  load_to_reg(to_reg, to_reg);
}

// reg[to_reg] = mem8[reg[array_reg] * 256 + reg[offset_reg]]
void array_get8(int array_reg, int offset_reg, int to_reg) {
  array_get16(array_reg, offset_reg, to_reg);
  clean_hi(to_reg);
}


void do_if_reg(int cond_reg, int r1, int r2, int to_reg) {
  static_assert(OFF_IF % 256 == 0);
  save16( OFF_IF, r1);
  save16( OFF_IF + 1, r2);
  set_to_const(8, OFF_IF / 256);
  array_get8(8, cond_reg, to_reg);
}


// reg[to_reg] = reg[cond_reg] ? on_true : on_false;
void do_if(int cond_reg, uint8_t on_false, uint8_t on_true, int to_reg) {
  static_assert(OFF_IF % 256 == 0);
#ifdef LOCAL
  assert(reg[cond_reg] == 0 || reg[cond_reg] == 1);
#endif
  set_to_const(8, on_false);
  save16( OFF_IF, 8);
  set_to_const(8, on_true);
  save16( OFF_IF + 1, 8);
  set_to_const(8, OFF_IF / 256);
  array_get8(8, cond_reg, to_reg);
}


// reg[r_res] = (reg[r_value] & (1 << bit)) != 0
void get_bit(int r_value, int bit, int r_res) {
  set_to_const(11, BITS_ARR_OFSET_FIRST + bit);
  array_get8(11, r_value, r_res);
}

// mem8[addr3] = mem8[addr1] + mem8[addr2], drop overflow
void add8(uint16_t addr1, uint16_t addr2, uint16_t addr3) {
  load8(addr1, 13);
  load8(addr2, 10);
  for (int i = 0; i < 8; i++) {
    get_bit(10, i, 12);
    do_if(12, ID_ARR_OFFSET, ADD_POW2_ARR_OFFSET_FIRST + i, 11);
    array_get8(11, 13, 13);
  }
  save16(addr3, 13);
}

// mem16[addr3] = mem8[addr1] * mem8[addr2]
void multiply8(uint16_t addr1, uint16_t addr2, uint16_t addr3) {
  set_to_const(6, 0);
  set_to_const(5, 0);
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (i + j < 8) {
        load8(addr1, 7);
        get_bit(7, i, 4);
        do_if(4, ZERO_ARR_OFFSET, CARRY_ARR_OFFSET_FIRST + (i + j), 3);
        set_to_const(2, ZERO_ARR_OFFSET);
        load8(addr2, 7);
        get_bit(7, j, 4);
        do_if_reg(4, 2, 3, 1);
        array_get8(1, 5, 1);
        do_if(1, ID_ARR_OFFSET, ADD_POW2_ARR_OFFSET_FIRST, 3);
        array_get8(3, 6, 6);

        load8(addr1, 7);
        get_bit(7, i, 4);
        do_if(4, ID_ARR_OFFSET, ADD_POW2_ARR_OFFSET_FIRST + (i + j), 3);
        set_to_const(2, ID_ARR_OFFSET);
        load8(addr2, 7);
        get_bit(7, j, 4);
        do_if_reg(4, 2, 3, 1);
        array_get8(1, 5, 5);
      } else {
        load8(addr1, 7);
        get_bit(7, i, 4);
        do_if(4, ID_ARR_OFFSET, ADD_POW2_ARR_OFFSET_FIRST + (i + j - 8), 3);
        set_to_const(2, ID_ARR_OFFSET);
        load8(addr2, 7);
        get_bit(7, j, 4);
        do_if_reg(4, 2, 3, 1);
        array_get8(1, 6, 6);
      }
    }
  }
  save16(OFF_TEMP_MUL, 5);
  save16(OFF_TEMP_MUL + 1, 6);
  copy16(OFF_TEMP_MUL, addr3);
}

// mem16[addr3] = mem16[addr1] * mem16[addr2]
void multiply16(uint16_t addr1, uint16_t addr2, uint16_t addr3) {
  multiply8(addr1, addr2, OFF_MULT);
  multiply8(addr1 + 1, addr2, OFF_MULT + 2);
  multiply8(addr1, addr2 + 1, OFF_MULT + 4);
  add8(OFF_MULT + 1, OFF_MULT + 2, OFF_MULT + 1);
  add8(OFF_MULT + 1, OFF_MULT + 4, OFF_MULT + 1);
  copy16(OFF_MULT, addr3);
}

// mem16[addr3] = mem16[addr1] * mem16[addr2]
void multiply16_by_2(uint16_t addr1, uint16_t addr2, uint16_t addr3) {
  multiply8(addr1, addr2, OFF_MULT);
  multiply8(addr1 + 1, addr2, OFF_MULT + 2);
  add8(OFF_MULT + 1, OFF_MULT + 2, OFF_MULT + 1);
  copy16(OFF_MULT, addr3);
}



void init() {
  for (int i = 0; i < 256; i++) {
    set_to_const(14, i);
    save16(ID_ARR_OFFSET * 256 + i, 14);
  }
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 256; j++) {
      set_to_const(14, (j >> i) & 1);
      save16((BITS_ARR_OFSET_FIRST + i) * 256 + j, 14);
    }
  }
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 256; j++) {
      set_to_const(14, (j + (1 << i)) & 0xff);
      save16((ADD_POW2_ARR_OFFSET_FIRST + i) * 256 + j, 14);
    }
  }
  for (int i = 0; i < 256; i++) {
    set_to_const(14, 0);
    save16(ZERO_ARR_OFFSET * 256 + i, 14);
  }
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 256; j++) {
      set_to_const(14, (j + (1 << i)) / 256);
      save16((CARRY_ARR_OFFSET_FIRST + i) * 256 + j, 14);
    }
  }
}


int main() {
#ifdef LOCAL
  freopen("l.in", "r", stdin);
  freopen("l.out", "w", stdout);
  int n;
  scanf("%d", &n);
  reg[0] = n;
  GLOB_N = n;
  int yy = 1;
  for (int i = 0; i < n; i++) {
    int x;
    //scanf("%d", &x);
    x = 1;//(rand() & 0x7fff) * 2 + 1;
    yy = (yy * x) & 0xffff;
    mem[2 * i] = x & 0xff;
    mem[2 * i + 1] = x >> 8;
  }
  eprintf("result = %d\n", yy);
#endif

  vector<int> copy;

  dump(0, 6, false);
  init();
  set_to_const(1, OFF_TEMP_N + 6);
  save16(N_PTR_ARR_OFFSET * 256, 1);
  set_to_const(1, OFF_TEMP_N + 8);
  save16(N_PTR_ARR_OFFSET * 256 + 2, 1);
  load8(OFF_TEMP_N + 4, 1);
  ops_fun.push_back([&] {
    eprintf("reg[1] = %d\n", reg[1]);
    assert(copy == vector<int>(mem, mem + 2 * n));
  });
  set_to_const(2, N_PTR_ARR_OFFSET);
  ops_fun.push_back([&] {
    assert(copy == vector<int>(mem, mem + 2 * n));
  });
  array_get16(2, 1, 1);
  eprintf("!!!\n");
  dump(N_PTR_ARR_OFFSET * 256, N_PTR_ARR_OFFSET * 256 + 4, false);
  ops_fun.push_back([&] {
    assert(copy == vector<int>(mem, mem + 2 * n));
  });
  save_to_mem(0, 1);
  ops_fun.push_back([&] {
    assert(copy == vector<int>(mem, mem + 2 * n));
  });
  set_to_const(1, 1);
  ops_fun.push_back([&] {
    assert(copy == vector<int>(mem, mem + 2 * n));
  });
  save16(OFF_TEMP_N + 4, 2);
  ops_fun.push_back([&] {
    assert(copy == vector<int>(mem, mem + 2 * n));
  });
  set_to_const(1, 2);
  ops_fun.push_back([&] {
    assert(copy == vector<int>(mem, mem + 2 * n));
  });
  save16(OFF_TEMP_N + 10, 1);
  ops_fun.push_back([&] {
    assert(copy == vector<int>(mem, mem + 2 * n));
  });
  multiply16_by_2(OFF_TEMP_N + 6, OFF_TEMP_N + 10, OFF_TEMP_N);

  ops_fun.push_back([&] {
    assert(copy == vector<int>(mem, mem + 2 * n));
  });

  eprintf("%d commands\n", (int)ops.size());
  set_to_const(1, 1);
  save16(OFF_TEMP_N + 2, 1);
  for (int j = 0; j < 2; j++) {
    load16(OFF_TEMP_N, 0);
    set_to_const(1, !j);
    save_to_mem(1, 0);

    load8(OFF_TEMP_N, 0);
    load8(OFF_TEMP_N + 1, 1);
    set_to_const(2, CARRY_ARR_OFFSET_FIRST);
    array_get8(2, 0, 2);
    do_if(2, ID_ARR_OFFSET, ADD_POW2_ARR_OFFSET_FIRST, 3);
    array_get8(3, 1, 1);
    set_to_const(2, ADD_POW2_ARR_OFFSET_FIRST);
    array_get8(2, 0, 0);
    save16(OFF_TEMP_MUL, 0);
    save16(OFF_TEMP_MUL + 1, 1);
    copy16(OFF_TEMP_MUL, OFF_TEMP_N);
  }
  ops_fun.push_back([&] {
    assert(copy == vector<int>(mem, mem + 2 * n));
  });


  eprintf("%d commands\n", (int)ops.size());
  ops_fun.push_back([&] {
    copy = vector<int>(mem + 2, mem + 2 * n);
  });
  multiply16(0, 2, 0);
  ops_fun.push_back([&] {
    assert(copy == vector<int>(mem + 2, mem + 2 * n));
  });
  eprintf("%d commands\n", (int)ops.size());
  ops_fun.push_back([&] {
    copy = vector<int>(mem + 4, mem + 2 * n);
  });
  for (int i = 1; i < 4042; i++) {
    copy16(2 * i + 2, 2 * i);
  }
  ops_fun.push_back([&] {
    assert(copy == vector<int>(mem + 2, mem + 2 * n - 2));
  });
  eprintf("%d commands\n", (int)ops.size());
  load16(0, 0);
  eprintf("%d commands\n", (int)ops.size());

  printf("%d\n", (int)ops.size());
  for (const auto& s : ops) {
    printf("%s\n", s.c_str());
  }

#ifdef LOCAL
  eprintf("done in %d commands\n", (int)ops.size());
  for (int i = 0; i < 4999; i++) {
    //dump(0, 2200, false);
    for (int j = 0; j < (int)ops_fun.size(); j++) {
      GLOB_I = i;
      GLOB_J = j;
      ops_fun[j]();
    }
  }
  eprintf("%d\n", reg[0]);
  assert(reg[0] == yy);
#endif
  return 0;
}
