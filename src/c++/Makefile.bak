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

annunciator.o: annunciator.h midget.h /usr/include/assert.h
annunciator.o: /usr/include/features.h /usr/include/stdc-predef.h types.h
annunciator.o: settable.h frame.h
annunciators.o: annunciators.h annunciator.h midget.h /usr/include/assert.h
annunciators.o: /usr/include/features.h /usr/include/stdc-predef.h types.h
annunciators.o: settable.h macros.h
app.o: /usr/include/fcntl.h /usr/include/features.h
app.o: /usr/include/stdc-predef.h /usr/include/time.h /usr/include/assert.h
app.o: app.h dashboard.h types.h tickable.h input_demux.h settable.h
background.o: background.h midget.h /usr/include/assert.h
background.o: /usr/include/features.h /usr/include/stdc-predef.h types.h
channel.o: /usr/include/ctype.h /usr/include/features.h
channel.o: /usr/include/stdc-predef.h /usr/include/endian.h
channel.o: /usr/include/xlocale.h /usr/include/stdio.h /usr/include/libio.h
channel.o: /usr/include/_G_config.h /usr/include/wchar.h channel.h
clock.o: app.h /usr/include/assert.h /usr/include/features.h
clock.o: /usr/include/stdc-predef.h dashboard.h types.h scale.h domain.h
clock.o: sweep.h tickable.h meter.h frame.h midget.h field.h macros.h
clock.o: graduation.h indicators.h indicator.h settable.h input_demux.h
clock.o: channel.h annunciators.h annunciator.h label.h text.h
color.o: /usr/include/assert.h /usr/include/features.h
color.o: /usr/include/stdc-predef.h /usr/include/stdio.h /usr/include/libio.h
color.o: /usr/include/_G_config.h /usr/include/wchar.h /usr/include/string.h
color.o: /usr/include/xlocale.h types.h
dashboard.o: dashboard.h types.h frame.h
discrete.o: discrete.h midget.h /usr/include/assert.h /usr/include/features.h
discrete.o: /usr/include/stdc-predef.h types.h frame.h
frame.o: types.h frame.h midget.h /usr/include/assert.h
frame.o: /usr/include/features.h /usr/include/stdc-predef.h
graduation.o: graduation.h midget.h /usr/include/assert.h
graduation.o: /usr/include/features.h /usr/include/stdc-predef.h types.h
graduation.o: field.h
indicator.o: /usr/include/assert.h /usr/include/features.h
indicator.o: /usr/include/stdc-predef.h sweep.h tickable.h scale.h domain.h
indicator.o: indicator.h midget.h types.h settable.h frame.h
indicators.o: indicators.h indicator.h midget.h /usr/include/assert.h
indicators.o: /usr/include/features.h /usr/include/stdc-predef.h types.h
indicators.o: settable.h macros.h meter.h frame.h field.h
input_demux.o: /usr/include/assert.h /usr/include/features.h
input_demux.o: /usr/include/stdc-predef.h input_demux.h settable.h channel.h
label.o: label.h midget.h /usr/include/assert.h /usr/include/features.h
label.o: /usr/include/stdc-predef.h types.h text.h
meter.o: meter.h frame.h types.h midget.h /usr/include/assert.h
meter.o: /usr/include/features.h /usr/include/stdc-predef.h field.h
midget.o: midget.h /usr/include/assert.h /usr/include/features.h
midget.o: /usr/include/stdc-predef.h types.h
nest.o: app.h /usr/include/assert.h /usr/include/features.h
nest.o: /usr/include/stdc-predef.h dashboard.h types.h scale.h domain.h
nest.o: sweep.h tickable.h meter.h frame.h midget.h field.h macros.h
nest.o: indicators.h indicator.h settable.h input_demux.h channel.h label.h
nest.o: text.h nest.h background.h readout.h
nest_funcs.o: nest.h background.h midget.h /usr/include/assert.h
nest_funcs.o: /usr/include/features.h /usr/include/stdc-predef.h types.h
nest_funcs.o: indicator.h settable.h readout.h label.h field.h meter.h
nest_funcs.o: frame.h
readout.o: readout.h label.h midget.h /usr/include/assert.h
readout.o: /usr/include/features.h /usr/include/stdc-predef.h types.h
readout.o: settable.h
scale.o: /usr/include/stdio.h /usr/include/features.h
scale.o: /usr/include/stdc-predef.h /usr/include/libio.h
scale.o: /usr/include/_G_config.h /usr/include/wchar.h /usr/include/math.h
scale.o: scale.h domain.h
settable.o: settable.h app.h /usr/include/assert.h /usr/include/features.h
settable.o: /usr/include/stdc-predef.h input_demux.h
sweep.o: /usr/include/math.h /usr/include/features.h
sweep.o: /usr/include/stdc-predef.h sweep.h tickable.h
text.o: text.h types.h
tickable.o: /usr/include/assert.h /usr/include/features.h
tickable.o: /usr/include/stdc-predef.h tickable.h dashboard.h types.h frame.h
