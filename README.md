# **Campus Information System**  

  
This project is a simulation of a campus information system (CIS). The CIS is a c++ program that loads campus data from text files and uses a command line menu to allow the user to locate campus facilities, explore building connections, identify routes, peruse a department heiarchy, and inspect summary reports

The project uses object-oriented programming and data structures to organize/manage campus information. For example, a hash table is implemented to store and search facilities by ID and an undirected graph is used to represent campus buildings and walkways. Additionally a general tree is used to represent the academic department hierarchy, allowing departments to be added, organized, and displayed using preorder traversal.

**_Objectives_**
-------------------------------------------------------------------------------------

*  Load campus info though instructor provided text files.
*  Display a menu that allows the user to do the following:
   *  Display all campus facilities.
   *  Search for facilities using ID.
   *  Display the campus graph.
   *  Display graph counts and degrees.
   *  Find reachable buildings using BFS.
   *  Add departments manually to the department tree.
   *  Search for departments.
   *  Exit the system.
*  Implement custom string hash function and hash table that stores and searches facilities using ID.
*  Implement an undirected graph to represent campus buildings and their connections.
*  Implement a BFS using a queue to find reachable buildings.
*  Implement a general tree to represent the academic department hierarchy.
   *  The tree operations will include insertion, searching, hierarchy display using indentation, and preorder traversal without indentation.
*  Validate the input data text documents and handle invalid inputs from the user.

**_Technologies / Tools Used_**
-------------------------------------------------------------------------------------
* C++
* C++ standard library
* GitHub
* Notepad++

**_Project Structure_**
-------------------------------------------------------------------------------------
Project2/  
|  
|--include/  
| |--DepartmentTree.h  
| |--DepartmentNode.h  
| |-- **FILL IN OTHER HEADER FILES**  
|  
|--src/  
| |--main.cpp  
| |--DepartmentTree.cpp  
| |-- **FILL IN OTHER CPP FILES HERE**  
|  
|--data/  
| |--buildings.txt  
| |--connections.txt  
| |--facilities.txt  
| L--departments.txt  
|  
|--README.md  
|--CONTRIBUTIONS.txt  
|--design_document.txt  
|--test_results.txt  
L--.gitignore  

**_Installation_**
-------------------------------------------------------------------------------------

1. Clone the repository:
   **FILL IN HERE**

2. Change to the project directory:
   **FILL IN HERE**

3. Compile the project:
  **FILL IN HERE**

**_How to Run_**
--------------------------------------------------------------------------------------------

Run the executable:

**FILL IN HERE**

The program will load resources from buildings.txt, connections.txt, facilities.txt, departments.txt and display a command-line menu.

**_Data Set / Input_**
-----------------------------------------------------------------------------------------------

* buildings.txt
* connections.txt
* facilities.txt
* departments.txt

**_Methodology_**
----------------------------------------------------------------------------------------------

1. Load campus information from the four data files in the required order.
2. Store facility records in a custom hash table using IDs as keys.
3. Represent buildings and their connections using an undirected graph.
4. Use BFS to identify reachable buildings.
5. Store academic departments in a general tree.
6. Implement department insertion and search.
7. Display department hierarchy using preorder with indentation.
8. Use preorder traversal without indentation.
9. Validate input data text files and manage invalid menu user inputs

**_Results_**
------------------------------------------------------------------------------------------------------

The Campus Information System was implemented as a command-line C++ application. The system loads campus information from four text files, and organizes it using various data structures.

A custom hash table is used for facility lookup by ID. An undirected graph that represents campus building and the walkways connecting them, allows the user to determine which buildings are reachable using BFS.

The department hierarchy is illustrated using a general tree, the user can add and search departments. Additionally the user can display the hierarchy with indentation or perform preorder traversal without indentation.

The system also includes input validation and file loading errors for invalid menu choices and duplicate entries 

Testing was performed for **FILL IN HERE**


**_Challenges / Limitations_**
------------------------------------------------------------------------------------------------------

* Coordinating class interactions
* Ensuring program compiles
* Managing parent and child relationships in the department tree
* Making all parts of the program work together 


<br>
<br>
<br>
<br>

**_Authors_**  
Jason Wildman  
Drake Thompson  
Benjamin Constantin

**_Course_**  
CSCE 2110 - Foundations of Data Structures

**_Instructor_**  
Professor Bahareh Dorri

**_University_**  
University of North Texas

**_Semester_**  
Fall 2026



