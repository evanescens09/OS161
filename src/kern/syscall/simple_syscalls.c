/*
Kevin Hon Man Chan
997385752 :: chanke25
CSCC69S12 Assignment 1
*/

#include <types.h>
#include <syscall.h>
#include <lib.h>
#include <thread.h>
#include <kern/errno.h>

void sys_exit(int exitcode)
{
	thread_exit(exitcode);
	DEBUG(DB_SYSCALL,"Error in sys_exit(), error code = %d\n", exitcode);
}

int sys_printchar(char c)
{
	int i = kprintf("%c", c);
	if(i == 1){
		return i;	
	}
	else {
		DEBUG(DB_SYSCALL,"Error in sys_printchar(), error code = %d\n", EFAULT);
		return EFAULT;
	}
}


