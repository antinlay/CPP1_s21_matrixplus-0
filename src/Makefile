GCC = gcc
SOURCE = s21_matrix_oop.cpp
OBJ = $(SOURCE:.cpp=.o)
CFLAGS=-std=c++17 -pthread
TESTFLAGS=-lgtest
GCOVFLAGS =-L. --coverage
HTML = lcov -t "test" -o rep.info -c -d .
OS = $(shell uname)

all: gcov_report

clean:
	rm -rf *.o *.a *.so *.gcda *.gcno *.gch rep.info *.html *.css test report *.txt *.dSYM

test: s21_matrix_oop.a
	$(GCC) $(CFLAGS) $(TESTFLAGS) s21_gtests.cpp s21_matrix_oop.a -o test 
	./test

s21_matrix_oop.a: clean $(OBJ)
	ar rcs s21_matrix_oop.a $(OBJ)
	ranlib s21_matrix_oop.a


gcov_report: test
	$(GCC) $(CFLAGS) $(SOURCE) s21_matrix_oop.a -o test
	./test
	$(HTML)
	genhtml -o report rep.info
	open report/index.html

check:
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config $(SOURCE) *.h
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extensions=c $(SOURCE) *.h
	rm -rf CPPLINT.cfg
	make test
ifeq ($(OS), Darwin)
	leaks --atExit -- test
else
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./test
endif
