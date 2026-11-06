#include <iostream>
#include <string>
#include "../include/DepartmentTree.h"
//FILL IN HERE: include facilities and hashtable headers
#include "../include/CampusGraph.h"
#include "../include/Utils.h" // String functions

using namespace std;

// Handler for BFS menu
// Reads one full line (spaces allowed), trims it, rejects blank, then calls the graph.
void handleBfsReachability(const CampusGraph& graph) {
  cout << "Enter starting building: ";
  string name;
  getline(cin, name);
  name = Utils::trim(name);
  if (name.empty()) {
      cout << "Error: building name cannot be blank.\n";
      return;
  }
  graph.bfsReachable(name);   // prints its own error if the building is unknown
}

int main(int argc, char* argv[])
{
  //this will initialize the department tree
  DepartmentTree departmentTree;

  //FILL IN HERE: intitialize facilities, hash table
  string dataDir = (argc > 1) ? argv[1] : "data";   // default data directory
  CampusGraph graph; // Initialize graph
  

  
  //FILES MUST BE LOADED IN THIS ORDER
  //FILL IN HERE: 1. load the buildings.txt
  graph.loadBuildings(dataDir);

  //FILL IN HERE: 2. load the connections.txt
  graph.loadConnections(dataDir);

  //FILL IN HERE: 3. load the facilities.txt
  
  //this will call the load function and load the department info from the data file
  departmentTree.LoadDepartments("data/departments.txt");

  //this is the menu selection variable
  int menuChoice = 0;

  //this is the main menu while loop
  while(menuChoice != 10)
    {
      cout << "======= CAMPUS INFORMATION SYSTEM =======" << endl;
      cout << "1. View all facilities" <<                    endl;
      cout << "2. Search facilities by ID" <<                endl;
      cout << "3. View campus graph" <<                      endl;
      cout << "4. Display graph counts and degrees" <<       endl;
      cout << "5. Find reachable buildings (BFS)" <<         endl;
      cout << "6. Add department" <<                         endl;
      cout << "7. Search department" <<                      endl;
      cout << "8. Display department hierarchy" <<           endl;
      cout << "9. Run preorder traversal" <<                 endl;
      cout << "10. Exit" <<                                  endl;
      

      cout << endl;
      cout << "Enter your choice: ";
      cin >> menuChoice;

      //checks for invalid input
      if(cin.fail())
      {
        cout << "Invalid input please try again." << endl;

        cin.clear();
        cin.ignore(1000, '\n');

        continue;
        
      }

      cin.ignore(1000, '\n');


      switch(menuChoice)
        {
          case 1:
            {
          //FILL IN HERE: display all facilities
          break;
            }

          case 2: 
            {
          //FILL IN HERE: search facilities by ID
          break;
            }

          case 3: 
            {
              graph.displayGraph(); // View campus graph
              break;
            }

          case 4: 
            {
              graph.displayCountsAndDegrees(); // Display graph counts and degrees
              break;
            }

          case 5:
            {
              handleBfsReachability(graph); // Find reachable buildings (BFS)
              break;
            }

          case 6:
            {
              string departmentName;
              string parentName;

              cout << "Enter department name: ";
              getline(cin, departmentName);

              cout << "Enter parent name (leave blank if tree is empty): ";
              getline(cin, parentName);

              //call the manual add department function
              departmentTree.AddDepartment(departmentName, parentName);

              break;
            }

          case 7:
            {
              string departmentName;

              cout << "Enter department name to search: ";
              getline(cin, departmentName);
              
              //this will call the search function
              departmentTree.Search4Department(departmentName);

              break;
              
            }

          case 8:
            {
              //This will call the display function
              departmentTree.DisplayHierarchy();
              break;
            }

          case 9:
            {
              //this will call the preorder traversal withoutt indentation function
              departmentTree.PreorderTraversal();
              break;
            }

          case 10:
            {
              cout << "Thank you for using the Campus Information System. Goodbye!" << endl;
              break;
            }

          default:
            {
              cout << "Invalid menu selection. Please try again" << endl;
            }
          
      
    }

  
}


return 0;
}
