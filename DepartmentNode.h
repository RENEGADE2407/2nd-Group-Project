#ifndef DEPARTMENTNODE_H
#define DEPARTMENTNODE_H

#include <string>
#include <vector>
using namespace std;


/*
This header file will define a node representing an individual department in the department tree
*/

struct DepartmentNode
{
  //department name
  string name;

  //pointer to parent department
  DepartmentNode* parent;

  //pointers to child departments
  vector<DepartmentNode*> children;

  //this will initialize a department node with no parent
  DepartmentNode(const string& departmentName)
  {
    name = departmentName;

    //defines parent as null because parent hasnt been assigned yet
    parent = nullptr;
  }


};



#endif
