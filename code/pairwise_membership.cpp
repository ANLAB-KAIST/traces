// File: pairwise_membership.cpp
// Version: 1.0
//-----------------------------------------------------------------------------
// Based on the article "Mining communities in networks: a solution for consistency and its evaluation"
// Copyright (C) 2009 Haewoon Kwak, Yoonchan Choi, Young-Ho Eom, Hawoong Jeong, Sue Moon
//-----------------------------------------------------------------------------

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {
	const int MAX_NODE = 10000;
	int start_id, end_id;
	if (argc != 5) {
		cout << "Usage: " << argv[0] << " [edge_list] [start file id] [end file id] [output]" << endl;
		return 0;
	} else {
		start_id = atoi(argv[2]);
		end_id = atoi(argv[3]);
	}

	int **node2comm = new int*[end_id-start_id+1];
	for (int i = 0; i < end_id-start_id+1; i++) {
		node2comm[i] = new int[MAX_NODE];
	}

	string line;

	const string prefix = "real_node2comm_";	
	const string postfix = ".txt";
	int white_space_idx = 0;

	long int node;
	long int comm;

	for (int i = 1; i <= end_id-start_id+1; i++) {
		ostringstream ifilename;
		ifilename << prefix << i << postfix;
		ifstream inode2comm (ifilename.str().c_str());

		if (inode2comm.is_open()) {
			while(!inode2comm.eof()) {
				getline(inode2comm, line);
				if (line.size() == 0) {
					continue;
				}
				white_space_idx = line.find("\t");
				node = atoi(line.substr(0, white_space_idx).c_str());
				comm = atoi(line.substr(white_space_idx+1).c_str());
				node2comm[i-1][node] = comm;
			}
		} else {
			cout << "File open error: " << ifilename.str() << endl;
		}
		inode2comm.close();
	}

	ifstream edge_list (argv[1]);
	ofstream output (argv[4]);
	long int from, to;


	if (edge_list.is_open()) {
		while(!edge_list.eof()) {
			getline(edge_list, line);
			if (line.size() == 0) {
				continue;
			}
			white_space_idx = line.find("\t");

			from = atoi(line.substr(0, white_space_idx).c_str());
			to = atoi(line.substr(white_space_idx+1).c_str());
			int community_cnt = 0;

			for (int i = 1; i <= end_id-start_id+1; i++) {
				if (node2comm[i-1][from] == node2comm[i-1][to]) {
					community_cnt ++;
				}
			}

			output << from << "\t" << to << "\t" << ((float)community_cnt/(end_id-start_id+1)) << endl;
		}
	}
	
	edge_list.close();
	output.close();
	
}
