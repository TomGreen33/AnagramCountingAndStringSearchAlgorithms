This program was my final submission for assignment 3 of my computer algorithms course at the university
of Guelph (CIS 3490). I took this course during the winter of 2021 alongside my full time job as a
technical support analyst.

The first two options of the program are used to count the number of anagrams of a given input
within anagrams.txt. An anagram is simply a string formed from another string by rearranging the latter's
symbols. For instance, 1234 and 1423 are anagrams of 1234; eat and ate are anagrams of tea. Because 
anagrams.txt is simply a list of numbers. As such, an example of an input for the program could be 1827336327, 
which returns anagrams 1386723723 and 1773238632, both of which can be found within anagrams.txt (by using ctrl + F). 
The first algorithm simply iterates through each string in the text file and checks whether it is an anagram 
of the original input, while the smart algorithm presorts the anagrams.txt file, and then 
uses the same logic as that of binary search. 

Options 3, 4, and 5 are simply string searching algorithms. They search for occurances of an input string 
within the stringSearch.txt file. Option 3 does so using a brute force algorithm, option 4 does so using 
Horspool's algorithm, and option 5 does so using Boyer-Moore's algorithm.

The following section was the original read me file that was part of the assignment's submission. It contains information on how to compile the
program, as well as efficiency analysis for the string search algorithms:


Name: Thomas Green
ID: 1048389
Assignment #: 3

Please insert the test files into the folder.
Use make to compile the program.
Use ./main to run the program.
Use make clean to clear the directory of any object files.

The following table is used to compare the brute force string search algorithm to that of the Horspool's algorithm (2.4): 

		Brute Force  	Horspool 	Brute Force 	Brute Force  	Horspool 	Brute Force 
        	Running Time	Running Time	/ Horspool 	Pattern Shifts	Pattern Shift	/ Horspool 
						Running Time					Shift Ratio
						Ratio

Dog		0.0625		0.03125		2		3296591		1139503		2.893007741
Book		0.0625		0.015625	4		3296591		858204		3.841267344
House		0.0625		0.015625	4		3296591		712336		4.627859606
Chapter		0.0625		0.015625	4		3296591		565519		5.829319616
bringing	0.0625		0.015625	4		3296591		468322		7.039154684
excellent	0.0625		0.015625	4		3296591		428366		7.695734489
assessment	0.0625		0.015625	4		3296591		395448		8.336345107
Engineering	0.0625		0.015625	4		3296591		374722		8.797431162
relationship	0.0625		0.015625	4		3296591		374799		8.795623788
governmental	0.0625		0.015625	4		3296591		378403		8.711852179

Average				3.8				6.656759572

						
Analysis: 

As can be seen, the brute force algorithm is on average about 3.8 times slower than the Horspool algorithm 
in terms of excecution time. Furthermore, the brute force algorithm performs about 6.657 times more shifts 
than the Horspool algorithm. This makes sense, as more shifts would result in a longer excecution time 
(as it can be considered as the basic operation). As such, it would be wise to utilize the Horspool algorithm 
in a software project, as it would yield faster run times.					
