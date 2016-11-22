# Requirements
* C/CXX compiler.
** GCC-4.8
** LLVM-7.0.2
* Git
* CMake-2.8.12.2.
* Python-2.7

# Getting Started
* You will need to save your ssh-key in [code-int.ornl.gov](https://code-int.ornl.gov/profile/keys).
* Clone wasp `git clone git@code-int.ornl.gov:lefebvre/wasp.git ~/wasp`
* Change directory into wasp `cd ~/wasp`
* Clone TriBITS `git clone https://github.com/lefebvre/TriBITS.git TriBITS` [TriBITS documentation](https://tribits.org/doc/TribitsDevelopersGuide.html)
* Clone extra repos `./TriBITS/tribits/ci_support/clone_extra_repos.py`
* Create a build directory `mkdir -p ~/build/wasp`
* Change into the build `cd ~/build/wasp`
* Create a configuration script in ~/build/. Lets call is ../configure.sh(linux)

```
#!/bin/bash
# Linux bash file example
rm -rf CMake*
cmake \
 -D CMAKE_BUILD_TYPE:STRING=RELEASE \
 -D wasp_ENABLE_ALL_PACKAGES:BOOL=ON \
 -D wasp_ENABLE_TESTS:BOOL=ON \
 -D CMAKE_INSTALL_PREFIX=`pwd`/install \
 -G "Unix Makefiles" \
 ~/wasp
```
E.g., to a script that will enable getpot
```
#!/bin/bash
# Linux bash file example
rm -rf CMake*
cmake \
 -D CMAKE_BUILD_TYPE:STRING=RELEASE \
 -D wasp_ENABLE_waspgetpot=ON \
 -D wasp_ENABLE_TESTS:BOOL=ON \
 -D CMAKE_INSTALL_PREFIX=`pwd`/install \
 -G "Unix Makefiles" \
 ~/wasp
```

* Invoke configure script in the build directory.
`../configure.sh or ..\configure.bat`
  * I place the configure script in the build directory as opposed to the build/wasp directory because it allows me to delete the build/wasp
directory without removing my script.
