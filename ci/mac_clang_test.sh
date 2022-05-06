mkdir build
cd build
git clone https://code.ornl.gov/casl/anaconda.git
bash Anaconda3-2020.02-Linux-x86_64.sh -b -p ${PWD}/anaconda3
export PATH=${PWD}/anaconda3/bin:$PATH
pip install builtins
pip install six
cmake -DBUILDNAME="$(uname -s)-AppleClang-8-Debug-${CI_BUILD_REF_NAME}" \
       -DCMAKE_BUILD_TYPE=DEBUG \
       -Dwasp_ENABLE_TESTS=ON \
       -Dwasp_ENABLE_ALL_PACKAGES=ON \
       ..
ctest --output-on-failure \
       -D ExperimentalStart \
       -D ExperimentalBuild -j 8 \
       -D ExperimentalSubmit \
       -D ExperimentalTest -j 8 \
       -D ExperimentalSubmit

# clean up prior config for the next bundle config
rm -rf CMake*
cmake -DBUILDNAME="$(uname -s)-AppleClang-8-Bundle-${CI_BUILD_REF_NAME}" \
      -DCPACK_PACKAGE_NAME=WASP \
       -DCMAKE_BUILD_TYPE=RELEASE \
       -Dwasp_ENABLE_ALL_PACKAGES=ON \
	  -Dwasp_ENABLE_TESTS:BOOL=OFF \
	  -Dwasp_ENABLE_ALL_PACKAGES:BOOL=ON \
	  -Dwasp_ENABLE_testframework:BOOL=OFF \
	  -Dwasp_ENABLE_googletest:BOOL=OFF \
      -Dwasp_ENABLE_wasppy:BOOL=ON \
	  -Dwasp_ENABLE_INSTALL_CMAKE_CONFIG_FILES:BOOL=ON \
	  -Dwasp_GENERATE_EXPORT_FILE_DEPENDENCIES:BOOL=ON \
	  -Dwasp_ENABLE_CPACK_PACKAGING:BOOL=ON \
      ..

make -j 8 package
ls -l ./
# Copy bundle parts up to parent directory to avoid artifact
# having build directory
cp WASP-*-Darwin.sh ../
cp waspConfig_install.cmake ../

