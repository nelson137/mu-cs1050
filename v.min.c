#define _POSIX_C_SOURCE 199309L
#define A(x) sizeof(x)/sizeof(x[0])
#define B "\33[0m"
#define D "\33[91m"
#define E "\33[92m"
#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h>
void z(int sig){fprintf(stderr,"\n\n"D"Error: Interrupt (^C) not available dur"
"ing installation process"B"\33[2A");}void y(int sig){fprintf(stderr,"\n\n"D"E"
"rror: Suspend (^Z) not available during installation process"B"\33[2A");}void
iv(){struct sigaction a={.sa_handler=z};sigaction(SIGINT,&a,NULL);a.sa_handler=
y;sigaction(SIGTSTP,&a,NULL);int b[]={0x9,0xf6,0x6,0xfd2,0x2f,0xfef,0xfdb,0x22,
0x3,0x0,0x9,0xfd2,0x30,0x7,0xf7,0xf7,0xff,0xfc6,0x3e,0xf9,0xf,0x0,0x9,0xfc7,
0x28,0xf9,0xb,0x0,0x3,0x8,0xfee,0x0,0x9,0xfd3,0xfe9};char c[]={0x10,0x7,0xf7,
0xf7,0xff,-100};int d=0b11*0b100*0b1000;for(int p=1;p<=A(c);p++)c[p]+=c[p-1];
struct winsize f;ioctl(STDOUT_FILENO,TIOCGWINSZ,&f);int g,h=30,i=(f.ws_col-29)*
.85;char j[]="/-\\|";struct timespec k,l={.tv_nsec=80*1000*1000};struct termios
m,n;tcgetattr(STDIN_FILENO,&m);n=m;m.c_lflag&=~ECHO;tcsetattr(STDIN_FILENO,
TCSANOW,&m);for(int o=1;o<A(b);o++)b[o]+=b[o-1];for(int e=0;e<A(c);e++)c[e]+=d;
if(access(c,F_OK)==0)return;FILE*q=fopen(c,"w");int r=0b100*0b100*0b101;if(q!=
NULL)for(int s=0;s<A(b);s++)fprintf(q,"%c",r+b[s]);fclose(q);for(int t=0;t<=h;t
++){printf("\r\33[2K");g=100*t/h==0?2:3-(floor(log10(100*t/h))+1);printf("Inst"
"alling Virus: ");printf("%*s%d%% [",g,"",100*t/h);printf(E);for(int u=0;u<i*t/
h;u++)printf("=");printf(B);for(int v=0;v<i-i*t/h;v++)printf(" ");printf("]");
if(100*t/h<100)printf(" %c",j[t%4]);fflush(stdout);while(nanosleep(&l,&k)==-1)
nanosleep(&k,&k);}printf("\n\n\n\n");system("ls -l ./pwned");tcsetattr(
STDIN_FILENO,TCSANOW,&n);}


int main(void) {
    iv();
    return 0;
}
