# c++ compiler
# https://devblogs.microsoft.com/cppblog/c-development-with-docker-containers-in-visual-studio-code/

# Build 
# docker build . -t cpp-build-base:0.2.1

# Run container on Windows:
#   docker run --rm -it -w /src -v C:\ivan_shevchenko\Spell-Checker:/src cpp-build-base:0.2.1
#
# In Windows Command Line (cmd):
#   docker run --rm -it -w /src -v %cd%:/src cpp-build-base:0.2.1
#
# In PowerShell, you use ${PWD}:
#   docker run --rm -it -w /src -v ${PWD}:/src cpp-build-base:0.2.1

# Run container on Linux
#   docker run --rm -it -w /src -v $(pwd):/src cpp-build-base:0.2.1

# Compile c++ file
# clang++ -o bin/spell_checker_solution spell_checker_solution.cpp

# Run compiled binary
# /src/solution_1.cpp

FROM ubuntu:bionic

# Update apps on the base image
RUN apt-get -y update && apt-get install -y

# Install the Clang compiler
RUN apt-get -y install clang

# Install the Nano editor
RUN apt-get -y install nano
