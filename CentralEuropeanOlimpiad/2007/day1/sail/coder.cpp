#include <cstdio>
#include <cassert>

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef unsigned char byte;

FILE *inpF, *outF;

int Code( int bits )
{
  if (bits < 26) return bits + 'a'; 
  if (bits < 52) return bits + 'A' - 26; 
  return bits + '0' - 52;
}

void Write( int bits )
{
  fputc(Code(bits), outF);
}

byte acc = 0;
int bn = 0;

void WriteBit( int b )
{
  acc |= b << bn++;
  if (bn == 6)
    Write(acc), bn = 0, acc = 0;
}

void Finalize()
{
  Write(acc);
}

const int MAX_LEN = 16777216;

byte buf[MAX_LEN];

int main( int argc, char *argv[] )
{
  if (argc < 3)
  {
    puts("Usage: <input> <output>");
    return 1;
  }

  printf("read from '%s' write to '%s'\n", argv[1], argv[2]);
  assert(inpF = fopen(argv[1], "rb"));
  assert(outF = fopen(argv[2], "wt"));

  fseek(inpF, 0, SEEK_END);
  long len = ftell(inpF);
  rewind(inpF);
  printf("len = %ld\n", len);

  assert(len <= MAX_LEN);
  assert(fread(buf, 1, len, inpF));
  fprintf(outF, "%ld\n", len);
  forn(i, len)
    forn(j, 8)
      WriteBit((buf[i] >> j) & 1);
  Finalize();

  fclose(inpF);
  fclose(outF);
  return 0;
}
