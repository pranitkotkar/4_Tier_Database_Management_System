Group Members:

    1.  Name : Pranit Gorakhnath Kotkar
        Email : pkotkar1@hawk.iit.edu
        CWID : A20512027

    2.  Name : Pranav Saji
        Email : psaji@hawk.iit.edu
        CWID : A20518289

    3.  Name : Kirthika Subramaniam B
        Email : ksubramaniam@hawk.iit.edu
        CWID : A20512536


Included Files:

    README.txt
    dberror.c
    dberror.h
    storage_mgr.c
    storage_mgr.h
    test_assign1_1.c
    test_helper.h
    Makefile
    

AIM
===========================
Our goal is to implement a simple storage manager - a module that is capable of reading blocks from a file on disk into memory and writing blocks from memory to a file on disk.

STEPS FOR RUNNING THE ASSIGNMENT1
=========================

1) Go to Project root (assign1) using Terminal.

2) Type "make clean" to discard the old compiled .o files.

3) Type "make" to compile all project files including "test_assign1_1.c" file.

4) Type "make run" to run "test_assign1_1.c" file.

FUNCTION DESCRIPTION
==========================

initStorageManager() : This function initializes the storage manager. 

createPageFile(...) : This function creates a page file.

openPageFile(...) : This function opens the created page file.

closePageFile(...) : This function closes the file.

destroyPageFile(...) : This function deletes the page file, if it is present, using the unlink function.

readBlock(...) : This method opens the file and reads the pagenumber value or block which is passed as an argument and then it stores its value or content to memory with the help of Pagehandleptr, which is the page handle.
 
getBlockPos(...) : This method gives the current page position. 

readFirstBlock(...) : This function calls the first block using readBlock(...) where 0 as the pageNum is being provided as argument.

readPreviousBlock(...) : This function calls the previous block using readBlock(...) where (current page position - 1) is being provided as argument.

readCurrentBlock(...) : This function calls the current block using readBlock(...) where (current page position) is being provided as argument.

readNextBlock(...) : This function calls the next block using readBlock(...) where (current page position + 1) is being provided as argument.

readLastBlock(...) : This function calls the last block using readBlock(...) where (total number of pages - 1) is being provided as argument.

writeBlock(...) : This function writes content to the page in our file.

writeCurrentBlock(...) : This function calls the current block using writeBlock(...) where pageNum = current is being provided as argument.

appendEmptyBlock(...) : This function appends a block or page to the existing file and hence updates the total number of pages by one.

ensureCapacity(...) : This function compares the passed number of page and the total number of page in the file and then adds that many number of empty blocks or pages which is further needed using appendEmptyBlock(...).
