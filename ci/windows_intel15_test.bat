call .\ci\setup.bat
cd build
set PATH=c:\vendors\cmake-ninja\bin;C:\Program Files (x86)\NSIS;%PATH%
call "C:\Program Files (x86)\Intel\Composer XE 2015\bin\ipsxe-comp-vars.bat" intel64 vs2013
cmake -DCMAKE_C_COMPILER=icl -D CMAKE_CXX_COMPILER=icl -DBUILDNAME="Windows-Intel-15.0-Release-%CI_BUILD_REF_NAME%" -DCMAKE_BUILD_TYPE:STRING=RELEASE -Dwasp_ENABLE_TESTS:BOOL=ON -Dwasp_ENABLE_ALL_PACKAGES:BOOL=ON -D wasp_ENABLE_INSTALL_CMAKE_CONFIG_FILES:BOOL=ON wasp_GENERATE_EXPORT_FILE_DEPENDENCIES:BOOL=ON -G "Ninja" ..
ctest -D ExperimentalStart -D ExperimentalBuild -D ExperimentalTest -D ExperimentalSubmit
copy /Y waspConfig_install.cmake install\lib\cmake\wasp\waspConfig.cmake
ninja bundle
dir 
