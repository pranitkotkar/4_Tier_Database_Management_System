Execute the following instructions in order to start the buffer management program on a Linux server.

$ make clean 

$ make

$ make run_test1

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
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
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Functions Implemented

1. PAGE MANAGEMENT FUNCTIONS
   -----------------------------
   Pages from the disk are loaded into the buffer pool using the page management-related functions, which are also used to unpin pages, mark pages as unclean, and compel page frames to be written to disk.

  pinPage(...)  

  ---> The function is used to retrieve a page from the page file on disk and pin it to a specified page number pageNum. Before pinning the page, the buffer pool is checked for available space. 
  ---> If there is space available, the page frame is placed in the buffer pool. 
  ---> There are four different page replacement mechanisms that can be used: FIFO, LRU, LFU, and CLOCK. 
  ---> When a page is selected for replacement, it is first checked to see if it is "dirty", which means that its contents have been modified since it was last written to the page file on disk. 
  ---> If the pgFrame flag is set to 1, the page's contents are written back to the page file on disk before it is replaced with the new page. 
  ---> Once the old page is written to disk, the new page can be placed in the same spot in the buffer pool where the old page was located.

  makeDirty(...) 

  ---> The function is used to mark a specified page frame as "dirty" by setting its pgFrame[iterator].dirty flag to 1. 
  ---> This is done by searching through each page in the buffer pool until the page with the specified pageNum is found. 
  ---> Once the page is located, its pgFrame[iterator].dirty flag is set to 1 to indicate that its contents have been modified since it was last written to the page file on disk.


 forcePage(...) 

 ---> The function is used to write the contents of a specified page frame to the page file on disk. 
 ---> It searches through each page in the buffer pool using a loop construct until it locates the page with the specified pageNum. 
 ---> Once the page is located, its contents are written to the page file on disk using Storage Management functions. 
 ---> After the write operation is complete, the dirtyBit flag for the page is set to 0 to indicate that its contents are now up-to-date with the page file on disk.

 unpinPage(...)

 ----> The function is used to unpin a specified page, which means that it is no longer actively being used by the client. 
 ----> To unpin the page, the function uses the pageNum of the page to search through each page in the buffer pool using a loop construct until it finds the page. 
 ----> Once the page is located, its pgFrame[iterator].clientCount is decreased by 1, indicating that the client has stopped using that page. 
 ----> This allows the page to potentially be replaced by another page in the buffer pool if there is a need for additional space.


----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


2. STATISTICS FUNCTIONS
   -------------------
 getNumWriteIO(...) 

 ---> The function returns the total number of pages that have been written to the disk by the buffer pool. 
 ---> This value is tracked by the numWrites variable, which is initialized to 0 when the buffer pool is created and incremented each time a page is written to the disk.

getNumReadIO(...) 

---> The function returns the total number of pages that have been read from the disk by the buffer pool. 
---> This value is tracked by the readCountOfNumPgs variable.

getDirtyFlags(...)

---> The function returns an array of bools, where the size of the array is equal to the number of pages in the buffer pool. 
---> To obtain the dirtyBit value for each page frame, the function iterates through all the page frames in the buffer pool and sets the "n"th element of the array to TRUE if the page saved in the "n"th frame is dirty.

getFrameContents(...) 

---> The function returns an array of PageNumbers, where the size of the array is equal to the number of pages in the buffer pool. 
---> To obtain the pageNum value of each page frame in the buffer pool, the function iterates through all the page frames and sets the "n"th element of the array to the pageNum of the page saved in the "n"th frame.

getFixCounts(...) 

---> The function returns an array of ints, where the size of the array is equal to the number of pages in the buffer pool. 
---> To obtain the fixCounts value for each page frame, the function iterates through all the page frames in the buffer pool and sets the "n"th element of the array to the fixCounts of the page saved in the "n"th frame.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

3. BUFFER POOL FUNCTIONS
   ----------------------
initBufferPool(...) 

---> initializes the buffer pool with a size determined by the numPages argument. 
---> The page file containing the cached pages in memory is tracked by pageFileName. 
---> The page replacement strategy is specified by the -> symbol and any required parameters are passed in stratData.

forceFlushPool(...) 

---> writes the modified pages, which have the isDirtyPage = 1 attribute, to disk. 
---> It checks each page frame in the buffer pool to see if it meets the criteria of isDirtyPage = 1 and fixCount = 0, indicating that no clients are currently using the page frame. 
---> If both criteria are met, the page frame is written to the page file on disk.

shutdownBufferPool(...) 

---> releases all memory and resources allocated for the buffer pool. 
---> Before erasing the buffer pool, forceFlushPool(...) is called to write all modified pages to disk. 
---> If any page is still being accessed by a client, the function throws an RC_BUFFER_PIN_PG.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

4. PAGE REPLACEMENT ALGORITHM FUNCTIONS
   -----------------------------------
FIFO_Strategy(...) - 

---> The First-In-First-Out (FIFO) page replacement algorithm uses a queue to manage the buffer pool. 
---> The page that was initially loaded into the buffer pool is the first to be replaced when needed.

LRU_Strategy(...) - 

---> The Least Recently Used (LRU) page replacement algorithm replaces the page frame in the buffer pool that hasn't been accessed for the longest period. 
---> The lstflNumber field keeps track of how many times each page frame has been accessed, and the page frame with the lowest lstflNumber value is replaced.

CLOCK_Strategy(...) - 

---> The CLOCK page replacement algorithm replaces the most recently added page frame to the buffer pool. 
---> It employs a circular list with a "hand" that indicates the page frame to be replaced next.




