 . ci/setup.sh
 cd build
 module load valgrind
 cmake -DBUILDNAME="$(uname -s)-GCC-4.8.5-Release-${CI_BUILD_REF_NAME}" -DCMAKE_BUILD_TYPE=RELEASE -Dwasp_ENABLE_TESTS=ON -Dwasp_ENABLE_ALL_PACKAGES=ON ..
 ctest -D ExperimentalStart -D ExperimentalBuild -D ExperimentalTest -D ExperimentalSubmit
