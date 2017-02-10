#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int dosya_cek(char *dir);
int write_control(char *name);
int make_control(char *line);
int main(int argc, char *argv[]){
  char dir[50]="/var/lib/dpkg/info/";
  strcat(dir,argv[1]);
  strcat(dir,".list");
  //open file for reading
  system("rm -rf ~/.repack/");
  //new workspace
  system("mkdir ~/.repack/"); 
  system("mkdir ~/.repack/DEBIAN");
  //copy files
  int i = dosya_cek(dir);
  printf("Copied %d files\n",i);
  //create control file
  i = write_control(argv[1]);
  printf("Find %d lines\n",i);
  return 0;
 
}
int dosya_cek(char *dir){
   char b[50000];
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

int write_control(char *name){
   FILE *file2;
   file2 = fopen("/var/lib/dpkg/status","r");
   char c[50000];
   int d=0;
   char start[50000]="Package: "; 
   char stop[9] = "Package: ";
   strcat(start,name);
   strcat(start,"\n");
   int status = 0;
   char *a;
   while (status==0)
   {
       int j=0;
       for (j=0;j<strlen(start)+1;j++){
           if (c[j] == start[j]){
               status = 1;
        }
           else{
               status = 0;
               a= fgets(c,50000,file2);
               break;
        }
    }
}
status = 0;
while (status==0){
    d++;
    make_control(c);
    a=fgets(c,50000,file2);
    if (c[0] == stop[0]& c[1] == stop[1]& c[2] == stop[2]& c[3] == stop[3]& c[4] == stop[4]& c[5] == stop[5]& c[6] == stop[6]& c[7] == stop[7])
    {
      status = 1;
    }
    else{
      status = 0;
    }    
}
   return d;
}
int make_control(char *line){
    char data[50000];
    char block[]="Status:";
    if (line[0] == block[0]& line[1] == block[1]& line[2] == block[2]& line[3] == block[3]& line[4] == block[4]& line[5] == block[5]& line[6] == block[6]){
        printf("%s\n",line);
    }
    else{
        char bash[50000]="echo \"";
        line[strlen(line)-1]=0;
        strcat(bash,line);
        strcat(bash,"\" >> ~/.repack/DEBIAN/control");
        system(bash);
    }
}
