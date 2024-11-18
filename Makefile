# Compiler & Flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Igoogletest/googletest/include -pthread


#Directories
SRC_DIR = src
TEST_DIR = tests
THIRD_PARTY_DIR = googletest

# Source and object files
SRC_FILES = $(SRC_DIR)/main.cpp $(SRC_DIR)/customerBasket.cpp \
			$(SRC_DIR)/printer.cpp $(SRC_DIR)/productDatabase.cpp \
			$(SRC_DIR)/UI.cpp
OBJ_FILES = $(SRC_DIR)/customerBasket.o \
			$(SRC_DIR)/printer.o $(SRC_DIR)/productDatabase.o \
			$(SRC_DIR)/UI.o
TEST_FILES = $(TEST_DIR)/test_customerBasket.cpp $(TEST_DIR)/test_printer.cpp \
			 $(TEST_DIR)/test_productDatabase.cpp $(TEST_DIR)/test_UI.cpp
TEST_OBJ_FILES = $(TEST_DIR)/test_customerBasket.o $(TEST_DIR)/test_printer.o \
			 $(TEST_DIR)/test_productDatabase.o $(TEST_DIR)/test_UI.o

# GTest-related files
GTEST_DIR = $(THIRD_PARTY_DIR)/googletest
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)
GTEST_OBJ = gtest-all.o
GTEST_MAIN = $(GTEST_DIR)/src/gtest_main.cc
GTEST_MAIN_OBJ = gtest_main.o
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

CPPFLAGS += -isystem $(GTEST_DIR)/include

# Targets
TARGET = checkout
TEST_TARGET = test_checkout

# Build main project
all: $(TARGET)

$(TARGET): $(OBJ_FILES) $(SRC_DIR)/main.o 
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ_FILES) $(SRC_DIR)/main.o

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build and run tests
test: $(GTEST_OBJ) $(GTEST_MAIN_OBJ) $(TEST_OBJ_FILES) $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(GTEST_OBJ) $(GTEST_MAIN_OBJ) $(TEST_OBJ_FILES) $(OBJ_FILES)
	./$(TEST_TARGET)

$(TEST_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(GTEST_OBJ) : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

$(GTEST_MAIN_OBJ) : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_MAIN)

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

# Clean up
clean:
	rm -f $(OBJ_FILES) $(TEST_OBJ_FILES) $(GTEST_OBJ) $(GTEST_MAIN_OBJ) $(TARGET) $(TEST_TARGET) $(SRC_DIR)/main.o