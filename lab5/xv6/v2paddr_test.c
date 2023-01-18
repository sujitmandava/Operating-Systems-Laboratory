#include "types.h"
#include "user.h"
#include "syscall.h"
#include "memlayout.h"
#include "mmu.h"

#define type_addr uint

int globalTest = 32767;

int main(int argc, char *argv[])
{
    int localTest = -32768;
    type_addr *kernelTest = (void *)(KERNBASE + 0x555);
    type_addr *lva = (type_addr *)(&localTest);
    type_addr *gva = (type_addr *)(&globalTest);
    type_addr *kva = kernelTest;

    type_addr lpa;
    type_addr gpa;
    type_addr kpa;

    int ls = v2paddr(&lpa, lva);
    int gs = v2paddr(&gpa, gva);
    int ks = v2paddr(&kpa, kva);

    if (ls == 0)
    {
        printf(1, "Physical Address of 0x%x(Local variable): 0x%x\n", lva, lpa);
    }
    else
    {
        printf(1, "Conversion of 0x%x(Local variable) failed\n", lva);
    }

    if (gs == 0)
    {
        printf(1, "Physical Address of 0x%x(Global variable): 0x%x\n", gva, gpa);
    }
    else
    {
        printf(1, "Conversion of 0x%x(Global variable) failed\n", gva);
    }

    if (ks == 0)
    {
        printf(1, "Physical Address of 0x%x(Kernel Space Address): 0x%x\n", kva, kpa);
    }
    else
    {
        printf(1, "Conversion of 0x%x(Kernel Space Address) failed\n", kva);
    }

    exit();
}