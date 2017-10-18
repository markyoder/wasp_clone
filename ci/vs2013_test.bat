 .\ci\setup.bat
 cd build
 call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat" x86_amd64
 cmake -DBUILDNAME="Windows-CL-18-Release-%CI_BUILD_REF_NAME%" -DCMAKE_BUILD_TYPE:STRING=RELEASE -Dwasp_ENABLE_TESTS:BOOL=ON -Dwasp_ENABLE_ALL_PACKAGES:BOOL=ON -G "Visual Studio 12 2013 Win64" ..
 ctest -D ExperimentalStart -D ExperimentalBuild -D ExperimentalTest -D ExperimentalSubmit:
