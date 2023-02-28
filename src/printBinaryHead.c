#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// this function prints out a binary files containing long long types

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
  
  if (kmer > 16)
  {
    unsigned long long hold;
    
    for (int i = 0; i < 10; i++)
    {
      fread(&hold, sizeof(unsigned long long), 1, input);
      printf("%llu ", hold);
    }
    
    printf("\n");
  }
  else
  {
    unsigned int hold;
    for (int i = 0; i < 10; i++)
    {
      fread(&hold, sizeof(unsigned int), 1, input);
      printf("%u ", hold);
    }
    printf("\n");
  }
  
  fclose(input);
}