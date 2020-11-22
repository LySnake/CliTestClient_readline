CXXFLAGS := -g -std=c++11 -DREADLINE_LIBRARY

INCLUDE_PATH := -I.\
                -Ilib/readline\
                -Ilib/spdlog/include/

SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp, %.o, $(SRCS))
DEPS := $(patsubst %.cpp, %.d, $(SRCS))

TARGET := testClient

.PHONY: all
all : $(TARGET)
	@echo compile all finish.

$(TARGET) : $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ -lreadline -pthread 


%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_PATH) -c -o $@ $<

#生成*.d，*.d中记录了cpp与依赖的*.h的生成依赖关系，保证每次源码修改每一个CPP可以直接make成最新的状态，而避免全编译
%.d : %.cpp
	@set -e; rm -f $@; \
	$(CXX) -MM $(CXXFLAGS) $(INCLUDE_PATH) $< > $@.$$$$;\
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

-include $(DEPS)

.PHONY: clean
clean :
	@rm -rf *.o  *.d *.d.*
	@rm -rf $(TARGET)
	@echo "Clean finish!"