function ecc () {
    "$@"
    if [[ $? -ne 0 ]]; then exit 1; fi
}

if [[ -d build  ]]; then
   rm -rf build
fi

mkdir -p build/miniconda3
cd build

# Setup a conda install
wget https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh -O ${PWD}/miniconda3/miniconda.sh
bash ${PWD}/miniconda3/miniconda.sh -b -u -p ${PWD}/miniconda3
eval "$(${PWD}/miniconda3/bin/conda shell.bash hook 2> /dev/null)"
conda env create -f ../ci/env.yml
conda activate wasp_ci
conda install -c conda-forge valgrind

ecc cmake -DBUILDNAME="$(uname -s)-GCC-4.8.5-Release-${CI_COMMIT_REF_NAME}" \
      -DCMAKE_BUILD_TYPE=RELEASE \
      -Dwasp_ENABLE_TESTS=ON \
      -Dwasp_ENABLE_SWIG=ON \
      -DBUILD_SHARED_LIBS:BOOL=ON \
      -Dwasp_ENABLE_ALL_PACKAGES=ON \
      -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/g++ \
      -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/gcc \
      ..

ecc ctest --output-on-failure \
      -D ExperimentalStart \
      -D ExperimentalBuild -j 8\
      -D ExperimentalSubmit \
      -D ExperimentalTest -j 8 \
      -D ExperimentalSubmit

# clean up prior config for the next bundle config
rm -rf CMake*

ecc cmake -DBUILDNAME="$(uname -s)-GCC-4.8.5-Bundle-${CI_COMMIT_REF_NAME}" \
      -DCPACK_PACKAGE_NAME=WASP \
      -DBUILD_SHARED_LIBS:BOOL=ON \
      -DCMAKE_BUILD_TYPE=RELEASE \
      -Dwasp_ENABLE_ALL_PACKAGES=ON \
      -Dwasp_ENABLE_TESTS:BOOL=OFF \
      -Dwasp_ENABLE_SWIG=ON \
      -Dwasp_ENABLE_ALL_PACKAGES:BOOL=ON \
      -Dwasp_ENABLE_testframework:BOOL=OFF \
      -Dwasp_ENABLE_googletest:BOOL=OFF \
      -Dwasp_ENABLE_wasppy:BOOL=ON \
      -Dwasp_ENABLE_INSTALL_CMAKE_CONFIG_FILES:BOOL=ON \
      -Dwasp_GENERATE_EXPORT_FILE_DEPENDENCIES:BOOL=ON \
      -Dwasp_ENABLE_CPACK_PACKAGING:BOOL=ON \
      -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/g++ \
      -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/gcc \
      ..

ecc make -j 8 package

# Copy bundle parts up to parent directory to avoid artifact
# having build directory
cp WASP-*-Linux.sh ../
cp *.whl ../
cp waspConfig_install.cmake ../
