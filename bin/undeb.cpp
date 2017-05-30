#include <stdlib.h>
#include <string.h>
using namespace std;
int build(char *sec){
    char code[105];
    strcpy(code,"cd ");
    strcat(code,sec);
    strcat(code," ; dpkg -b $(pwd)");
    int i = system(code);
    return i;
}
int unpack(char *prim,char *sec){
    char code[500];
    int i = system("rm -rf ~/.undeb/ ; mkdir ~/.undeb/");
    strcpy(code,"cp -prf ");
    strcat(code,prim);
    strcat(code," ~/.undeb");
    i = system(code);
    strcpy(code," cd ~/.undeb ; ar -x ~/.undeb/*deb ; rm -rf ~/.undeb/debian-binary ; rm -rf ~/.undeb/*.deb ; mkdir ~/.undeb/DEBIAN ; mv ~/.undeb/control.tar.* ~/.undeb/DEBIAN ; cd ~/.undeb/DEBIAN ; tar -xf ./control.tar.* ; rm -rf ./control.tar.* ; cd ../ ; tar -xf ./data.tar.* ; rm -rf ./data.tar.* ");
    i = system(code);
    strcpy(code,"mkdir $(pwd)/");
    strcat(code,sec);
    strcat(code,"/ ; mv  ~/.undeb/* $(pwd)/");
    strcat(code,sec);
    strcat(code,"/");
    i= system(code);
    return i;
}

int main(int argc, char *argv[]){
    int i = 0;
    char prim[100];
    char sec[100];
    strcpy(prim,argv[1]);
    strcpy(sec,argv[2]);
    if (strstr(argv[1],"-t"))
    {
        i = build(sec);
    }
    else
    {
        i = unpack(prim,sec);
    }
    return i;
}

