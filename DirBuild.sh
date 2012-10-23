#!/bin/bash

NDIR=$1
ROOTDIR="MercuPy"
MASTER="RUNDIR"
PATHDIR=$(pwd)

###################
# PROGRAMS NAME
###################
ELEMENT6="element6.for"
CLOSE6="close6.for"
MERCURY="mercury6_2.for"

echo -e "\n************************************"
echo -e "CREATION OF RUN DIRECTORIES"
echo -e "************************************"
echo -e "Cleaning '$MASTER' directory:"
rm -rf $MASTER
echo -e "......DONE"
echo -e "Creating '$MASTER' Directory:"
mkdir $MASTER
echo -e "......DONE"
echo -e "Creating directories of runs:"
for i in `seq 1 $NDIR`;
do
    name=run$i
    mkdir $MASTER/$name
	mkdir $MASTER/$name/output
	mkdir $MASTER/$name/tmp
     #echo -e "Dir: $MASTER/$name.....done\n"	
done
echo -e "......DONE"

echo -e "Creating Simbolic link from Mercupy:"
for i in `seq 1 $NDIR`;
do
    name=run$i
    ln -s $PATHDIR/$ROOTDIR/bin $PATHDIR/$MASTER/$name
    #ln -s $PATHDIR/$ROOTDIR/doc $PATHDIR/$MASTER/$name
    #ln -s $PATHDIR/$ROOTDIR/examples $PATHDIR/$MASTER/$name
    ln -s $PATHDIR/$ROOTDIR/util $PATHDIR/$MASTER/$name
    ln -s $PATHDIR/$ROOTDIR/$ELEMENT6 $PATHDIR/$MASTER/$name
    ln -s $PATHDIR/$ROOTDIR/$CLOSE6 $PATHDIR/$MASTER/$name
    ln -s $PATHDIR/$ROOTDIR/$MERCURY $PATHDIR/$MASTER/$name
    ln -s $PATHDIR/$ROOTDIR/element6.sh $PATHDIR/$MASTER/$name
    #ln -s $PATHDIR/$ROOTDIR/compileMercury.sh $PATHDIR/$MASTER/$name
    ln -s $PATHDIR/$ROOTDIR/makefile $PATHDIR/$MASTER/$name
    cp $PATHDIR/$ROOTDIR/*.exe $PATHDIR/$MASTER/$name
    #cp $PATHDIR/$ROOTDIR/Makefile $PATHDIR/$MASTER/$name/
done
echo -e "...... DONE"
#echo -e "PATHDIR: $PATHDIR"
#echo $NDIR
