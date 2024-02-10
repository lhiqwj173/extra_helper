#include <iostream>
#include "../extra_helper_lib/time/time.h"

using namespace std;
int main() {
	extra::time::timestamp_ms t = 1707571939155;
	auto t_str = extra::time::strptime(t);
	cout << t << " -> \n\t"
		<<t_str << endl;
}