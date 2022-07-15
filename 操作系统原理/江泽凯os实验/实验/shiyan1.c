#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun
{
        int val; /* value for SETVAL */
        struct semid_ds *buf; /* buffer for IPC_STAT, IPC_SET */
        unsigned short *array; /* array for GETALL, SETALL */
        struct seminfo *__buf; /* buffer for IPC_INFO */
};

/***对信号量数组semnum编号的信号量做P操作***/
int P(int semid, int semnum)
{
        struct sembuf sops={semnum,-1, SEM_UNDO};
        return (semop(semid,&sops,1));
}

/***对信号量数组semnum编号的信号量做V操作***/
int V(int semid, int semnum)
{
        struct sembuf sops={semnum,+1, SEM_UNDO};
        return (semop(semid,&sops,1));
}
 

int main(int argc, char **argv)
{
        int key ;
        int semid,ret;
        union semun arg;
        struct sembuf semop;
        int flag ;
        key = ftok("/tmp", 0x66 ) ;

        if ( key < 0 )
        {
            perror("ftok key error") ;
            return -1 ;
        }

        /***create semaphore:***/
        semid = semget(key,3,IPC_CREAT|0600);
        if (semid == -1)
        {
                perror("create semaphore error");
                return ;
        }
        if ( argc == 1 )
        {
        printf("please enter the init value of semaphore:");
        int temp;
        scanf("%d", &temp);
        printf("\n");
            arg.val = temp;
            /***对0号信号量设置初始值***/
            ret =semctl(semid,0,SETVAL,arg);
            if (ret < 0 )
            {
                    perror("ctl semaphore error");
                    semctl(semid,0,IPC_RMID,arg);
                    return -1 ;
            }
        }

        /***取0号信号量的值***/
        ret =semctl(semid,0,GETVAL,arg);
        printf("after semctl, sem[0].val =[%d]\n",ret);
        system("date") ;

    char c='0';
    while(c!='E')
    {
        printf("please enter op:（P:P operate,V:Voperate,E:exit）");
        scanf("%c",&c);

        if(c=='P')
        {
                printf("P operate begin： ") ;
                flag = P(semid,0)  ;
                if ( flag )
                {
                    perror("P operate error！") ;
                    return -1 ;
                }

                printf("P operate end\n") ;
                ret =semctl(semid,0,GETVAL,arg);
                printf("after P sem[0].val=[%d]\n",ret);
                system("date") ;
        }
            //if ( argc == 1 )
            //{
            //    sleep(10) ;
            //}
        if(c=='V')
        {
                printf("V operate begin： ");
                if (V(semid, 0) < 0)
                {
                    perror("V operate error");
                    return -1;
                }
    
                printf("V operate end\n") ;
                ret =semctl(semid,0,GETVAL,arg);
                printf("after V sem[0].val=%d\n",ret);
                system("date") ;

            if ( argc >1 )
                {
                        semctl(semid,0,IPC_RMID,arg);
                }
        }
    }

        return 0 ;

}
