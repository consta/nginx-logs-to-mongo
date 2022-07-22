#!/bin/bash

# WORKING_DIR is defined outside container
export OUTPUT_DIR=cmake-build-linux-debug
export CMAKE_BUILD_TYPE=Debug
export CMAKE_DEPENDS_USE_COMPILER=FALSE

cd $WORKING_DIR
rm -rf $OUTPUT_DIR && mkdir $OUTPUT_DIR
cmake -G "CodeBlocks - Unix Makefiles" $WORKING_DIR -B$OUTPUT_DIR
cmake --build $WORKING_DIR/$OUTPUT_DIR --target nginx_logs_to_mongo -- -j 12