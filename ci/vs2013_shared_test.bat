call .\ci\setup.bat
cd build
set "conda=%cd%"
git clone https://code.ornl.gov/casl/anaconda.git
%conda%\anaconda\Anaconda3-2021.11-Windows-x86_64.exe /S /D=%conda%
set "PATH=%conda%\Scripts;%conda%;%conda%\Library\bin;%PATH%"

call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat" x86_amd64


cmake -DBUILD_SHARED_LIBS=ON ^
      -DBUILDNAME="Windows-CL-18-Shared-Release-%CI_BUILD_REF_NAME%" ^
      -DCMAKE_BUILD_TYPE:STRING=RELEASE ^
      -Dwasp_ENABLE_TESTS:BOOL=ON ^
      -Dwasp_ENABLE_ALL_PACKAGES:BOOL=ON ^
      -G "Visual Studio 12 2013 Win64" ..
ctest --output-on-failure ^
      -D ExperimentalStart ^
      -D ExperimentalBuild ^
      -D ExperimentalTest ^
      -D ExperimentalSubmit
