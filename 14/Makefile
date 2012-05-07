CXX=g++-4.7
CXXFLAGS=-std=c++0x -O3 -g -I.
CXXLIBS=
SOURCES=solution.cxx
ADDITIONAL_SOURCES=
TARGET=solution
TOKEN="iZi5G3iJk6fOoHt0QLwS"
TARBALL=$(TARGET).tgz

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $^ $(CXXLIBS) -o $@

test: $(TARGET)
	python ../Tools/test_challenge.py $(TOKEN) ./$(TARGET)

submit: $(TARGET) $(TARBALL)
	python ../Tools/submit_challenge.py $(TOKEN) $(TARBALL) ./$(TARGET)

$(TARBALL): $(SOURCES) Makefile
	tar -czf $(TARBALL) $(SOURCES) $(ADDITIONAL_SOURCES) Makefile

clean:
	rm -f $(TARGET) $(TARBALL)
