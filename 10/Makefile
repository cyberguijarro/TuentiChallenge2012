CXX=g++-4.7
CXXFLAGS=-std=c++0x -O3 -g
CXXLIBS=
SOURCES=solution.cxx
TARGET=solution
TOKEN="LzLw-DPofPhsbFd0QLwS"
TARBALL=$(TARGET).tgz

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $^ $(CXXLIBS) -o $@

test: $(TARGET)
	python ../Tools/test_challenge.py $(TOKEN) ./$(TARGET)

submit: $(TARGET) $(TARBALL)
	python ../Tools/submit_challenge.py $(TOKEN) $(TARBALL) ./$(TARGET)

$(TARBALL): $(SOURCES) Makefile
	tar -czf $(TARBALL) $(SOURCES) Makefile

clean:
	rm -f $(TARGET) $(TARBALL)
