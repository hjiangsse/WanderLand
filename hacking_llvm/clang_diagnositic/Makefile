LLVM_CONFIG?=llvm-config

SRC_DIR?=$(PWD)
LDFLAGS+=$(shell $(LLVM_CONFIG) --ldflags)
COMMON_FLAGS=-w
CXXFLAGS=$(COMMON_FLAGS) $(shell $(LLVM_CONFIG) --cxxflags)
CPPFLAGS=$(shell $(LLVM_CONFIG) --cppflags) -I$(SRC_DIR)

LLVMLIBS=$(shell $(LLVM_CONFIG) --libs)
CLANGLIBS =  -Wl,--start-group \
	     -lclang \
	     -Wl,--end-group \

default: clang_diag

clang_diag.o : $(SRC_DIR)/clang_diag.cpp
	@echo Compiling clang_diag.cpp
	@clang++ -c $(CPPFLAGS) $(CXXFLAGS) clang_diag.cpp

clang_diag : clang_diag.o
	@echo Linking $@
	@clang++ -o clang_diag $(CXXFALGS) $(LDFLAGS) $^ $(CLANGLIBS) $(LLVMLIBS)
