INCLUDE(GoogleTest)

# configure paths for template tests
configure_file("Paths.h.in" "Paths.h" @ONLY)

configure_file("data/file_import_file_missing.result.txt.in" "file_import_file_missing.result.txt" @ONLY)
configure_file("data/unmatched_conditional_terminator.result.txt.in" "unmatched_conditional_terminator.result.txt" @ONLY)
configure_file("data/unmatched_conditional_elseif.result.txt.in" "unmatched_conditional_elseif.result.txt" @ONLY)
configure_file("data/unmatched_conditional_else.result.txt.in" "unmatched_conditional_else.result.txt" @ONLY)
configure_file("data/undefined_attribute.result.txt.in" "undefined_attribute.result.txt" @ONLY)
configure_file("data/expression_evaluation_syntax_error.result.txt.in" "expression_evaluation_syntax_error.result.txt" @ONLY)
configure_file("data/expression_evaluation_format_error.result.txt.in" "expression_evaluation_format_error.result.txt" @ONLY)

ADD_GOOGLE_TEST(tstHaliteTreeConstruction.cpp NP 1)
ADD_GOOGLE_TEST(tstHaliteEngine.cpp NP 1)
ADD_GOOGLE_TEST(tstHaliteErrors.cpp NP 1)
ADD_GOOGLE_TEST(tstSubStringIndexer.cpp NP 1)
ADD_GOOGLE_TEST(tstDataAccessor.cpp NP 1)

