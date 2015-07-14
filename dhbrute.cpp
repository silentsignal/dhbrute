#include <openssl/bn.h>
#include <iostream>
#include <stdint.h>

using namespace std;

int main(int argc, char **argv) {

	if (argc < 3) {
		cerr << "Usage: " << argv[0] << " <modulus> <base>" << endl;
		return 1;
	}

	BIGNUM *m, *b, *r;
	BN_CTX *t = BN_CTX_new();

	BN_CTX_init(t);
	m = BN_new();
	b = BN_new();
	r = BN_new();

	BN_dec2bn(&m, argv[1]);
	BN_dec2bn(&b, argv[2]);
	BN_copy(r, b);

	for (uint64_t i = 0; i < 100000000; i++) {
		BN_mod_mul(r, r, b, m, t);
		if (BN_cmp(r, b) == 0) {
			printf("Found at iteration %lu\n", i);
			break;
		}
	}

	return 0;
}
