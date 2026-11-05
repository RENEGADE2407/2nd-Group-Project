#include "DepartmentTree.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>

using namespace std;

/* 
Description: This file will implement the department tree class
Author: Jason Wildman
*/


//_________________________________________________________________________________________________________________________________________________________________________________________________________


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

//_________________________________________________________________________________________________________________________________________________________________________________________________________


//Constructor
//intitializes empty department tree
DepartmentTree::DepartmentTree()
{
  root = nullptr;
}

//_________________________________________________________________________________________________________________________________________________________________________________________________________


//destructor
//deletes dynamically allocated memory
DepartmentTree::~DepartmentTree()
{
  DeleteTree(root);
}

//_________________________________________________________________________________________________________________________________________________________________________________________________________


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


//_________________________________________________________________________________________________________________________________________________________________________________________________________

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

//_________________________________________________________________________________________________________________________________________________________________________________________________________


//this will load the file passed to the function attempt to open it and then read the file
bool DepartmentTree::LoadDepartments(const string& filename)
{
  //declares input file stream
  ifstream fin;

  //this will attempt to open the file based on the name passed to function
  fin.open(filename);

  //checks if file was opened
  if(fin.fail())
  {
    cout << "Error: Unable to open " << filename << endl;
    return false;
  }

  //variables needed to read file 
  //1. this will store the current line 
  string line;
  //2. this will track which line is being processed
  int lineNumber = 0;
  //3. this will count valid records
  int accepted = 0;
  //4. this counts invalid records
  int rejected = 0;

  //getline will read one line from file and store it in "line" the while loop makes sure every line is read.
  while(getline(fin, line))
    {
      lineNumber++;

      //calls the RemoveWhiteSpace function to remove the white space from begining and end current line
      line = RemoveWhiteSpace(line);

      //this will skip the line if it is blank
      if(line.empty())
      {
        continue;
      }

      //if the line is a comment line, skip it
      if(line[0] == '#')
      {
        continue;
      }

      //tracks whether seperator character was found
      bool foundSeparator = false;

      //this stores the position of separator
      size_t separatorPosition = 0;

      //this searches the current line for the separator
      for(size_t i = 0; i < line.length(); ++i)
        {
          //save position of separator if found and flag foundSeparator
          if(line[i] == '|')
          {
            separatorPosition = i;

            foundSeparator = true;

            break;
          }

        }

      //checks foundSparator to see if line contained a separator if it did not then display warning
      if(foundSeparator == false)
      {
        cout << "WARNING: No separator in " << filename << " file, line number: " << lineNumber << "." << endl;

        rejected++;

        //skip whats left of current loop iteration and read next line
        continue;

      }

      //this extracts the department name (left of separator) and clears any white space surrounding the name
      string departmentName = RemoveWhiteSpace(line.substr(0, separatorPosition));

      //this extracts the parant name (right side of the separator) and removes any whitespace around the name
      string parentName = RemoveWhiteSpace(line.substr(separatorPosition + 1));

      // this will check if either department name or parent name is empty and display warning + increment rejected counter
      if(departmentName.empty() || parentName.empty())
      {
        cout << "WARNING: Empty department or parent name in " << filename << " file, line number: " << lineNumber << "." << endl;

        ++rejected;

        //skip whats left of current iteration
        continue;

      }


      //this will check whether the dpartment name already exists in the tree if it is then it will display warning and increment rejected counter
      if(FindDepartment(departmentName) != nullptr)
      {
        cout << "WARNING: Duplicate department name in " << filename << " file, line number: " << lineNumber << "." << endl;

        ++rejected;

        //skip the rest of the current iteration
        continue;
      }


      //this checks whether the tree is empty in order to determine if the department should be the root
      if(root == nullptr)
      {
        // checks if the parent name is NONE
        if(LowercaseName(parentName) != "none")
        {
          cout << "WARNING: Root department must have NONE as its parent in " << filename << " file, line number: " << lineNumber << "." << endl;

          ++rejected;

          //skip the rest of the current iteration
          continue;

        }

        //If it passes the check create the root department
        root = new DepartmentNode(departmentName);

        ++accepted;

        //move to next line 
        continue;
      }


      //this searches ffor parent department in tree
      DepartmentNode* parent = FindDepartment(parentName);

      //this checks if parent exists
      if(parent == nullptr)
      {
        cout << "WARNING: Parent department not found for " << filename << " file, line number: " << lineNumber << "." << endl;

          ++rejected;

        //skip rest of current iteration
        continue;
      }

      //this creates a new department node
      DepartmentNode* newDepartment = new DepartmentNode(departmentName);

      //this will connect the new node to its parent
      newDepartment->parent = parent;

      //this adds the new department to the parents children vector
      parent->children.push_back(newDepartment);

      ++accepted;

      
    }

  // this displays the accepted and rejected count
  cout << "The " << filename << " file accepted " << accepted << " departments, and rejected " << rejected << "." << endl; 

  //closes file when done
  fin.close();

  return true;

}


