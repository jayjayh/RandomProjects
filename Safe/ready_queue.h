//Jesse Huang
#ifndef READY_QUEUE_H
#define READY_QUEUE_H

#include "process.h"
#include "disk.h"
#include "memory.h"
#include <iostream>
#include <vector>
using namespace std;

class ReadyQueue{

public:

ReadyQueue(){

  pid = 0;
  rt = {};
  common = {};
  cpuBusy = 0;

}

//returns 1 if there are no realtime processes in ready queue
bool noRT(){

  return rt.size() == 0;

}

bool noCommon(){

  return common.size() == 0;

}

void addCP(long long int size){

  Process p(COMMON,pid,size);
  if(mem.addToMemory(p)){

    common.push_back(p);
    pid++;
    nextInQueue();
    //cout << "Common process added to queue." << endl;

  }

}

void addRT(long long int size){

  Process p(REAL,pid,size);
  if(mem.addToMemory(p)){

    rt.push_back(p);
    pid++;
    nextInQueue();
    //cout << "Real Time process added to queue." << endl;

  }


}

void timeSlice(){

  if(cpuBusy){

    if(running.getType() == REAL){

      rt.push_back(running);
      cpuBusy = false;
      nextInQueue();

    }
    else{

      common.push_back(running);
      cpuBusy = false;
      nextInQueue();

    }

  }
  else
    cout << "There are no processes running for time slice. " << endl;

}

void nextInQueue(){

  if(!noRT()){

    if(!cpuBusy){

      running = rt.front();
      cpuBusy = true;
      deleteFront(rt);

    }
    else if(running.getType() == COMMON){

      common.emplace(common.begin(),running);
      running = rt.front();
      cpuBusy = true;
      deleteFront(rt);

    }

  }
  else if(!noCommon()){

    if(!cpuBusy){

      running = common.front();
      cpuBusy = true;
      deleteFront(common);

    }

  }
  else
    cpuBusy = false;

}

void deleteFront(vector<Process> & queue){

  queue.erase(queue.begin());

}

void para(){

  cout << "Real time process size: " << rt.size() << endl;
  cout << "Common process size: " << common.size() << endl;
  cout << "Running process: " << running.getPid() << endl;
  cout << "pid: " << pid << endl;

}

void terminate(){

  if(cpuBusy){

    removeFromMem(running.getPid());
    cpuBusy = false;
    nextInQueue();

  }
  else{

    cout << "No running process to terminate. " << endl;

  }

}

void printQueue(){

  if(running.getPid() == -1 or !cpuBusy)
    cout << "CPU: Idle. " << endl;
  else
    cout << "CPU: " << running.getPid() << endl;
  cout << "Real Time:";
  if(noRT()) cout << " No real time processes in queue.";
  for(auto p: rt){

    cout << " < " << p.getPid();

  }
  cout << endl << "Common:";
  if(noCommon()) cout << " No common processes in queue.";
  for(auto p: common){

    cout << " < " << p.getPid();

  }
  cout << endl;

}

// ------------------ IO -------------------//

void startIO(int d){

  for(int num = 0; num < d; num++){

    disks.push_back(Disk(num));

  }
  cout << "Num of disks: " << disks.size() << endl;

}

void addToDisk(int diskid){

  if(cpuBusy){

    disks[diskid].addToDisk(running);
    cpuBusy = false;

  }
  else
    cout << "There are no processes running. " << endl;
  nextInQueue();
  disks[diskid].printQueue();

}

void finishBurst(int diskid){

  if(disks[diskid].isBusy()){

    Process temp = disks[diskid].returnRunningProcess();
    if(temp.getType() == REAL){

      rt.push_back(temp);
      nextInQueue();

    }
    else{

      common.push_back(temp);
      nextInQueue();

    }

  }
  else{

    cout << "Disk was not busy." << endl;

  }

}

void printDisks(){

  for(Disk d: disks){

    d.printQueue();

  }

}


// ------------------- MEM ------------------ //

void startMemory(long long memory){

  mem.initialize(memory);

}

void printMemory(){

  mem.printMemory();

}

void removeFromMem(int id){

  mem.deleteProcess(id);

}

private:

  int pid;
  vector<Process> rt;
  vector<Process> common;
  vector<Disk> disks;
  Process running;
  bool cpuBusy;
  Memory mem;


};

#endif
