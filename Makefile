# Makefile for code_analysis() problem
#
# To build:
#   make
#
# To run tests in code_analysis_t:
#   make test
#
# To clean build:
#   make clean
#
# To run tests in both get_language_from_filename_t and code_analysis_t:
#   make testall

.PHONY.: all
all: code_analysis_t get_language_from_filename_t

# test program for code_analysis() and related functions
code_analysis_t: code_analysis_t.o code_analysis.o get_language_from_filename.o
	g++ $^ -o $@

code_analysis_t.o: code_analysis_t.cpp
	g++ -std=c++11 -c $<

code_analysis.o: code_analysis.cpp code_analysis.hpp xmlWrapper.hpp
	g++ -std=c++11 -c $<

# test program for get_language_from_filename()
get_language_from_filename_t: get_language_from_filename_t.o get_language_from_filename.o
	g++ $^ -o $@

get_language_from_filename.o: get_language_from_filename.cpp get_language_from_filename.hpp
	g++ -std=c++11 -c $<

get_language_from_filename_t.o: get_language_from_filename_t.cpp get_language_from_filename.hpp
	g++ -std=c++11 -c $<

.PHONY.: clean
clean :
	rm -f code_analysis_t.o code_analysis_t get_language_from_filename.o get_language_from_filename_t.o get_language_from_filename_t code_analysis.o

.PHONY.: testall
testall: get_language_from_filename_t code_analysis_t
	./get_language_from_filename_t
	./code_analysis_t

.PHONY.: test
test: code_analysis_t
	./code_analysis_t
