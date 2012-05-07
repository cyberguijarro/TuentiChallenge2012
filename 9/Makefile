SOURCES=solution.py
ADDITIONAL_SOURCES=indexer.py
TARGET=solution.py
TOKEN="HqyurCG98BPUYHJ0QLwS"
TARBALL=solution.tgz

test: $(TARGET)
	python ../Tools/test_challenge.py $(TOKEN) python $(TARGET)

submit: $(TARGET) $(TARBALL)
	python ../Tools/submit_challenge.py $(TOKEN) $(TARBALL) python $(TARGET)

$(TARBALL): $(SOURCES) Makefile
	tar -czf $(TARBALL) $(SOURCES) $(ADDITIONAL_SOURCES) Makefile

clean:
	rm -f $(TARBALL)
