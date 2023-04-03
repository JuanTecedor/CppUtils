FROM ubuntu:22.04

COPY . .

RUN apt-get update \
    && apt-get install gcc git cmake build-essential -y \
    && git clone https://github.com/catchorg/Catch2.git \
    && cd Catch2 \
    && git checkout v3.3.2 \
    && cmake -Bbuild -H. -DBUILD_TESTING=OFF \
    && cmake --build build/ --target install
