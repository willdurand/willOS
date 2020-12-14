/** @file */
#ifndef CORE_SYS_SYSCALL_H
#define CORE_SYS_SYSCALL_H

#include <core/isr.h>
#include <sys/types.h>

/// This type represents a syscall handler.
typedef void (*syscall_handler_t)(registers_t* registers);

/**
 * Initializes the syscalls management.
 */
void syscall_init();

/**
 * This is the handler attached to the interrupt used by the syscalls. It is
 * called by the interrupt handler and responsible for finding the right
 * syscall handler to call.
 *
 * @param registers the registers passed to the handler
 */
void syscall_handler(registers_t* registers);

int k_open(const char* pathname, uint32_t flags);
int k_close(int fd);
ssize_t k_read(int fd, void* buf, size_t count);
off_t k_lseek(int fd, off_t offset, int whence);

// Below are the different syscall handlers.
void syscall_test(registers_t* registers);
void syscall_write(registers_t* registers);
void syscall_gettimeofday(registers_t* registers);
void syscall_reboot(registers_t* registers);
void syscall_fstat(registers_t* registers);
void syscall_socket(registers_t* registers);
void syscall_sendto(registers_t* registers);
void syscall_recvfrom(registers_t* registers);

#endif
