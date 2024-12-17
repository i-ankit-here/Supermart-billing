# **Supermart-billing**
It is a program to generate bills of a Supermart which also includes features like inventory management. User can add,remove and update the items in the stock/inventory any time and can genrate bills for the customer simultaneously. It is developed by utilizing the basic and advanced concepts of Object-Oriented Programming (OOP) using C++ programming language.

## Instructions to install and run the program
- Clone the repository or download the zip file and extract in a folder<br/>
> git clone https://github.com/i-ankit-here/Supermart-billing
- Main.cpp file will be there
- Open it and use and build and run it with any modern c++ compiler
- It will be a menu driven program, so choose the operation you need to perform from the menu.
- Inventory.dat has some sample items in the inventory already, if you you want add all items by yourself you can delete it first and then build and run main.cpp

## Object-Oriented Programming (OOP) Concepts Utilized:
### Basic Concepts 
- **Classes and Objects**: The system defines classes such as item(abstract class), electronic, grocery to represent individual items in the inventory. Inventory class is defined to to manage inventory items. Bill class manages the bills using billItem class.
- **Encapsulation**: Data members within classes are kept private, with public member functions provided to access and modify these attributes, ensuring controlled interaction with the data.
- **Abstraction**: Implementation details are hidden while essential features are shown and utilized by the users.
- **Inheritence**: Inheritence is utilized within the classes like electronic and grocery derived from abstract class item.
- **Containership**: Inventory class holds the pointers of item class which basicaly points to the derived objects and bill contains objects of billItem class to generate bills.
****
### Advanced Concepts
- **Abstract class**: item is an abstract class with pure virtual functions for calculating discount and tax on the item.
- **Pure virtual functions**: These are utilized in the abstract classes.
- **Runtime Polymorphism**: inventory class contains the vector of pointer of item abstract class which points to any of the derived class objects and can be utilized to manage items in the inventory.
- **Constructors and destructors**: Constroctors are utilized very efficiently to create items and bills and open files and read data from inventory.dat, destructor is utilized to finally update the inventory.dat and closing it.
- **Exception handling**: Using try, catch, and throw for runtime error management during the program to enhance user experience and handle unwanted behavior by the program.
- **File handling**: inventory.dat is used to store the items in the inventory along with their details. It is being used in Binary mode whereas a bill is genrated in a text file which is formatted and can be printed.
****
## File Details
- **main.cpp**: It is the main file containing menu and the instructions. This is the only file that is needed to be compiled for the execution.
- **product.cpp**: It contains the abstract class item and its derived classes electronic and grocery;
- **inventory.cpp**: It contains the inventory class which is basically doing inventory management by including methods such as add, remove and update.
- **bill.cpp**: It caontains the billItem class which represents the details of individual bill items in the bill and the bill class which contains the methods to manage and generate the bill.
- **inventory.dat**: It is a binary file to store the inventory items and their details.
- **customer** (text file): The name of the file will be name of the customer and it will contain the genrated bill.