//////////////////////////////////////////////////////////////////////////
// FileMgr.cpp - find files matching specified patterns                 //
//               on a specified path                                    //
// ver 2.0                                                              //
// Application: Project #4 Dependency-Based Remote Code Repository      //
// Language:    C++, Visual Studio 2015                                 //
// Platform:    Dell Inspiron 5548, Core-i5, Windows 10                 //
// Author:      Jim Fawcett, CST 4-187, Syracuse University             //
//              (315) 443-3948, jfawcett@twcny.rr.com                   //
//////////////////////////////////////////////////////////////////////////



#include "FileMgr.h"
#include "../DataStore/DataStore.h"
#include <iostream>

#ifdef TEST_FILEMGR

int main()
{
  std::cout << "\n  Testing FileMgr";
  std::cout << "\n =================";

  DataStore ds;
  FileMgr fm("..", ds);
  fm.addPattern("*.h");
  fm.addPattern("*.cpp");
  //fm.addPattern("s*.partial");
  fm.search();

  std::cout << "\n\n  contents of DataStore";
  std::cout << "\n -----------------------";
  for (auto fs : ds)
  {
    std::cout << "\n  " << fs;
  }
  std::cout << "\n\n";
  return 0;
}
#endif
