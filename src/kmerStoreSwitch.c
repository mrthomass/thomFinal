#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// this function gets kmers from reads in fasta format
// then it exports them to either a 4 byte unsigned int binary file or
// a 8 byte unsigned long binary file depending on the kmer size (> 16 or not)

// looming bug, will only stop while loop IF there is a newline '\n' at end of input file


unsigned long long changeLL(char *inp);
unsigned int changeI(char *inp);
int getFastaLL(FILE *inp, FILE *opt, short k);
int getFastaI(FILE *inp, FILE *opt, short k);
int getFastqLL(FILE *inp, FILE *opt, short k);
int getFastqI(FILE *inp, FILE *opt, short k);
unsigned int powFour(int a);

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
	  if (kmer > 16)
	  {
	    getFastaLL(f, opf, kmer);
	  }
	  else
	  {
	    getFastaI(f, opf, kmer);
	  }
	  
	}
	if (argv[1][sizeFileArg - 1] == 'q')
	{
	  // run the fastq code
	  if (kmer > 16)
	  {
	    getFastqLL(f, opf, kmer);
	  }
	  else
	  {
	    getFastqI(f, opf, kmer);
	  }
	  
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


// encoder functions::
unsigned long long changeLL(char *inp)
{
  unsigned long long opt = 0;
  unsigned long scale = 1;
  for (int i = 0; i < strlen(inp); i++)
  {
    opt = opt + (inp[i]%5 + inp[i]%2 - 1) * scale;
    scale = scale * 4;
  }
  return(opt);
}

unsigned int changeI(char *inp)
{
  unsigned int opt = 0;
  unsigned int scale = 1;
  for (int i = 0; i < strlen(inp); i++)
  {
    opt = opt + (inp[i]%5 + inp[i]%2 - 1) * scale;
    scale = scale * 4;
  }
  return(opt);
}
// encoder functions::



// this file does the heavy lifting if the input is a `fastA` file
int getFastaLL(FILE *inp, FILE *opt, short k)
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
        cap = changeLL(printer);
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

int getFastaI(FILE *inp, FILE *opt, short k)
{
  long holdPos;
  char checkChar;
  char *printer = malloc(sizeof(char) * k);
  short printOp = 1;
  unsigned int cap;

  
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
        cap = changeI(printer);
        fwrite(&cap, sizeof(unsigned int), 1, opt);
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
int getFastqLL(FILE *inp, FILE *opt, short k)
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
        cap = changeLL(printer);
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

int getFastqI(FILE *inp, FILE *opt, short k)
{
  long holdPos;
  char checkChar;
  char *printer = malloc(sizeof(char) * k);
  short printOp = 1;
  unsigned int cap;
  
  
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
        cap = changeI(printer);
        fwrite(&cap, sizeof(unsigned int), 1, opt);
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
