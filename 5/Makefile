SOURCES=solution.py
TARGET=solution.py
TOKEN="Ar72lW2r7PO-FLV0QLwS"
TARBALL=solution.tgz

test: $(TARGET)
	python ../Tools/test_challenge.py $(TOKEN) python $(TARGET)

submit: $(TARGET) $(TARBALL)
	python ../Tools/submit_challenge.py $(TOKEN) $(TARBALL) python $(TARGET)

$(TARBALL): $(SOURCES) Makefile
	tar -czf $(TARBALL) $(SOURCES) Makefile

clean:
	rm -f $(TARGET) $(TARBALL)
