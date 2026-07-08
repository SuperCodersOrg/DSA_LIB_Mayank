**Date:** 8 July 2026 | **Time:** 9:00 - 11:30

Session – Redis Lite Foundation
---------------------------------

Today I started building the **Redis Lite** project on top of my custom DSA library. The goal of this project is to create a lightweight in-memory key-value database similar to Redis while using my own implementations of data structures instead of the C++ STL containers.

### Work Completed

*   Designed the overall architecture of the project by separating responsibilities into different classes:
    
    *   RedisLite – Command Line Interface (CLI)
        
    *   RedisStorage – Storage layer
        
    *   CommandParser – Command identification
        
    *   RedisStats – Operation statistics
        
    *   HashMap – Backend storage
        
*   Created the CommandType enum class to represent all supported commands in a type-safe manner instead of relying on string comparisons throughout the program.
    
*   Implemented the CommandParser class, which converts user-entered command strings such as SET, GET, and DEL into their corresponding CommandType values.
    
*   Implemented the RedisStorage wrapper around my custom HashMap, exposing high-level operations like:
    
    *   set()
        
    *   get()
        
    *   del()
        
    *   exists()
        
    *   clear()
        
    *   size()
        
    *   capacity()
        
    *   print()
        
*   Built the initial version of the RedisLite command-line interface.
    
*   Added a welcome screen displaying all supported commands and usage examples.
    
*   Implemented the command-processing loop using:
    
    *   getline() to read complete user input.
        
    *   std::stringstream to tokenize the command.
        
    *   CommandParser to identify the command.
        
    *   switch statement to dispatch execution to the appropriate handler function.
        
*   Implemented the first command handler:
    
    *   handleSet()
        

### Concepts Learned

During this session I learned several important C++ concepts:

*   Difference between enum and enum class.
    
*   Why large C++ projects separate declarations (.h) from implementations (.cpp).
    
*   How to define member functions outside the class using the scope resolution operator (::).
    
*   How private member functions can still be implemented inside a .cpp file because they belong to the class.
    
*   How std::stringstream can be used to parse command-line input.
    
*   Difference between extracting input using >> and std::getline().
    
*   Why getline() leaves a leading space after reading previous tokens and how erase(0, 1) removes it.
    
*   Importance of const correctness while designing reusable data structures.
    

### Problems Faced

*   Encountered several compilation errors related to const correctness in HashMap and LinkedList.
    
*   Updated accessor functions such as get\_size() and get\_capacity() to be const.
    
*   Learned that calling non-const member functions on const objects causes compiler errors.
    
*   Permission denied: RedisLite.exeThis happened because the executable was still running while attempting to rebuild. Closing the running process resolved the issue.
    

### Current Status

The Redis Lite application can now:

*   Display a welcome screen.
    
*   Continuously accept user commands.
    
*   Parse commands using CommandParser.
    
*   Route commands through a switch statement.
    
*   Execute the initial SET command handler.
    

The project structure is now established, making it straightforward to implement the remaining Redis commands (GET, DEL, EXISTS, PRINT, CLEAR, SIZE, KEYS, and STATS) in the upcoming sessions.

### Next Goals

*   Implement the remaining command handlers.
    
*   Add complete statistics tracking.
    
*   Implement the KEYS command.
    
*   Improve output formatting.
    
*   Add file persistence (SAVE and LOAD) in future versions.