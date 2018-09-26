// 'channel.h'
// implementation of the channel and some utilities by Peng Rui
// modified some of the methods from Project 1

#ifndef CHANNEL_H
#define CHANNEL_H

#include "trellis.h"

// construct a trivial random generator engine from a time-based seed
default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());

vector<vector<int> > generate_signals(int N, trellis tr) {
	uniform_int_distribution<int> distribution(0, 1);
	vector<vector<int> > signals(N);
	for (int i = 0; i < N; i++) {
		signals[i].resize(tr.data[0].next.begin()->second.input_bits.size());
		for (int j = 0; j < (int)signals[i].size(); j++) {
			signals[i][j] = distribution(generator);
			if (signals[i][j] == 0)
				signals[i][j] = -1;
		}
	}
	return signals;
}

// pass the signals through the channel whose standard deviation of Gaussian noises is sqrt(N0 / 2)
vector<vector<double> > receive_signals(vector<vector<int> > encoded, double N0) {
	normal_distribution<double> distribution(0, sqrt(N0 / 2));
	vector<vector<double> > result(encoded.size());
	for (int i = 0; i < (int)encoded.size(); i++)
		for (int j = 0; j < (int)encoded[i].size(); j++)
			result[i].push_back(encoded[i][j] + distribution(generator));
	return result;
}

// calculate the bit error rate
template <typename T1, typename T2>
double BER(vector<vector<T1> > v1, vector<vector<T2> > v2) {
	vector<double> received, signals;
	for (int i = 0; i < (int)v1.size(); i++) {
		received.insert(received.end(), v1[i].begin(), v1[i].end());
		signals.insert(signals.end(), v2[i].begin(), v2[i].end());
	}
	int err = 0;
	for (int i = 0; i < (int)received.size(); i++) {
		int pos = 0;
		for (int j = 0; j < (int)received.size(); j++)
			if (abs(received[i] - signals[j]) < abs(received[i] - signals[pos]))
				pos = j;
		if (signals[i] != signals[pos])
			err++;
	}
	return (double)err / received.size();
}

#endif  // CHANNEL_H

