# Variabili
CC = gcc
CFLAGS = -Wall -Werror -Iinclude

# Creo i targets per la compilazione
TARGETS = monoprocesso multiprocesso
SRC_DIR = src
BUILD_DIR = build

# Trovo tutti i file sorgenti comuni
COMMON_SRCS = $(wildcard $(SRC_DIR)/*.c)

# Divido i file sorgenti per monoprocesso e multiprocesso
MONO_SRCS = $(filter-out $(SRC_DIR)/multiprocesso.c,$(COMMON_SRCS))
MULTI_SRCS = $(filter-out $(SRC_DIR)/monoprocesso.c,$(COMMON_SRCS))

# Creo gli oggetti comuni, monoprocesso e multiprocesso
COMMON_OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(COMMON_SRCS))
MONO_OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(MONO_SRCS))
MULTI_OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(MULTI_SRCS))

# Target predefinito "all" per compilare tutti i target
all: $(TARGETS)

# Regola di compilazione per il target "monoprocesso"
monoprocesso: $(MONO_OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	
# Regola di compilazione per il target "multiprocesso"
multiprocesso: $(MULTI_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Regola per la compilazione degli oggetti
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Regola per la pulizia
clean:
	rm -f $(BUILD_DIR)/*.o $(TARGETS)

.PHONY: all clean


