// ref: http://www.cplusplus.com/reference/random/
#pragma GCC optimize "O3,omit-frame-pointer,inline"
#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <cmath>
#include <climits>

#define N 66666

using namespace std;

double N0;

vector<double> signals;
vector<double> noises;
vector<double> received;

default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());

void generate_signals() {
	uniform_int_distribution<int> distribution(0, 1);
	signals.resize(N);
	for (int i = 0; i < N; i++) {
		signals[i] = distribution(generator);
		if (signals[i] == 0)
			signals[i] = -1;
	}
}

void generate_noises() {
	noises.resize(N);
	normal_distribution<double> distribution(0, sqrt(N0 / 2));
	for (int i = 0; i < N; i++)
		noises[i] = distribution(generator);
}

void receive_signals() {
	received.resize(N);
	for (int i = 0; i < N; i++)
		received[i] = signals[i] + noises[i];
}

double BER() {
	int err = 0;
	for (int i = 0; i < N; i++) {
		int pos = 0;
		for (int j = 0; j < N; j++)
			if (abs(received[i] - signals[j]) < abs(received[i] - signals[pos]))
				pos = j;
		if (signals[i] != signals[pos])
			err++;
	}
	return (double)err / N;
}

void test(double _N0) {
	N0 = _N0;
	generate_signals();
	generate_noises();
	receive_signals();
	cout << 1 / N0 << ": " << BER() << endl;
}

int main() {
	test(2);
	for (int i = 1; i < 10; i++)
		test((double)1 / i);
	return 0;
}

