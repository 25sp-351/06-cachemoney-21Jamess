CC = gcc
CFLAGS = -Wall -Wextra -g

MAIN_SRCS = main.c money_to_string.c cache.c bozo_cache.c
MAIN_OBJS = main.o money_to_string.o cache.o bozo_cache.o

COMMON_SRCS = money_to_string.c cache.c bozo_cache.c
COMMON_OBJS = money_to_string.o cache.o bozo_cache.o

TEST_SRCS = tests.c
TEST_OBJS = tests.o

TARGET = moneytostring
TEST_TARGET = tests

all: $(TARGET) $(TEST_TARGET)

$(TARGET): main.o $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) main.o $(COMMON_OBJS)

$(TEST_TARGET): tests.o $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) tests.o $(COMMON_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(MAIN_OBJS) $(TEST_OBJS) $(TARGET) $(TEST_TARGET)

.PHONY: all clean
