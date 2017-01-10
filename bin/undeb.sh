#!/bin/bash
dizin=$(pwd)
if [ "$1" == "-t" ]
then
cd $2
dpkg -b $(pwd)
else
rm -rf ~/.undeb/ 
mkdir ~/.undeb/
cp -prf $1 ~/.undeb/
cd ~/.undeb/
ar -x ~/.undeb/*.deb
rm -rf ~/.undeb/*.deb
rm -rf ~/.undeb/debian-binary
mkdir ~/.undeb/DEBIAN
mv ~/.undeb/control.tar.* ~/.undeb/DEBIAN/
cd ~/.undeb/DEBIAN/
tar -xf ./control.tar.*
rm -rf ./control.tar.*
cd ../
tar -xf ./data.tar.*
rm -rf ./data.tar.*
mv ~/.undeb/ $dizin
mv $dizin/.undeb/ $dizin/$2
fi
