// CRC-16 Program
// ref: https://en.wikipedia.org/wiki/Cyclic_redundancy_check
// ref: https://en.wikipedia.org/wiki/Computation_of_cyclic_redundancy_checks
// Implemented by Peng Rui
#pragma GCC optimize "O3,omit-frame-pointer,inline"
#include <iostream>
#include <chrono>
#include <vector>
#include <random>
using namespace std;

default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());

// convert a number to a bit string
vector<int> convert(int num, int len) {
	vector<int> bitString;
	while (num) {
		bitString.insert(bitString.begin(), num % 2);
		num /= 2;
	}
	bitString.insert(bitString.begin(), len - bitString.size(), 0);
	return bitString;
}

// generate a bit string
vector<int> generate() {
	vector<int> bitString;
	uniform_int_distribution<int> distribution(0, 1);
	for (int i = 0; i < 1024; i++)
		bitString.push_back(distribution(generator));
	return bitString;
}

// CRC encoding
vector<int> CRC_encode(vector<int> bitString, vector<int> remainderPolynomial) {
	int len = bitString.size(), n = remainderPolynomial.size();
	vector<int> CRC_code = bitString;
	bitString.insert(bitString.end(), n - 1, 0);
	for (int i = 0; i < len; i++)
		if (bitString[i])
			for (int j = 0; j < n; j++)
				bitString[i + j] ^= remainderPolynomial[j];
	CRC_code.insert(CRC_code.end(), bitString.begin() + len, bitString.end());
	return CRC_code;
}

// CRC decoding
vector<int> CRC_decode(vector<int> bitString, vector<int> remainderPolynomial) {
	int n = remainderPolynomial.size(), len = bitString.size() - n + 1;
	vector<int> CRC_code = bitString;
	for (int i = 0; i < len; i++)
		if (bitString[i])
			for (int j = 0; j < n; j++)
				bitString[i + j] ^= remainderPolynomial[j];
	for (int i = 0; i < len + n - 1; i++)
		CRC_code[i] |= bitString[i];
	return vector<int>(CRC_code.begin(), CRC_code.begin() + len);
}

// binary symmetric channel with crossover probability p
vector<int> BSC(vector<int> bitString, double p) {
	uniform_real_distribution<double> distribution(0, 1);
	for (int i = 0; i < (int)bitString.size(); i++)
		if (distribution(generator) < p)
			bitString[i] = 1 - bitString[i];
	return bitString;
}

// test the program with a message with block length 1024
void test1() {
	vector<int> data = generate();
	vector<int> remainderPolynomial = convert(0x18005, 17);
	vector<int> encoded = CRC_encode(data, remainderPolynomial);
	vector<int> decoded = CRC_decode(encoded, remainderPolynomial);
	if (data == decoded)
		cout << "Test1 completed!" << endl << endl;
}

// test the program further by passing the encoded data through a binary symmetric channel
void test2(double p) {
	int undetected_errors = 0, verified = 0, tests = 1234567;
	for (int i = 0; i < tests; i++) {
		vector<int> data = generate();
		vector<int> remainderPolynomial = convert(0x18005, 17);
		vector<int> encoded = CRC_encode(data, remainderPolynomial);
		vector<int> passed = BSC(encoded, p);
		vector<int> decoded = CRC_decode(passed, remainderPolynomial);
		if (data == decoded) {
			if (encoded != passed)
				undetected_errors++;
			verified++;
		}
	}
	cout << p << "\t->  " << (double)undetected_errors / verified << endl;
}

int main() {
	test1();
	cout << "Test2:" << endl;
	for (double p = 0.0001; p < 1; p *= 10)
		test2(p);
	return 0;
}

