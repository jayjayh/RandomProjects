//Jesse Huang

#include "ready_queue.h"
#include <string>
#include <iostream>

using namespace std;

int main(){

  long long int mem = 0;
  int disks = 0;
  ReadyQueue test;
  string command = "";
  string op = "";
  string other = "";

  cout << "How much Memory does your system have?" << endl;
  cin >> mem;
  cout << "How many disks does your system have?" << endl;
  cin >> disks;

  //test.para();
  test.startIO(disks);
  test.startMemory(mem);
  cout << "Type quit to exit simulation. " << endl;
  while(command != "quit"){

    cin >> command;
    if(command == "A"){

      cin >> mem;
      test.addCP(mem);

    }
    else if(command == "AR"){

      cin >> mem;
      test.addRT(mem);

    }
    else if(command == "D"){

      int temp;
      cin >> temp;
      if(temp < disks)
        test.finishBurst(temp);
      else
        cout << "Disk number invalid." << endl;

    }
    else if(command == "d"){

      int temp;
      cin >> temp;
      if(temp < disks)
        test.addToDisk(temp);
      else
        cout << "Disk number invalid." << endl;


    }
    else if(command == "Q"){

      test.timeSlice();

    }
    else if(command == "S"){

      cin >> command;
      if(command == "r")
        test.printQueue();
      else if(command == "i")
        test.printDisks();
      else if(command == "m")
        test.printMemory();
      else
        cout << "Use S r to print CPU and ready queue. \nUse S i to print processes using disks. \nUse S m to show the state of memory. " << endl;

    }
    else if(command == "t"){

      test.terminate();

    }
    else if(command == "quit"){}
    else{

      cout << "Unknown command. " << endl;

    }

  }

  return 0;

}
