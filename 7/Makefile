CXX=g++-4.7
CXXFLAGS=-std=c++0x -O3
SOURCES=solution.cxx
TARGET=solution
TOKEN="wvb02xJh99NZyIN0QLwS"
TARBALL=$(TARGET).tgz

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $^ -o $@

test: $(TARGET)
	python ../Tools/test_challenge.py $(TOKEN) ./$(TARGET)

submit: $(TARGET) $(TARBALL)
	python ../Tools/submit_challenge.py $(TOKEN) $(TARBALL) ./$(TARGET)

$(TARBALL): $(SOURCES) Makefile
	tar -czf $(TARBALL) $(SOURCES) Makefile

clean:
	rm -f $(TARGET) $(TARBALL)
