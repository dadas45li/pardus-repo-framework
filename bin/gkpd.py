#!/usr/bin/python
import os
import sys
	
file1= open("/var/lib/dpkg/info/" + sys.argv[1] + ".list")
os.system("mkdir ~/.repack/")
os.system("rm -rf ~/.repack/*")

def dosya_cek():
  data = "\n"
  while "\n" in data:
    data = file1.readline()
    j=1
    data2 = data.split("\n")
    data3 = data2[0]
    data4=data3.split("/")
    data5=""
    while j < len(data4) -1:
      data5=data5+"/"+data4[j]
      j=j+1
    
    os.system("mkdir -p ~/.repack" + data5) 
    if data3 != "":
	os.system("cp -vf " + data3 + " ~/.repack" + data3)
dosya_cek()      
os.system("mkdir ~/.repack/DEBIAN")
os.system("cp -f /var/lib/dpkg/info/" + sys.argv[1] +".* ~/.repack/DEBIAN")
os.system("cp /var/lib/dpkg/status ~/.repack/DEBIAN/status")
os.system('echo "--veri--" >> ~/.repack/DEBIAN/status')
file2= open(os.environ["HOME"]+"/.repack/DEBIAN/status")
veri = ""
arch=""
ver=""
veri = file2.readline()
while  "--veri--" not in veri:
  veri = file2.readline()
  if ("Package: " + sys.argv[1]) in veri:
    veri = veri.split("\n")
    os.system("echo "+ veri[0] + " > ~/.repack/DEBIAN/control" )
    veri = file2.readline()
    while "Package: " not in veri:
      veri = veri.split("\n")
      if "Status: " in veri[0]:
	print ""
      else:
	os.system('echo "'+ veri[0] + '" >> ~/.repack/DEBIAN/control' )
      if "Architecture:" in veri[0]:
	arch = veri[0].split(": ")[1]
      if "Version:" in veri[0]:
	ver = veri[0].split(": ")[1]
      veri = file2.readline()
    
os.system("rm -f ~/.repack/DEBIAN/*.list")
os.system("rm -f ~/.repack/DEBIAN/*.md5sums")
os.system("rm -f ~/.repack/DEBIAN/status")
os.system("mv ~/.repack/DEBIAN/*.postinst ~/.repack/DEBIAN/postinst")
os.system("mv ~/.repack/DEBIAN/*.postrm ~/.repack/DEBIAN/postrm")
os.system("mv ~/.repack/DEBIAN/*.prerm ~/.repack/DEBIAN/prerm")
os.system("mv ~/.repack/DEBIAN/*.preinst ~/.repack/DEBIAN/preinst")
os.system("mv ~/.repack/DEBIAN/*.conffiles ~/.repack/DEBIAN/conffiles")
os.system("mv ~/.repack/DEBIAN/*.shlibs ~/.repack/DEBIAN/shlibs")
os.system("mv ~/.repack/DEBIAN/*.symbols ~/.repack/DEBIAN/symbols")
os.system("mv ~/.repack/DEBIAN/*.templates ~/.repack/DEBIAN/templates")
os.system("mv ~/.repack/DEBIAN/*.config ~/.repack/DEBIAN/config")
os.system("mv ~/.repack/DEBIAN/*.triggers ~/.repack/DEBIAN/triggers")
#Baska varsa belirtin...
os.system("dpkg -b ~/.repack/")
os.system("mv  ~/.repack.deb ./"+ sys.argv[1]+"_"+ver+"_"+arch+".deb")
os.system("rm -rf ~/.repack/")
