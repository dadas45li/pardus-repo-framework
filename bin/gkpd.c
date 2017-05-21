#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int dosya_cek(char *dir);
int write_control(char *name);
int make_control(char *line);
int package_file(char *name);
int copydeb(char *name);
char name[1000];
char version[50];
char arch[50];
int main(int argc, char *argv[]){
  strcpy(name,argv[1]);
  char dir[50]="/var/lib/dpkg/info/";
  strcat(dir,argv[1]);
  strcat(dir,".list");
  //open file for reading
  printf("Remove old workspace\n");
  system("rm -rf ~/.repack/ ");
  //new workspace
  printf("create new workspace\n");
  system("mkdir ~/.repack/"); 
  system("mkdir ~/.repack/DEBIAN ");
  //copy files
  int i = dosya_cek(dir);
  printf("Copy %d files\n",i);
  //create control file
  i = write_control(argv[1]);
  printf("Find %d lines\n",i);
  //copy package files
  i = package_file(argv[1]);
  printf("Copy package files\n");
  //make deb package
  printf("Make deb package: %s_%s_%s.deb\n",name,version,arch);
  system("dpkg -b ~/.repack/ 2> /dev/null | cat > /dev/null");
  printf("Move package file\n");
  i = copydeb(argv[1]);
  printf("Finish\n");
  return i;
 
}
int dosya_cek(char *dir){
   char b[50000];
   FILE *file1;
   file1 = fopen(dir,"r");
   int i = 0;
   while (fgets(b,50000,file1) != NULL )
   {
     b[strlen(b)-1] = 0;
     // cp -pvf 
     char kom1[1100]="";
     strcpy(kom1,"cp -pf ");
     strcat(kom1,b);
     strcat(kom1," ~/.repack");
     strcat(kom1,b);
     strcat(kom1," 2> /dev/null");
     char kom2[1100]="";
     int status = 1;
     char *bolu = "/";
     while (b[strlen(b)-1] != bolu[0]){
         b[strlen(b)-1]=0;
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
    if (strstr(c,stop) != NULL)
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
    char tmp[50000];
    if (strstr(line,"Architecture:") != NULL){
        for(int i=14;i!=strlen(line)-1;i++){
            arch[i-14]=line[i];
        }
    }
    if (strstr(line,"Version:") != NULL){
        for(int i=9;i!=strlen(line)-1;i++){
            version[i-9]=line[i];
        }
    }
    if (strstr(line,"Status:") == NULL){
        char bash[50000]="echo \"";
        line[strlen(line)-1]=0;
        strcat(bash,line);
        strcat(bash,"\" >> ~/.repack/DEBIAN/control");
        system(bash);
    }
}
int package_file(char *name){
    char bash[100]="cp -prf /var/lib/dpkg/info/";
    strcat(bash,name);
    strcat(bash,".* ~/.repack/DEBIAN/");
    system(bash);
    system("rm -f ~/.repack/DEBIAN/*.list 2> /dev/null");
    system("rm -f ~/.repack/DEBIAN/*.md5sums 2> /dev/null");
    system("rm -f ~/.repack/DEBIAN/status 2> /dev/null");
    system("mv ~/.repack/DEBIAN/*.postinst ~/.repack/DEBIAN/postinst 2> /dev/null");
    system("mv ~/.repack/DEBIAN/*.postrm ~/.repack/DEBIAN/postrm 2> /dev/null");
    system("mv ~/.repack/DEBIAN/*.prerm ~/.repack/DEBIAN/prerm 2> /dev/null");
    system("mv ~/.repack/DEBIAN/*.preinst ~/.repack/DEBIAN/preinst 2> /dev/null");
    system("mv ~/.repack/DEBIAN/*.conffiles ~/.repack/DEBIAN/conffiles 2> /dev/null");
    system("mv ~/.repack/DEBIAN/*.shlibs ~/.repack/DEBIAN/shlibs 2> /dev/null");
    system("mv ~/.repack/DEBIAN/*.symbols ~/.repack/DEBIAN/symbols 2> /dev/null");
    system("mv ~/.repack/DEBIAN/*.templates ~/.repack/DEBIAN/templates 2> /dev/null");
    system("mv ~/.repack/DEBIAN/*.config ~/.repack/DEBIAN/config 2> /dev/null");
    system("mv ~/.repack/DEBIAN/*.triggers ~/.repack/DEBIAN/triggers 2> /dev/null");
    return 0;
}
int copydeb(char *name){
 
    char bash[500] = "mv -f ~/.repack.deb $(pwd)/";
    strcat(bash,name);
    strcat(bash,"_");
    strcat(bash,version);
    strcat(bash,"_");
    strcat(bash,arch);
    strcat(bash,".deb");
    return system(bash);   
}
