FROM debian

RUN apt update
RUN apt install -y g++
RUN apt install -y gcc
RUN apt install -y gcc-multilib
RUN apt install -y gdb

COPY ./script_c.cpp .
COPY ./script_asm.s .

RUN g++ -g ./script_c.cpp -o ./script_c
RUN gcc -g -m32 -no-pie ./script_asm.s -o ./script_asm
