CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11

SRC_PATH=./core/math_calc
FIN_SRC_PATH=./core/fin_calc

SRC = $(wildcard $(SRC_PATH)/*.c)
OBJS=$(patsubst $(SRC_PATH)/%.c, ../build/%.o,$(SRC))
FIN_SRC = $(wildcard $(FIN_SRC_PATH)/*.c)
FIN_OBJS=$(patsubst $(FIN_SRC_PATH)/%.c, ../build/%.o,$(FIN_SRC))
TEST_SRC = $(wildcard ./core/tests/*.c)
TEST_OBJS=$(patsubst ./core/tests/%.c, ../build/%.o,$(TEST_SRC))
MAIN_SRC=$(wildcard ./core/*.c)
MAIN_OBJS=$(patsubst ./core/%.c, ../build/%.o,$(MAIN_SRC))
CORE=../build/core.a
LIBS =  -lcheck -lm 
ifeq ($(filter-out $@,$(MAKECMDGOALS)),gcov_report)
	CFLAGS += --coverage
endif

ifeq ($(filter-out $@,$(MAKECMDGOALS)),debug)
	CFLAGS += -g
endif

all: 
	make uninstall
	make clean 
	make install 
	make dvi 
	make gcov_report 
	make dist
	make run

install: app_folder
	cd interface && qmake6 && make && make clean && rm -f Makefile && rm -f .qmake.stash && mv SmartCalc.app ../../appbuild


run:
	../appbuild/SmartCalc.app/Contents/MacOS/SmartCalc 

uninstall:
	rm -rf ../appbuild

dvi:
	open dvi.html

dist:
	mkdir -p ../dist
	cp -R ../appbuild/SmartCalc.app ../dist/SmartCalc.app
	cp dvi.html ../dist/SmartCalc.app/Contents/MacOS/dvi.html
	cd .. && tar -cf dist.tar dist && rm -rf dist


gcov_report: clean $(CORE) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) $(CORE) -o ../build/gcov_unit_test $(LIBS)
	../build/gcov_unit_test
	lcov -t "test" -o ../build/test.info -c -d ../build
	genhtml -o ../report/ ../build/test.info
	open ../report/index.html
	make clean_without_report


memchk: test
	leaks -atExit -- ../build/unit_test

############### подключение библиотеки к юнит тестам######################
test: $(CORE) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) $(CORE) -o ../build/unit_test $(LIBS)
	../build/unit_test


############################################################################

debug: clean $(CORE) $(MAIN_OBJS)
	$(CC) $(CFLAGS) $(MAIN_OBJS) $(CORE) -o debuge $(LIBS)
	
	
############################################################################

############### подключение библиотеки к мейну ######################
main: $(CORE) $(MAIN_OBJS)
	$(CC) $(CFLAGS) $(MAIN_OBJS) $(CORE) -o ../build/main_test $(LIBS)
	../build/main_test

############################################################################

######чистая библиотека########
$(CORE): folder $(OBJS) $(FIN_OBJS)
	ar rcs $(CORE) $(OBJS) $(FIN_OBJS)

######### Компиляция объектников
../build/%.o: $(SRC_PATH)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

../build/%.o: $(FIN_SRC_PATH)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

../build/main.o: ./core/main.c
	$(CC) $(CFLAGS) -c $< -o $@

../build/%.o: ./core/tests/%.c
	$(CC) $(CFLAGS) -c $< -o $@

folder:
	mkdir -p ../build

app_folder:
	mkdir -p ../appbuild

clean_without_report: 
	rm -f debuge
	rm -rf ../build
	rm -f ../dist.tar
	rm -rf ../dist

clean: clean_without_report
	rm -rf ../report
