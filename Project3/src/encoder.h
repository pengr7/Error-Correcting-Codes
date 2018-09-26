// 'encoder.h'
// implementation of the encoder by Peng Rui

#ifndef ENCODER_H
#define ENCODER_H

#include "trellis.h"

vector<vector<int> > encode(vector<vector<int> > input, trellis tr) {
	vector<vector<int> > result;
	int state = 0;
	for (int i = 0; i < (int)input.size(); i++) {
		result.push_back(tr.data[state].next[input[i]].output_bits);
		state = tr.data[state].next[input[i]].to_state;
	}
	return result;
}

namespace my_debugger {
	template <typename T>
	void print_vector(vector<T> vec) {
		for (int i = 0; i < (int)vec.size(); i++) {
			if (vec[i] > 0)
				cout << "+";
			cout << vec[i] << " ";
		}
		cout << endl;
	}
	template <typename T>
	void print_vector(vector<vector<T> > vec) {
		for (int i = 0; i < (int)vec.size(); i++)
			print_vector(vec[i]);
		cout << endl;
	}
}

#endif  // ENCODER_H

