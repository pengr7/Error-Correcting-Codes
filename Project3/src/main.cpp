#include "headers.h"
#include "encoder.h"
#include "channel.h"
#include "decoder.h"

int main() {
	trellis tr;

	vector<vector<int> > input = generate_signals(4, tr);
	my_debugger::print_vector(input);

	vector<vector<int> > encoded = encode(input, tr);
	my_debugger::print_vector(encoded);

	vector<vector<double> > received = receive_signals(encoded, 0.1);
	my_debugger::print_vector(received);

	//test
	vector<vector<double> > receival = {{.8, .1}, {1, -.5}, {-1.8, 1.1}, {1.6, -1.6}};
	vector<vector<int> > decoded = decode(receival, tr);

	// cout << BER(input, decoded) << endl;

	return 0;
}

