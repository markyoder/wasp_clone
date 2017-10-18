call .\ci\setup.bat
cd build
set PATH=c:\vendors\cmake-ninja\bin;C:\Program Files (x86)\NSIS;%PATH%
call "C:\Program Files (x86)\Intel\Composer XE 2015\bin\ipsxe-comp-vars.bat" intel64 vs2013
cmake -DCMAKE_C_COMPILER=icl -D CMAKE_CXX_COMPILER=icl -DBUILDNAME="Windows-Intel-15.0-Release-%CI_BUILD_REF_NAME%" -DCMAKE_BUILD_TYPE:STRING=RELEASE -Dwasp_ENABLE_TESTS:BOOL=ON -Dwasp_ENABLE_ALL_PACKAGES:BOOL=ON -G "Ninja" ..
ctest -D ExperimentalStart -D ExperimentalBuild -D ExperimentalTest -D ExperimentalSubmit
rd /s /q CMake*

cmake -DCMAKE_C_COMPILER=icl -D CMAKE_CXX_COMPILER=icl -DBUILDNAME="Windows-Intel-15.0-Bundle-%CI_BUILD_REF_NAME%" -DCMAKE_BUILD_TYPE:STRING=RELEASE -Dwasp_ENABLE_TESTS:BOOL=OFF -Dwasp_ENABLE_ALL_PACKAGES:BOOL=ON -Dwasp_ENABLE_testframework:BOOL=OFF -Dwasp_ENABLE_googletest:BOOL=OFF -Dwasp_ENABLE_INSTALL_CMAKE_CONFIG_FILES:BOOL=ON -Dwasp_GENERATE_EXPORT_FILE_DEPENDENCIES:BOOL=ON -Dwasp_ENABLE_CPACK_PACKAGING:BOOL=ON -G "Ninja" ..
REM need to fix the install
copy /Y waspConfig_install.cmake install\lib\cmake\wasp\waspConfig.cmake
ninja package
dir 
