#ifndef  _SHM_COM_H
#define _SHM_COM_H
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHM_BUFSIZE 1024
/*定义共享内存数据结构*/
typedef struct 
{
    pid_t pid;
    char buffer[SHM_BUFSIZE];
}shm_buf;



#endif

