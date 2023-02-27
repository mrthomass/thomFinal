#include <stdio.h>
#include <stdlib.h>

// this function takes in a binary of long longs and sorts them
  
int cmpfunc (const void * a, const void * b);

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("File Argument Required\n");
    return(1);
  }
  
  FILE *input = fopen(argv[1], "rb");
  if (input == NULL)
  {
    printf("INVALID FILE ARGUMENT\n");
    return(2);
  }
  
  fseek(input, 0, SEEK_END);
  unsigned long len = ftell(input);
  unsigned long nll = len / sizeof(unsigned long long);
  rewind(input);
  
  unsigned long long *toSort = malloc(sizeof(unsigned long long) * nll);
  if (toSort == NULL)
  {
    fclose(output);
    return(3);
  }
  fread(toSort, sizeof(unsigned long long), nll, input);
  
  fclose(input);
  
  qsort(toSort, nll, sizeof(unsigned long long), cmpfunc);

  FILE *output = fopen(argv[1], "wb");
  fwrite(toSort, sizeof(unsigned long long), nll, output);
  
  fclose(output);
  free(toSort);
  return(0);
}

int cmpfunc (const void * a, const void * b) 
{
  return ( *(long long int*)a - *(long long int*)b );
}
