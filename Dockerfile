# c++ compiler
# https://devblogs.microsoft.com/cppblog/c-development-with-docker-containers-in-visual-studio-code/

# Build 
# docker build . -t cpp-build-base:0.2.1

# Run container
# docker run --rm -it -w /src -v C:\ivan_shevchenko\Spell-Checker:/src cpp-build-base:0.2.1

# Compile c++ file
# clang++ -o solution_1 solution_1.cpp

# Run compiled binary
# /src/solution_1.cpp

FROM ubuntu:bionic

# Update apps on the base image
RUN apt-get -y update && apt-get install -y

# Install the Clang compiler
RUN apt-get -y install clang

# Install the Nano editor
RUN apt-get -y install nano
