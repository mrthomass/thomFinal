#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// this function gets kmers from reads in fasta format
unsigned long long change(char *inp);

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
	
	// STRAIGHTEN ALL THIS INFORMATION UP
	
	long sizeFileArg = strlen(argv[1]);
	if (argv[1][sizeFileArg - 1] == 'q')
	{
	  printf("this is a fastq file.\n");
	  // since unsupported at this time
	  fclose(f);
	  return(0);
	}
	if (argv[1][sizeFileArg - 1] != 'q' && argv[1][sizeFileArg - 1] != 'a')
	{
	  printf("INPUT FILE TYPE UNKNOWN\n");
	  fclose(f);
	  return(4);
	}
	
	// ^^ STRAIGHTEN ALL THIS INFORMATION UP
	
	short kmer;
	sscanf(argv[3], "%hi", &kmer);
  if (kmer < 2 || kmer > 32)
  {
    printf("INVALID KMER ARGUMENT\n");
    fclose(f);
    return(3);
  }
  
  FILE *opf = fopen(argv[2], "wb");
	

	long holdPos;
	char checkChar;
	char *printer = malloc(sizeof(char) * kmer);
  short printOp = 1;
  unsigned long long cap;

	
	while (!feof(f))
	{

		fscanf(f, ">%*[^\n]\n");
		checkChar = 'a';

		while (checkChar != 10)
		{
	
			holdPos = ftell(f);
			fseek(f, holdPos + kmer, SEEK_SET);
			fscanf(f, "%c", &checkChar);
			fseek(f, holdPos, SEEK_SET);

			for (int i = 0; i < kmer; i++)
			{
			  fscanf(f, "%c", &printer[i]);
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
			  fwrite(&cap, sizeof(unsigned long long), 1, opf);
			  // this is where we will instead print to a binary file
			}
			else
			{
			  printOp = 1;
			}


			fseek(f, holdPos + 1, SEEK_SET); // go back
		}
		
		fscanf(f, "%*[^\n]\n");

	}

	fclose(f);
	fclose(opf);
	free(printer);

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
