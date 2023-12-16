#include "systemclass.h"
#include <cstdio>


int main(){
  SystemClass * System;
  bool result;

  System = new SystemClass;

  result = System->Initialize();
  if(!result){
    printf("ERROR: Couldn't initialize system\n");
    return -1;
  }
  System->Frame();

  System->Shutdown();
  delete System;
  System = 0;
  return 0;
}

