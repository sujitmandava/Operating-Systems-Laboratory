#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

#define type_addr uint

int sys_fork(void)
{
    return fork();
}

int sys_exit(void)
{
    exit();
    return 0; // not reached
}

int sys_wait(void)
{
    return wait();
}

int sys_kill(void)
{
    int pid;

    if (argint(0, &pid) < 0)
        return -1;
    return kill(pid);
}

int sys_getpid(void)
{
    return myproc()->pid;
}

int sys_sbrk(void)
{
    int addr;
    int n;

    if (argint(0, &n) < 0)
        return -1;
    addr = myproc()->sz;
    if (growproc(n) < 0)
        return -1;
    return addr;
}

int sys_sleep(void)
{
    int n;
    uint ticks0;

    if (argint(0, &n) < 0)
        return -1;
    acquire(&tickslock);
    ticks0 = ticks;
    while (ticks - ticks0 < n)
    {
        if (myproc()->killed)
        {
            release(&tickslock);
            return -1;
        }
        sleep(&ticks, &tickslock);
    }
    release(&tickslock);
    return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int sys_uptime(void)
{
    uint xticks;

    acquire(&tickslock);
    xticks = ticks;
    release(&tickslock);
    return xticks;
}

int sys_v2paddr(void)
{
    type_addr *pa, *va;

    if (argptr(0, (void *)&pa, sizeof(*pa)) < 0)
    {
        return -1;
    }

    if (argptr(1, (void *)&va, sizeof(*va)) < 0)
    {
        return -1;
    }

    struct proc *currProcess = myproc();
    pde_t *pgdir = currProcess->pgdir;
    pde_t *pde = &pgdir[PDX(va)];

    if (!(*pde & PTE_P))
    {
        return -1;
    }

    if (!(*pde & PTE_U))
    {
        return -1;
    }

    pde_t *pgtab = (pte_t *)P2V(PTE_ADDR(*pde));
    pde_t *pte = &pgtab[PTX(va)];
    if (!(*pte & PTE_P))
    {
        return -1;
    }

    if (!(*pte & PTE_U))
    {
        return -1;
    }

    *pa = PTE_ADDR(*pte) | PTE_FLAGS(va);
    return 0;
}