#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include "md5.h"

// Total number of combinations to produce for lengths 1-7
#define COMBS 456976

// Pthreads created
#define NUM_THREADS 32

// Size of set below
#define SET_SIZE sizeof(set)

// Set of characters to choose from
char set[] = {'a','b','c','d','e','f','g','h','i','j','k','l',
                'm','n','o','p','q','r','s','t','u','v','w','x','y','z'};

// Return produced combination
std::string ReturnProduceComb(long long);

// Produce combination and compare
void ProduceComb(long long);

// Pthread call for ProduceComb
void* ProduceComb(void*);

// Struct for pthread method - stores start,end range and pthread id
struct CombStruct{
    long long start;
    long long end;
    int thread_id;
};

// Distributes range of work per thread
// Arguments: vector, total combinations, num_threads
void DistributeRange(std::vector<CombStruct>&, long long, int);

// Chosen password and hash
std::string password = "drwz";
std::string hash = md5(password);

// Execution time purposes
double get_wall_time();

// t1 marks start of program, t2 marks time match found, t3 marks end producing all combinations
double t1, t2, t3;

int main(){

    // Create NUM_THREADS CombStruct objects per pthread
    std::vector<CombStruct>vec_structs;
    // Distribute work range per thread
    DistributeRange(vec_structs, COMBS, NUM_THREADS);

    // Track start time
    t1 = get_wall_time();
    std::cout << "Main - Starting time\n\n";

    // Creating NUM_THREADS pthreads
    pthread_t threads[NUM_THREADS];
    int id[NUM_THREADS];
    for(int i = 0; i < NUM_THREADS; i++){
        id[i] = i;
        pthread_create(&threads[i], NULL, &ProduceComb, (void*)&vec_structs[id[i]]);
    }
    
    // Wait for threads to join
    for(int i = 0; i < NUM_THREADS; i++){
        pthread_join(threads[i], NULL);
    }
   
    // End run time
    t3 = get_wall_time();
    std::cout << "\nAll pthreads joined\nTime elapsed: " << (t3-t1) << std::endl;
   
   return 0;
}

// Distributes work range per thread - depending on total combinations and num_threads
void DistributeRange(std::vector<CombStruct>& vec, long long total, int num_threads){
    if(num_threads == 1){
        vec.push_back(CombStruct());
        vec[num_threads - 1].start = num_threads - 1;
        vec[num_threads - 1].end = total;
        vec[num_threads - 1].thread_id = num_threads;
    }
    else{
        long long majority_tasks = floor(total/num_threads);
        long long single_tasks = total - (majority_tasks * (num_threads - 1));
        
        for(int i = 0; i < num_threads - 1; i++){
            vec.push_back(CombStruct());
            vec[i].start = i * majority_tasks;
            vec[i].end = (i + 1) * majority_tasks;
            vec[i].thread_id = i + 1;
        }
        vec.push_back(CombStruct());
        vec[num_threads - 1].start = total - single_tasks;
        vec[num_threads - 1].end = total;
        vec[num_threads - 1].thread_id = num_threads;
    }
}

// Pthread call for ProduceComb below, passes range to produce combinations for
void* ProduceComb(void* args){
    struct CombStruct* arg_struct = (struct CombStruct*)args;
    long long start = arg_struct->start;
    long long end = arg_struct->end;

    for(start; start < end; start++){
        ProduceComb(start);
    }

    pthread_exit(NULL);
}

// Method compares produced combination to password
void ProduceComb(long long index){
    std::string comb;
    do{
        comb += set[index % SET_SIZE];
        index /= SET_SIZE;
    } while(index);

    std::string test_hash = md5(comb);
    if(test_hash == hash){
        std::cout << "MATCHING HASH FOUND!!!\n";
        std::cout << "Combination: " << comb << "\n";
        std::cout << "Hash: " << test_hash << "\n";
        // Time to find match
        t2 = get_wall_time();
        std::cout << "Time to find match: " << (t2-t1) << std::endl;
    }
}

// Methods return produced combination
std::string ReturnProduceComb(long long index){
    std::string comb;
    do{
        comb += set[index % SET_SIZE];
        index /= SET_SIZE;
    } while(index);

    return comb;
}

// Execution time tracking
double get_wall_time(){
    struct timeval time;
    if (gettimeofday(&time,NULL)){
        //  Handle error
        return 0;
    }
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}