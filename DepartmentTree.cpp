#include "DepartmentTree.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>

using namespace std;

/* this file will implement the department tree class*/

//this will remove the whitespace from the beginning and end of a string
string RemoveWhiteSpace(const string& text)
{
  size_t start = 0;
  size_t end = text.length();

  //we will skip whitespace at beginning 
  while (start < end && (text[start] == ' ' || text[start] == '\t' || text[start] == '\r'))
    {
      start++;

    }

  //then we skip whitespace at the end
  while(end > start && (text[end - 1] == ' ' || text[end - 1] == '\t' || text[end - 1] == '\r'))
    {
      end--;

    }

  //this will return the new string without the outer whitespaces
  return text.substr(start, end - start);
}

//this will convert string to lowercase for comparison
string LowercaseName(const string& name)
{
  string lowercased = name;

  for (size_t i = 0; i < lowercased.length(); ++i)
    {
      lowercased[i] = tolower(static_cast<unsigned char>(lowercased[i]));

    }
  return lowercased;

}




//Constructor
//intitializes empty department tree
DepartmentTree::DepartmentTree()
{
  root = nullptr;
}

//destructor
//deletes dynamically allocated memory
DepartmentTree::~DepartmentTree()
{
  DeleteTree(root);
}


//free allocated memory
void DepartmentTree::DeleteTree(DepartmentNode* node)
{
  //if node null return early
  if(node == nullptr)
  {
    return; 
  }

    //go through and delelte each node
  for(size_t i = 0; i < node->children.size(); ++i)
    {
      DeleteTree(node->children[i]);
    }

  delete node;


}


//this shall search the tree for a particular department based on the name of the department
DepartmentNode* DepartmentTree::FindDepartment(const string& name) const
{
  if (root == nullptr)
  {
    return nullptr;
  }

  vector<DepartmentNode*> pending;

  pending.push_back(root);

  size_t i = 0;

  while( i < pending.size())
    {
      DepartmentNode* current = pending[i];
      
      if(LowercaseName(current->name) == LowercaseName(name))
      {
        return current;
      }

      //add current departments children to search
      for(size_t j = 0; j < current->children.size(); ++j)
      {
        pending.push_back(current->children[j]);

      }
      ++i;

    }

  return nullptr;

}


