CC = gcc
CFLAGS = -Wall -Iunity -I../include

# Soubory
SRC = password_generator.c strength_check.c compromise_check.c
OBJS = $(SRC:.c=.o)

TEST_SRC = ../tests/test_password_generator.c ../tests/test_strength_check.c ../tests/test_compromise_check.c ../tests/main_test.c
TEST_OBJS = ../tests/test_password_generator.o ../tests/test_strength_check.o ../tests/test_compromise_check.o ../tests/main_test.o

UNITY_SRC = ../unity/unity.c
UNITY_OBJ = ../unity/unity.o

TARGET = tests

# Výchozí cíl
all: $(TARGET)

# Kompilace zdrojových testovacích souborů
../tests/test_password_generator.o: ../tests/test_password_generator.c
	$(CC) $(CFLAGS) -c $< -o $@

../tests/test_strength_check.o: ../tests/test_strength_check.c
	$(CC) $(CFLAGS) -c $< -o $@

../tests/test_compromise_check.o: ../tests/test_compromise_check.c
	$(CC) $(CFLAGS) -c $< -o $@

../tests/main_test.o: ../tests/main_test.c
	$(CC) $(CFLAGS) -c $< -o $@

# Kompilace Unity testovací knihovny
$(UNITY_OBJ): $(UNITY_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

# Kompilace hlavního binárního souboru
$(TARGET): $(OBJS) $(TEST_OBJS) $(UNITY_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Vyčištění
clean:
	rm -f $(OBJS) $(TEST_OBJS) $(UNITY_OBJ) $(TARGET)

# Spuštění testů
run: $(TARGET)
	./$(TARGET)
