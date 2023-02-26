#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// this function gets the counts of each unique read

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("NEED BINARY LONG LONG FILE ARGUMENT\n");
    return(1);
  }
  
  FILE *inp = fopen(argv[1], "rb");
  if (inp == NULL)
  {
    printf("FILE DOES NOT EXIST\n");
    return(2);
  }
  
  FILE *out = fopen("testOrg.thom", "w");
  
  unsigned long long hold; 
  // fscanf(inp, "%c\n", &hold);
  fread(&hold, sizeof(unsigned long long), 1, inp);
  unsigned long long buff;
  unsigned int count = 1;
  
  while (!feof(inp))
  {
    //fscanf(inp, "%c\n", &buff);
    fread(&buff, sizeof(unsigned long long), 1, inp);
    if (buff == hold)
    {
      count++;
    }
    if (buff != hold)
    {
      fprintf(out, "%llu,%u\n", hold, count);
      hold = buff;
      count = 1;
    }
  }
  
  fprintf(out, "%llu,%u\n", hold, count);
  
  fclose(inp);
  fclose(out);
  return(0);
}
