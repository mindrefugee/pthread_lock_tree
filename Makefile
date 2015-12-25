TARGET=pthread_lock_tree

.PHONY: all clean

all:$(TARGET)



$(TARGET): main.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LDADD)

main.o: pc_map.h MT.h


clean:
	-rm *.o $(TARGET)
