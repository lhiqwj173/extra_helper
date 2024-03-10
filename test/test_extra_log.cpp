#include "extra_helper/logger/log.h"

int main() {
	while(1) {
		LINFO("LINFO");
		LDEBUG("LDEBUG");
		LTRACE("LTRACE");
		LWARN("LWARN");
		LERR("LERR");
		LCRITICAL("LCRITICAL");
	}
}
