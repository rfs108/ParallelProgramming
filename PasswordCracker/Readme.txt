Parallel & Distr. Programming
ECE445 Fall 2018

Author: Richard Santana

Project 2 Problem 3: Password Cracker using Pthreads

------------------------------------------------------------------------

Compile using the following command:
g++ main.cpp md5.cpp -lpthread

Then execute using default object file:
./a.out

------------------------------------------------------------------------

Overview:

The following source code uses a brute force implementation to produce and compare different string combinations and their hashes. The set of characters considered uses lowercase alphabet from a-z. 

In main.cpp the line --> #define COMBS X allows for the modification of value X where it is the total number of combinations from lengths 1-X. 

In main.cpp the line --> #define NUM_THREADS X allows for the modification of value X where it is the total number of pthreads to distribute the work with.

Each combination produce within a thread is MD5 hashed and compared to our choice of password hash:

In main.cpp the global string password = "mypassword" can be modified to hash any choice of password within the limits of set of characters in set.

Set can also be modified but for time and testing purposes, the priority is lowercase set a-z.

Matching hashes could be found up to length 8 however the wait time is long for all threads to join. Most test cases and analysis was done with lengths 1-6.

-------------------------------------------------------------------------

Source Elaboration:

This implementation uses a combinatorial method that treats each combination as counting towards the total number of combinations. For example given set = {a,b,c,d} then a combination can be 'a' + 0 = 'a', 'a' + 1 = 'b' and so on where we can concatenate for a certain length through loops. This is done in the ProducePerms method. The workload for each pthread is a range between 0 - total number of combinations, and DistributeRange computes a balanced range for each. This start and end indices for each pthread is stored through a CombStruct, which allows the passing of range arguments to void* ProducePerms which will loop for the specified pthread range and produce the combinations using ProducePerms. 