
include makefile.head

all: $(DIR) $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $^ $(LDFLAGS) $(LIBS) -o $@
	rm -rf $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)


clean:
	rm -rf $(BIN_NAME)
