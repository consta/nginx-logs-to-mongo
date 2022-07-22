FROM ubuntu:16.04
RUN apt-get -y update && apt-get -y install gcc g++ cmake libssl-dev libsasl2-dev curl wget git
RUN mkdir -p /usr/local/sources; \
    cd /usr/local/sources; \
    wget https://github.com/mongodb/mongo-c-driver/releases/download/1.22.0/mongo-c-driver-1.22.0.tar.gz; \
    tar -xzf mongo-c-driver-1.22.0.tar.gz; \
    cd /usr/local/sources/mongo-c-driver-1.22.0; \
    mkdir cmake-build && cd cmake-build; \
    cmake -DENABLE_AUTOMATIC_INIT_AND_CLEANUP=OFF -DMONGOC_TEST_USE_CRYPT_SHARED=FALSE .. ; \
    cmake --build .; \
    cmake --build . --target install
RUN cd /usr/local/sources; \
    curl -OL https://github.com/mongodb/mongo-cxx-driver/releases/download/r3.6.7/mongo-cxx-driver-r3.6.7.tar.gz; \
    tar -xzf mongo-cxx-driver-r3.6.7.tar.gz; \
    cd /usr/local/sources/mongo-cxx-driver-r3.6.7/build; \
    cmake --build . --target EP_mnmlstc_core; \
    cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local; \
    cmake --build .; \
    cmake --build . --target install
RUN cd /usr/local/sources; \
    git clone --branch v2.13.9 https://github.com/catchorg/Catch2.git; \
    cd /usr/local/sources/Catch2; \
    cmake -DCMAKE_C_COMPILER="/usr/bin/gcc" -DCMAKE_CXX_COMPILER="/usr/bin/g++" -Bbuild -H. -DBUILD_TESTING=OFF; \
    cmake --build build/ --target install
RUN rm -rf /usr/local/sources/*
