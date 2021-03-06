#include "../include/w_io.h" //silly name for a file
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int redir_in_to(int fd) // used by pipes 
{
    //int stdin_fd=dup(1);
    dup2(fd,0);

    return 0;

}

int redir_out_to(int fd) // 1 >& fd or >& fd
{
    //int stdout_fd=dup(1);
    dup2(fd,1);

    return 0;
}


int out_to_file(const char * filepath)// cmd > filename or > filename or 1 > filename
{
    int file_fd= open(filepath,O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH); //added mode because of O_CREAT flag 
    dup2(file_fd,1);

    return file_fd;
}

int append_to_file(const char * filepath)// cmd >> filename or >> filename or 1 >> filename
{
    int file_fd= open(filepath,O_WRONLY|O_CREAT|O_APPEND,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);//added mode because of O_CREAT flag 
    dup2(file_fd,1);

    return file_fd;
}

int err_to_file(const char *filepath)
{
    int file_fd= open(filepath,O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);//added mode because of O_CREAT flag 
    dup2(file_fd,2);

    return file_fd;
}


int append_err_to_file(const char *filepath)
{
    int file_fd= open(filepath,O_WRONLY|O_CREAT|O_APPEND,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);//added mode because of O_CREAT flag 
    dup2(file_fd,1);

    return file_fd;
}


int truncate_file(const char* filepath) // : > filename
{
    int file_fd= open(filepath,O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);//added mode because of O_CREAT flag
    close(file_fd);     
    return 0;
}


int redir_to_file(int fd,const char* filepath) // fd > filename
{
    int orig_fd= dup(fd);
    int file_fd = open(filepath,O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH); //added mode because of O_CREAT flag 
    dup2(file_fd,fd);
    return orig_fd;
}


int redir(int M,int N) // M >& N
{
    int orig_M = dup(M);
    dup2(N,M);
    return orig_M;
}

int rdir_err_out_to_file(const char* filename) // &> filename //new to BASH
{
    int file_fd = open(filename,O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    dup2(file_fd,1);
    dup2(file_fd,2);
    return file_fd;
}



