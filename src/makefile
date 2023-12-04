CC=g++
FLAGS=-std=gnu++17 -Wall -Wextra -Werror

OS=$(shell uname)
ifeq ($(OS), Linux)
  LIBS=--coverage -lgtest -lpthread 
else
  LIBS=--coverage -lgtest
endif

all: install

run:
ifeq ($(OS), Darwin)
	@../build/Mazik.app/Contents/MacOS/Mazik
endif

gcov_report: tests
	@lcov --no-external --capture --directory  . --output-file coverage.info 
	@genhtml -o report coverage.info
	open ./report/index.html

style:
	clang-format -n -style=Google model/*.cc model/*.h --verbose
	clang-format -n -style=Google ui/*.cpp ui/*.h --verbose
	clang-format -n -style=Google tests/*.cc --verbose

tests: clean
	$(CC) $(FLAGS) tests/tests.cc back/*.cc $(LIBS) && ./a.out

install: uninstall
	@mkdir -p ../build
	@cd ../build && cmake ../src/front > /dev/null 2>&1
	@make -C ../build > /dev/null 2>&1
	
ifneq ($(OS), Linux)
	@mkdir -p ~/Applications ; cp -r ./../build/Mazik.app ~/Applications/Mazik.app
endif

	@echo "Done!"
	@echo "*if you use mac - press F4*"

uninstall: clean
	@rm -rf ~/Applications/Mazik.app

dist:
	@cd .. && tar -czvf Mazik.tar src

dvi:
	@open dvi.html

clean:
	@rm -rf ../build ../.vscode a.out *.gcno *.gcda *.info tests/*txt coverage_report report build
