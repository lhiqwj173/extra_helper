#include <iostream>
#include "../extra_helper/time/time.h"

using namespace std;
int main() {
	cout << "\n²âÊÔ strptime 1" << endl;
	extra::time::timestamp_ms t = 1707571939155;
	auto t_str = extra::time::strftime(t);
	cout << t << " -> \n\t"
		<<t_str << endl;

	cout << "\n²âÊÔ strptime 2" << endl;
	std::time_t t2 = 1707571939;
	auto t_str2 = extra::time::strftime(t2);
	cout << t2 << " -> \n\t"
		<< t_str2 << endl;

	cout << "\n²âÊÔ strptime 3" << endl;
	auto t_str3 = extra::time::strftime(t, "%YÄê%mÔÂ%dÈÕ %HÊ±%M·Ö%SÃë%fºÁÃë");
	cout << t << " -> \n\t"
		<< t_str3 << endl;

	cout << "\n²âÊÔ strptime 1" << endl;
	extra::time::timestamp_ms r1 = extra::time::strptime(t_str);
	cout << t_str << " -> \n\t"
		<< r1 << endl;

	cout << "\n²âÊÔ strptime 2" << endl;
	extra::time::timestamp_ms r2 = extra::time::strptime(t_str2);
	cout << t_str2 << " -> \n\t"
		<< r2 << endl;

	cout << "\n²âÊÔ strptime 3" << endl;
	extra::time::timestamp_ms r3 = extra::time::strptime(t_str3, "%YÄê%mÔÂ%dÈÕ %HÊ±%M·Ö%SÃë%fºÁÃë");
	cout << t_str3 << " -> \n\t"
		<< r3 << endl;
}