# Libreria dinamica


#1: Osservate come viene compilata una libreria dinamica 
#2: digitare "make -f MakefileShLib" per compilare
#3: digitare "make -f MakefileShLib clean" per pulire la compilazione
#4: Prima di eseguire collegate la variabile d'ambiente LD_LIBRARY_PATH con la directory corrente: 
#Pertanto, mettetevi all'interno della directory dove e' posizionata la libreria e digitate
#"export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD
#5: ldd calc
#6: ./calc