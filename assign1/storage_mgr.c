#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<math.h>
#include <stdbool.h> 
#include "storage_mgr.h"

 //creating a file pointer 
FILE *Fpointer;

void initStorageManager (void){
    printf("..........Initializing Storage Manager..........\n");
}


//in this function new page file is created here 
RC createPageFile (char *Fname){    
    //here the new page file is created 
    Fpointer = fopen(Fname, "w+");
    if (Fname != NULL){
        //allocating a memory for the page size 
    SM_PageHandle newBlankPg = (SM_PageHandle)calloc(PAGE_SIZE, sizeof(char)); 
    fwrite(newBlankPg, 1, PAGE_SIZE,Fpointer);
    //closing the file pointer 
    fclose(Fpointer);
    printf("File is closed successfully\n");

    //Memory Management using free() function
    free(newBlankPg);
    printf("Memory allocated is freed successfully\n");
    return RC_OK;
    }
    else
    {
        return RC_FILE_NOT_FOUND;
    }
}


//In this function the created page file is opened

RC openPageFile(char *Fname, SM_FileHandle *filehandleptr)
{

/*The storage manager has to maintain several types of information for an open file: 
The number of total pages in the file, the current page position (for reading and writing), 
the file name, and a POSIX file descriptor or FILE pointer.
We are have all the variables,functions or info available in the structure named SM_FileHandle
*/

//We have to open the file initially
Fpointer = fopen(Fname, "r+");

//verifying whether the file exists
if(Fpointer != NULL)
//here file exists
{
//we can find the starting position and the total number of pages with the help of fseek and ftell functions
// Seek to end so ftell reads correct number of char
    fseek(Fpointer, 0, SEEK_END);
    int end_value=0;
    int totalpagenum=0;
    end_value=ftell(Fpointer);
    //finding total number of pages
    if((end_value % PAGE_SIZE)==0){
        totalpagenum=(end_value/PAGE_SIZE);
    }
    else
    {
          totalpagenum=(end_value/PAGE_SIZE)+1;
    }
    //now, we will initialize all the required attributes needed
    int a,b;
    //storing total number of pages
    filehandleptr->totalNumPages = totalpagenum; 
    a=filehandleptr->totalNumPages;
    printf("total number of page is %d \n",a);

    //Setting the current page position to the start position or 0
    filehandleptr->curPagePos = 0; 
    b=filehandleptr->curPagePos;
    printf("current page is %d \n",b);
    //storing filename
    filehandleptr->fileName = Fname;

    //storing file pointer
    filehandleptr->mgmtInfo = Fpointer;
    return RC_OK;
}
else {
//here file do not exist
return RC_FILE_NOT_FOUND;
}
}

//In this function the opened page file is closed

RC closePageFile(SM_FileHandle *filehandleptr) {
    //if the file is not existing it returns a error 
    if (filehandleptr->mgmtInfo == NULL) 
    {
        return RC_FILE_NOT_FOUND;
    }
    // this fclose condition will close the file 
    if (fclose(filehandleptr->mgmtInfo) != 0) 
    {
        return RC_FILE_NOT_FOUND;
    }
    else 
    {
    Fpointer = NULL;
    // this statment is printed when the file is closed sucessfully
    printf("Succesfully the file is closed \n ");
    return RC_OK;
    }
}

//In this function the page file is destroyed 
RC destroyPageFile (char *Fname)
{	// here we are trying to remove if there is any file existing 
	Fpointer = fopen(Fname, "r");
    if(Fpointer != NULL){
        //closing file before terminating
        fclose(Fpointer);
        
        unlink(Fname);
        Fpointer=NULL;
        printf("\n page destroyed successfully \n");
        return RC_OK;
    
        }
    else
    {
         return RC_FILE_NOT_FOUND;
    }
}

//the page in the memory block is readed 

