#ifndef MEMORY_H
#define MEMORY_H

#include "process.h"
#include <vector>
#include <iostream>
using namespace std;

class Memory{

private:

  struct hole{

    long long begin,end;
    bool empty,mark;
    int pid;

    hole(long long beg,long long ed){

      begin = beg;
      end = ed;
      empty = true;
      pid = -1;
      mark = 0;

    }

    hole(long long beg,long long ed, int id){

      begin = beg;
      end = ed;
      pid = id;
      empty = false;
      mark = 0;

    }

  };
  long long maxmemory;
  vector<hole> holes;
  long long memleft;

public:

Memory(){

  maxmemory = 0;
  memleft = maxmemory;

}

void initialize(long long int mem){

  static bool initialized;
  if(!initialized){

    initialized = true;
    memleft = mem;
    maxmemory = mem - 1;
    holes.push_back(hole(0,maxmemory));

  }
  else
    cout << "Memory already initialized. " << endl;

}

bool addToMemory(Process p){

  if(memleft >= p.getSize()){

    int index = getFirstFit(p.getSize());
    if(index >= 0){

      fitInHole(p.getPid(),p.getSize(),index);
      return true;

    }
    else{

      cout << "The program does not fit in memory. " << endl;
      return false;

    }

  }
  else{

    cout << "The program does not fit in memory. " << endl;
    return false;

  }

}

int getFirstFit(long long size){

  for(int h = 0; h < holes.size();h++){

    if(holes[h].empty and (holes[h].end - holes[h].begin) + 1 >= size){

      return h;

    }

  }
  return -1;

}

void fitInHole(int id,long long int size,int index){

  if((holes[index].end - holes[index].begin + 1) == size){

    holes[index].pid = id;
    holes[index].empty = false;
    memleft -= size;

  }
  else{

    hole newhole(holes[index].begin,size+holes[index].begin-1,id);
    holes[index].begin = holes[index].begin + size;
    holes.insert(holes.begin()+index,newhole);
    memleft -= size;

  }

}

int getHoleToDelete(int id){

  for(int h = 0; h < holes.size();h++){

    if(!holes[h].empty and holes[h].pid == id)
      return h;

  }
  return -1;

}

void mergeHoles(){

  for(int index = 0; index < holes.size()-1;index++){

    if(holes[index].empty and holes[index+1].empty){

      holes[index+1].begin = holes[index].begin;
      holes[index].mark = true;

    }

  }
  deleteMark();

}

void deleteMark(){

  for(int h = 0; h < holes.size();h++){

    //cout << "Running: " << endl;
    if(holes[h].mark){

      //cout << "Deleted: " << holes[h].pid << endl;
      holes.erase(holes.begin() + h);

    }

  }

}

void deleteProcess(int id){

  int index = getHoleToDelete(id);
  if(index >= 0){

    memleft += (holes[index].end - holes[index].begin + 1);
    holes[index].empty = true;
    mergeHoles();

  }
  else{

    cout << "Process to delete from memory not found. " << endl;

  }

}

void printMemory(){

  cout << "Memory: " << endl;
  for(hole h:holes){

    if(!h.empty)
      cout << "P" << h.pid << ": " << h.begin << " - " << h.end << endl;

  }
  cout << "Free: " << memleft << " bytes" << endl;

}

};

#endif
