#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// this function gets the counts of each unique read

int main(int argc, char *argv[])
{
  if (argc < 4)
  {
    printf("NEED BINARY LONG LONG FILE ARGUMENT FOR INPUT AND TEXT FILE AS OUTPUT\n");
    return(1);
  }
  
  FILE *inp = fopen(argv[1], "rb");
  if (inp == NULL)
  {
    printf("FILE DOES NOT EXIST\n");
    return(2);
  }
  
  short kmer;
  sscanf(argv[3], "%hi", &kmer);
  if (kmer < 2 || kmer > 32)
  {
    printf("INVALID KMER ARGUMENT\n");
    fclose(inp);
    return(3);
  }
  
  FILE *out = fopen(argv[2], "w");
  
  // large size files in the binary file
  if (kmer > 16)
  {
    unsigned long long hold; 
    fread(&hold, sizeof(unsigned long long), 1, inp);
    unsigned long long buff;
    unsigned int count = 1;
    
    while (!feof(inp))
    {

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
  }
  // smaller size objects in the binary file
  else
  {
    printf("USING SMALLER FORMAT SIMPLIFIER\n");
    unsigned int hold; 
    fread(&hold, sizeof(unsigned int), 1, inp);
    unsigned int buff;
    unsigned int count = 1;
    
    while (!feof(inp))
    {
      fread(&buff, sizeof(unsigned int), 1, inp);
      if (buff == hold)
      {
        count++;
      }
      if (buff != hold)
      {
        fprintf(out, "%u,%u\n", hold, count);
        hold = buff;
        count = 1;
      }
    }
    
    fprintf(out, "%u,%u\n", hold, count);
  }
  
  fclose(inp);
  fclose(out);
  return(0);
}
