test:test.cpp solution.cpp sudoku_dancing_links.cc neighbor.cc redundance_code.h sudoku_generator.cpp
	g++ test.cpp solution.cpp sudoku_dancing_links.cc neighbor.cc redundance_code.cpp sudoku_generator.cpp -O0 -lpthread -o $@
clean:
	rm -rf test