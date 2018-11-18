#! /bin/env python
import os
from argparse import *
from string import *
import sys
import sqlite3 as lite
from sql_functions import *

path='../template/'
src_path='../src/'
inc_path='../include/'

def processArgs(args):
    if args.level == 'root':
        print 'making a root factory '+args.name
        tmp_h=path+'Root_h.tmp'
        tmp_cpp=path+'Root_cpp.tmp'
    else:
        print 'making a plugin '+args.name
        tmp_h=path+'Plugin_h.tmp'
        tmp_cpp=path+'Plugin_cpp.tmp'
    header=''
    cpp=''
    with open(tmp_h,'r') as f:
        header+=f.read()
    with open(tmp_cpp,'r') as f:
        cpp+=f.read()
    tmp_dic={'name':args.name, 'NAME':args.name.upper(),'base':args.base, 'BASE':args.base.upper()}
    with open(inc_path+args.name+'.h','w') as f:
        f.write(header%tmp_dic)
    with open(src_path+args.name+'.cpp','w') as f:
        f.write(cpp%tmp_dic)
    pass



def main():

    parser =ArgumentParser()
    #options and args added
    parser.add_argument("name", help="name of new plugin root")
    parser.add_argument("--level","-l", help="plugin(just a new plugin),root(new root plugin)",choices=('plugin','root'),default='plugin',dest='level')
    parser.add_argument("--base","-b", help="name of base class",default= 'Plugin',dest='base')
    
    
    args=parser.parse_args()
    processArgs(args)
    pass


if __name__=="__main__":
    main()
