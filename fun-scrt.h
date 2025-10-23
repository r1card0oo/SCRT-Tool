#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdarg.h>

// 1 function to print how to usage tool
void help_usage(){
    char usage_help[512] ;
    strcpy( usage_help , "Usage: scrt [Options] {target ip}\n" ) ;
    strcat( usage_help , "argument\n" ) ;
    strcat( usage_help , "    -p  <port>    scan ports , defaulte from 0 to 10000\n" ) ;
    strcat( usage_help , "    --help        show help \n" ) ;
    strcat( usage_help , "Example: scrt -p 80 domin.com \n" ) ;
    strcat( usage_help , "         scrt domin.com \n" ) ;
    printf("%s", usage_help ) ;
    exit(1) ;
}

// 2 when enter Ctrl+C print this function
void ctrl_c(){
    printf("\n----< OK GOOD BAY Ctrl+C >----\n") ;
    exit(1) ;
}

// 3 function the firts string likes the second string
int strxstr(char const ch1[] , char const ch2[] ){
    if( strcmp(ch1 , ch2 ) != 0){
        return 0 ;
    } 
    int len_str = strlen(ch1) ;
    int i ;
    for(i = 0 ; i < len_str ; i++) {
        if( ch1[i] == ch2[i] );
        else {
            return 0 ;
        }
    }
    return 1 ;
}
// 4 if string is int return 1 else return 0 
int strisint(char const str[] ){
    int lenstr = strlen(str) ;
    for(int i = 0 ; i < lenstr ; i++ ){
        if( str[i] == '0' ) ;
        else if( str[i] == '1') ;
        else if( str[i] == '2') ;
        else if( str[i] == '3') ;
        else if( str[i] == '4') ;
        else if( str[i] == '5') ;
        else if( str[i] == '6') ;
        else if( str[i] == '7') ;
        else if( str[i] == '8') ;
        else if( str[i] == '9') ;
        else {
            return 0 ;
        }
    }
    return 1 ;
}

// 5 how match character at string 
int strxchar(char const str[],char const ch){
    int lenstr = strlen(str) ;
    int x = 0 ;
    for(int i = 0; i < lenstr ; i++ ){
        if( str[i] == ch ){
            x++ ;
        }
    }
    return x ;
}

// 6 location character at string
int locxchar(char const str[], char const ch , int nu ){
    int chnu = strxchar(str,ch) ;
    int lenstr = strlen(str) ;
    int x = 0 ;
    if(chnu <= nu ){
        return 0 ;
    }
    for(int i = 0 ; i < lenstr ; i++ ){
        if(str[i] == ch ){
            if(x == nu){
                return i ;
            }
            x++ ;
        }
    }
    return 0 ;
}

// 7 cut string to small part when variable
int strxcut(char *cut , char str[] , char const ch , int x ){
    for(int f = 0 ; cut[f] != 0 ; f++ ){    cut[f] = 0 ;    }
    int lenstr = strlen(str) ;
    int z = 0 ;
    int y = 0 ;
    if(x > strxchar(str , ch)){
        return 0 ;
    }
    if( ( x - 1 ) != - 1 ){
        z = ( locxchar(str , ch ,(x - 1 )) + 1 ) ;
    }
    for(int i = z ; i < lenstr ; i++ ){
        if( str[i] == ch ){
            return 1 ;
        }
        else {
            cut[y] = str[i] ;
            y++ ;
        }
    }
    return 1 ;
}

