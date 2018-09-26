// 'decoder.h'
// implementation of the BCJR decoder by Peng Rui

#ifndef DECODER_H
#define DECODER_H

#include "trellis.h"

namespace my_debugger {
	void branch_metrics_printer(vector<map<pair<int, int>, double> > branch_metrics) {
		cout << "branch metrics printer:" << endl;
		for (int i = 0; i < (int)branch_metrics.size(); i++)
			for (map<pair<int, int>, double>::iterator it = branch_metrics[i].begin(); it != branch_metrics[i].end(); it++)
				cout << i << " (S" << it->first.first << ", S" << it->first.second << "):   " << it->second << endl;
		cout << endl;
	}
	void forward_metrics_printer(vector<map<int, double> > forward_metrics) {
		cout << "forward metrics printer:" << endl;
		for (int i = 0; i < (int)forward_metrics.size(); i++)
			for (map<int, double>::iterator it = forward_metrics[i].begin(); it != forward_metrics[i].end(); it++)
				cout << i << " (S" << it->first << "):   " << it->second << endl;
		cout << endl;
	}
	void backward_metrics_printer(vector<map<int, double> > backward_metrics) {
		cout << "backward metrics printer:" << endl;
		for (int i = backward_metrics.size() - 1; i >= 0; i--)
			for (map<int, double>::iterator it = backward_metrics[i].begin(); it != backward_metrics[i].end(); it++)
				cout << i << " (S" << it->first << "):   " << it->second << endl;
		cout << endl;
	}
}

double max_helper(vector<double> vec) {
	double result = 0;
	for (double temp : vec)
		result += exp(temp);
	return log(result);
} 

vector<vector<int> > decode(vector<vector<double> > received, trellis tr) {
	int nodes = tr.data.size();
	int size = received.size();
	int output_size = tr.data[0].next.begin()->second.output_bits.size();
	vector<vector<int> > result(size);

	// compute the log-domain branch metrics
	// assume that the priori probabilities of the information bits are equally likely
	vector<map<pair<int, int>, double> > branch_metrics(size);
	for (int i = 0; i < size; i++)
		for (int j = 0; j < nodes; j++) {
			for (int k = 0; k < nodes; k++) {
				for (map<vector<int>, edge>::iterator it = tr.data[j].next.begin(); it != tr.data[j].next.end(); it++)
					if (it -> second.to_state == k)
						for (int l = 0; l < output_size; l++)
							branch_metrics[i][pair<int, int>(j, k)] += received[i][l] * tr.data[j].next[it -> second.input_bits].output_bits[l] / 2;
				if (i == size - 1)
					break;
			}
			if (i == 0)
				break;
		}
	my_debugger::branch_metrics_printer(branch_metrics);

	// compute the log-domain forward metrics
	vector<map<int, double> > forward_metrics(size);
	for (int i = 1; i < size; i++) {
		for (int j = 0; j < nodes; j++) {
			vector<double> temp;
			for (int k = 0; k < nodes; k++)
				if (branch_metrics[i - 1][pair<int, int>(k, j)])
					temp.push_back(branch_metrics[i - 1][pair<int, int>(k, j)] + forward_metrics[i - 1][k]);
			forward_metrics[i][j] = max_helper(temp);
		}
	}
	my_debugger::forward_metrics_printer(forward_metrics);

	// compute the log-domain backward metrics
	vector<map<int, double> > backward_metrics(size);
	for (int j = 0; j < nodes; j++)
		backward_metrics[size - 1][j] = branch_metrics[size - 1][pair<int, int>(j, 0)];
	for (int i = size - 2; i >= 0; i--) {
		for (int j = 0; j < nodes; j++) {
			vector<double> temp;
			for (int k = 0; k < nodes; k++)
				if (branch_metrics[i][pair<int, int>(j, k)])
					temp.push_back(branch_metrics[i][pair<int, int>(j, k)] + backward_metrics[i + 1][k]);
			backward_metrics[i][j] = max_helper(temp);
		}
	}
	my_debugger::backward_metrics_printer(backward_metrics);
	
	// compute the APP L-values for the imformation bits
	vector<double> app_l_values(size);
	for (int i = 0; i < size - 1; i++)
		app_l_values[i] = sqrt((double)i);
	my_debugger::print_vector(app_l_values);
	
	return result;
}

#endif  // DECODER_H

