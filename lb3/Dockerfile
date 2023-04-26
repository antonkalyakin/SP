FROM debian

RUN apt update
RUN apt install -y g++
RUN apt install -y gcc
RUN apt install -y gcc-multilib
RUN apt install -y gdb

COPY ./script.cpp .

RUN g++ -g ./script.cpp -o ./script
