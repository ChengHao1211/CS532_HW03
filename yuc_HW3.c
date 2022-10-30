/* 
Name:Cheng-Hao Yu 
BlazerId: yuc
Project #: HW03
To compile: use make mysearch to compile. 
To run: use ./search to run the program. Also you can put in some command. For example: -S -s -f -t -e -E. 
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>

char *filetype(unsigned char type) {
  char *str;
  switch(type) {
  case DT_BLK: str = "block device"; break;
  case DT_CHR: str = "character device"; break;
  case DT_DIR: str = "directory"; break;
  case DT_FIFO: str = "named pipe (FIFO)"; break;
  case DT_LNK: str = "symbolic link"; break;
  case DT_REG: str = "regular file"; break;
  case DT_SOCK: str = "UNIX domain socket"; break;
  case DT_UNKNOWN: str = "unknown file type"; break;
  default: str = "UNKNOWN";
  }
  return str;
}



int subcount = 0;
char subpath[4096] = "./";
char sub[10] = "/";

int Sflag = 0;
int sflag = 0;
int fflag = 0;
int tflag = 0;
int Eflag = 0;
int eflag = 0;
char *cvalue = NULL, *strIndex = NULL, *eIndex = NULL, *EIndex = NULL;
char *Inputsubstring = NULL, *substring = NULL, *strlayer;
int layer ;
int sizeindex = 0;
char **eInput;
char **EInput;
char* arr[10];
char* Eflaguse[100];
int EflagNum = 3;
char UseForE[20][100];
int UseForEnum = 0;





typedef int MYFUNC(char path[]);

int findDir(char path[]) {
  int q = 0;
  while (arr[q] != NULL)
  {
    q++;
  }
  
  char* arr2[q+1];
  q = 0;
  while (arr[q] != NULL)
  {
    arr2[q] = arr[q];
    //printf("arr2[%d] = %s    ",q,arr2[q]);
    q++;
  }
  arr2[q+1] = NULL;
  //printf("arr2[%d] = %s    \n",q,arr2[q]);



  /*--------------------------------------------------------*/
  
  char prepath[4096] = "";
  char space[4096] = "";
  char exactfile[4096];
  struct dirent *dirent;
  char Ewow[1000];


  DIR *parentDir;
    parentDir = opendir (path);
    if (parentDir == NULL) {
        printf ("Error opening directory '%s'\nError:%s\n\n", path, strerror(errno));
        exit (-1);
    }

    for (int i = 0; i < subcount; i++){
            strcat(space,"      ");
    }
    while((dirent = readdir(parentDir)) != NULL){
      struct stat buf;


      //printf("path === %s          file === %s\n", path, dirent->d_name);


      strcpy(exactfile,path);
      strcat(exactfile,dirent->d_name);
      //printf("exactfile == %s\n",exactfile);

      if (stat(exactfile, &buf) < 0) {
              printf("lstat error\n");
              exit(-1);
          }

      if(strcmp(dirent->d_name,".") != 0 && strcmp(dirent->d_name,"..") != 0){
        //printf("%d  %d  %d\n", Sflag, sflag, fflag);
        //printf("path === %s \n",path);
	      if (Sflag == 1){
          if(sflag == 1 ){
            if(buf.st_size <= sizeindex){
              if (fflag == 1){
                if(strstr(dirent->d_name,substring) != NULL && subcount <= layer){
                  if (tflag == 1){
                    if(strcmp(cvalue,"f") == 0){
                        if (strcmp(filetype(dirent->d_type),"regular file") == 0){
                          /*===============Eflag arg===============*/
                          if (Eflag == 1){
                            //printf("path === %s \n",path);
                            strcpy(Ewow,path);
                            strcat(Ewow,dirent->d_name);
                          } 
                          /*===============Eflag arg===============*/
                          
                          /*===============eflag===============*/
                          if (eflag == 1){
                            printf ("%s%s File size: %lld  perission : %lo Last access: %s\n",space, dirent->d_name, (long long)buf.st_size, (unsigned long) buf.st_mode, ctime(&buf.st_mtime));
                            //if (strcmp(filetype(dirent->d_type),"directory") == 0){
                              //printf("----%s---get youuuuu directory\n",dirent->d_name);
                              pid_t pid;
                              int status;
                              pid = fork();
                              if (pid == 0) {/* this is child process */
                                //printf("this is child process\n");

                                /*===============execvp arg===============*/
                                //printf("path === %s \n",path);
                                char wow[1000];
                                strcpy(wow,path);
                                arr2[q] = wow;
                                strcat(arr2[q],dirent->d_name);
                                //strcat(arr2[q],sub);
                                arr2[q+1] = NULL;
                                //printf("arr2[%d] = %s    \n",q,arr2[q]);
                                //printf("arr2[%d] = %s    \n",q+1,arr2[q+1]);
                                /*===============execvp arg===============*/

                                execvp(arr2[0],arr2);
                                perror("execvp");
                                exit(-1);
                              }
                              else if (pid > 0) { /* this is the parent process */
                                      //printf("Wait for the child process to terminate\n");
                                      wait(&status); /* wait for the child process to terminate */
                                      if (WIFEXITED(status)) { /* child process terminated normally */
                                          //printf("Child process exited with status = %d\n", WEXITSTATUS(status));
                                      } 
                                      else { /* child process did not terminate normally */
                                          printf("Child process did not terminate normally!\n");
                                          /* look at the man page for wait (man 2 wait) to determine
                                            how the child process was terminated */
                                      }
                              } 
                              else { /* we have an error */
                                      perror("fork"); /* use perror to print the system error message */
                                      exit(EXIT_FAILURE);
                              }
                            //}
                          }
                          /*===============eflag===============*/
                          else{
                            printf ("%s%s File size: %lld  perission : %lo Last access: %s\n",space, dirent->d_name, (long long)buf.st_size, (unsigned long) buf.st_mode, ctime(&buf.st_mtime));
                          }
                        }
                    }   
                    else if(strcmp(cvalue,"d") == 0){
                         if (strcmp(filetype(dirent->d_type),"directory") == 0){
                          /*===============Eflag arg===============*/
                          if (Eflag == 1){
                            //printf("path === %s \n",path);
                            strcpy(Ewow,path);
                            strcat(Ewow,dirent->d_name);
                          } 
                          /*===============Eflag arg===============*/

                          /*===============eflag===============*/
                          if (eflag == 1){
                            printf ("%s%s File size: %lld  perission : %lo Last access: %s\n",space, dirent->d_name, (long long)buf.st_size, (unsigned long) buf.st_mode, ctime(&buf.st_mtime));
                            //if (strcmp(filetype(dirent->d_type),"directory") == 0){
                              //printf("----%s---get youuuuu directory\n",dirent->d_name);
                              pid_t pid;
                              int status;
                              pid = fork();
                              if (pid == 0) {/* this is child process */
                                //printf("this is child process\n");

                                /*===============execvp arg===============*/
                                //printf("path === %s \n",path);
                                char wow[1000];
                                strcpy(wow,path);
                                arr2[q] = wow;
                                strcat(arr2[q],dirent->d_name);
                                //strcat(arr2[q],sub);
                                arr2[q+1] = NULL;
                                //printf("arr2[%d] = %s    \n",q,arr2[q]);
                                //printf("arr2[%d] = %s    \n",q+1,arr2[q+1]);
                                /*===============execvp arg===============*/

                                execvp(arr2[0],arr2);
                                perror("execvp");
                                exit(-1);
                              }
                              else if (pid > 0) { /* this is the parent process */
                                      //printf("Wait for the child process to terminate\n");
                                      wait(&status); /* wait for the child process to terminate */
                                      if (WIFEXITED(status)) { /* child process terminated normally */
                                          //printf("Child process exited with status = %d\n", WEXITSTATUS(status));
                                      } 
                                      else { /* child process did not terminate normally */
                                          printf("Child process did not terminate normally!\n");
                                          /* look at the man page for wait (man 2 wait) to determine
                                            how the child process was terminated */
                                      }
                              } 
                              else { /* we have an error */
                                      perror("fork"); /* use perror to print the system error message */
                                      exit(EXIT_FAILURE);
                              }
                            //}
                          }
                          /*===============eflag===============*/
                          else{
                            printf ("%s%s File size: %lld  perission : %lo Last access: %s\n",space, dirent->d_name, (long long)buf.st_size, (unsigned long) buf.st_mode, ctime(&buf.st_mtime));
                          }
                        }
                    }
                  }
                  else{
                    /*===============Eflag arg===============*/
                    if (Eflag == 1){
                      //printf("path === %s \n",path);
                      strcpy(Ewow,path);
                      strcat(Ewow,dirent->d_name);
                    } 
                    /*===============Eflag arg===============*/

                    /*===============eflag===============*/
                    if (eflag == 1){
                      printf ("%s%s File size: %lld  perission : %lo Last access: %s\n",space, dirent->d_name, (long long)buf.st_size, (unsigned long) buf.st_mode, ctime(&buf.st_mtime));
                      //if (strcmp(filetype(dirent->d_type),"directory") == 0){
                        //printf("----%s---get youuuuu directory\n",dirent->d_name);
                        pid_t pid;
                        int status;
                        pid = fork();
                        if (pid == 0) {/* this is child process */
                          //printf("this is child process\n");

                          /*===============execvp arg===============*/
                          //printf("path === %s \n",path);
                          char wow[1000];
                          strcpy(wow,path);
                          arr2[q] = wow;
                          strcat(arr2[q],dirent->d_name);
                          //strcat(arr2[q],sub);
                          arr2[q+1] = NULL;
                          //printf("arr2[%d] = %s    \n",q,arr2[q]);
                          //printf("arr2[%d] = %s    \n",q+1,arr2[q+1]);
                          /*===============execvp arg===============*/

                          execvp(arr2[0],arr2);
                          perror("execvp");
                          exit(-1);
                        }
                        else if (pid > 0) { /* this is the parent process */
                                //printf("Wait for the child process to terminate\n");
                                wait(&status); /* wait for the child process to terminate */
                                if (WIFEXITED(status)) { /* child process terminated normally */
                                    //printf("Child process exited with status = %d\n", WEXITSTATUS(status));
                                } 
                                else { /* child process did not terminate normally */
                                    printf("Child process did not terminate normally!\n");
                                    /* look at the man page for wait (man 2 wait) to determine
                                      how the child process was terminated */
                                }
                        } 
                        else { /* we have an error */
                                perror("fork"); /* use perror to print the system error message */
                                exit(EXIT_FAILURE);
                        }
                      //}
                    }
                    /*===============eflag===============*/
                    else{
                      printf ("%s%s File size: %lld  perission : %lo Last access: %s\n",space, dirent->d_name, (long long)buf.st_size, (unsigned long) buf.st_mode, ctime(&buf.st_mtime));
                    }
                  }
                }
              }
              else{
                /*===============eflag===============*/
                if (eflag == 1){
                  printf ("%s%s File size: %lld  perission : %lo Last access: %s\n",space, dirent->d_name, (long long)buf.st_size, (unsigned long) buf.st_mode, ctime(&buf.st_mtime));
                  //if (strcmp(filetype(dirent->d_type),"directory") == 0){
                    //printf("----%s---get youuuuu directory\n",dirent->d_name);
                    pid_t pid;
                    int status;
                    pid = fork();
                    if (pid == 0) {/* this is child process */
                      //printf("this is child process\n");

                      /*===============execvp arg===============*/
                      //printf("path === %s \n",path);
                      char wow[1000];
                      strcpy(wow,path);
                      arr2[q] = wow;
                      strcat(arr2[q],dirent->d_name);
                      //strcat(arr2[q],sub);
                      arr2[q+1] = NULL;
                      //printf("arr2[%d] = %s    \n",q,arr2[q]);
                      //printf("arr2[%d] = %s    \n",q+1,arr2[q+1]);
                      /*===============execvp arg===============*/

                      execvp(arr2[0],arr2);
                      perror("execvp");
                      exit(-1);
                    }
                    else if (pid > 0) { /* this is the parent process */
                            //printf("Wait for the child process to terminate\n");
                            wait(&status); /* wait for the child process to terminate */
                            if (WIFEXITED(status)) { /* child process terminated normally */
                                //printf("Child process exited with status = %d\n", WEXITSTATUS(status));
                            } 
                            else { /* child process did not terminate normally */
                                printf("Child process did not terminate normally!\n");
                                /* look at the man page for wait (man 2 wait) to determine
                                  how the child process was terminated */
                            }
                    } 
                    else { /* we have an error */
                            perror("fork"); /* use perror to print the system error message */
                            exit(EXIT_FAILURE);
                    }
                  //}
                }
                /*===============eflag===============*/
                else{
                  printf ("%s%s File size: %lld  perission : %lo Last access: %s\n",space, dirent->d_name, (long long)buf.st_size, (unsigned long) buf.st_mode, ctime(&buf.st_mtime));
                }
              }

            }
          }

          else if (fflag == 1){
            if(strstr(dirent->d_name,substring) != NULL && subcount <= layer){
              if (tflag == 1){
                if(strcmp(cvalue,"f") == 0){
                  if (strcmp(filetype(dirent->d_type),"regular file") == 0){
                    /*===============Eflag arg===============*/
                    if (Eflag == 1){
                      //printf("path === %s \n",path);
                      strcpy(Ewow,path);
                      strcat(Ewow,dirent->d_name);
                    } 
                    /*===============Eflag arg===============*/

                    /*===============eflag===============*/
                    if (eflag == 1){
                      printf ("%s%s File size: %lld  perission : %lo Last access: %s\n",space, dirent->d_name, (long long)buf.st_size, (unsigned long) buf.st_mode, ctime(&buf.st_mtime));
                      //if (strcmp(filetype(dirent->d_type),"directory") == 0){
                        //printf("----%s---get youuuuu directory\n",dirent->d_name);
                        pid_t pid;
                        int status;
                        pid = fork();
                        if (pid == 0) {/* this is child process */
                          //printf("this is child process\n");

                          /*===============execvp arg===============*/
                          //printf("path === %s \n",path);
                          char wow[1000];
                          strcpy(wow,path);
                          arr2[q] = wow;
                          strcat(arr2[q],dirent->d_name);
                          //strcat(arr2[q],sub);
                          arr2[q+1] = NULL;
                          //printf("arr2[%d] = %s    \n",q,arr2[q]);
                          //printf("arr2[%d] = %s    \n",q+1,arr2[q+1]);
                          /*===============execvp arg===============*/

                          execvp(arr2[0],arr2);
                          perror("execvp");
                          exit(-1);
                        }
                        else if (pid > 0) { /* this is the parent process */
                                //printf("Wait for the child process to terminate\n");
                                wait(&status); /* wait for the child process to terminate */
                                if (WIFEXITED(status)) { /* child process terminated normally */
                                    //printf("Child process exited with status = %d\n", WEXITSTATUS(status));
                                } 
                                else { /* child process did not terminate normally */
                                    printf("Child process did not terminate normally!\n");
                                    /* look at the man page for wait (man 2 wait) to determine
                                      how the child process was terminated */
                                }
                        } 
                        else { /* we have an error */
                                perror("fork"); /* use perror to print the system error message */
                                exit(EXIT_FAILURE);
                        }
                      //}
                    }
                    /*===============eflag===============*/
                    else{
                      printf ("%s%s File size: %lld  perission : %lo Last access: %s\n",space, dirent->d_name, (long long)buf.st_size, (unsigned long) buf.st_mode, ctime(&buf.st_mtime));
                    }
                  }
                }   
                else if(strcmp(cvalue,"d") == 0){
                  if (strcmp(filetype(dirent->d_type),"directory") == 0){
                    /*===============Eflag arg===============*/
                    if (Eflag == 1){
                      //printf("path === %s \n",path);
                      strcpy(Ewow,path);
                      strcat(Ewow,dirent->d_name);
                    } 
                    /*===============Eflag arg===============*/

                    /*===============eflag===============*/
                    if (eflag == 1){
                      printf ("%s%s File size: %lld  perission : %lo Last access: %s\n",space, dirent->d_name, (long long)buf.st_size, (unsigned long) buf.st_mode, ctime(&buf.st_mtime));
                      //if (strcmp(filetype(dirent->d_type),"directory") == 0){
                        //printf("----%s---get youuuuu directory\n",dirent->d_name);
                        pid_t pid;
                        int status;
                        pid = fork();
                        if (pid == 0) {/* this is child process */
                          //printf("this is child process\n");

                          /*===============execvp arg===============*/
                          //printf("path === %s \n",path);
                          char wow[1000];
                          strcpy(wow,path);
                          arr2[q] = wow;
                          strcat(arr2[q],dirent->d_name);
                          //strcat(arr2[q],sub);
                          arr2[q+1] = NULL;
                          //printf("arr2[%d] = %s    \n",q,arr2[q]);
                          //printf("arr2[%d] = %s    \n",q+1,arr2[q+1]);
                          /*===============execvp arg===============*/

                          execvp(arr2[0],arr2);
                          perror("execvp");
                          exit(-1);
                        }
                        else if (pid > 0) { /* this is the parent process */
                                //printf("Wait for the child process to terminate\n");
                                wait(&status); /* wait for the child process to terminate */
                                if (WIFEXITED(status)) { /* child process terminated normally */
                                    //printf("Child process exited with status = %d\n", WEXITSTATUS(status));
                                } 
                                else { /* child process did not terminate normally */
                                    printf("Child process did not terminate normally!\n");
                                    /* look at the man page for wait (man 2 wait) to determine
                                      how the child process was terminated */
                                }
                        } 
                        else { /* we have an error */
                                perror("fork"); /* use perror to print the system error message */
                                exit(EXIT_FAILURE);
                        }
                      //}
                    }
                    /*===============eflag===============*/
                    else{
                      printf ("%s%s File size: %lld  perission : %lo Last access: %s\n",space, dirent->d_name, (long long)buf.st_size, (unsigned long) buf.st_mode, ctime(&buf.st_mtime));
                    }
                  }
                }
              }
              else{
                /*===============Eflag arg===============*/
                if (Eflag == 1){
                  //printf("path === %s \n",path);
                  strcpy(Ewow,path);
                  strcat(Ewow,dirent->d_name);
                } 
                /*===============Eflag arg===============*/

                /*===============eflag===============*/
                if (eflag == 1){
                  printf ("%s%s File size: %lld  perission : %lo Last access: %s\n",space, dirent->d_name, (long long)buf.st_size, (unsigned long) buf.st_mode, ctime(&buf.st_mtime));
                  //if (strcmp(filetype(dirent->d_type),"directory") == 0){
                    //printf("----%s---get youuuuu directory\n",dirent->d_name);
                    pid_t pid;
                    int status;
                    pid = fork();
                    if (pid == 0) {/* this is child process */
                      //printf("this is child process\n");

                      /*===============execvp arg===============*/
                      //printf("path === %s \n",path);
                      char wow[1000];
                      strcpy(wow,path);
                      arr2[q] = wow;
                      strcat(arr2[q],dirent->d_name);
                      //strcat(arr2[q],sub);
                      arr2[q+1] = NULL;
                      //printf("arr2[%d] = %s    \n",q,arr2[q]);
                      //printf("arr2[%d] = %s    \n",q+1,arr2[q+1]);
                      /*===============execvp arg===============*/

                      execvp(arr2[0],arr2);
                      perror("execvp");
                      exit(-1);
                    }
                    else if (pid > 0) { /* this is the parent process */
                            //printf("Wait for the child process to terminate\n");
                            wait(&status); /* wait for the child process to terminate */
                            if (WIFEXITED(status)) { /* child process terminated normally */
                                //printf("Child process exited with status = %d\n", WEXITSTATUS(status));
                            } 
                            else { /* child process did not terminate normally */
                                printf("Child process did not terminate normally!\n");
                                /* look at the man page for wait (man 2 wait) to determine
                                  how the child process was terminated */
                            }
                    } 
                    else { /* we have an error */
                            perror("fork"); /* use perror to print the system error message */
                            exit(EXIT_FAILURE);
                    }
                  //}
                }
                /*===============eflag===============*/
                else{
                  printf ("%s%s File size: %lld  perission : %lo Last access: %s\n",space, dirent->d_name, (long long)buf.st_size, (unsigned long) buf.st_mode, ctime(&buf.st_mtime));
                }
              }
            }
          }
          
          else if (tflag == 1){
            if(strcmp(cvalue,"f") == 0){
              if (strcmp(filetype(dirent->d_type),"regular file") == 0){
                /*===============eflag===============*/
                if (eflag == 1){
                  printf ("%s%s File size: %lld  perission : %lo Last access: %s\n",space, dirent->d_name, (long long)buf.st_size, (unsigned long) buf.st_mode, ctime(&buf.st_mtime));
                  //if (strcmp(filetype(dirent->d_type),"directory") == 0){
                    //printf("----%s---get youuuuu directory\n",dirent->d_name);
                    pid_t pid;
                    int status;
                    pid = fork();
                    if (pid == 0) {/* this is child process */
                      //printf("this is child process\n");

                      /*===============execvp arg===============*/
                      //printf("path === %s \n",path);
                      char wow[1000];
                      strcpy(wow,path);
                      arr2[q] = wow;
                      strcat(arr2[q],dirent->d_name);
                      //strcat(arr2[q],sub);
                      arr2[q+1] = NULL;
                      //printf("arr2[%d] = %s    \n",q,arr2[q]);
                      //printf("arr2[%d] = %s    \n",q+1,arr2[q+1]);
                      /*===============execvp arg===============*/

                      execvp(arr2[0],arr2);
                      perror("execvp");
                      exit(-1);
                    }
                    else if (pid > 0) { /* this is the parent process */
                            //printf("Wait for the child process to terminate\n");
                            wait(&status); /* wait for the child process to terminate */
                            if (WIFEXITED(status)) { /* child process terminated normally */
                                //printf("Child process exited with status = %d\n", WEXITSTATUS(status));
                            } 
                            else { /* child process did not terminate normally */
                                printf("Child process did not terminate normally!\n");
                                /* look at the man page for wait (man 2 wait) to determine
                                  how the child process was terminated */
                            }
                    } 
                    else { /* we have an error */
                            perror("fork"); /* use perror to print the system error message */
                            exit(EXIT_FAILURE);
                    }
                  //}
                }
                /*===============eflag===============*/
                else{
                  printf ("%s%s File size: %lld  perission : %lo Last access: %s\n",space, dirent->d_name, (long long)buf.st_size, (unsigned long) buf.st_mode, ctime(&buf.st_mtime));
                }
              }
            }   
            else if(strcmp(cvalue,"d") == 0){
              if (strcmp(filetype(dirent->d_type),"directory") == 0){
                /*===============eflag===============*/
                if (eflag == 1){
                  printf ("%s%s File size: %lld  perission : %lo Last access: %s\n",space, dirent->d_name, (long long)buf.st_size, (unsigned long) buf.st_mode, ctime(&buf.st_mtime));
                  //if (strcmp(filetype(dirent->d_type),"directory") == 0){
                    //printf("----%s---get youuuuu directory\n",dirent->d_name);
                    pid_t pid;
                    int status;
                    pid = fork();
                    if (pid == 0) {/* this is child process */
                      //printf("this is child process\n");

                      /*===============execvp arg===============*/
                      //printf("path === %s \n",path);
                      char wow[1000];
                      strcpy(wow,path);
                      arr2[q] = wow;
                      strcat(arr2[q],dirent->d_name);
                      //strcat(arr2[q],sub);
                      arr2[q+1] = NULL;
                      //printf("arr2[%d] = %s    \n",q,arr2[q]);
                      //printf("arr2[%d] = %s    \n",q+1,arr2[q+1]);
                      /*===============execvp arg===============*/

                      execvp(arr2[0],arr2);
                      perror("execvp");
                      exit(-1);
                    }
                    else if (pid > 0) { /* this is the parent process */
                            //printf("Wait for the child process to terminate\n");
                            wait(&status); /* wait for the child process to terminate */
                            if (WIFEXITED(status)) { /* child process terminated normally */
                                //printf("Child process exited with status = %d\n", WEXITSTATUS(status));
                            } 
                            else { /* child process did not terminate normally */
                                printf("Child process did not terminate normally!\n");
                                /* look at the man page for wait (man 2 wait) to determine
                                  how the child process was terminated */
                            }
                    } 
                    else { /* we have an error */
                            perror("fork"); /* use perror to print the system error message */
                            exit(EXIT_FAILURE);
                    }
                  //}
                }
                /*===============eflag===============*/
                else{
                  printf ("%s%s File size: %lld  perission : %lo Last access: %s\n",space, dirent->d_name, (long long)buf.st_size, (unsigned long) buf.st_mode, ctime(&buf.st_mtime));
                }
              }
            }
          }

          else{
            /*===============eflag===============*/
            if (eflag == 1){
              printf ("%s%s File size: %lld  perission : %lo Last access: %s\n",space, dirent->d_name, (long long)buf.st_size, (unsigned long) buf.st_mode, ctime(&buf.st_mtime));
              //if (strcmp(filetype(dirent->d_type),"directory") == 0){
                //printf("----%s---get youuuuu directory\n",dirent->d_name);
                pid_t pid;
                int status;
                pid = fork();
                if (pid == 0) {/* this is child process */
                  //printf("this is child process\n");

                  /*===============execvp arg===============*/
                  //printf("path === %s \n",path);
                  char wow[1000];
                  strcpy(wow,path);
                  arr2[q] = wow;
                  strcat(arr2[q],dirent->d_name);
                  //strcat(arr2[q],sub);
                  arr2[q+1] = NULL;
                  //printf("arr2[%d] = %s    \n",q,arr2[q]);
                  //printf("arr2[%d] = %s    \n",q+1,arr2[q+1]);
                  /*===============execvp arg===============*/

                  execvp(arr2[0],arr2);
                  perror("execvp");
                  exit(-1);
                }
                else if (pid > 0) { /* this is the parent process */
                        //printf("Wait for the child process to terminate\n");
                        wait(&status); /* wait for the child process to terminate */
                        if (WIFEXITED(status)) { /* child process terminated normally */
                            //printf("Child process exited with status = %d\n", WEXITSTATUS(status));
                        } 
                        else { /* child process did not terminate normally */
                            printf("Child process did not terminate normally!\n");
                            /* look at the man page for wait (man 2 wait) to determine
                              how the child process was terminated */
                        }
                } 
                else { /* we have an error */
                        perror("fork"); /* use perror to print the system error message */
                        exit(EXIT_FAILURE);
                }
              //}
            }
            /*===============eflag===============*/
            else{
              printf ("%s%s File size: %lld  perission : %lo Last access: %s\n",space, dirent->d_name, (long long)buf.st_size, (unsigned long) buf.st_mode, ctime(&buf.st_mtime));
            }
          }

        }



        else if (sflag == 1){
          if (buf.st_size <= sizeindex){
            if (fflag == 1){
              if(strstr(dirent->d_name,substring) != NULL && subcount <= layer){
                if (tflag == 1){
                  if(strcmp(cvalue,"f") == 0){
                    if (strcmp(filetype(dirent->d_type),"regular file") == 0){
                      /*===============Eflag arg===============*/
                      if (Eflag == 1){
                        //printf("path === %s \n",path);
                        strcpy(Ewow,path);
                        strcat(Ewow,dirent->d_name);
                      } 
                      /*===============Eflag arg===============*/

                      /*===============eflag===============*/
                      if (eflag == 1){
                        printf ("\n%s%s\n",space, dirent->d_name);
                        //if (strcmp(filetype(dirent->d_type),"directory") == 0){
                          //printf("----%s---get youuuuu directory\n",dirent->d_name);
                          pid_t pid;
                          int status;
                          pid = fork();
                          if (pid == 0) {/* this is child process */
                            //printf("this is child process\n");

                            /*===============execvp arg===============*/
                            //printf("path === %s \n",path);
                            char wow[1000];
                            strcpy(wow,path);
                            arr2[q] = wow;
                            strcat(arr2[q],dirent->d_name);
                            //strcat(arr2[q],sub);
                            arr2[q+1] = NULL;
                            //printf("arr2[%d] = %s    \n",q,arr2[q]);
                            //printf("arr2[%d] = %s    \n",q+1,arr2[q+1]);
                            /*===============execvp arg===============*/

                            execvp(arr2[0],arr2);
                            perror("execvp");
                            exit(-1);
                          }
                          else if (pid > 0) { /* this is the parent process */
                                  //printf("Wait for the child process to terminate\n");
                                  wait(&status); /* wait for the child process to terminate */
                                  if (WIFEXITED(status)) { /* child process terminated normally */
                                      //printf("Child process exited with status = %d\n", WEXITSTATUS(status));
                                  } 
                                  else { /* child process did not terminate normally */
                                      printf("Child process did not terminate normally!\n");
                                      /* look at the man page for wait (man 2 wait) to determine
                                        how the child process was terminated */
                                  }
                          } 
                          else { /* we have an error */
                                  perror("fork"); /* use perror to print the system error message */
                                  exit(EXIT_FAILURE);
                          }
                        //}
                      }
                      /*===============eflag===============*/
                      else{
                        printf ("%s%s \n",space, dirent->d_name);
                      }
                    }
                  }   
                  else if(strcmp(cvalue,"d") == 0){
                    if (strcmp(filetype(dirent->d_type),"directory") == 0){
                      /*===============Eflag arg===============*/
                      if (Eflag == 1){
                        //printf("path === %s \n",path);
                        strcpy(Ewow,path);
                        strcat(Ewow,dirent->d_name);
                      } 
                      /*===============Eflag arg===============*/

                      /*===============eflag===============*/
                      if (eflag == 1){
                        printf ("\n%s%s\n",space, dirent->d_name);
                        //if (strcmp(filetype(dirent->d_type),"directory") == 0){
                          //printf("----%s---get youuuuu directory\n",dirent->d_name);
                          pid_t pid;
                          int status;
                          pid = fork();
                          if (pid == 0) {/* this is child process */
                            //printf("this is child process\n");

                            /*===============execvp arg===============*/
                            //printf("path === %s \n",path);
                            char wow[1000];
                            strcpy(wow,path);
                            arr2[q] = wow;
                            strcat(arr2[q],dirent->d_name);
                            //strcat(arr2[q],sub);
                            arr2[q+1] = NULL;
                            //printf("arr2[%d] = %s    \n",q,arr2[q]);
                            //printf("arr2[%d] = %s    \n",q+1,arr2[q+1]);
                            /*===============execvp arg===============*/

                            execvp(arr2[0],arr2);
                            perror("execvp");
                            exit(-1);
                          }
                          else if (pid > 0) { /* this is the parent process */
                                  //printf("Wait for the child process to terminate\n");
                                  wait(&status); /* wait for the child process to terminate */
                                  if (WIFEXITED(status)) { /* child process terminated normally */
                                      //printf("Child process exited with status = %d\n", WEXITSTATUS(status));
                                  } 
                                  else { /* child process did not terminate normally */
                                      printf("Child process did not terminate normally!\n");
                                      /* look at the man page for wait (man 2 wait) to determine
                                        how the child process was terminated */
                                  }
                          } 
                          else { /* we have an error */
                                  perror("fork"); /* use perror to print the system error message */
                                  exit(EXIT_FAILURE);
                          }
                        //}
                      }
                      /*===============eflag===============*/
                      else{
                        printf ("%s%s \n",space, dirent->d_name);
                      }
                    }
                  }
                }
                else
                {
                  /*===============Eflag arg===============*/
                  if (Eflag == 1){
                    //printf("path === %s \n",path);
                    strcpy(Ewow,path);
                    strcat(Ewow,dirent->d_name);
                  } 
                  /*===============Eflag arg===============*/

                  /*===============eflag===============*/
                  if (eflag == 1){
                    printf ("\n%s%s\n",space, dirent->d_name);
                    //if (strcmp(filetype(dirent->d_type),"directory") == 0){
                      //printf("----%s---get youuuuu directory\n",dirent->d_name);
                      pid_t pid;
                      int status;
                      pid = fork();
                      if (pid == 0) {/* this is child process */
                        //printf("this is child process\n");

                        /*===============execvp arg===============*/
                        //printf("path === %s \n",path);
                        char wow[1000];
                        strcpy(wow,path);
                        arr2[q] = wow;
                        strcat(arr2[q],dirent->d_name);
                        //strcat(arr2[q],sub);
                        arr2[q+1] = NULL;
                        //printf("arr2[%d] = %s    \n",q,arr2[q]);
                        //printf("arr2[%d] = %s    \n",q+1,arr2[q+1]);
                        /*===============execvp arg===============*/

                        execvp(arr2[0],arr2);
                        perror("execvp");
                        exit(-1);
                      }
                      else if (pid > 0) { /* this is the parent process */
                              //printf("Wait for the child process to terminate\n");
                              wait(&status); /* wait for the child process to terminate */
                              if (WIFEXITED(status)) { /* child process terminated normally */
                                  //printf("Child process exited with status = %d\n", WEXITSTATUS(status));
                              } 
                              else { /* child process did not terminate normally */
                                  printf("Child process did not terminate normally!\n");
                                  /* look at the man page for wait (man 2 wait) to determine
                                    how the child process was terminated */
                              }
                      } 
                      else { /* we have an error */
                              perror("fork"); /* use perror to print the system error message */
                              exit(EXIT_FAILURE);
                      }
                    //}
                  }
                  /*===============eflag===============*/
                  else{
                    printf ("%s%s \n",space, dirent->d_name);
                  }
                }
              }
            }
            else if (tflag == 1){
              if(strcmp(cvalue,"f") == 0){
                if (strcmp(filetype(dirent->d_type),"regular file") == 0){
                    /*===============eflag===============*/
                    if (eflag == 1){
                      printf ("\n%s%s\n",space, dirent->d_name);
                      //if (strcmp(filetype(dirent->d_type),"directory") == 0){
                        //printf("----%s---get youuuuu directory\n",dirent->d_name);
                        pid_t pid;
                        int status;
                        pid = fork();
                        if (pid == 0) {/* this is child process */
                          //printf("this is child process\n");

                          /*===============execvp arg===============*/
                          //printf("path === %s \n",path);
                          char wow[1000];
                          strcpy(wow,path);
                          arr2[q] = wow;
                          strcat(arr2[q],dirent->d_name);
                          //strcat(arr2[q],sub);
                          arr2[q+1] = NULL;
                          //printf("arr2[%d] = %s    \n",q,arr2[q]);
                          //printf("arr2[%d] = %s    \n",q+1,arr2[q+1]);
                          /*===============execvp arg===============*/

                          execvp(arr2[0],arr2);
                          perror("execvp");
                          exit(-1);
                        }
                        else if (pid > 0) { /* this is the parent process */
                                //printf("Wait for the child process to terminate\n");
                                wait(&status); /* wait for the child process to terminate */
                                if (WIFEXITED(status)) { /* child process terminated normally */
                                    //printf("Child process exited with status = %d\n", WEXITSTATUS(status));
                                } 
                                else { /* child process did not terminate normally */
                                    printf("Child process did not terminate normally!\n");
                                    /* look at the man page for wait (man 2 wait) to determine
                                      how the child process was terminated */
                                }
                        } 
                        else { /* we have an error */
                                perror("fork"); /* use perror to print the system error message */
                                exit(EXIT_FAILURE);
                        }
                      //}
                    }
                    /*===============eflag===============*/
                  else{
                    printf ("%s%s \n",space, dirent->d_name);
                  }
                }
              }   
              else if(strcmp(cvalue,"d") == 0){
                if (strcmp(filetype(dirent->d_type),"directory") == 0){
                  /*===============eflag===============*/
                  if (eflag == 1){
                    printf ("\n%s%s\n",space, dirent->d_name);
                    //if (strcmp(filetype(dirent->d_type),"directory") == 0){
                      //printf("----%s---get youuuuu directory\n",dirent->d_name);
                      pid_t pid;
                      int status;
                      pid = fork();
                      if (pid == 0) {/* this is child process */
                        //printf("this is child process\n");

                        /*===============execvp arg===============*/
                        //printf("path === %s \n",path);
                        char wow[1000];
                        strcpy(wow,path);
                        arr2[q] = wow;
                        strcat(arr2[q],dirent->d_name);
                        //strcat(arr2[q],sub);
                        arr2[q+1] = NULL;
                        //printf("arr2[%d] = %s    \n",q,arr2[q]);
                        //printf("arr2[%d] = %s    \n",q+1,arr2[q+1]);
                        /*===============execvp arg===============*/

                        execvp(arr2[0],arr2);
                        perror("execvp");
                        exit(-1);
                      }
                      else if (pid > 0) { /* this is the parent process */
                              //printf("Wait for the child process to terminate\n");
                              wait(&status); /* wait for the child process to terminate */
                              if (WIFEXITED(status)) { /* child process terminated normally */
                                  //printf("Child process exited with status = %d\n", WEXITSTATUS(status));
                              } 
                              else { /* child process did not terminate normally */
                                  printf("Child process did not terminate normally!\n");
                                  /* look at the man page for wait (man 2 wait) to determine
                                    how the child process was terminated */
                              }
                      } 
                      else { /* we have an error */
                              perror("fork"); /* use perror to print the system error message */
                              exit(EXIT_FAILURE);
                      }
                    //}
                  }
                  /*===============eflag===============*/
                  else{
                    printf ("%s%s \n",space, dirent->d_name);
                  }
                }
              }
            }
            else{
              /*===============eflag===============*/
              if (eflag == 1){
                printf ("\n%s%s\n",space, dirent->d_name);
                //if (strcmp(filetype(dirent->d_type),"directory") == 0){
                  //printf("----%s---get youuuuu directory\n",dirent->d_name);
                  pid_t pid;
                  int status;
                  pid = fork();
                  if (pid == 0) {/* this is child process */
                    //printf("this is child process\n");

                    /*===============execvp arg===============*/
                    //printf("path === %s \n",path);
                    char wow[1000];
                    strcpy(wow,path);
                    arr2[q] = wow;
                    strcat(arr2[q],dirent->d_name);
                    //strcat(arr2[q],sub);
                    arr2[q+1] = NULL;
                    //printf("arr2[%d] = %s    \n",q,arr2[q]);
                    //printf("arr2[%d] = %s    \n",q+1,arr2[q+1]);
                    /*===============execvp arg===============*/

                    execvp(arr2[0],arr2);
                    perror("execvp");
                    exit(-1);
                  }
                  else if (pid > 0) { /* this is the parent process */
                          //printf("Wait for the child process to terminate\n");
                          wait(&status); /* wait for the child process to terminate */
                          if (WIFEXITED(status)) { /* child process terminated normally */
                              //printf("Child process exited with status = %d\n", WEXITSTATUS(status));
                          } 
                          else { /* child process did not terminate normally */
                              printf("Child process did not terminate normally!\n");
                              /* look at the man page for wait (man 2 wait) to determine
                                how the child process was terminated */
                          }
                  } 
                  else { /* we have an error */
                          perror("fork"); /* use perror to print the system error message */
                          exit(EXIT_FAILURE);
                  }
                //}
              }
              /*===============eflag===============*/
              else{              
                printf ("%s%s \n",space, dirent->d_name);
              }
            }
          }
        }
              

              
        else if (fflag == 1){
          if(strstr(dirent->d_name,substring) != NULL && subcount <= layer){
            if (tflag == 1){
              if(strcmp(cvalue,"f") == 0){
                if (strcmp(filetype(dirent->d_type),"regular file") == 0){
                  /*===============Eflag arg===============*/
                  if (Eflag == 1){
                    //printf("path === %s \n",path);
                    strcpy(Ewow,path);
                    strcat(Ewow,dirent->d_name);
                  } 
                  /*===============Eflag arg===============*/

                  /*===============eflag===============*/
                  if (eflag == 1){
                    printf ("\n%s%s\n",space, dirent->d_name);
                    //if (strcmp(filetype(dirent->d_type),"directory") == 0){
                      //printf("----%s---get youuuuu directory\n",dirent->d_name);
                      pid_t pid;
                      int status;
                      pid = fork();
                      if (pid == 0) {/* this is child process */
                        //printf("this is child process\n");

                        /*===============execvp arg===============*/
                        //printf("path === %s \n",path);
                        char wow[1000];
                        strcpy(wow,path);
                        arr2[q] = wow;
                        strcat(arr2[q],dirent->d_name);
                        //strcat(arr2[q],sub);
                        arr2[q+1] = NULL;
                        //printf("arr2[%d] = %s    \n",q,arr2[q]);
                        //printf("arr2[%d] = %s    \n",q+1,arr2[q+1]);
                        /*===============execvp arg===============*/

                        execvp(arr2[0],arr2);
                        perror("execvp");
                        exit(-1);
                      }
                      else if (pid > 0) { /* this is the parent process */
                              //printf("Wait for the child process to terminate\n");
                              wait(&status); /* wait for the child process to terminate */
                              if (WIFEXITED(status)) { /* child process terminated normally */
                                  //printf("Child process exited with status = %d\n", WEXITSTATUS(status));
                              } 
                              else { /* child process did not terminate normally */
                                  printf("Child process did not terminate normally!\n");
                                  /* look at the man page for wait (man 2 wait) to determine
                                    how the child process was terminated */
                              }
                      } 
                      else { /* we have an error */
                              perror("fork"); /* use perror to print the system error message */
                              exit(EXIT_FAILURE);
                      }
                    //}
                  }
                  /*===============eflag===============*/

                  else{
                  printf ("%s%s \n",space, dirent->d_name);
                  }
                }
              }   
              else if(strcmp(cvalue,"d") == 0){
                if (strcmp(filetype(dirent->d_type),"directory") == 0){
                  /*===============Eflag arg===============*/
                  if (Eflag == 1){
                    //printf("path === %s \n",path);
                    strcpy(Ewow,path);
                    strcat(Ewow,dirent->d_name);
                  } 
                  /*===============Eflag arg===============*/

                  /*===============eflag===============*/
                  if (eflag == 1){
                    printf ("\n%s%s\n",space, dirent->d_name);
                    //if (strcmp(filetype(dirent->d_type),"directory") == 0){
                      //printf("----%s---get youuuuu directory\n",dirent->d_name);
                      pid_t pid;
                      int status;
                      pid = fork();
                      if (pid == 0) {/* this is child process */
                        //printf("this is child process\n");

                        /*===============execvp arg===============*/
                        //printf("path === %s \n",path);
                        char wow[1000];
                        strcpy(wow,path);
                        arr2[q] = wow;
                        strcat(arr2[q],dirent->d_name);
                        //strcat(arr2[q],sub);
                        arr2[q+1] = NULL;
                        //printf("arr2[%d] = %s    \n",q,arr2[q]);
                        //printf("arr2[%d] = %s    \n",q+1,arr2[q+1]);
                        /*===============execvp arg===============*/

                        execvp(arr2[0],arr2);
                        perror("execvp");
                        exit(-1);
                      }
                      else if (pid > 0) { /* this is the parent process */
                              //printf("Wait for the child process to terminate\n");
                              wait(&status); /* wait for the child process to terminate */
                              if (WIFEXITED(status)) { /* child process terminated normally */
                                  //printf("Child process exited with status = %d\n", WEXITSTATUS(status));
                              } 
                              else { /* child process did not terminate normally */
                                  printf("Child process did not terminate normally!\n");
                                  /* look at the man page for wait (man 2 wait) to determine
                                    how the child process was terminated */
                              }
                      } 
                      else { /* we have an error */
                              perror("fork"); /* use perror to print the system error message */
                              exit(EXIT_FAILURE);
                      }
                    //}
                  }
                  /*===============eflag===============*/
                  else{
                  printf ("%s%s \n",space, dirent->d_name);
                  }
                }
              }
            }
            else{
              /*===============Eflag arg===============*/
                if (Eflag == 1){
                  //printf("path === %s \n",path);
                  strcpy(Ewow,path);
                  strcat(Ewow,dirent->d_name);
                } 
              /*===============Eflag arg===============*/

              /*===============eflag===============*/
              if (eflag == 1){
                printf ("\n%s%s\n",space, dirent->d_name);
                //if (strcmp(filetype(dirent->d_type),"directory") == 0){
                  //printf("----%s---get youuuuu directory\n",dirent->d_name);
                  pid_t pid;
                  int status;
                  pid = fork();
                  if (pid == 0) {/* this is child process */
                    //printf("this is child process\n");

                    /*===============execvp arg===============*/
                    //printf("path === %s \n",path);
                    char wow[1000];
                    strcpy(wow,path);
                    arr2[q] = wow;
                    strcat(arr2[q],dirent->d_name);
                    //strcat(arr2[q],sub);
                    arr2[q+1] = NULL;
                    //printf("arr2[%d] = %s    \n",q,arr2[q]);
                    //printf("arr2[%d] = %s    \n",q+1,arr2[q+1]);
                    /*===============execvp arg===============*/

                    execvp(arr2[0],arr2);
                    perror("execvp");
                    exit(-1);
                  }
                  else if (pid > 0) { /* this is the parent process */
                          //printf("Wait for the child process to terminate\n");
                          wait(&status); /* wait for the child process to terminate */
                          if (WIFEXITED(status)) { /* child process terminated normally */
                              //printf("Child process exited with status = %d\n", WEXITSTATUS(status));
                          } 
                          else { /* child process did not terminate normally */
                              printf("Child process did not terminate normally!\n");
                              /* look at the man page for wait (man 2 wait) to determine
                                how the child process was terminated */
                          }
                  } 
                  else { /* we have an error */
                          perror("fork"); /* use perror to print the system error message */
                          exit(EXIT_FAILURE);
                  }
                //}
              }
              /*===============eflag===============*/
              else{
                printf ("%s%s \n",space, dirent->d_name);
              }
            }
          }
        }
            


        else if (tflag == 1){
          if(strcmp(cvalue,"f") == 0){
            if (strcmp(filetype(dirent->d_type),"regular file") == 0){
              /*===============eflag===============*/
              if (eflag == 1){
                printf ("\n%s%s\n",space, dirent->d_name);
                //if (strcmp(filetype(dirent->d_type),"directory") == 0){
                  //printf("----%s---get youuuuu directory\n",dirent->d_name);
                  pid_t pid;
                  int status;
                  pid = fork();
                  if (pid == 0) {/* this is child process */
                    //printf("this is child process\n");

                    /*===============execvp arg===============*/
                    //printf("path === %s \n",path);
                    char wow[1000];
                    strcpy(wow,path);
                    arr2[q] = wow;
                    strcat(arr2[q],dirent->d_name);
                    //strcat(arr2[q],sub);
                    arr2[q+1] = NULL;
                    //printf("arr2[%d] = %s    \n",q,arr2[q]);
                    //printf("arr2[%d] = %s    \n",q+1,arr2[q+1]);
                    /*===============execvp arg===============*/

                    execvp(arr2[0],arr2);
                    perror("execvp");
                    exit(-1);
                  }
                  else if (pid > 0) { /* this is the parent process */
                          //printf("Wait for the child process to terminate\n");
                          wait(&status); /* wait for the child process to terminate */
                          if (WIFEXITED(status)) { /* child process terminated normally */
                              //printf("Child process exited with status = %d\n", WEXITSTATUS(status));
                          } 
                          else { /* child process did not terminate normally */
                              printf("Child process did not terminate normally!\n");
                              /* look at the man page for wait (man 2 wait) to determine
                                how the child process was terminated */
                          }
                  } 
                  else { /* we have an error */
                          perror("fork"); /* use perror to print the system error message */
                          exit(EXIT_FAILURE);
                  }
                //}
              }
              /*===============eflag===============*/
              else{
              printf ("%s%s  \n",space, dirent->d_name);
              }
            }
          }
          else if(strcmp(cvalue,"d") == 0){
            if (strcmp(filetype(dirent->d_type),"directory") == 0){
              /*===============eflag===============*/
              if (eflag == 1){
                printf ("\n%s%s\n",space, dirent->d_name);
                //if (strcmp(filetype(dirent->d_type),"directory") == 0){
                  //printf("----%s---get youuuuu directory\n",dirent->d_name);
                  pid_t pid;
                  int status;
                  pid = fork();
                  if (pid == 0) {/* this is child process */
                    //printf("this is child process\n");

                    /*===============execvp arg===============*/
                    //printf("path === %s \n",path);
                    char wow[1000];
                    strcpy(wow,path);
                    arr2[q] = wow;
                    strcat(arr2[q],dirent->d_name);
                    //strcat(arr2[q],sub);
                    arr2[q+1] = NULL;
                    //printf("arr2[%d] = %s    \n",q,arr2[q]);
                    //printf("arr2[%d] = %s    \n",q+1,arr2[q+1]);
                    /*===============execvp arg===============*/

                    execvp(arr2[0],arr2);
                    perror("execvp");
                    exit(-1);
                  }
                  else if (pid > 0) { /* this is the parent process */
                          //printf("Wait for the child process to terminate\n");
                          wait(&status); /* wait for the child process to terminate */
                          if (WIFEXITED(status)) { /* child process terminated normally */
                              //printf("Child process exited with status = %d\n", WEXITSTATUS(status));
                          } 
                          else { /* child process did not terminate normally */
                              printf("Child process did not terminate normally!\n");
                              /* look at the man page for wait (man 2 wait) to determine
                                how the child process was terminated */
                          }
                  } 
                  else { /* we have an error */
                          perror("fork"); /* use perror to print the system error message */
                          exit(EXIT_FAILURE);
                  }
                //}
              }
              /*===============eflag===============*/
              else{
              printf ("%s%s \n",space, dirent->d_name);
              }
            }
          }
        }


        /*===============eflag===============*/
        else if (eflag == 1){
          printf ("\n%s%s\n",space, dirent->d_name);
          //if (strcmp(filetype(dirent->d_type),"directory") == 0){
            //printf("----%s---get youuuuu directory\n",dirent->d_name);
            pid_t pid;
            int status;
            pid = fork();
            if (pid == 0) {/* this is child process */
              //printf("this is child process\n");

              /*===============execvp arg===============*/
              //printf("path === %s \n",path);
              char wow[1000];
              strcpy(wow,path);
              arr2[q] = wow;
              strcat(arr2[q],dirent->d_name);
              //strcat(arr2[q],sub);
              arr2[q+1] = NULL;
              //printf("arr2[%d] = %s    \n",q,arr2[q]);
              //printf("arr2[%d] = %s    \n",q+1,arr2[q+1]);
              /*===============execvp arg===============*/

              execvp(arr2[0],arr2);
              perror("execvp");
              exit(-1);
            }
            else if (pid > 0) { /* this is the parent process */
                    //printf("Wait for the child process to terminate\n");
                    wait(&status); /* wait for the child process to terminate */
                    if (WIFEXITED(status)) { /* child process terminated normally */
                        //printf("Child process exited with status = %d\n", WEXITSTATUS(status));
                    } 
                    else { /* child process did not terminate normally */
                        printf("Child process did not terminate normally!\n");
                        /* look at the man page for wait (man 2 wait) to determine
                          how the child process was terminated */
                    }
            } 
            else { /* we have an error */
                    perror("fork"); /* use perror to print the system error message */
                    exit(EXIT_FAILURE);
            }
          //}
        }
        /*===============eflag===============*/
        else
        {
          //printf("defalt\n");
          printf ("%s%s\n",space, dirent->d_name);
        }
        

        if(filetype(dirent->d_type) == "directory"){
          strcpy(prepath,subpath);
	        //printf("prePATH == %s\n",prepath);
          //strcat(subpath,sub);
          strcat(subpath,dirent->d_name);
          strcat(subpath,sub);
          //printf("subpath %s\n", subpath);
          subcount++;
          opfunc(subpath,findDir);
          strcpy(subpath,prepath);
          //printf("S-- subpath %s\n", subpath);

        }
      }
      
    }
    

  subcount--;
  closedir (parentDir);
