// File: consistency.c
// Version: 1.0
//-----------------------------------------------------------------------------
// Based on the article "Mining communities in networks: a solution for consistency and its evaluation"
// Copyright (C) 2009 Haewoon Kwak, Yoonchan Choi, Young-Ho Eom, Hawoong Jeong, Sue Moon
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	FILE *fn_in;

	int row, column;
	float sim;

	double num_pairs = 0;
	double sum  = 0;
	double consistency = 0;
	double diff = 0;
	
	if(argc != 2) {
		printf("Usage: %s[pairwise membership file]\n", argv[0]);
		exit(1);
	}

	if((fn_in = fopen(argv[1],"r")) == NULL) {
		fprintf(stderr,"file open error...\n");
		exit(1);
	}

	while(0 < fscanf(fn_in, "%d %d %f", &row, &column, &sim)) {
		diff = (double)sim - 0.5;
		num_pairs += 1;
		sum += (diff * diff);
	}

	consistency = (sum / num_pairs) * 4;
	fclose(fn_in);

	printf("number of pairs: %lf\n", num_pairs);
	printf("%lf\n", consistency);
}
