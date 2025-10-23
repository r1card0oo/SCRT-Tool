#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "fun-scrt.h"

int main(int argc , char *argv[]){
    if( argc < 2 ){
        help_usage();
    }
    signal(SIGINT, ctrl_c ) ;
    int ip_true = 0 , port_true = 0 , socket_scan ;
    char ip_address[1024] ;
    struct sockaddr_in machen ;
    for( int i = 1 ; i < argc ; i++ ){
        if(strxstr( argv[i] , "-p" ) == 1 ){
            i++ ;
            if( argc == i ){
                fprintf(stderr,"You should write port after argumant '-p' \n") ;
                fprintf(stderr,"example 'scrt -p 8080 domin.com' \n") ;
                exit(1);
            }
            if( strisint( argv[i] ) == 0 ){
                fprintf(stderr,"Port must be int ,") ;
                fprintf(stderr,"This '%s' is not port \nexample ", argv[i] ) ;
                fprintf(stderr,"'scrt -p 8080 domin.com' \n") ;
                exit(1);
            }
            machen.sin_port = htons( atoi( argv[i] ) ) ;
            port_true = 1 ;
        }
        else if(strxstr( argv[i] , "--help" ) == 1 ){    help_usage() ;    }
        else if(argv[i][0] == '-' ){
            fprintf(stderr, "scrt: unrecognized option '%s'\n", argv[i] );
            fprintf(stderr , "See the output of 'scrt --help' for how to usage. \n") ;
            exit(1) ;
        }
        else {
            char cut_ip_start[1024] ;
            int chack_ip_start , atoi_ip ;
            int point_ip_chack = strxchar( argv[i] , '.' ) ;
            if(point_ip_chack != 3 ){
                fprintf(stderr , "scrt: this is not IP '%s' \n", argv[i] ) ;
                fprintf(stderr , "See the output of 'scrt --help' for how to usage. \n") ;
                exit(1) ;
            }
            for( chack_ip_start = 0 ; chack_ip_start <= point_ip_chack ; chack_ip_start++ ){
                strxcut(cut_ip_start , argv[i] , '.', chack_ip_start ) ;
                if( strisint(cut_ip_start) != 1 ){
                    fprintf(stderr , "scrt: this is not IP '%s' \n", argv[i] ) ;
                    fprintf(stderr , "See the output of 'scrt --help' for how to usage. \n") ;
                    exit(1) ;
                }
                atoi_ip = atoi( cut_ip_start ) ;
                if( (atoi_ip >= 0) && (atoi_ip <= 255) ){
                }
                else {
                    fprintf(stderr , "scrt: this is not IP '%s' \n", argv[i] ) ;
                    fprintf(stderr , "See the output of 'scrt --help' for how to usage. \n") ;
                    exit(1) ;
                }
            }
            machen.sin_family = AF_INET ;
            if( inet_pton(AF_INET , argv[i] , &machen.sin_addr) <= 0 ){
                fprintf(stderr , "scrt: this is not IP '%s' \n", argv[i] ) ;
                fprintf(stderr , "See the output of 'scrt --help' for how to usage. \n") ;
                exit(1) ;
            }
            strcpy(ip_address , argv[i] ) ;
            ip_true = 1 ;
        }
    }
    
/* complet select options now scan */
    int many = 0 ;
    if(ip_true != 1){
        fprintf(stderr,"scrt: No IP , must write IP \n") ;
        fprintf(stderr , "See the output of 'scrt --help' for how to usage. \n") ;
        exit(0) ;
    }
    printf("Starting scrt to scan IP [v1.0.0] \n") ;
    printf("scan scan report for IP [%s] \n" , ip_address ) ;
    printf("\n") ;
    printf("PORT    STATE \n") ;
    if(port_true == 1 ){
        socket_scan = socket(AF_INET , SOCK_STREAM , 0 ) ;
        printf("%d" , ntohs( machen.sin_port ) ) ;
        if( connect(socket_scan , (struct sockaddr *) &machen , sizeof(machen) )  < 0 ){
            printf("    closed\n") ;
        }
        else {
            printf("    opened\n") ;
            many++ ;
        }
        printf("\nfind %d port is opened \n" , many ) ;
    }
    else {
        for( int i = 0 ; i <= 10000 ; i++ ){
            socket_scan = socket(AF_INET , SOCK_STREAM , 0 ) ;
            memset( &machen , 0 , sizeof( machen )) ;
            machen.sin_family = AF_INET ;
            machen.sin_port = htons( i ) ;
            inet_pton(AF_INET , ip_address , &machen.sin_addr) ;
            if( connect(socket_scan , (struct sockaddr *) &machen , sizeof(machen) ) < 0 ) ;
            else {
                printf("%d" , ntohs( machen.sin_port ) ) ;
                printf("    opened\n") ;
                many++ ;
            }
        }
        printf("\nfind %d ports is opened \n" , many ) ;
    }
    printf("----< it is end, scrt >---- \n") ;
    
    return 0;
}