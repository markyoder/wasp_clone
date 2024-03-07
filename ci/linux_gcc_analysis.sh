. ci/setup.sh
cd build

# Setup a conda install
wget https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh -O ${PWD}/miniconda3/miniconda.sh
bash ${PWD}/miniconda3/miniconda.sh -b -u -p ${PWD}/miniconda3
eval "$(${PWD}/miniconda3/bin/conda shell.bash hook 2> /dev/null)"
conda env create -f ../ci/env.yml
conda activate wasp_ci
conda install -c conda-forge valgrind

cmake -MEMCHECK_COMMAND="$(which valgrind)" \
      -DBUILDNAME="$(uname -s)-Analysis-Debug-${CI_COMMIT_REF_NAME}" \
      -DCMAKE_BUILD_TYPE=DEBUG \
      -DWASP_ENABLE_SWIG=ON \
      -Dwasp_ENABLE_COVERAGE_TESTING=ON \
      -DCOVERAGE_EXTRA_FLAGS="-s ${CI_PROJECT_DIR}/googletest -d" \
      -Dwasp_ENABLE_TESTS=ON \
      -Dwasp_ENABLE_ALL_PACKAGES=ON \
      ..



ctest --output-on-failure \
      -D Experimental -j 8 \
      -D ExperimentalMemCheck \
      -D ExperimentalCoverage \
      -D ExperimentalSubmit

