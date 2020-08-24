#include "shell.h"

int main() {
  //arguments
  char * args[64];

  do {

    //prompt = $shell_4
    printf("%s ", "$shell_4 ");

    //eisodos apo to xrhsth
    char eisodos[256];
    fgets(eisodos, 255, stdin);

    //diagrafei teleutaio char pou mphke me thn fgets
    eisodos[strlen(eisodos) - 1] = '\0';

    //xwrizoume se "lekseis" thn eisodo
    char * arg = strtok(eisodos, " ");

    //counter "leksewn"
    int i = 0;

    //pername to apotelesma tou strtok sto args
    while (arg) {
      //an exoume to xarakthra  '<' kaloume thn apoarxeio kai kanoume strtok auto pou epistrefei
      if ( * arg == '<') {
        apoarxeio(strtok(NULL, " "));
        //an exoume to xarakthra  '>' kaloume thn prosarxeio kai kanoume strtok auto pou epistrefei
      } else if ( * arg == '>') {
        prosarxeio(strtok(NULL, " "));
        //an exoume to xarakthra  '|' kaloume thn solinosi
      } else if ( * arg == '|') {
        args[i] = NULL;
        solinosi(args);
        i = 0;
      } else {
        // an den exoume kanenan apo tous 3 xarakthres gia anakateuthinsi h solinosi pername to arg sto array args
        args[i] = arg;
        i++;
      }
      //kanoume strtok sto arg
      arg = strtok(NULL, " ");
    }
    //sto teleutaio stoixeio tou args vazw NULL
    args[i] = NULL;

    //fork
    pid_t pid;
    if (strcmp(args[0], "exit") != 0) {
      pid = fork();
      if (pid < 0) {
        fprintf(stderr, "error");
      }
      //diergasia-paidi
      else if (pid == 0) {
        execvp(args[0], args);
      }
      //diergasia-pateras
      else {
        if (anamoni) {
          waitpid(pid, NULL, 0);
        } else {
          anamoni = 0;
        }
      }
      break;
    } else {
      flag_exit = 0;
    }

  } while (flag_exit);

}

