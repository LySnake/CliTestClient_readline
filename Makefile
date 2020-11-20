CXXFLAGS := -g -std=c++11 -DREADLINE_LIBRARY

OBJ_PATH := .
SRC_PATH := .
INCLUDE_PATH := -I.\
                -Ilib/readline

SRCS  := $(wildcard $(SRC_PATH)/*.cpp)
OBJS := $(patsubst $(SRC_PATH)/%.cpp, $(OBJ_PATH)/%.o, $(SRCS))
DEPS := $(patsubst $(SRC_PATH)/%.cpp, $(OBJ_PATH)/%.d, $(SRCS))

TARGET := testClient

.PHONY: all
all : $(TARGET)
	@echo compile all finish.

$(TARGET) : $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ -lreadline -ltermcap  -pthread 


%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_PATH) -c -o $@ $<

#生成*.d，*.d中记录了cpp与依赖的*.h的生成依赖关系，保证每次源码修改每一个CPP可以直接make成最新的状态，而避免全编译
$(OBJ_PATH)/%.d : $(SRC_PATH)/%.cpp
	@set -e; rm -f $@; \
	$(CXX) -MM $(CXXFLAGS) $(INCLUDE_PATH) $< > $@.$$$$;\
	sed 's,\($*\)\.o[ :]*,/\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

-include $(DEPS)

.PHONY: clean
clean :
	@rm -rf $(OBJ_PATH)/*.o  $(OBJ_PATH)/*.d $(OBJ_PATH)/*.d.*
	@rm -rf $(TARGET)
	@echo "Clean finish!"