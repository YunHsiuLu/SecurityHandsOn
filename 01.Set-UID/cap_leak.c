#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
    int	fd = 0;
    char *v[2];
    
    fd = open( "/etc/zzz", O_RDWR | O_APPEND );
    //O_RDWR = open in read & write
    //O_APPEND = open in append file
    
    if( fd == -1 )
    {
        printf( "Cannot open /etc/zzz\n" );
        exit(0);
    }
    
    printf( "fd is %d\n", fd );

    //close(fd); // downgrade after close file

    // Disable the privilege
    setuid( getuid() );
    
    // Execute /bin/sh
    v[0] = "/bin/sh";
    v[1] = 0;
    execve( v[0], v, 0 );
    
    return 0;
}
