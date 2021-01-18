#Copyright (c) <2021>, <hjiang>

#Redistribution and use in source and binary forms, with or without
#modification, are permitted provided that the following conditions are met:

#1. Redistributions of source code must retain the above copyright notice,
#this list of conditions and the following disclaimer.
#2. Redistributions in binary form must reproduce the above copyright notice,
#this list of conditions and the following disclaimer in the documentation
#and/or other materials provided with the distribution.

#THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
#ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
#WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
#DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
#ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
#(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
#LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
#ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
#THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

import sys
import getopt
import json
from datetime import datetime

from utils import *

#----------------------------业务函数 BEGIN---------------------------------
def CheckConfigFile(conf):
	isStartWithRm = conf["MemStructName"].startswith("RmReflib")
	isEndWithT = conf["MemStructName"].endswith("T")
	if not isStartWithRm or not isEndWithT:
		print("[MemStructName] must start with \"RmReflib\" and end with \"T\"")
		print("Fix it! Bye!:)")
		sys.exit(1)

def DumpStruHeadFile(conf):
	stru_h_file = getStruHeadFileName(conf)
	genTitleOfCodeFile(stru_h_file, stru_h_file, getAuthor(conf))
	genStruHeaderFile(conf, stru_h_file)

def DumpStruSourceFile(conf):
	stru_c_file = getStruSourceFileName(conf)
	genTitleOfCodeFile(stru_c_file, stru_c_file, getAuthor(conf))
	genStruSourceFile(conf, stru_c_file)

def DumpStruDefHeadFile(conf):
	stru_def_file = getDefHeadFileName(conf)
	genTitleOfCodeFile(stru_def_file, stru_def_file, getAuthor(conf))
	genDefHeadFile(conf, stru_def_file)

def DumpStruShmNewFile(conf):
	shm_new_file = "shm_new.ini"
	genShmNewFile(conf, shm_new_file)

def DumpInterfaceFile(conf):
	interface_h_file = conf["ReflibInterface"] + ".h"
	interface_c_file = conf["ReflibInterface"] + ".c"
	genTitleOfCodeFile(interface_h_file, interface_h_file, getAuthor(conf))
	genTitleOfCodeFile(interface_c_file, interface_c_file, getAuthor(conf))
	genInterfaceFile(conf, interface_h_file, interface_c_file)

def DumpFicherFile(conf):
	ficherFile = getFicherFileName(conf)
	genTitleOfCodeFile(ficherFile, ficherFile, getAuthor(conf))
	genFicherFile(conf, ficherFile)

def DumpIfmFile(conf):
	ifmFile = getIfmFileName(conf)
	genTitleOfCodeFile(ifmFile, ifmFile, getAuthor(conf))
	genIfmFile(conf, ifmFile)

def DumpShmLoadFile(conf):
	loadFile = getLoadShmFileName(conf)
	genTitleOfCodeFile(loadFile, loadFile, getAuthor(conf))
	genLoadShmFile(conf, loadFile)
#----------------------------业务函数 END-----------------------------------
#----------------------------主程序 BEGIN-----------------------------------
def help():
	print("Usage: python working_horse.py -c <config_path> -o <output_path>")
	print("<config_path> -- the json config which contain the shm data sturct.")
	print("<output_path> -- the output path")

def main(argv):
    try:
        opts, args = getopt.getopt(argv, "hc:o:", ["cfg=","out=",])
    except getopt.GetoptError:
        help()
        sys.exit(2)

    for opt, arg in opts:
        if opt == '-h':
            help()
            sys.exit()
        elif opt in ("-c", "--cfg"):
        	confpath = arg
        elif opt in ("-o", "--out"):
        	outpath = arg

    with open(confpath) as f:
        conf = json.load(f)
        CheckConfigFile(conf)      #先对用户的配置文件进行校验
        DumpStruHeadFile(conf)     #落包含内存结构定义头文件
        DumpStruSourceFile(conf)   #落包含内存结构定义源文件
        DumpStruDefHeadFile(conf)  #落宏定义头文件
        DumpStruShmNewFile(conf)   #落shm_new.ini文件
        DumpInterfaceFile(conf)    #落接口文件
        DumpFicherFile(conf)       #落ficher文件
        DumpIfmFile(conf)          #落ifm文件
        DumpShmLoadFile(conf)      #自动生成从文件加载数据到内存的源文件

if __name__ == "__main__":
    main(sys.argv[1:])
#----------------------------主程序 END-------------------------------------
