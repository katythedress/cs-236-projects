I'm not proud of this code, but I'm leaving it here for some poor kid who's failing the class. Yay, BYU.

These assignments are written in C++ and together make a sort of "interpreter" for simple Datalog "programs." Each of these labs passes according to the fall 2014 requirements. I had Barker as a professor. Crazy dude.

There is a "tests" folder for each project. "inX.txt" is the input for the program and "outX\_real.txt" is the expected output from the program. "outX.txt" will be generated each time you run a terminal command similar to the one below and should be compared to "outX\_real.txt" to see if your program passes the lab requirements. The above-mentioned text files were provided by the professor and renamed for convenience by me.

If you run the following terminal command (after using "cd" to get to the directory containing the lab you want to play with), you'll be greeted with a cycolomatic complexity analysis courtesy of "pmccabe" (according to the lab requirements, no function can have a complexity level greater than 8; pay attention to the first number on each line), a memory leak check from "valgrind," and (hopefully) no output from "diff" (if diff doesn't print anything, that means the output from the program that ends up in "out1.txt" is identical to "out1_real.txt" which contains the expected output).

    pmccabe *.h *.cpp; g++ -Wall -g -std=c++11 *.cpp -o main && valgrind --leak-check=full ./main "tests/in1.txt" "tests/out1.txt" && diff "tests/out1.txt" "tests/out1_real.txt"

Enjoy all the hacks.
