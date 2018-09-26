// 'trellis.h'
// implementation of trellis by Peng Rui
// you can modify the trellis in 'trellis.txt'

#ifndef TRELLIS_H
#define TRELLIS_H

#include "node.h"

class trellis {
	public:
		vector<node> data;
		trellis() {
			read_from_file();
		}
		void read_from_file() {
			ifstream file("trellis.txt");
			string line, type;
			node temp_node(INT_MAX);
			int state, to_state, temp_int;
			vector<int> input_bits, output_bits;
			while (getline(file, line)) {
				if (line == "")
					continue;
				stringstream ss(line);
				ss >> type;
				if (type == "state") {
					temp_node.clear();
					ss >> state;
					temp_node.set_state(state);
				}
				if (type == "to_state") {
					input_bits.clear();
					output_bits.clear();
					ss >> to_state;
				}
				if (type == "input")
					while (ss >> temp_int)
						input_bits.push_back(temp_int);
				if (type == "output")
					while (ss >> temp_int)
						output_bits.push_back(temp_int);
				if (type == "to_state_end")
					temp_node.set_next_state(to_state, input_bits, output_bits);
				if (type == "state_end")
					data.push_back(temp_node);
			}
		}
		void print() {
			cout << "trellis printer:" << endl;
			for (int i = 0; i < (int)data.size(); i++)
				data[i].print();
		}
};

#endif  // TRELLIS_H

