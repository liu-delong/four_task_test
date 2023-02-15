test:test.cpp solution.cpp sudoku_dancing_links.cc neighbor.cc redundance_code.h sudoku_generator.cpp
	g++ test.cpp solution.cpp sudoku_dancing_links.cc neighbor.cc redundance_code.cpp sudoku_generator.cpp -O0 -lpthread -o $@
clean:
	rm -rf test
test2:
	@echo bujunheng
	sudo perf stat -e cache-misses ./test_bujunheng
	@echo junheng
	sudo perf stat -e cache-misses ./test_junheng
	@echo junheng
	sudo perf stat -e cache-misses ./test_junheng
	@echo bujunheng
	sudo perf stat -e cache-misses ./test_bujunheng

four_matrix_task:main.cpp
	g++ main.cpp -O0 -lpthread -o $@
fmt_test:four_matrix_task
	sudo perf stat -e cache-misses ./four_matrix_task bujunheng
	sudo perf stat -e cache-misses ./four_matrix_task
