#!/usr/bin/env bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

g++ -std=c++20 ${SCRIPT_DIR}/main.cpp -pthread -I${SCRIPT_DIR}/../../ -o ${SCRIPT_DIR}/test
${SCRIPT_DIR}/test
