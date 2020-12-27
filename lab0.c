//
//  lab0.c
//
//  Created by Jeannie Chiem on 10/3/17.
//  Copyright © 2017 Jeannie Chiem. All rights reserved.
//  Email: gnyorly@gmail.com
//  ID: 504-666-652
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <string.h>

void segsignal(int sig)
{
    if (sig == SIGSEGV)
    {
        fprintf(stderr, "ERROR-segmentation fault; %s\n", strerror(errno));
        exit(4);
    }
}

void mkSegfault()
{
    char y;
    char* x = NULL;
    y = *x;
}

int main(int argc, char** argv)
{
    char* inFile = NULL;
    char* outFile = NULL;
    int opt, ifd, ofd;
    int segf_flag = 0;
    
    static struct option long_options[] =
    {
        {"input", required_argument, NULL, 'i'},
        {"output", required_argument, NULL, 'o'},
        {"segfault", no_argument, NULL, 's'},
        {"catch", no_argument, NULL, 'c'},
        {0,0,0,0}
    };
    
    
    while(1)
    {
        opt = getopt_long(argc, argv, "i:o:sc", long_options, NULL);
        
        if (opt == -1)
            break;
        
        switch(opt)
        {
            case 'i':
                inFile = optarg;
                break;
            case 'o':
                outFile = optarg;
                break;
            case 's':
                segf_flag = 1;
                break;
            case 'c':
                signal(SIGSEGV, segsignal);
                break;
            default:
                fprintf(stderr, "ERROR-invalid argument\n\nUSAGE:\n\n\tlab0 [sc] -i FILE1 -o FILE2\n\n");
                exit(1);
        }
    }
    
    if(inFile)
    {
        ifd = open(inFile, O_RDONLY);

        if (ifd >= 0)
        {
            close(0);
            dup(ifd);
            close(ifd);
        }
        else
        {
            perror("ERROR-failure to open input file");
            exit(2);
        }

    }
    
    if(outFile)
    {
        ofd = creat(outFile, 0666);
        
        if (ofd >= 0)
        {
            close(1);
            dup(ofd);
            close(ofd);
        }
        else
        {
            perror("ERROR-failure to create output file");
            exit(3);
        }
    }

    if(segf_flag == 1)
    {
        mkSegfault();
    }
    
    char* buf;
    buf = (char*)malloc(sizeof(char));
    ssize_t rbyte = read(0, buf, 1);
    while(rbyte > 0)
    {
        write(1, buf, 1);
        rbyte = read(0, buf, 1);
    }
    
    free(buf);
    
    exit(0);
}



