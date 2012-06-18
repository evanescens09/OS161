/*
 * Copyright (c) 2000, 2001, 2002, 2003, 2004, 2005, 2008, 2009
 *	The President and Fellows of Harvard College.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE UNIVERSITY AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE UNIVERSITY OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * Process-related syscalls.
 */

#include <types.h>
#include <kern/errno.h>
#include <kern/wait.h>
#include <lib.h>
#include <machine/trapframe.h>
#include <clock.h>
#include <thread.h>
#include <current.h>
#include <copyinout.h>
#include <pid.h>
#include <syscall.h>

/*
 * sys__exit - calls thread exit with a macro to encode the status.
 */
void
sys__exit(int status)
{
	thread_exit(_MKWAIT_EXIT(status));
}

/*
 * sys_getpid - returns the PID of the current thread.
 */
int
sys_getpid(pid_t *retval)
{
	return currthread->t_pid;
}

/*
 * sys_waitpid - return the exit status of a thread after it exits.
 */
int
sys_waitpid(pid_t pid, userptr_t retstatus, int flags, pid_t *retval)
{
	(void)pid;
	(void)retstatus;
	(void)flags;
	(void)retval;
	
	// Implement me
	return EUNIMP;
}

/*
 * sys_fork - create a new process.
 */
int
sys_fork(struct trapframe *tf, pid_t *retval)
{
	(void)tf;
	(void)retval;
	
	// Implement me
	return EUNIMP;
}

/*
 * execv - load the specified program and start it running.
 */
int
sys_execv(userptr_t prog, userptr_t argv)
{
	(void)prog;
	(void)argv;
	
	// Implement me
	return EUNIMP;
}

