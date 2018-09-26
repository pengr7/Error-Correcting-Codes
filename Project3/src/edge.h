// 'edge.h'
// implementation of each edge in trellis by Peng Rui

#ifndef EDGE_H
#define EDGE_H

#include "headers.h"

// when 'input_bits' input, the state can change from 'from_state' to 'to_state' with 'output_bits' output
class edge {
	public:
		int from_state;
		int to_state;
		vector<int> input_bits;
		vector<int> output_bits;
		edge() {}
		edge(int _from_state, int _to_state, vector<int> _input_bits, vector<int> _output_bits) {
			from_state = _from_state;
			to_state = _to_state;
			input_bits = _input_bits;
			output_bits = _output_bits;
		}
		void print() {
			cout << "        edge printer:" << endl;
			cout << "            from state: " << from_state << endl;
			cout << "            to state: " << to_state << endl;
			cout << "            input bits: {";
			vector<int>::iterator it, temp;
			for (it = input_bits.begin(); it != input_bits.end(); it++) {
				if (*it > 0)
					cout << "+";
				cout << *it;
				if (++(temp = it) != input_bits.end())
					cout << ", ";
			}
			cout << "}" << endl << "            output bits: {";
			for (it = output_bits.begin(); it != output_bits.end(); it++) {
				if (*it > 0)
					cout << "+";
				cout << *it;
				if (++(temp = it) != output_bits.end())
					cout << ", ";
			}
			cout << "}" << endl;
		}
};

#endif  // EDGE_H

