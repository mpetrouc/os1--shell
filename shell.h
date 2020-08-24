#include <stdio.h>
#include <string.h> //gia strtok
#include <stdlib.h>
#include <unistd.h> //gia thn execvp kai dup2
#include <sys/wait.h> //gia thn waitpid
#include <errno.h> //gia stderr
#include <fcntl.h> //gia open
#include <sys/stat.h>

//flag = 0 gia exodo kai flag = 1 gia kanoniki leitourgia
int flag_exit = 1;
//anamoni = 0 gia waitpid kai anamoni = 1 gia kanoniki leitourgia
int anamoni = 1;

//functions
void apoarxeio(char * arxeio_eisodou);
void prosarxeio(char * arxeio_eisodou);
void solinosi(char * args[]);

void apoarxeio(char * arxeio_eisodou) {
  //anoigma arxeiou gia anagnwsi(O_RDONLY)
  int fd1 = open(arxeio_eisodou, O_RDONLY);
  //dhmiourgeitai antigrafo tou file descriptor
  dup2(fd1, 0);
  //kleisimo arxeiou
  close(fd1);
}

void prosarxeio(char * arxeio_eisodou) {
  //anoigma arxeiou gia grapsimo(O_WRONLY)
  //an to arxeio den uparxei to dhmiourgei( O_CREAT)

  int fd2 = open(arxeio_eisodou, O_WRONLY | O_TRUNC | O_CREAT, 0600);
  //dhmiourgeitai antigrafo tou file descriptor
  dup2(fd2, 1);
  //kleisimo arxeiou
  close(fd2);
}

void solinosi(char * args[]) {
  //array me 2 file descriptors,enan gia to diavasma kai enan gia to grapsimo
  int p[2];
  //pipe sinartisi
  //an apotuxei ginetai exodos
  if (pipe(p) < 0) {
    exit(1);
  }
  //dhmiourgeitai antigrafo twn 2 file descriptors kai kleisimo
  dup2(p[0], 0);
  close(p[0]);

  dup2(p[1], 1);
  close(p[1]);
}
