#ifndef DEPARTMENTTREE_H
#define DEPARTMENTTREE_H

#include "../include/DepartmentNode.h"
#include <string>
using namespace std;

// This header file will define the departmentTree class, which will manage the department hierarchy in the department tree


class DepartmentTree
{

  private:
      //pointer to department root
      DepartmentNode* root;

      //this will search tree for department by name
      DepartmentNode* FindDepartment(const string& name) const;

      //this will display department hierachy in preorder
      void DisplayHierarchy(DepartmentNode* node, int depth) const;

      //Traverses tree preorder style
      void Preorder(DepartmentNode* node) const;

      //recursively ldeletes nodes to free allocated memory
      void DeleteTree(DepartmentNode* node);

      //determines depth of a department
      int GetDepth(DepartmentNode* node) const;


  public:

      //Initializes empty department tree
      DepartmentTree();

      //deletes dynamically allocated memorey
      ~DepartmentTree();

      //This will load the departments from data file
      bool LoadDepartments(const string& filename);

      //this will add a department to the tree, if tree is empty, the first department will be root
      // if the tree is not empty a parent must be specified
      bool AddDepartment(const string& name, const string& parentName = "");


      //this will search for a department based on the name and then display the deparments info
      void Search4Department(const string& name) const;


      //Puts department hierarchy on display in preorder with indentation
      void DisplayHierarchy() const;

      //function to check if tree is empty, used when creating a root node to keep parent node from displaying message
      bool IsEmpty() const;




      //Performs/Displays preorder traversal no indentation
      void PreorderTraversal() const;

};



#endif