//_________________________________________________________________________________________________________________________________________________________________________________________________________


//This will allow the user to add departments manually instead of loading them from the .txt file
bool DepartmentTree::AddDepartment(const string& name, const string& parentName)
{

  //this removes the whitespace from the dpartment name
  string departmentName = RemoveWhiteSpace(name);


  //checks if the department name is empty 
  if(departmentName.empty())
  {
    cout << "WARNING: Department name empty." << endl;
    return false;
  }

  // calls the find function to check for duplicate names
  if(FindDepartment(departmentName) != nullptr)
  {
    cout << "WARNING: There is already a department named: " << departmentName << "." << endl;
    return false;
  }


  //this will check if the tree is empty, if it is this will make the added department the root
  if(root == nullptr)
  {
    //this makes the department added the root
    root = new DepartmentNode(departmentName);

    cout << departmentName << " has been added as the root node." << endl;
    return true;
  }


  //if there is already a root then a parent is needed from the user

  //this will clear the parent name of whitespace
  string parentNoWhiteSpace = RemoveWhiteSpace(parentName);

  //this will check if parent blank display warning if it is
  if(parentNoWhiteSpace.empty())
  {
    cout << "WARNING: The department tree's root has already been filled, therefore parent department must be specified" << endl;
    return false;
  }


  //if check passes then this will search the tree to confirm the parent department actually exists
  if(FindDepartment(parentNoWhiteSpace) == nullptr)
  {
    cout << "WARNING: Parent department not found in department tree." << endl;
    return false;
  }


  //this creates a new department node 
  DepartmentNode* newDepartment = new DepartmentNode(departmentName);


  //This assigns the new department with its parent
  newDepartment->parent = FindDepartment(parentNoWhiteSpace);

  //this will add the new department to the parents child vector
  newDepartment->parent->children.push_back(newDepartment);


  //this will inform the user of a successful addition to the tree (another happy landing)
  cout << departmentName << " has been successfully added to the department tree." << endl;

  return true;
  
}

//_________________________________________________________________________________________________________________________________________________________________________________________________________


//This function will get the depth of a node in the tree
int DepartmentTree::GetDepth(DepartmentNode* node) const
{
  //this will track the departments depth
  int depth = 0;

  //this will traverse the tree upward through the parents until it reaches the root
  while(node != root)
    {
      node = node->parent;

      ++depth;
        
    }
  return depth;
}

//_________________________________________________________________________________________________________________________________________________________________________________________________________


//This function will use the FindDepartment and GetDepth functions to search for a department and display relative info
void DepartmentTree::Search4Department(const string& name) const
{
  //starts by removing whitespace
  string departmentName = RemoveWhiteSpace(name);

  //then call the find department funct and make store it in a pointer for later use
  DepartmentNode* departmentPointer = FindDepartment(departmentName);

  //this will then check to ensure that the department actually exists. If it doesnt display warning mssg
  if(departmentPointer == nullptr)
  {
    cout << "WARNING: " << departmentName << " department not found." << endl;
    return;
  }

  //now that the existence of the department is determined begin displaying the department's info
  cout << "----Department found----" << endl;
  cout << "Department Name: " << departmentPointer->name << endl;

  //this will check if there is a root before displaying the parent node
  if(departmentPointer->parent != nullptr)
  {
    cout << "Parent Department: " << departmentPointer->parent->name << endl;
  }
  else
  {
    cout << "Parent Department: None, " << departmentPointer->name << " is the root node." << endl;
  }

  cout << "Direct-child/children: " << departmentPointer->children.size() << endl;

  cout << "Depth: " << GetDepth(departmentPointer) << endl;

}

//_________________________________________________________________________________________________________________________________________________________________________________________________________


//this function will handle the traversal and the display for the hierarchy in preorder
void DepartmentTree::DisplayHierarchy(DepartmentNode* node, int depth) const
{
  //first check if node exists
  if(node == nullptr)
  {
    return;
  }

  //this will use the depth and a loop to indent the department based on the depth
  for(int i = 0; i < depth; ++i)
    {
      cout << "    ";
    }

  //once properly indented this will display the departments name
  cout << node->name << endl;

  //this will visit each child recursively in preorder
  for(size_t i = 0; i < node->children.size(); ++i)
    {
      DisplayHierarchy(node->children[i], depth + 1);
      
    }

  
}

//overloaded function
//this is the public function that will start the process of the display
void DepartmentTree::DisplayHierarchy() const
{
  //this checks if tree is empty
  if(root == nullptr)
  {
    cout << "Department tree is empty." << endl;
    return;
  }

  //this calls the actual function to begin displaying the hierarchy in preorder
  DisplayHierarchy(root, 0);

  
}

//_________________________________________________________________________________________________________________________________________________________________________________________________________
