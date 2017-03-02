TRIBITS_SUBPACKAGE(py)

#
# Add test directory
TRIBITS_ADD_TEST_DIRECTORIES(test)

install(DIRECTORY .
        DESTINATION "../wasppy"
        PATTERN "./*.py"
        PATTERN "./test/*.py"
        PATTERN "./test/*.son"
        PATTERN "./test/*.sch"
)