/*===============Eflag===============*/
  if (strstr(Ewow,"./")){
    /* code */
    //printf("Ewow = %s\n",Ewow);
    strcpy(UseForE[UseForEnum],Ewow);
    UseForEnum++;
  }
/*===============Eflag===============*/
}

int opfunc(char path[], MYFUNC *f) {
        //printf("-----%s",path);
        return findDir(path);
}

int main (int argc, char **argv)
{
  int c;


  opterr = 0;


  while ((c = getopt (argc, argv, "Ss:f:t:E:e:")) != -1)
    switch (c)
      {
      case 'S':
        Sflag = 1;
        break;
        break;
      case 's':
        sflag = 1;
        strIndex = optarg;
        sizeindex = atoi(strIndex);
        break;
      case 'f':
        fflag = 1;
        Inputsubstring = optarg;
        //printf("%s\n",Inputsubstring);
        substring = strtok(Inputsubstring," ");
        strlayer = strtok(NULL, " ");
        layer = atoi(strlayer);
        break;
      case 't':
        tflag = 1;
        cvalue = optarg;
        break;
      case 'E':
        Eflag = 1;
        EIndex = optarg;
        break;
      case 'e':
        eflag = 1;
        eIndex = optarg;
        break;
      case '?':
        if (optopt == 't')
          printf ("Option -%c requires an argument.\n", optopt);
        else if (optopt == 'E')
          printf ("Option -%c requires an argument.\n", optopt);
        else if (optopt == 'e')
          printf ("Option -%c requires an argument.\n", optopt);
        else
          printf ("Unknown option character `\\x%x'.\n",optopt);
        return 1;
      default:
        abort ();
      }

  //printf ("Sflag = %d, sflag = %d sizeindex = %d,  fflag = %d layer = %d, tflag = %d FotTcvalue = %s, Eflag = %d EIndex = %s, eflag = %d eIndex = %s\n\n",Sflag, sflag, sizeindex, fflag, layer, tflag, cvalue, Eflag, EIndex, eflag, eIndex);

   
  if (argv[optind] != NULL){
    strcat(subpath,argv[optind]);
  }
  
  //strcat(subpath,sub);
  //strcpy(prepath,subpath);
  //printf("%s\n",subpath);
  
  int x = 1;
  char tokenchar[100];
  eInput =(char **) malloc(10 * sizeof(char **));
  if (eIndex != NULL){
    char* token = strtok(eIndex," ");
    //printf("token 0 = %s\n",token);
    strcpy(tokenchar,token);
    eInput[0] = (char *) malloc(100 * sizeof(char));
    strcpy(eInput[0],tokenchar);
    //printf("eInput %s\n",eInput[0]);
    token = strtok(NULL," ");
    
    while (token != NULL){
      //printf("token %d = %s\n",x,token);
      strcpy(tokenchar,token);
      eInput[x] = (char *) malloc(100 * sizeof(char));
      //printf("tokenchar %s\n",tokenchar);
      strcpy(eInput[x],tokenchar);
      x++;
      eInput[x] = NULL;
      token = strtok(NULL," ");
    }
    x++;
    //printf("X == %d\n",x);
    
    
    int y = 0;
    while (eInput[y] != NULL)
    {
      arr[y] = eInput[y];
      //printf("arr %d = %s\n",y,arr[y]);
      y++;
      arr[y] = NULL;
      //printf("arr %d = %s\n",y,arr[y]);
    }
    
  }


  int j = 1;
  char Etokenchar[100];
  EInput =(char **) malloc(10 * sizeof(char **));
  if (EIndex != NULL){
    char* token = strtok(EIndex," ");
    //printf("token 0 = %s\n",token);
    strcpy(Etokenchar,token);
    EInput[0] = (char *) malloc(100 * sizeof(char));
    strcpy(EInput[0],Etokenchar);
    //printf("EInput %s\n",EInput[0]);
    token = strtok(NULL," ");
    
    while (token != NULL){
      //printf("token %d = %s\n",x,token);
      strcpy(Etokenchar,token);
      EInput[j] = (char *) malloc(100 * sizeof(char));
      //printf("Etokenchar %s\n",Etokenchar);
      strcpy(EInput[j],Etokenchar);
      j++;
      EInput[j] = NULL;
      token = strtok(NULL," ");
    }
    j++;
    //printf("j == %d\n",j);
    
    
    int y = 0;
    while (EInput[y] != NULL)
    {
      Eflaguse[y] = EInput[y];
      //printf("EInput %d = %s\n",y,EInput[y]);
      y++;
      Eflaguse[y] = NULL;
      //printf("Eflaguse %d = %s\n",y,Eflaguse[y]);
    }
    
  }
  

  opfunc(subpath,findDir);


  /*===============Eflag===============*/
  int l = 0;
  while (strstr(UseForE[l],"./") != NULL){
    /* code */
    Eflaguse[EflagNum] = UseForE[l];
    //printf("Eflaguse[%d] = %s\n",l,Eflaguse[l+3]);
    //printf("UseForE[%d] = %s\n",l,UseForE[l]);
    l++;
    EflagNum++;
  }

  if (Eflag == 1){
    if (Eflaguse[3] != NULL){
        //printf("-------get youuuuu directory\n");
        pid_t pid;
        int status;
        pid = fork();
        if (pid == 0) {/* this is child process */
          //printf("this is child process\n");
          execvp(Eflaguse[0],Eflaguse);
          perror("execvp");
          exit(-1);
        }
        else if (pid > 0) { /* this is the parent process */
                //printf("Wait for the child process to terminate\n");
                wait(&status); /* wait for the child process to terminate */
                if (WIFEXITED(status)) { /* child process terminated normally */
                    //printf("Child process exited with status = %d\n", WEXITSTATUS(status));
                } 
                else { /* child process did not terminate normally */
                    printf("Child process did not terminate normally!\n");
                    /* look at the man page for wait (man 2 wait) to determine
                      how the child process was terminated */
                }
        } 
        else { /* we have an error */
                perror("fork"); /* use perror to print the system error message */
                exit(EXIT_FAILURE);
        }
    }
  }
  /*===============Eflag===============*/

  free(eInput);
  return 0;
}

