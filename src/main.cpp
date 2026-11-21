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
  while(menuChoice != 18)
    {
      cout << "======= CAMPUS INFORMATION SYSTEM =======" << endl;
      cout << "1. View all facilities" <<                    endl;
      cout << "2. Search facility by ID" <<                  endl;
      cout << "3. Search facility by name" <<                 endl;
      cout << "4. Search facility by category" <<             endl;
      cout << "5. View campus graph" <<                      endl;
      cout << "6. Display graph counts and degrees" <<       endl;
      cout << "7. Find reachable buildings (BFS)" <<         endl;
      cout << "8. Find shortest path (BFS)" <<               endl;
      cout << "9. Add department" <<                         endl;
      cout << "10. Search department" <<                     endl;
      cout << "11. Display department hierarchy*" <<         endl;
      cout << "12. Preorder traversal**" <<                  endl;
      cout << "13. Postorder traversal" <<                   endl;
      cout << "14. Level-order traversal" <<                 endl;
      cout << "15. Department statistics" <<                 endl;
      cout << "16. Facility category report" <<              endl;
      cout << "17. Graph connectivity report" <<             endl;
      cout << "18. Exit" <<                                  endl;
      

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
          //**View all facilities**
          case 1:
            {
          facilities.displayAll();
          break;
            }
          
          //**Search facility by ID**
          case 2: 
            {
          cout << "Enter facility ID: ";
          string id;
          getline(cin, id);
          facilities.searchById(id);
          break;
            }
          
          //**Search facility by name**
          case 3:
            {
              
              //NEEDS TO BE FILLED IN 
              break;
              
            }

          //**Search facility by category**
          case 4:
            {

              //NEEDS TO BE FILLED IN
              break;
              
            }

          //**View campus graph**
          case 5: 
            {
              graph.displayGraph(); // View campus graph
              break;
            }

          //**Display graph counts and degrees**
          case 6: 
            {
              graph.displayCountsAndDegrees(); // Display graph counts and degrees
              break;
            }

          //**Find reachable buildings**
          case 7:
            {
              handleBfsReachability(graph); // Find reachable buildings (BFS)
              break;
            }

          //**Find shortest path (BFS)**
          case 8:
            {

              //NEEDS TO BE FILLED IN
              break;
              
            }

          //**Add department**
          case 9:
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

          //**Search department**
          case 10:
            {
              string departmentName;

              cout << "Enter department name to search: ";
              getline(cin, departmentName);
              
              //this will call the search function
              departmentTree.Search4Department(departmentName);

              break;
              
            }

          //**Display department hierarchy**
          case 11:
            {
              //This will call the display function
              departmentTree.DisplayHierarchy();
              break;
            }

          //**Preorder traversal**
          case 12:
            {
              //this will call the preorder traversal withoutt indentation function
              departmentTree.PreorderTraversal();
              break;
            }

          //**Postorder traversal**
          case 13:
            {
              departmentTree.PostorderTraversal();
              break;
            }

          //**Level-order traversal**
          case 14:
            {
              departmentTree.LevelOrderTraversal();
              break;
            }

          //**Department statistics**
          case 15:
            {

              //NEEDS TO BE FILLED IN
              break;
              
            }

          //**Facility category report**
          case 16:
            {

              //NEEDS TO BE FILLED IN
              break;
              
            }

          //**Graph connectivity report**
          case 17:
            {

              //NEEDS TO BE FILLED IN
              break;
              
            }

          //**Exit**
          case 18:
            {
              cout << "Thank you for using the Campus Information System. Goodbye!" << endl;
              break;
            }

          //**Invalid input**
          default:
            {
              cout << "Invalid menu selection. Please try again" << endl;
            }
          
      
    }

  
}


return 0;
}
