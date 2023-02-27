#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// this function gets kmers from reads in fasta format
unsigned long long change(char *inp);
int getFasta(FILE *inp, FILE *opt, short k);
int getFastq(FILE *inp, FILE *opt, short k);

int main(int argc, char *argv[])
{

	if (argc < 4)
	{
	  // need the input file, output file and kmer size `k` as args
		printf("File Argument Required\n");
		return(1);
	}

	FILE *f = fopen(argv[1], "r");
	if (f == NULL)
	{
		printf("INVALID FILE ARGUMENT\n");
		return(2);
	}
	
	short kmer;
	sscanf(argv[3], "%hi", &kmer);
	if (kmer < 2 || kmer > 32)
	{
	  printf("INVALID KMER ARGUMENT\n");
	  fclose(f);
	  return(3);
	}
	
	// STRAIGHTEN ALL THIS INFORMATION UP
	FILE *opf = fopen(argv[2], "wb");
	
	long sizeFileArg = strlen(argv[1]);
	if (argv[1][sizeFileArg - 1] == 'a')
	{
	  // run the fasta code
	  getFasta(f, opf, kmer);
	  // maybe check for error here too...
	}
	if (argv[1][sizeFileArg - 1] == 'q')
	{
	  // run the fastq code
	  getFastq(f, opf, kmer);
	  
	}
	if (argv[1][sizeFileArg - 1] != 'q' && argv[1][sizeFileArg - 1] != 'a')
	{
	  // throw an error
	  printf("INPUT FILE TYPE UNKNOWN\n");
	  fclose(f);
	  return(4);
	}

	fclose(f);
	fclose(opf);
	return(0);
}

// this file converts a max-32mer into a long long easily storeable
unsigned long long change(char *inp)
{
  unsigned long long opt = 0;
  for (int i = 0; i < strlen(inp); i++)
  {
    opt = opt + inp[i] * 4 * i;
  }
  return(opt);
}

// this file does the heavy lifting if the input is a `fastA` file
int getFasta(FILE *inp, FILE *opt, short k)
{
  long holdPos;
  char checkChar;
  char *printer = malloc(sizeof(char) * k);
  short printOp = 1;
  unsigned long long cap;
  
  
  while (!feof(inp))
  {
    
    fscanf(inp, ">%*[^\n]\n");
    checkChar = 'a';
    
    while (checkChar != 10) 
    {
      
      holdPos = ftell(inp);
      fseek(inp, holdPos + k, SEEK_SET);
      fscanf(inp, "%c", &checkChar);
      fseek(inp, holdPos, SEEK_SET);
      
      for (int i = 0; i < k; i++)
      {
        fscanf(inp, "%c", &printer[i]);
        // some ambiguity here, if there was another major error it would notice
        if (printer[i] == 'N' || printer[i] > 85)
        {
          printOp = 0;
          break;
        }
      }
      
      if (printOp == 1)
      {
        cap = change(printer);
        fwrite(&cap, sizeof(unsigned long long), 1, opt);
        // this is where we will instead print to a binary file
      }
      else
      {
        printOp = 1;
      }
      
      
      fseek(inp, holdPos + 1, SEEK_SET); // go back
    }
    
    fscanf(inp, "%*[^\n]\n");
    
  }
  free(printer);
  return(0);
}


// this file does the heavy lifting if the input is a `fastQ` file
int getFastq(FILE *inp, FILE *opt, short k)
{
  long holdPos;
  char checkChar;
  char *printer = malloc(sizeof(char) * k);
  short printOp = 1;
  unsigned long long cap;
  
  
  while (!feof(inp))
  {
    
    fscanf(inp, "@%*[^\n]\n"); // change here too
    checkChar = 'a';
    
    while (checkChar != 10) 
    {
      
      holdPos = ftell(inp);
      fseek(inp, holdPos + k, SEEK_SET);
      fscanf(inp, "%c", &checkChar);
      fseek(inp, holdPos, SEEK_SET);
      
      for (int i = 0; i < k; i++)
      {
        fscanf(inp, "%c", &printer[i]);
        // some ambiguity here, if there was another major error it would notice
        if (printer[i] == 'N' || printer[i] > 85)
        {
          printOp = 0;
          break;
        }
      }
      
      if (printOp == 1)
      {
        cap = change(printer);
        fwrite(&cap, sizeof(unsigned long long), 1, opt);
        // this is where we will instead print to a binary file
      }
      else
      {
        printOp = 1;
      }
      
      
      fseek(inp, holdPos + 1, SEEK_SET); // go back
    }
    
    fscanf(inp, "%*[^\n]\n%*[^\n]\n%*[^\n]\n"); // this is whats different between fasta
    
  }
  free(printer);
  return(0);
}
