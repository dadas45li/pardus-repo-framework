#!/usr/bin/python
import sys
import os
kaynak=sys.argv[len(sys.argv)-1]
if "/main/" in kaynak:
  hedef="pts/pool/main"
if "/contrib/" in kaynak:
  hedef="pts/pool/contrib"
if "/non-free/" in kaynak:
  hedef="pts/pool/non-free"

print "Secilen Dosya: "+kaynak
dosya=kaynak.split("/")[len(kaynak.split("/"))-1]
#dosya ismi tespit edildi.
print "Bulunan dosya: "+dosya
os.system("mkdir -p "+hedef+ "/"+dosya[0]+"/"+dosya.split("_")[0]+"/")
os.system("cp -f "+kaynak+ " " + hedef+ "/"+dosya[0]+"/"+dosya.split("_")[0]+"/"+dosya)
print "Kopyalandi: "+ kaynak + " -> " + hedef+ "/"+dosya[0]+"/"+dosya.split("_")[0]+"/"+dosya
#paket adi wine_1.8_amd64.deb olan bir paket argument/w/wine/wine_1.8_amd64.deb kopyalanacak.
