sources = $(wildcard *.cpp)
objects = $(sources:%.cpp=%.o)
deps = $(sources:%.cpp=%.d)
CFLAGS += -g
CXXFLAGS += -g

CPPFLAGS = -DSHOW_NETWORK
override CPPFLAGS += -Isexp

all: $(objects) sexp/libclient_sexp.a visualizer

%.d: %.cpp
	@set -e; rm -f $@; \
	(dirname $< | tr '\n' '/'; $(CXX) -MM $(CPPFLAGS) $<) > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

.PHONY: clean all subdirs

clean:
	rm -f $(objects) $(deps) visualizer
	$(MAKE) -C sexp clean

visualizer: $(objects) sexp/sexp.a
	$(CXX) $(LDFLAGS) $(LOADLIBES) $(LDLIBS) $^ -g -o visualizer

sexp/sexp.a sexp/libclient_sexp.a:
	$(MAKE) -C $(dir $@) $(notdir $@)

-include $(deps)
