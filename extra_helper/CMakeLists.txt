add_library(extra_helper SHARED "time/time.cpp")

set(HEADERS "time/time.h")
file(INSTALL ${HEADERS} DESTINATION include/extra_helper)

set(EXTRA_HELPER_LIB extra_helper CACHE INTERNAL "link extra_helper libraries")

