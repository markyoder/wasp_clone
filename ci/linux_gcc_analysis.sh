. ci/setup.sh
cd build

# Setup a conda install
wget https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh -O ${PWD}/miniconda.sh
bash ${PWD}/miniconda.sh -b -u -p ${PWD}/miniconda3
eval "$(${PWD}/miniconda3/bin/conda shell.bash hook 2> /dev/null)"
conda env create -f ../ci/env.yml
conda activate wasp_ci
conda install -c conda-forge valgrind

cmake -DBUILDNAME="$(uname -s)-Analysis-Debug-${CI_COMMIT_REF_NAME}" \
      -DCMAKE_BUILD_TYPE=DEBUG \
      -Dwasp_ENABLE_COVERAGE_TESTING=ON \
      -DCOVERAGE_EXTRA_FLAGS="-s ${CI_PROJECT_DIR}/googletest -d" \
      -Dwasp_ENABLE_TESTS=ON \
      -Dwasp_ENABLE_ALL_PACKAGES=ON \
      ..

export CMAKE_BUILD_PARALLEL_LEVEL=8

ctest --output-on-failure \
      -D Experimental -j 8 \
      -D ExperimentalMemCheck \
      -D ExperimentalCoverage \
      -D ExperimentalSubmit

