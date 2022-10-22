OUTFILE = wordle-solver.exe

build:
	g++ main.cc -o $(OUTFILE)
build-debug:
	g++ -g main.cc -o $(OUTFILE)
clean:
	rm -f $(OUTFILE)
test:
	./$(OUTFILE)
debug:
	gdb ./$(OUTFILE)