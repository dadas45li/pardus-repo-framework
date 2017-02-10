#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int dosya_cek(char *dir);
int main(int argc, char *argv[]){
  char dir[50]="/var/lib/dpkg/info/";
  strcat(dir,argv[1]);
  strcat(dir,".list");
  //open file for reading
  system("rm -rf ~/.repack/");
  system("mkdir ~/.repack/"); 
  //workspace cleared  
  int i = dosya_cek(dir);
  printf("Copied %d files\n",i);
  return 0;
 
}
int dosya_cek(char *dir){
   char b[500];
   FILE *file1;
   file1 = fopen(dir,"r");
   int i = 0;
   while (fscanf(file1,"%s",b) == 1 )
   {
     // cp -pvf 
     char kom1[1100]="";
     strcpy(kom1,"cp -pf ");
     strcat(kom1,b);
     strcat(kom1,"  ~/.repack");
     strcat(kom1,b);
     strcat(kom1," 2> /dev/null");
     char kom2[1100]="";
     int status = 1;
     char *bolu = "/";
     while (status == 1){
       if (b[strlen(b)-1] != bolu[0]) {
         b[strlen(b)-1]=0;
       }
       else{
         break;
       }
     }
     strcpy(kom2,"mkdir -p");
     strcat(kom2," ~/.repack");
     strcat(kom2,b);
     int exec = 0;
     exec = system(kom2);
     exec = system(kom1);
     i++;
   }
   return i;
}
