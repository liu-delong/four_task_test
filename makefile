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
.PHONY:fmt_test_pro
fmt_test_pro:
	echo matrix_size,task1_cnt,task2_cnt,mode,cache-misses,total_time,epoch>log.csv
	@for epoch in 1 2 3 4 5 6 7 8 9 10;do\
		for matrix_size in 10 100 1000; do \
			for time in 1006 1210 2010;do \
				mul_time_1=$$((time/100));\
				mul_time_2=$$((time%100));\
				g++ main.cpp -O0 -D matrix_size=$$matrix_size -D mul_time_1=$$mul_time_1 -D mul_time_2=$$mul_time_2 -lpthread -o $@;\
				\
				echo matrix_size:$$matrix_size task1_cnt:$$mul_time_1 task2_cnt:$$mul_time_2 mode:bujunheng;\
				echo $$matrix_size $$mul_time_1 $$mul_time_2 bujunheng > temp.txt;\
				sudo perf stat -e cache-misses ./$@ bujunheng 2>temp2.txt && cat temp2.txt|awk '/cache-misses|seconds time elapsed/{print $$1}'|sed 's/,/""/g' >> temp.txt;\
				echo $$epoch >> temp.txt;\
				cat temp.txt | xargs |sed 's/[ ][ ]*/,/g'>> log.csv;\
				\
				echo messageLine---- matrix_size:$$matrix_size task1_cnt:$$mul_time_1 task2_cnt:$$mul_time_2 mode:junheng;\
				echo $$matrix_size $$mul_time_1 $$mul_time_2 junheng > temp.txt;\
				sudo perf stat -e cache-misses ./$@ 2>temp2.txt && cat temp2.txt|awk '/cache-misses|seconds time elapsed/{print $$1}'|sed 's/,/""/g'>>temp.txt;\
				echo $$epoch >> temp.txt;\
				cat temp.txt |xargs |sed 's/[ ][ ]*/,/g'>> log.csv;\
				\
			done;\
		done;\
	done


