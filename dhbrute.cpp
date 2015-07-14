#include <openssl/bn.h>
#include <iostream>
#include <QHash>
#include <QByteArray>

using namespace std;

int main(int argc, char **argv) {

	if (argc < 3) {
		cerr << "Usage: " << argv[0] << " <modulus> <base>" << endl;
		return 1;
	}

	BIGNUM *m, *b, *r;
	BN_CTX *t = BN_CTX_new();
	QHash<QByteArray, quint64> seen;

	BN_CTX_init(t);
	m = BN_new();
	b = BN_new();
	r = BN_new();

	BN_dec2bn(&m, argv[1]);
	BN_dec2bn(&b, argv[2]);
	BN_copy(r, b);

	for (quint64 i = 0; i < 10000000; i++) {
		unsigned char bin[BN_num_bytes(r)];
		BN_bn2bin(r, bin);

		QByteArray ba((const char*)bin);

		if (seen.contains(ba)) {
			cout << "Found at iteration " << i << " from iteration " << seen[ba] << endl;
		} else {
			seen[ba] = i;
		}
		BN_mod_mul(r, r, b, m, t);
	}

	return 0;
}
