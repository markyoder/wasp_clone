 . ci/setup.sh
 cd build
 cmake -DBUILDNAME="$(uname -s)-AppleClang-8-Debug-${CI_BUILD_REF_NAME}" -DCMAKE_BUILD_TYPE=DEBUG -Dwasp_ENABLE_TESTS=ON -Dwasp_ENABLE_ALL_PACKAGES=ON ..
 ctest -D ExperimentalStart -D ExperimentalBuild -D ExperimentalTest -D ExperimentalSubmit
