#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// this function prints out a binary files containing long long types

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
  
  unsigned long long hold;
  
  while (!feof(input))
  {
    fread(&hold, sizeof(unsigned long long), 1, input);
    printf("%llu ", hold);
  }
  
  printf("\n");
  
  fclose(input);
}