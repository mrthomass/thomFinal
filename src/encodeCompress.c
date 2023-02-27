#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// this function transfers kmers in text to binary

unsigned long long change(char *inp);

int main(int argc, char *argv[])
{
  if (argc < 3)
  {
    // need the input file, output file 
    printf("File Argument Required\n");
    return(1);
  }
  
  FILE *input = fopen(argv[1], "r");
  if (input == NULL)
  {
    printf("INVALID FILE ARGUMENT\n");
    return(2);
  }
  
  FILE *output = fopen(argv[2], "wb");
  
  char *hold = malloc(sizeof(char) * 21);
  unsigned long long cap;
  
  while (!feof(input))
  {
    fscanf(input, "%s\n", hold);
    cap = change(hold);
    fwrite(&cap, 8, 1, output);
  }
  
  fclose(input);
  fclose(output);
  free(hold);
}

unsigned long long change(char *inp)
{
  unsigned long long opt = 0;
  for (int i = 0; i < strlen(inp); i++)
  {
    opt = opt + inp[i] * 4 * i;
  }
  return(opt);
}