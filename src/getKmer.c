#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// this function gets kmers from reads in fasta format

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
  
  FILE *opf = fopen(argv[2], "w");
	

	long holdPos;
	char checkChar;
	char *printer = malloc(sizeof(char) * kmer);
  short printOp = 1;

	
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
			  
			  if (printer[i] == 'N' || printer[i] > 85)
			  {
			    printOp = 0;
			    break;
			  }
			}

			if (printOp == 1)
			{
			  fprintf(opf, "%s\n", printer);
			  // instead we want to print to a binary file here
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
