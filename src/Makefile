CC = gcc -Wall -Werror -Wextra -std=c++17

all: my_matrix_oop.a

clean:
	rm -rf *.o *.a *.out *.info report my_test.dSYM *.gcno my_test

test: clean
	$(CC) test.cc my_matrix_oop.cc -lgtest -o my_test -lstdc++
	./my_test

my_matrix_oop.a:
	$(CC) -c my_matrix_oop.cc -o my_matrix_oop.o -lstdc++
	ar rcs my_matrix_oop.a *.o
	ranlib my_matrix_oop.a

gcov_report: 
	$(CC) --coverage my_matrix_oop.cc -c -lstdc++
	$(CC) test.cc -c -lstdc++
	$(CC) --coverage *.o -lgtest -o my_test -lstdc++
	./my_test
	lcov -t "my_test" -c -d ./ --output-file ./test.info
	genhtml -o report test.info
	rm -rf *.gcda *.gch *.gcno *.out *.o *.out
	open report/index.html

style:
	clang-format -n --style=Google *.cc *.h

leaks: test
	leaks -atExit -- ./my_test
