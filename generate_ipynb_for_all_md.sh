#!/bin/bash

set -xeu

WORKING_DIR=$(cd "$(dirname "$0")";pwd)

echo ${WORKING_DIR}

python3 ${WORKING_DIR}/tools/md2ipynb.py generate-all --data-dir=${WORKING_DIR}

