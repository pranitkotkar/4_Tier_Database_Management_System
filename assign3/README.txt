RUNNING THE SCRIPT
=======================================

$ make clean 

$ make

$ make run

$ make test_expr

$ make run_expr

========================================

Group Memebers:

    1.  Name : Pranit Gorakhnath Kotkar
        Email : pkotkar1@hawk.iit.edu
        CWID : A20512027

    2.  Name : Pranav Saji
        Email : psaji@hawk.iit.edu
        CWID : A20518289

    3.  Name : kirthika subramaniam B
        Email :ksubramaniam@hawk.iit.edu
        CWID : A20512536
 
1. TABLE AND RECORD MANAGER FUNCTIONS
=======================================

The record manager provides functions for initializing and shutting down the record manager. These functions utilize the BufferPool and StorageManager components to manage the storage and retrieval of records. The record manager is responsible for managing tables and their associated records. It provides functions for creating, opening, closing, and deleting tables, as well as functions for retrieving and modifying the data stored in those tables. The record manager is a critical component of many database management systems, as it provides the necessary functionality for managing large volumes of structured data.

initRecordManager():
The record manager must be initialized using the initRecordManager() function. The resources and components required to maintain records in a database system are configured by this function. In order to manage the memory and disk storage for the data, the function generates a BufferPool and a StorageManager when it is invoked. The system is ready to build and manage tables and records, as well as run queries and other operations on the data by initializing the record manager.

shutdownRecordManager:
The record manager is shut down and allotted resources are released via the RecordManager() function. This function releases all the resources that the record manager has accumulated while it was in use. Release of the memory and disk storage resources allotted to the BufferPool and StorageManager is part of this process. It's crucial to shut down the record manager to guarantee that all resources are released and that no memory leaks or other problems develop. Usually, the function is invoked when the record manager is no longer required or when the database system is shutting down.

createTable:
The createTable() function creates a new table with the name specified in the name parameter, and a schema defined by the schema parameter. The schema defines the attributes of the table, including the names, data types, and sizes of the attributes. The function creates the necessary data structures and allocates memory for the new table. After the function call, the new table is ready to be populated with records. The createTable() function is typically called when a new table is needed in the database system.

openTable:
The name parameter specifies the name of the table that will be opened by the openTable() function. The function locates the table in the database system when it is invoked and builds a data structure to represent it. The function also reads the table's schema data, which includes the names, sizes, and data types of its attributes. For use in later operations on the table, this data is stored in the data structure. The table is available for usage and can be queried or altered as needed following the function call. When a table in the database system needs to be accessed, the openTable() function is commonly used.

closeTable:
A table that was previously opened with the openTable() method is closed using the closeTable() function. The data structure constructed to represent the table and any other resources allotted while the table was in use are released when the function is called. If the table's contents have changed and have not yet been saved, this also entails flushing those changes to disk. The table is not used again until the openTable() function is used to reopen it after the function call. When the database system no longer needs to access the table or when the program using the table is ending, the closeTable() method is normally called.

deleteTable:
A whole table can be permanently deleted from the database using the deleteTable() function. If the table is still open when the function is called, it shuts it first before deleting all of the data connected to it, including any meta-data about the table's attributes or schema. If a backup copy is not there, it is impossible to restore a deleted table. The deleteTable() function should only be used with caution because misuse can result in unwanted consequences. When the table is no longer required and its contents are not crucial to keep, the function should only be utilized.

getNumTuples:
The getNumTuples() function gives the total number of rows (or tuples) that are currently kept in a given table. The data in the table can be subjected to numerous analyses using this, such as computing averages or percentages based on the total number of records. It is crucial to understand that this function does not account for any potential changes to the table after it is run; instead, it just returns the current number of tuples in the table.


==========================================================================================================================



2. RECORD FUNCTIONS

These functions are used to carry out tasks connected to controlling and modifying tables and the records that belong to them. The actions include initializing and shutting down the record manager as well as generating, opening, closing, and deleting tables. In addition, the record manager offers methods for getting details about the data kept in a table, like the quantity of tuples. In general, these functions give programmers a mechanism to work with and maintain database tables and the data they contain.


insertRecord:
To add a new record to a particular table, use the insertRecord function. It requires a pointer to the buffer pool manager, a pointer to the record's data, and a pointer to the table's schema as inputs. It provides an integer value that indicates whether the operation was successful or unsuccessful.

deleteRecord:
deleteRecord is a function that deletes the record with the specified Record ID 'id' from the table.

updateRecord:
--> Modifies a record in the table pointed to by the parameter "rel".

getRecord(....):
The function getRecord(...) is used to retrieve a record from the table having the Record ID specified by the parameter "id".

========================================================================

3. SCAN FUNCTIONS

The scan-related functions are made to extract tuples from a table that satisfy a particular requirement. Depending on the search criteria, these functions can scan the full table or just a section of it. One or more tuples that meet the provided criteria can be found using the scan functions.


startScan:
--> Initializes a scan operation for a table

next:
--> returns the subsequent table record that meets the specified criterion.

closeScan:
--> Closes the ongoing scan operation on a table

==========================================================================


4. SCHEMA FUNCTIONS

The table's schemas can be changed using the schema functions. They can be used to generate a new schema or to determine the size of the records in bytes for a specific schema.

getRecordSize:
The getRecordSize() function determines and returns the record's size in bytes for the given schema.

freeSchema:
The memory allotted for the schema must be deallocated using the freeSchema function.

createSchema:
A new schema is created by allocating memory for it and setting its properties, such as the number of attributes, the names of the attributes, the datatypes, and the lengths.

================================================================================


5. ATTRIBUTE FUNCTIONS

These functions allow accessing the attributes of a record

createRecord:
The function "createRecord" generates a brand-new record for a specified schema with all fields initialized to NULL values.

getAttr:
Using the stated schema, the function getAttr fetches an attribute's value from a given record.

setAttr:
The setAttr function is used to change a record's value of a particular attribute in accordance with the given schema.

attrOffset:
Sets the offset with attrOffset.

freeRecord:
The "freeRecord" function frees up memory that had been allotted to a record.











