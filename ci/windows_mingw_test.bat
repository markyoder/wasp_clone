call .\ci\setup.bat
cd build
cmake -DBUILDNAME="Windows-MinGW-GCC-4.8.5-Debug-%CI_BUILD_REF_NAME%" -DCMAKE_BUILD_TYPE=DEBUG -Dwasp_ENABLE_TESTS=ON -Dwasp_ENABLE_ALL_PACKAGES=ON -G "MinGW Makefiles" ..
ctest -D ExperimentalStart -D ExperimentalBuild -D ExperimentalTest -D ExperimentalSubmit
