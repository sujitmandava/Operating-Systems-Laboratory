typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;
typedef uint pde_t;

typedef struct syspage_entry
{
    int syscall_number;
    int status;
    int argc;
    int args[7];
    int retval;
} syspage_entry;