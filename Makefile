service: cli.o
	$(CXX) $< $(LDFLAGS) -o $@
cli.o: cli.cpp
version:
	$(CXX) --version

clean:
	rm -f cli.o service
