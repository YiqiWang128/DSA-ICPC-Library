g++ make_random_data.cpp -o make_random_data -g
g++ code_to_test.cpp -o code_to_test -g
g++ correct_solution.cpp -o correct_solution -g
:loop
	make_random_data.exe >input_data.txt
	code_to_test.exe <input_data.txt >output_test.txt
	correct_solution.exe <input_data.txt >output_correct.txt
	fc output_test.txt output_correct.txt
if not errorlevel 1 goto loop
pause
goto loop