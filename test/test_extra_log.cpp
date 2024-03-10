#include "extra_helper/logger/log.h"

#include <string>

int main() {
	int a = 10;
	std::string b = "hello 1";
	unsigned long long c = 10000000000000000000;
	long d = 1000000000;
	double e = 100.565;
	float f = 500000.0000565;
	char* g = "hello 2";
	char h = 'a';

	while (1) {
		LINFO("LINFO %llu", c);
		LINFO("LINFO p:%p", (void*)&a);
		LINFO("LINFO int:%d", a);
		LINFO("LINFO str:%s", b.c_str());

		LINFO("LINFO int:\t{}", (void*)&a);
		LINFO("LINFO string:\t{}", b);
		LINFO("LINFO ull:\t{}", c);
		LINFO("LINFO long:\t{}", d);
		LINFO("LINFO double:\t{}", e);
		LINFO("LINFO double:\t{:.2f}", e);
		LINFO("LINFO float:\t{}", f);
		LINFO("LINFO char *:\t{}", g);
		LINFO("LINFO char:\t{}", h);

	}
}
