a.out: main.cpp reader/transaction_parser.cpp processor/food_item.cpp processor/warehouse.cpp processor/inventory_item.cpp reader/transaction.cpp reader/file_data.cpp processor/processor.cpp
	g++ -std=c++11 $^

profile: main.cpp reader/transaction_parser.cpp processor/food_item.cpp processor/warehouse.cpp processor/inventory_item.cpp reader/transaction.cpp reader/file_data.cpp processor/processor.cpp
	g++ -pg -std=c++11 $^

analysis: 
	gprof ./a.out gmon.out > analysis.txt

clean:
	rm -f *.out analysis.txt
