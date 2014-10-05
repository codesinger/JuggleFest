
PROF_OPT :=
#PROF_OPT := -pg
LDPROF_OPT :=

ifneq (,$(PROF_OPT))
  LDPROF_OPT := -g $(PROF_OPT)
endif

INCL_PATH := 

CXXFLAGS := -Wall -W -Werror -ansi -pedantic -fPIC -m64 -g3 -fmessage-length=0
CFLAGS := -Wall -Werror -fPIC -m64 -g3  $(INCL_PATH)
CC := gcc
CXX := g++

CXXFLAGS += $(PROF_OPT)

ALL_SOURCE := \
assign.cpp \
circuit.cpp \
juggler.cpp \
juggler_circuit.cpp \
scheduler.cpp \
talent.cpp




ALL_SRC := $(ALL_SOURCE)

D_FILES1 := $(ALL_SOURCE:%.cpp=%.d)

ALL_D_FILES := $(D_FILES1:%.c=%.d)

COMMON_OBJ := $(ALL_SOURCE:%.cpp=%.o)
ALL_OBJ := $(COMMON_OBJ:%.c=%.o)

.PHONY: all

all: assign


%.d : %.cpp		 
		 g++ -MM $(INCL_PATH) $< | sed 's/$*.o/& $@/g' > $@

%.d : %.c
		 gcc -MM $(INCL_PATH) $< | sed 's/$*.o/& $@/g' > $@


assign: $(ALL_OBJ)
		 $(CXX) -o $@ $^ $(LDPROF_OPT)


include $(ALL_D_FILES)

.PHONY: clean

clean:
		 - rm -f assign *.o *.d

%.d : %.cpp		 
		 g++ -MM $(INCL_PATH) $< | sed 's/$*.o/& $@/g' > $@

#include $(ALL_SRC:.cpp=.d)


