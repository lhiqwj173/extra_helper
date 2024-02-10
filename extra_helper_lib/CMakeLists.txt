add_library(extra_helper SHARED "time/time.cpp")

set(EXTRA_HELPER_LIB extra_helper CACHE INTERNAL "link extra_helper libraries")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET extra_helper PROPERTY CXX_STANDARD 20)
endif()

