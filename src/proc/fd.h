#ifndef PROC_FD_H
#define PROC_FD_H

#include <fs/vfs.h>
#include <stdint.h>

typedef struct file_descriptor
{
  inode_t inode;
  uint32_t offset;
  uint32_t flags;
} file_descriptor_t;

int create_file_descriptor(inode_t inode, uint32_t flags);

file_descriptor_t* get_file_descriptor(int fd);

void delete_file_descriptor(int fd);

#endif
