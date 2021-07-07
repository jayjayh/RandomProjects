#ifndef DISK_H
#define DISK_H

#include "process.h"
#include <vector>
#include <iostream>

class Disk{

public:

Disk(int num){

  d = num;
  queue = {};
  busy = false;

}

bool isBusy(){

  return busy;

}

void addToDisk(Process process){

  queue.push_back(process);
  if(!busy){

    nextInQueue();
    busy = true;

  }

}

void nextInQueue(){

  if(!queue.empty()){

    running = queue.front();
    deleteFront();

  }
  else{

    busy = false;

  }

}

void deleteFront(){

  queue.erase(queue.begin());

}

Process returnRunningProcess(){

  Process temp = running;
  nextInQueue();
  return temp;

}

void printQueue(){

  if(busy){

    cout << "Disk " << d << " Status: Running p" << running.getPid() << " \nqueue:";
    for(auto p: queue){

      cout << " < " << p.getPid();

    }
    cout << endl;

  }
  else{

    cout << "Disk " << d << " Status: idle \nqueue: " << endl;

  }

}

private:

  int d;
  vector<Process> queue;
  Process running;
  bool busy;

};

#endif
