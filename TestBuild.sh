#!/bin/bash

NameDir=$1
ROOTDIR="MercuPy"
MASTER="TEST"
PATHDIR=$(pwd)

###################
# PROGRAMS NAME
###################
ELEMENT6="element6.for"
CLOSE6="close6.for"
MERCURY="mercury6_2.for"


echo -e "\n************************************"
echo -e "CREATION OF TEST FOLDER"
echo -e "************************************"
echo -e "Creating the folder '$NameDir :'"

mkdir $MASTER/$NameDir
mkdir $MASTER/$NameDir/output
mkdir $MASTER/$NameDir/tmp

echo -e "........ DONE"


echo -e "Creating Simbolic link from Mercupy:"

ln -s $PATHDIR/$ROOTDIR/bin $PATHDIR/$MASTER/$NameDir
ln -s $PATHDIR/$ROOTDIR/doc $PATHDIR/$MASTER/$NameDir
ln -s $PATHDIR/$ROOTDIR/examples $PATHDIR/$MASTER/$NameDir
ln -s $PATHDIR/$ROOTDIR/util $PATHDIR/$MASTER/$NameDir
ln -s $PATHDIR/$ROOTDIR/$ELEMENT6 $PATHDIR/$MASTER/$NameDir
ln -s $PATHDIR/$ROOTDIR/$CLOSE6 $PATHDIR/$MASTER/$NameDir
ln -s $PATHDIR/$ROOTDIR/$MERCURY $PATHDIR/$MASTER/$NameDir
ln -s $PATHDIR/$ROOTDIR/element6.sh $PATHDIR/$MASTER/$NameDir
ln -s $PATHDIR/$ROOTDIR/compileMercury.sh $PATHDIR/$MASTER/$NameDir
ln -s $PATHDIR/$ROOTDIR/makefile $PATHDIR/$MASTER/$NameDir

echo -e "...... DONE\n"

