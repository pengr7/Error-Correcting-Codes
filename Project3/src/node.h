// 'node.h'
// implementation of each node in trellis by Peng Rui

#ifndef NODE_H
#define NODE_H

#include "edge.h"

class node {
	public:
		int state;
		map<vector<int>, edge> next;
		node(int _state) {
			state = _state;
		}
		void set_state(int _state) {
			state = _state;
		}
		void set_next_state(int _to_state, vector<int> _input_bits, vector<int> _output_bits) {
			next[_input_bits] = edge(state, _to_state, _input_bits, _output_bits);
		}
		void print() {
			cout << "    node printer:" << endl;
			cout << "        state: " << state << endl;
			for (map<vector<int>, edge>::iterator it = next.begin(); it != next.end(); it++)
				it -> second.print();
		}
		void clear() {
			next.clear();
		}
};

#endif  // NODE_H

