INCLUDE(GoogleTest)

TRIBITS_ADD_LIBRARY(test_server_lib
  SOURCES TestServer.cpp TestServer.h
  TESTONLY
)

ADD_GOOGLE_TEST(tstLSP.cpp       NP 1)
ADD_GOOGLE_TEST(tstServer.cpp    NP 1 DEPLIBS test_server_lib wasplsp)
ADD_GOOGLE_TEST(tstIntegrate.cpp NP 1 DEPLIBS test_server_lib wasplsp)
