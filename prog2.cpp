#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdio.h>

using namespace std;
int main()
{
  // Key base for program text.
  char pathname[] = "prog1.cpp";
  
  // Key base for program size. 
  char pathname2[] = "prog2.cpp";
  
  // Read program size from shm.
  key_t key = ftok(pathname2, 0);
  int shmid = shmget(key, sizeof(int),0);
  int* shStringSize = (int*) shmat(shmid,NULL,0);
  int progTxtSize = *shStringSize;
  
  // Detach and delete shm.
  shmdt(shStringSize);
  shmctl(shmid, IPC_RMID, NULL);
  
  // Read program text from shm.
  key = ftok(pathname, 0);
  shmid = shmget(key, progTxtSize,0);
  char* shString = (char*) shmat(shmid,NULL,0);
  
  // Output program text.
  cout<<shString<<endl;
  
  // Detach and delete shm.
  shmdt(shString);
  shmctl(shmid, IPC_RMID, NULL);
  
  return 0;
}
