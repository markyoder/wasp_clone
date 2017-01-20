INCLUDE(GoogleTest)

include(SetDefault)
SET_DEFAULT(GETPOT_TEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}" )
configure_file("Paths.h.in" "${CMAKE_CURRENT_BINARY_DIR}/Paths.h" @ONLY)

ADD_GOOGLE_TEST(tstGetPot.cpp NP 1)
ADD_GOOGLE_TEST(tstHIVE.cpp NP 1)