RC readBlock (int pagenumber, SM_FileHandle *filehandleptr, SM_PageHandle pagehandleptr)
{
     /*
This method opens the file and reads the pagenumber value or block which is passed as an argument and then it stores its value or content to memory with the help of Pagehandleptr, which is the page handle.
*/
    Fpointer = fopen(filehandleptr->fileName, "r");
    if (Fpointer != NULL)
    {
        printf("The file is opened\n");
        //Page number is passed as an argument to this function and if this value is greater than the total number of pages, then it should throw an error code

        if ((filehandleptr->totalNumPages)> pagenumber && pagenumber>=0)
        {
            printf("\nYaay! The page you are looking exists!");
        }
        else
        {
             int totalPagenum;
             totalPagenum=filehandleptr->totalNumPages;
             printf("\ntotal number of page is %d \n",totalPagenum);
            
            printf("\n page is  %d",pagenumber);
            printf("\nOops! The page you are looking for does not exist \n");
            return RC_READ_NON_EXISTING_PAGE;
        }
        int pagestart = (pagenumber *PAGE_SIZE);

       //using SEEK_SET to point to the start of the page
        if(fseek(Fpointer, pagestart, SEEK_SET)!=0)
        {
            printf("\nFailed to put pointer to start of the page");
            exit(1);
        }
        else
        {
            printf("\nPointer is now pointed to the start of the page");
        }
	    printf("\nBefore reading the file, the pointer is positioned at  %d \n \n", pagestart);
        int ptrpos;
        fread(pagehandleptr, sizeof(char), PAGE_SIZE, Fpointer);
	    ptrpos=ftell(Fpointer);

        printf("After reading the file, the pointer is positioned at  %d \n \n", ptrpos);
           
        int currentpos;
      
        if((ptrpos % PAGE_SIZE)==0){
        currentpos=((ptrpos/PAGE_SIZE)-1);
        }
        else
        {
          currentpos=(ptrpos/PAGE_SIZE);
        }
       
        // Updating the current position of pointer in the struct SM_FileHandle
        filehandleptr -> curPagePos = currentpos;

     int a=filehandleptr -> curPagePos;
     printf("current position of block after readblock is %d \n",a);
     int b=filehandleptr->totalNumPages;
    printf("total number of pages, called inside read block %d \n",b);

            if(fclose(Fpointer) == 0)
            {
                printf("The file is closed succesfully\n");
                return RC_OK;
            }
            
            else  
            {
                printf("\nOops! The file is not closed \n");
                exit(1);
            }
    }
    else 
    {
        printf("\nThe file does not exist\n");
        return RC_FILE_NOT_FOUND;
        
    }
}


// getting the position of the current block 
int getBlockPos (SM_FileHandle *filehandleptr) 
{   
    if (filehandleptr != NULL) 
    {
        int bposition = filehandleptr->curPagePos;
       
        printf("the position of the Block is %d\n", bposition);
        
    //returning the currentpage position
        return bposition;
    }
    if(filehandleptr == NULL)
    printf("the given File handler is not initiated.");
    return 0;
}

// reading the page from first block 
RC readFirstBlock (SM_FileHandle *filehandleptr, SM_PageHandle pagehandleptr)
{
    if (filehandleptr == NULL) {
        return RC_FILE_NOT_FOUND;
    }
    //calling the readBlock() fuction 
   int bposition = filehandleptr->curPagePos;
        printf("the position of the Block before reading first block is %d\n", bposition);

    return readBlock(0, filehandleptr, pagehandleptr);
}

// reading the page from Previous block 

RC readPreviousBlock (SM_FileHandle *filehandleptr, SM_PageHandle pagehandleptr)
{
    int currentPgPos;
    int prevPgNum;
    currentPgPos = getBlockPos(filehandleptr);
    prevPgNum = currentPgPos - 1;
    filehandleptr->curPagePos=prevPgNum;
     int bposition = filehandleptr->curPagePos;
        printf("the position of the Block after reading prev block is %d\n", bposition);

    //calling the readBlock() fuction 
    return readBlock(prevPgNum, filehandleptr, pagehandleptr);

}

// reading the page from current block 
RC readCurrentBlock (SM_FileHandle *filehandleptr, SM_PageHandle pagehandleptr)
{
	int currentPgPos;
	currentPgPos = getBlockPos(filehandleptr);
     int bposition = filehandleptr->curPagePos;
        printf("the position of the Block after reading current block is %d\n", bposition);
    //calling the readBlock() fuction
    return readBlock(currentPgPos, filehandleptr, pagehandleptr);
}

// reading the page from next block 
RC readNextBlock (SM_FileHandle *filehandleptr, SM_PageHandle pagehandleptr)
{
    int currentPgPos;
    int nextPgPos;
	currentPgPos = getBlockPos(filehandleptr);
    nextPgPos = currentPgPos + 1;
    filehandleptr -> curPagePos=nextPgPos;
       int currentpos=filehandleptr -> curPagePos;
     printf("current position of block after readnextblock is %d \n",currentpos);
	fclose(Fpointer); 
    //calling the readBlock() fuction
    return readBlock(nextPgPos, filehandleptr, pagehandleptr);
}

// reading the page from Last block 
RC readLastBlock (SM_FileHandle *filehandleptr, SM_PageHandle pagehandleptr)
{
    int lastPgNum = filehandleptr->totalNumPages - 1;
    //calling the readBlock() fuction
    return readBlock(lastPgNum, filehandleptr, pagehandleptr);
}

