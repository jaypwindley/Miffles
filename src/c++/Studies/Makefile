PGM := foo
OBJ := foo.o

OPTIM := -O4

$(PGM): $(OBJ)
	g++ -std=gnu++11 $(OPTIM) -o $(PGM) `pkg-config --libs gtkmm-3.0` $(OBJ)

.cpp.o:
	g++ -std=gnu++11 $(OPTIM) -c `pkg-config --cflags gtkmm-3.0` $<

clean:
	rm -f $(PGM) $(OBJ) *~
