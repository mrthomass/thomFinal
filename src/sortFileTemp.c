#include <stdio.h>
#include <stdlib.h>

// this function takes in a binary of long longs and sorts them
  
int cmpfunc (const void * a, const void * b);

int main(int argc, char *argv[])
{
  if (argc < 3)
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
  
  short kmer;
  sscanf(argv[2], "%hi", &kmer);
  if (kmer < 2 || kmer > 32)
  {
    printf("INVALID KMER ARGUMENT\n");
    fclose(input);
    return(3);
  }
  // maybe have this find the kmer size from the binary file
  fseek(input, 0, SEEK_END);
  unsigned long len = ftell(input);
  rewind(input);
  // here we make the output file ^
  
  // this is if it is unsigned longs
  if (kmer > 16) 
  {
    unsigned long nll = len / sizeof(unsigned long long);
    unsigned long long *toSort = malloc(sizeof(unsigned long long) * nll);
    if (toSort == NULL)
    {
      fclose(input);
      return(3);
    }
    fread(toSort, sizeof(unsigned long long), nll, input);
    fclose(input);
    
    FILE *output = fopen(argv[1], "wb");
    qsort(toSort, nll, sizeof(unsigned long long), cmpfunc);
    fwrite(toSort, sizeof(unsigned long long), nll, output);
    free(toSort);
    fclose(output);
  }
  // this is if it is unsigned ints
  else
  {
    printf("USING SMALLER FORMAT SORT\n");
    unsigned long nll = len / sizeof(unsigned int);
    unsigned int *toSort = malloc(sizeof(unsigned int) * nll);
    if (toSort == NULL)
    {
      fclose(input);
      return(3);
    }
    fread(toSort, sizeof(unsigned int), nll, input);
    fclose(input);
    
    FILE *output = fopen(argv[1], "wb");
    qsort(toSort, nll, sizeof(unsigned int), cmpfunc);
    fwrite(toSort, sizeof(unsigned int), nll, output);
    free(toSort);
    fclose(output);
  }
  
  return(0);
}

int cmpfunc (const void * a, const void * b) 
{
  return ( *(long long int*)a - *(long long int*)b );
}
