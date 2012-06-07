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
 * Code for running a user program from the menu, and code for execv,
 * which have a lot in common.
 */

#include <types.h>
#include <kern/errno.h>
#include <kern/fcntl.h>
#include <limits.h>
#include <lib.h>
#include <thread.h>
#include <current.h>
#include <synch.h>
#include <copyinout.h>
#include <addrspace.h>
#include <vm.h>
#include <vfs.h>
#include <syscall.h>
#include <test.h>

/*
 * Core code for runprogram: load the executable into memory.
 */
static
int
loadexec(char *path, vaddr_t *entrypoint, vaddr_t *stackptr)
{
	struct addrspace *newvm, *oldvm;
	struct vnode *v;
	char *newname;
	int result;

	/* New name for thread. */
	newname = kstrdup(path);
	if (newname == NULL) {
		return ENOMEM;
	}

	/* Open the file. */
	result = vfs_open(path, O_RDONLY, 0, &v);
	if (result) {
		kfree(newname);
		return result;
	}

	/* Make a new address space. */
	newvm = as_create();
	if (newvm == NULL) {
		vfs_close(v);
		kfree(newname);
		return ENOMEM;
	}

	/* Replace address spaces, and activate the new one. */
	oldvm = curthread->t_addrspace;
	curthread->t_addrspace = newvm;
	as_activate(curthread->t_addrspace);

 	/*
	 * Load the executable. If it fails, restore the old address
	 * space and (re-)activate it.
	 */
	result = load_elf(v, entrypoint);
	if (result) {
		vfs_close(v);
		curthread->t_addrspace = oldvm;
		as_activate(curthread->t_addrspace);
		as_destroy(newvm);
		kfree(newname);
		return result;
	}

	vfs_close(v);

	/* Define the user stack in the address space */
	result = as_define_stack(curthread->t_addrspace, stackptr);
	if (result) {
		curthread->t_addrspace = oldvm;
		as_activate(curthread->t_addrspace);
		as_destroy(newvm);
		kfree(newname);
		return result;
        }

	/*
	 * Wipe out old address space.
	 *
	 * Note: once this is done, execv() must not fail, because there's
	 * nothing left for it to return an error to.
	 */
	if (oldvm) {
		as_destroy(oldvm);
	}

	/*
	 * Now that we know we're succeeding, change the current thread's
	 * name to reflect the new process.
	 */
	kfree(curthread->t_name);
	curthread->t_name = newname;

	return 0;
}


/*
 * Load program "progname" and start running it in usermode.
 * Does not return except on error. Does not accept any arguments
 * to "progname".
 *
 * Calls vfs_open on PROGNAME (via loadexec) and thus may destroy it,
 * so it needs to be mutable.
 */
int
runprogram(char *progname)
{
	vaddr_t entrypoint, stackptr;
	int result;
 
	/* We must be a thread that can run in a user process. */
	KASSERT(curthread->t_pid >= PID_MIN && curthread->t_pid <= PID_MAX);

	/* We should be a new thread. */
	KASSERT(curthread->t_addrspace == NULL);

	/* Load the executable. Note: must not fail after this succeeds. */
	result = loadexec(progname, &entrypoint, &stackptr);
	if (result) {
		return result;
	}

	/* Warp to user mode. */
	enter_new_process(0 /*argc*/, NULL /*userspace addr of argv*/, stackptr, entrypoint);
	
	/* enter_new_process does not return. */
	panic("enter_new_process returned\n");
	return EINVAL;
}

