CC=cc
#어떤 컴파일ㄹ러를 사용할 것인가?
CFLAGS=-std=c99
#컴파일러 옵션. c99를 사용한다. 
CFLAGS+=-W -Wall
#모든 Warning message 숨기기 옵션 / 일부 경고 메세지 키기.
#CFLAGS+=-O3
CFLAGS+=-O0 -g -ggdb
#컴파일 시간을 줄여주고 예상되는 디버깅을 해준다 / Debugging information을 생성한다. / GDB를 이용한 디버깅 information을 생성한다.
CFLAGS+=-MMD  # generate dependency .d files
#Like -MD except mention only user header files, not system header files.

LDLIBS=
LDFLAGS=

SRCS=src/foo-test.c src/foo.c src/bar/bar.c
#source file
TARGETS=src/foo-test libfoo.a libbar.a
#target

libbar.a: src/bar/bar.o
libfoo.a: src/foo.o
src/foo-test: src/foo-test.o libfoo.a libbar.a
#target과 prerequisites들이다. 

TEST_SUITE=src/foo-test

.DEFAULT_GOAL=all
.PHONY: all
all: $(TARGETS)

SRC_DIR ?= $(patsubst %/,%, $(dir $(abspath $(firstword $(MAKEFILE_LIST)))))
CFLAGS+=-I$(SRC_DIR)/include
#Include directory의 위치 설정

.PHONY: clean
#모든 임시 파일들을 삭제한다.
clean:
	$(RM) $(TARGETS)
	$(RM) $(OBJS)
	$(RM) $(DEPS)
	$(RM) cscope.out cscope.out.in cscope.out.po
	$(RM) tags TAGS
ifeq ($(COVERAGE), 1)
	$(RM) -r coverage
	$(RM) coverage.info
	$(RM) $(OBJS:.o=.gcno)
	$(RM) $(OBJS:.o=.gcda)
endif
ifeq ($(PROFILE), 1)
	$(RM) gmon.out
	$(RM) gprof.out
endif
ifneq ($(SRC_DIR), $(CURDIR))
	-@rmdir $(OBJDIRS)
endif

.PHONY: test
#TEST_SUITE를 통한 테스트
test: $(TEST_SUITE)
	$(CURDIR)/$(TEST_SUITE)

#SRCS=$(notdir $(wildcard $(SRC_DIR)src/*.c))
OBJS=$(SRCS:.c=.o)
DEPS=$(OBJS:.o=.d)

# Object file subdirectories
ifneq ($(SRC_DIR), $(CURDIR))
vpath %.c $(SRC_DIR)

#타겟을 만들기 위한 OBJ파일들
OBJDIRS=$(filter-out $(CURDIR)/, $(sort $(dir $(abspath $(OBJS)))))
$(OBJDIRS): ; @mkdir $@
$(DEPS): | $(OBJDIRS)
$(OBJS): | $(OBJDIRS)
endif

-include $(DEPS)

# implicit rules for building archives not parallel safe (e.g. make -j 3)
%.a: ; ar rcs $@ $^

# cscope.out
cscope.out: $(SRCS)
	cscope -f $@ -I$(SRC_DIR)/include -bq $^

# ctags
tags: $(SRCS)
	ctags -f $@ -R $(SRC_DIR)/include $^

# etags
TAGS: $(SRCS)
	etags -f $@ -R $(SRC_DIR)/include $^

# Profile (gprof)
ifeq ($(PROFILE), 1)
CFLAGS+=-pg
LDFLAGS+=-pg

gmon.out: test

gprof.out: gmon.out
	gprof $(CURDIR)/$(TEST_SUITE) > $@

.PHONY: profile
profile: gprof.out
endif

# Coverage (gcov, lcov)
ifeq ($(COVERAGE), 1)
CFLAGS+=-ftest-coverage -fprofile-arcs
LDFLAGS+=-coverage
LDLIBS+=-lgcov

$(OBJS:.o=.gcda): test

coverage.info: $(OBJS:.o=.gcda)
	lcov --capture --base-directory $(SRC_DIR) --directory $(CURDIR) --output-file $@

coverage/index.html: coverage.info
	genhtml -o coverage $<

.PHONY: coverage
coverage: coverage/index.html
endif