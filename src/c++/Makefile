PGM := nest
OBJ := nest.o
LIB := libmiffles

# Objects needed to build Miffles library.
LIBOBJ :=           \
	annunciator.o   \
	annunciators.o  \
	app.o           \
	background.o    \
	channel.o       \
	color.o         \
	dashboard.o     \
	discrete.o      \
	frame.o         \
	graduation.o    \
	indicator.o     \
	indicators.o    \
	input_demux.o   \
	label.o         \
	meter.o         \
	midget.o        \
	nest_funcs.o    \
	readout.o       \
	scale.o         \
	settable.o      \
	sweep.o         \
	text.o          \
	tickable.o

OPTIM := -g
#OPTIM := -O4
STD   := -std=gnu++11

$(LIB): $(LIBOBJ)
	ar crv libmiffles.a $(LIBOBJ)
	g++ -o $(LIB).so -shared $(LIBOBJ)

$(PGM): $(OBJ)
	g++ $(STD) $(OPTIM) -o $(PGM) `pkg-config --libs gtkmm-3.0` $(OBJ) -L. -lmiffles

.cpp.o:
	g++ $(STD) $(OPTIM) -fPIC -c `pkg-config --cflags gtkmm-3.0` $<

clean:
	rm -f $(PGM) $(OBJ) $(LIB).a $(LIB).so $(LIBOBJ) *~
# DO NOT DELETE