//This function writes content to the page in our file.
RC writeBlock(int pageNum, SM_FileHandle *filehandleptr, SM_PageHandle pagehandleptr)
{
if (Fpointer != NULL)
{
// Check if page number is within range
if (pageNum >= 0 && pageNum < filehandleptr->totalNumPages)
{
// Check if file handle is valid
if (filehandleptr == NULL)
{
    printf("\nsfile handle is not valid \n");
return RC_FILE_HANDLE_NOT_INIT;
}
else
{
// Check if file pointer is valid
FILE *filePtr = filehandleptr->mgmtInfo;
if (filePtr == NULL)
{
    printf("\nsfile pointer is not valid \n");
return RC_FILE_NOT_FOUND;
}
else
{
// Move the file pointer to the desired page
int seekResult = fseek(filePtr, pageNum * PAGE_SIZE, SEEK_SET);
if (seekResult != 0)
{
printf("\nseek didnt work \n");
return RC_WRITE_FAILED;
}
else
{
// Write the page content to the file
size_t writeResult = fwrite(pagehandleptr, sizeof(char), PAGE_SIZE, filePtr);

if (writeResult != PAGE_SIZE)
{
return RC_WRITE_FAILED;
}
else
{
// Update the current page position and return success
filehandleptr->curPagePos = pageNum;
int currentpos=filehandleptr -> curPagePos;
printf("current position of block after write block is %d \n",currentpos);
int a=filehandleptr->totalNumPages;
printf("total number of pages, called inside write block %d \n",a);

return RC_OK;
}
}
}
}
}
else
{
    printf("\nPage size exceeded \n");
return RC_WRITE_FAILED;
}
}
else{
      printf("\nThe file does not exist\n");
        return RC_FILE_NOT_FOUND;
}
}



//This function writes content to the current block or page in our file.

RC writeCurrentBlock (SM_FileHandle *filehandleptr, SM_PageHandle pagehandleptr)
{
    // Check if file handle is valid
    if (filehandleptr == NULL)
    {
         printf("\nThe file does not exist\n");
        return RC_FILE_NOT_FOUND;
    }
    else
    {
    int currentBlockPos;
    currentBlockPos = filehandleptr->curPagePos;
    // Write memory page to the current block
    RC result = writeBlock(currentBlockPos, filehandleptr, pagehandleptr);
    return result;
    }
}

//This function appends a block or page to the existing file and hence updates the total number of pages by one.

RC appendEmptyBlock (SM_FileHandle *filehandleptr)
{
if (Fpointer != NULL)
{
    //allocating memory for the page
char emptyPage = (char) calloc(PAGE_SIZE, sizeof(char));

if (fseek(filehandleptr -> mgmtInfo, 0, SEEK_END) == 0) {
    //writing data to the page
	fwrite(emptyPage, PAGE_SIZE, 1, filehandleptr -> mgmtInfo);

    // updating total number of pages 
	filehandleptr->totalNumPages++;
    filehandleptr -> curPagePos++;
    int a;
    int currentpos;
    int totalpage;
    totalpage=filehandleptr->totalNumPages;
    currentpos=filehandleptr -> curPagePos;
    printf("total number of page after appendemptyblock is %d \n",totalpage);
    printf("current position of block after appendemptyblock is %d \n",currentpos);

  

} else {
    //free the memory 
	free(emptyPage);
	return RC_WRITE_FAILED;
}

free(emptyPage);
return RC_OK;
}
else{
     printf("\nThe file does not exist\n");
        return RC_FILE_NOT_FOUND;
}
}



/*This function compares the passed number of page and the total number of page in the file and 
then adds that many number of empty blocks or pages which is further needed using appendEmptyBlock(...).*/
RC ensureCapacity (int totalNumofPages, SM_FileHandle *filehandleptr)
{
	Fpointer = fopen(filehandleptr->fileName, "a");

	if(Fpointer != NULL)
	{    //checking the total number of pages in our file with the number of pages passed as the argument 
		if(totalNumofPages <= filehandleptr->totalNumPages) 
	    {
            
		    return RC_OK;
	    }
	    else
        {      
            //call the appendEmptyBlock() block till it satifies the condition 
		    while((filehandleptr->totalNumPages) < totalNumofPages)
		    {

			    appendEmptyBlock(filehandleptr);
		    }

	    } 
	}
    else
    {
         printf("\nThe file does not exist\n");
        return RC_FILE_NOT_FOUND;
    }
         int currentpos=filehandleptr -> curPagePos;
     printf("current position of block after appendemptyblock or ensure capacity is %d \n",currentpos);
      int totalpage=filehandleptr->totalNumPages;
     printf("total pagenumber after appendemptyblock or ensure capacity is %d \n",totalpage);
	fclose(Fpointer); 
    return RC_OK;
}

