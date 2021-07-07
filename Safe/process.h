//Jesse Huang
#ifndef PROCESS_H
#define PROCESS_H

using namespace std;

enum type{UNKNOWN,REAL,COMMON};

class Process{

public:


Process(){

  pid = -1;
  t_process = UNKNOWN;

}

Process(type t,int id,long long s){

  pid = id;
  t_process = t;
  size = s;

}

int getPid(){

  return pid;

}

long long int getSize(){

  return size;

}

type getType(){

  return t_process;

}

private:

long long int size;
type t_process;
int pid;

};

#endif
