#include <iostream>
#include <string>
#include "../include/DepartmentTree.h"
#include "../include/FacilityDatabase.h"
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

// Reads a whole line and converts it to a menu number.
// Returns -1 for blank/letters/too long, and -2 when input has ended (EOF).
int readMenuChoice()
{
  string line;
  if (!getline(cin, line))
    return -2;
  line = Utils::trim(line);
  if (line.empty() || line.size() > 3)
    return -1;
  for (size_t i = 0; i < line.size(); ++i)
    if (line[i] < '0' || line[i] > '9')
      return -1;
  return stoi(line);
}

int main(int argc, char* argv[])
{
  //this will initialize the department tree
  DepartmentTree departmentTree;

  FacilityDatabase facilities;
  string dataDir = (argc > 1) ? argv[1] : "data";   // default data directory
  CampusGraph graph; // Initialize graph
  

  
  //FILES MUST BE LOADED IN THIS ORDER
  //1. load the buildings.txt
  graph.loadBuildings(dataDir);

  //2. load the connections.txt
  graph.loadConnections(dataDir);

  //3. load the facilities.txt
  vector<string> buildingNames;
  for (int i = 0; i < graph.buildingCount(); i++) {
      buildingNames.push_back(graph.buildingName(i));
  }
  facilities.loadFromFile(dataDir + "/facilities.txt", "facilities.txt", buildingNames);
  
  //this will call the load function and load the department info from the data file
  departmentTree.LoadDepartments(dataDir + "/departments.txt");

  //this is the menu selection variable
  int menuChoice = -1;

  //this is the main menu while loop
  while(menuChoice != 0)
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
      cout << "0. Exit" <<                                  endl;
      

      cout << endl;
      cout << "Enter your choice: ";
         menuChoice = readMenuChoice();

      //input ended (End of File): stop instead of looping forever
      if(menuChoice == -2)
      {
        break;
      }
  
      //checks for invalid input (blank, letters, too long)
      if(menuChoice == -1)
      {
        cout << "Invalid input please try again." << endl;
        continue;
      }
  


      switch(menuChoice)
        {
          case 1:
            {
          facilities.displayAll();
          break;
            }

          case 2: 
            {
          cout << "Enter facility ID: ";
          string id;
          getline(cin, id);
          facilities.searchById(id);
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

              if(departmentTree.IsEmpty())
              {
                 //Add the first department as root
                departmentTree.AddDepartment(departmentName);
              }
              
              else
              {
                cout << "Enter parent name: ";
                getline(cin, parentName);

                //Add department under specified parent
                departmentTree.AddDepartment(departmentName, parentName);
              }

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

          case 0:
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
