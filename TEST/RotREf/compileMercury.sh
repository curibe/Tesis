#!/bin/bash

gfortran mercury6_2.for -o mercury6_2.exe &>> errors.log
gfortran element6.for -o element6.exe &>> errors.log
gfortran close6.for -o close6.exe &>> errors.log
