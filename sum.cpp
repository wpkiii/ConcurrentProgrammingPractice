******************************************************************************
* DESCRIPTION:
*   A "hello world" Pthreads program which demonstrates one safe way
*   to pass arguments to threads during thread creation.
******************************************************************************/
#include <pthread.h>
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <fstream>
using namespace std;
int combo[10];


void combo_lock() {
    ifstream fin("combo.txt");
    int i = 0;
    while( fin >> combo[i] ) i++;   
}

int oracle( int key, int id){
    if(combo[id] == key) return 1;
    else return 0;
}    

void *work(void *threadid) {
   int *id_ptr, taskid, i = 1, key, c = 0;
   id_ptr = (int *) threadid;
   taskid = *id_ptr;
   for(i = 1; i<101; i++){
      c = oracle(i,taskid);
      if(c == 1) {
      cout << " Tumbler " << taskid << " correct value is: "<< i <<  endl;
      pthread_exit(NULL);   
      }
   }
   pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
 if(argc > 1){
   int num_threads = atoi(argv[1]);
   pthread_t threads[num_threads];
   int *taskids[num_threads];
   int rc, t;
   combo_lock();
   for(t=0;t<num_threads;t++) {
      taskids[t] = (int *) malloc(sizeof(int));
      *taskids[t] = t;
      cout << "Creating thread " << t <<" "<< endl;
      rc = pthread_create(&threads[t], NULL, work, (void *) taskids[t]);
      if (rc) {
          cout << "ERROR; return code from pthread_create() is "<< rc << endl;
          exit(-1);
          }
      }
     for(t = 0; t < num_threads;t++){
        if(pthread_join(threads[t],NULL)){
        cout << "error joining threads." << endl;
        exit (-1); }
       cout << t << endl;
     }

  return 0;
  }
  else cerr << "missing input parameter: number of threads\n";
}

