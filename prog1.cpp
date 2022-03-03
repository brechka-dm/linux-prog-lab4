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
  
  // Open program text.
  ifstream file(pathname);
  string line;
  string progTxt;
  
  // Read program text.
  if(file.is_open())
  {
    while(getline(file, line))
    {
      progTxt+=line+"\n";
    }
  }
  file.close();
  
  // Create shm for program text
  key_t key = ftok(pathname, 0);
  int shmid = shmget(key, progTxt.size(),0666|IPC_CREAT|IPC_EXCL);
  
  // Attach shm.
  char* shString = (char*) shmat(shmid,NULL,0);
  
  // Copy program text to shm.
  strcpy(shString,progTxt.c_str());
  
  // Detach shm.
  shmdt(shString);
  
  // Create shm for program size.
  key = ftok(pathname2, 0);
  shmid = shmget(key, sizeof(int),0666|IPC_CREAT|IPC_EXCL);
  int* shStringSize = (int*) shmat(shmid,NULL,0);
  
  // Copy program size to shm.
  *shStringSize = progTxt.size();
  
  // Detach shm.
  shmdt(shStringSize);
  
  return 0;
}
