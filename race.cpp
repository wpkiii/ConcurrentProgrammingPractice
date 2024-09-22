#include <pthread.h>
#include <cstdlib>
#include <iostream>
using namespace std;
int sum = 0;

void *PrintHello(void *threadid)
{
   int *id_ptr, taskid;
   id_ptr = (int *) threadid;
   taskid = *id_ptr;
   cout << "Hello this is thread " << taskid << endl;
   sum = sum + 1;
   pthread_exit(NULL);
}

int main(int argc, char *argv[]){
int n;
if (argc > 1){
   n = atoi(argv[1]);
   pthread_t threads[n];
   int *taskids[n];
   int rc, t;

   for(t=0;t<n;t++) {
      taskids[t] = (int *) malloc(sizeof(int));
      *taskids[t] = t;
      //cout << "Creating thread " << t << endl;
      rc = pthread_create(&threads[t], NULL, PrintHello, (void *) taskids[t]);
      if (rc) {
         cout << "ERROR; return code from pthread_create() is "<< rc << endl;
         exit(-1);
      }
  }
  for(t = 0; t<n;t++){
  if(pthread_join(threads[t],NULL)){
    cout << "error joining threads." << endl;
  exit (-1); }
  }
  cout << sum << endl;
}
  else { cout << "missing parameter /n";
       return -1;
  }

pthread_exit(NULL);
}

