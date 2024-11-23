.PHONY: clean

TARGET_EXEC = run

SOURCE_DIR = ./code
OUTPUT_DIR = ./exec

SRCS := $(shell find $(SOURCE_DIR) -name "*.cxx")
OBJS := $(SRCS:%=$(OUTPUT_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INCLUDE_DIRS := $(shell find $(SOURCE_DIR) -type d)
INCLUDE_FLAG := $(addprefix -I,$(INCLUDE_DIRS))

C++ = g++ -std=c++20

LINKER_FLAG =
COMPILER_FLAG = -MMD -MP
DEBUGGER_FLAG = -O0 -g3

LINKER = $(C++) $(LINKER_FLAG)
COMPILER = $(C++) $(COMPILER_FLAG) $(DEBUGGER_FLAG) $(INCLUDE_FLAG)

RMDIR = rm --recursive
MKDIR = mkdir --parents

# LINK
$(OUTPUT_DIR)/$(TARGET_EXEC): $(OBJS)
	$(LINKER) -o $@ $(OBJS)

# COMPILE
$(OUTPUT_DIR)/%.cxx.o: %.cxx
	$(MKDIR) $(dir $@)
	$(COMPILER) -o $@ -c $<

clean:
	$(RMDIR) $(OUTPUT_DIR)

-include $(DEPS)