// File: shuffling_wedges.c
// Version: 1.0
//-----------------------------------------------------------------------------
// Based on the article "Mining communities in networks: a solution for consistency and its evaluation"
// Copyright (C) 2009 Haewoon Kwak, Yoonchan Choi, Young-Ho Eom, Hawoong Jeong, Sue Moon
//-----------------------------------------------------------------------------

#define MAX_NODE_NUM	20000000
#define SHUFFLE_NUM		100

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int random_order[MAX_NODE_NUM];

int main(int argc, char *argv[])
{
	FILE *fp_in;
	FILE *fp_out;
	char filename[50];

	int i, j;

	int rand_pos;
	int tmp;

	int self_ID;
	int neighbor_ID;
	float weight;

	int node_num;
	int edge_num;

	int start_ID;
	int end_ID;


	// check the argument
	if(argc != 5)
	{
		fprintf(stderr, "Usage: %s [network file] [edge file] [start file ID] [end file ID]\n", argv[0]);
		exit(1);
	} else {
		start_ID = atoi(argv[3]);
		end_ID = atoi(argv[4]);
	}
	

	if((fp_in = fopen(argv[1], "r")) == NULL)
	{
		fprintf(stderr,"file open error...\n");
		exit(1);
	}

	fscanf(fp_in, "%d%d", &node_num, &edge_num);
	fclose(fp_in);


	for(i = 0; i < node_num; i++)
	{
		random_order[i] = i;
	}

	srand(time(NULL));
	for(i = start_ID; i <= end_ID; i++)
	{
		for(j = 0; j < node_num - 1; j++)
		{
			rand_pos = rand() % (node_num - j) + j;
			tmp = random_order[j];

			random_order[j] = random_order[rand_pos];
			random_order[rand_pos] = tmp;
		}

		if((fp_in = fopen(argv[2],"r")) == NULL)
		{
			fprintf(stderr,"file open error...\n");
			exit(1);
		}

		sprintf(filename, "shuffle_%d.pairs", i);
		if((fp_out = fopen(filename,"w")) == NULL)
		{
			fprintf(stderr,"file open error...\n");
			exit(1);
		}

		while(!feof(fp_in))
		{
			if(fscanf(fp_in, "%d%d%f", &self_ID, &neighbor_ID, &weight) == -1)
			{
				break;
			}

			fprintf(fp_out, "%d\t%d\t%d\n", random_order[self_ID], random_order[neighbor_ID], (int)(weight*100));
		}

		fclose(fp_in);
		fclose(fp_out);

		sprintf(filename, "shuffle_convert_%d.txt", i);
		if((fp_out = fopen(filename,"w")) == NULL)
		{
			fprintf(stderr,"file open error...\n");
			exit(1);
		}

		for(j = 0; j < node_num; j++)
		{
			fprintf(fp_out, "%d\t%d\n", j, random_order[j]);
		}

		fclose(fp_out);
		fprintf(stderr,"%d shuffles created...\n", i);
	}
}
