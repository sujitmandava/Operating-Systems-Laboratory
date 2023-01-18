#   Project Outline: 

##  Abstract: 
Implementing flexible system calls on the __xv6__ operating system. 

## Approach:
The following steps provide a broad outline regarding our plan to implement and test flexible system calls for the xv6 operating system:

-   Create system call pages to add entries of system calls to be executed/scheduled (Accessible to the user process). (Feature Addition)

-   Edit the scheduler for the 4th CPU to handle only system calls. (Minor tweak)
    - Currently, do polling for finding system call entries with status as *submited* on the *syscall* page, optimization is system call scheduling
-   `flexsc_register()` (minor tweak): Writes into *syscall* page
    -   `flexsc_register()` handler function (Feature Addition).

-   `flexsc_wait()` (minor tweak) : Executes at least one system call registered by the process.
    -  `flexsc_wait()` handler function (Feature Addition)

-   User-level threading on xv6 will be implemented in line with previously existing source code. This [code](Source:github.com/amay19970/uthreads/tree/2e1c03ebca1337bbbf624bc13170c0215b2111fc/xv6-public) was written by GitHub user amay19970. It implements a context-switching mechanism for user-level threading, along with a scheduler for the threads. Any tweaks required to implement flexible system calls will be made as needed. (Addition)
-   Test case 1: To check if the basic functionality of `flexsc_register()` is working properly.
-   Test case 2: To check if the functionality of both `flexsc_register()` and `flexsc_wait()` is working together.

-   New system calls that use exception-less system calls will be used in the above test cases for testing.  



