from datetime import datetime

_all__ = [ 'genConsAndDesFuncs', 'genBatchInitFunc',
		   'genFieldSpec', 'genStruSourceFile',
		   'genTitleOfCodeFile', 'genStruct',
		   'genGetMaxItem', 'genGetLength',
		   'genGetName', 'genInsert',
		   'genIsExist', 'genGetUniRecord',
		   'genGetUniRecordAt', 'genClear',
		   'genAllUpdFuncs','initSourceFile', 
		   'initHeaderFile','printFicherComment',
		   'printIfmComment', 'genLoadMainFunc',
		   'genStructConvertFunc', 'genFinishFunc']

#----------------------------技术函数 BEGIN---------------------------------
#生成内存结构体定义头文件信息
def genStruHeaderFile(conf, file):
	struName = conf["MemStructName"]
	allFields = conf["MemStructFields"]
	with open(file, "a+") as f:
		f.write("#include <stdint.h>\n\n");
		f.write("#ifndef " + getStruHeadMacroName(conf) + "\n");
		f.write("#define " + getStruHeadMacroName(conf) + "\n\n")
		f.write("#include \"" + getDefHeadFileName(conf) + "\"\n\n")
		writeExternCHead(f)
		f.write(genStarStartLine(73) + "\n");
		f.write("* @struct  : " + struName + "\n")
		f.write("* @brief   : " + getStruDesc(conf) + "\n")
		f.write(genStarEndLine(73) + "\n");
		f.write("#pragma pack(push, 1)\n")
		genStruct(f, struName, conf)
		f.write("#pragma pack(pop)\n")

		#结构体数据打印函数原型
		f.write("\n\n");
		f.write(genStarStartLine(73) + "\n");
		f.write("* @func    : " + struName[2:-1] + "PrintRecord" + "\n")
		f.write("* @brief   : 打印一条" + struName[2:-1] + "信息" + "\n")
		f.write(genStarEndLine(73) + "\n");
		f.write("void " + struName[2:-1] + "PrintRecord(const " + struName + "* pInfo);\n")
		f.write("\n\n");
		f.write(genStarStartLine(73) + "\n");
		f.write("* @func    : " + struName[2:-1] + "PrintRecordHead" + "\n")
		f.write("* @brief   : 打印一条" + struName[2:-1] + "头部信息" + "\n")
		f.write(genStarEndLine(73) + "\n");
		f.write("void " + struName[2:-1] + "PrintRecordHead();\n")
		f.write("\n\n");

		writeExternCTail(f)
		f.write("#endif\n")

#生成内存定义的头文件
def genDefHeadFile(conf, file):
	fieldDict = {}
	allFields = conf["MemStructFields"]
	with open(file, "a+") as f:
		f.write("#ifndef " + getDefMacroName(conf) + "\n")
		f.write("#define " + getDefMacroName(conf) + "\n")
		f.write("\n")
		f.write("#define _FIX2_STR_ARGS(X) (int)sizeof(X), (int)sizeof(X), (X)" + "\n")
		f.write("#define _FIX_STR_ARGS(X)  (int)sizeof(X), (X)" + "\n\n")
		writeExternCHead(f)

		for info in allFields:
			if info["LenMacro"] not in fieldDict:
				if info["Type"] == "char" and info["Length"] > 1:
					f.write("#define " + info["LenMacro"] + " " + str(info["Length"]) + "\n")
					fieldDict[info["LenMacro"]] = 1

		writeExternCTail(f)
		f.write("#endif\n")

#生成shm_new.ini中的元数据
def genShmNewFile(conf, file):
	keyoffset, keylen, keytype = getKeyFieldOffset(conf)
	memName = conf["MemName"]
	memTblName = conf["MemTableName"]
	memRecMax = conf["MemRecordMaxNum"]

	with open(file, "w") as f:
		f.write("[shm]\n")
		f.write("shmSpaces.@@ = " + memName + ", 0x###${ENV_NUM}1\n")
		f.write("[" + memName + "]" + "\n")
		f.write("space.maxSize = " + getStoreSize(conf) + "\n")
		f.write("[" + memName + ".tables.1]" + "\n")
		f.write("record.dataTypeSize = " + str(getRecordSize(conf)) + "B" + "\n")
		f.write("table.type = HashMap\n")
		f.write("table.name = " + memTblName + "\n")
		f.write("table.maxItem = " + getMaxItem(memRecMax) + "\n")
		f.write("index.number = 1\n")
		f.write("index.1.name = " + getIndexTableName(conf) + "\n")
		f.write("index.1.isUnique = true" + "\n")
		f.write("index.1.type = hash" + "\n")
		f.write("index.1.fieldOffset = " + str(keyoffset) + "\n")
		f.write("index.1.fieldSize = " + str(keylen) + "\n")
		f.write("index.1.fieldType = " + keytype + "\n")

def genInterfaceFile(conf, head_file, source_file):
	with open(head_file, "w") as fh, open(source_file, "w") as fs:
		initSourceFile(conf, fs)
		initHeaderFile(conf, fh)
		#自动生成一系列增删查改函数
		genGetMaxItem(conf, fh, fs)
		genGetLength(conf, fh, fs)
		genGetName(conf, fh, fs)
		genInsert(conf, fh, fs)
		genIsExist(conf, fh, fs)
		genGetUniRecord(conf, fh, fs)
		genGetUniRecordAt(conf, fh, fs)
		genClear(conf, fh, fs)
		genAllUpdFuncs(conf, fh, fs)
		writeExternCTail(fh)

#生成ficher头文件
def genFicherFile(conf, ficherfile):
	mainStr = ""
	with open(ficherfile, "a+") as f:
		emptylines(f,1)
		printIfdef(f, getFicherFileMacro(conf))
		printInclude(f, "ficher_basic.h")
		printInclude(f, getIfmFileName(conf))
		emptylines(f,1)
		writeExternCHead(f)
		printFicherComment(f)
		emptylines(f,1)
		f.write("DECLARE_FILE_BEGIN(" + getFicherHndlName(conf) + ")\n")
		mainStr += ttop(1) + "{" + getFicherHndlName(conf) + ", "
		mainStr += getIfmHndlName(conf) + ", "
		mainStr += conf["FileInfos"]["BftType"] + ", "
		mainStr += conf["FileInfos"]["BfeType"] + ", "
		mainStr += conf["FileInfos"]["DirPath"] + ", "
		mainStr += conf["FileInfos"]["Name"] + ", "
		mainStr += conf["FileInfos"]["PathDateFlag"] + ", "
		mainStr += conf["FileInfos"]["NameDateFlag"] + "}"
		f.write(mainStr + "\n")
		f.write("DECLARE_FILE_END(" + getFicherHndlName(conf) + ")\n")
		writeExternCTail(f)
		printEndif(f, getFicherFileMacro(conf))

#生成ifm头文件
def genIfmFile(conf, ficherfile):
	with open(ficherfile, "a+") as f:
		emptylines(f,1)
		printIfdef(f, getIfmFileMacro(conf))
		printInclude(f, "file_index.h")
		printInclude(f, "stream_basic.h")
		printInclude(f, getDefHeadFileName(conf))
		emptylines(f,1)
		writeExternCHead(f)
		genStruct(f, getIfmStruName(conf), conf) #生成ifm文件中的结构体
		emptylines(f,1)
		printIfmComment(f)                       #生成ifm文件中的注释
		emptylines(f,1)
		genFieldSpec(f, conf)                    #生成ifm文件中的字段注释信息
		writeExternCTail(f)
		printEndif(f, getIfmFileMacro(conf))

#生成加载文件到内存的cpp文件
def genLoadShmFile(conf, loadshmfile):
	with open(loadshmfile, "a+") as f:
		emptylines(f,1)
		printInclude(f, "job_obj.h")
		printInclude(f, "bat_file.h")
		printInclude(f, "shm_ctl.h")
		printInclude(f, getFicherFileName(conf))
		printInclude(f, conf["ReflibInterface"] + ".h")
		emptylines(f,1)
		f.write("class " + getLoadClassName(conf) + ": ")
		f.write("public " + "CJobObject" + " {" + "\n")
		#定义文件成员变量
		f.write("private:" + "\n")
		f.write(ttop(1) + "CBatFile " + getLoadFileObjName(conf) + ";" + "\n")
		#构造函数和析构函数
		genConsAndDesFuncs(f, conf)
		#初始化函数
		genBatchInitFunc(f, conf)
		#主处理函数
		genLoadMainFunc(f, conf)
		#结构转换函数
		genStructConvertFunc(f, conf)
		#扫尾函数
		genFinishFunc(f, conf)
		f.write("};" + "\n")
		f.write("//注册批" + "\n")
		f.write("__REGISTER_APP(" + getLoadClassName(conf) + ")" + "\n")
#----------------------------技术函数 END-----------------------------------

#------------------------------------------------------------------------
#产生清空内存的函数
def genClear(conf, fh, fs):
	memVar = conf["MemStructName"][2:-1]
	funVar = memVar + "Clear"
	writeFuncComment(fh, funVar, "清空所有内存记录")
	writeFuncComment(fs, funVar, "清空所有内存记录")
	fh.write("ResCodeT " + funVar + "();" + "\n\n")
	fs.write("ResCodeT " + funVar + "()" + "\n")

	writeHeadBodyOfFunc(fs, 0)
	fs.write(ttop(2) + "CSTHANDLE hTable = NULL;\n")
	fs.write(ttop(2) + "THROW_ERROR(" + memVar + "GetHandle(&hTable), RTN);" + "\n\n")
	fs.write(ttop(2) + "THROW_ERROR(SMDTClear(hTable), RTN);" + "\n")
	writeTailBodyOfFunc(fs)

#产生根据位置查询记录的函数
def genGetUniRecordAt(conf, fh, fs):
	struName = conf["MemStructName"]
	memVar = struName[2:-1]
	funVar = memVar + "GetUniRecordAt"
	argVar = "p" + memVar + "Info"
	posVar = "(__IN size_t iPos,"
	smdtGetPosStr = "THROW_ERROR(SMDTGetRecordAt(hTable, iPos, "

	writeFuncComment(fh, funVar, "按位置查询，获得记录")
	writeFuncComment(fs, funVar, "按位置查询，获得记录")

	fh.write("ResCodeT " + funVar + posVar + struName + " *" + argVar + ");" + "\n\n")
	fs.write("ResCodeT " + funVar + posVar + struName + " *" + argVar + ")" + "\n")

	writeHeadBodyOfFunc(fs, 0)
	fs.write(ttop(2) + "CSTHANDLE hTable = NULL;\n")
	fs.write(ttop(2) + "THROW_ERROR(" + memVar + "GetHandle(&hTable), RTN);" + "\n\n")
	fs.write(ttop(2) + "int iLen = sizeof(" + struName + ");" + "\n")
	fs.write(ttop(2) + smdtGetPosStr + argVar + ", &iLen), RTN);" + "\n")
	writeTailBodyOfFunc(fs)

#产生根据索引字段查询记录的函数
def genGetUniRecord(conf, fh, fs):
	struName = conf["MemStructName"]
	memVar = struName[2:-1]
	funVar = memVar + "GetUniRecord"
	argVar = "p" + memVar + "Info"

	_, _, keyType = getKeyFieldOffset(conf)
	writeFuncComment(fh, funVar, "按主键查询，获得记录")
	writeFuncComment(fs, funVar, "按主键查询，获得记录")
	funcStr = "ResCodeT " + funVar + "(const "+ keyType + " *szKey," + struName + " *" + argVar + ")"
	fh.write(funcStr + ";" + "\n" * 2)
	fs.write(funcStr + "\n")
	writeHeadBodyOfFunc(fs, 0)
	fs.write(ttop(2) + "CSTHANDLE hTable = NULL;\n")
	fs.write(ttop(2) + "THROW_ERROR(" + memVar + "GetHandle(&hTable), RTN);" + "\n" * 2)
	fs.write(ttop(2) + "int iLen = sizeof(" + struName + ");" + "\n")

	smdtHead = "THROW_ERROR(SMDTGetRecord(hTable, "
	smdtTail = "szKey, " + argVar + ", &iLen), RTN);"
	if keyType == "char":
		fs.write(ttop(2) + smdtHead + smdtTail + "\n")
	else:
		fs.write(ttop(2) + smdtHead + "(const char *)" + smdtTail + "\n")

	writeTailBodyOfFunc(fs)

#产生判断索引字段是否存在的函数
def genIsExist(conf, fh, fs):
	struName = conf["MemStructName"]
	memVar = struName[2:-1]
	funVar = memVar + "IsExist"
	argVar = "p" + memVar + "Info"

	keyoffset, keylen, keyType = getKeyFieldOffset(conf)

	writeFuncComment(fh, funVar, "判断索引字段是否存在")
	writeFuncComment(fs, funVar, "判断索引字段是否存在")
	headStr = "ResCodeT " + funVar + "(__IN const "+ keyType
	tailStr = " *szKey, __IN BOOL* bIsExist)"

	fh.write(headStr + tailStr + ";" + "\n" * 2)
	fs.write(headStr + tailStr + "\n")
	writeHeadBodyOfFunc(fs, 1)
	fs.write(ttop(2) + "CSTHANDLE hTable = NULL;\n")
	fs.write(ttop(2) + struName + " *" + argVar + " = NULL;" + "\n\n")
	fs.write(ttop(2) + "THROW_ERROR(" + memVar + "GetHandle(&hTable), RTN);" + "\n\n")

	smdtHead = "rc = SMDTGetDirectRecordDirty(hTable, "
	smdtTail = "szKey, (LPRECORD*)&" + argVar + ");"
	if keyType == "char":
		fs.write(ttop(2) + smdtHead + smdtTail + "\n")
	else:
		fs.write(ttop(2) + smdtHead + "(const char *)" + smdtTail + "\n")

	fs.write(ttop(2) + "switch(rc)" + "\n")
	fs.write(ttop(2) + "{" + "\n")
	fs.write(ttop(3) + "case NO_ERR:" + "\n")
	fs.write(ttop(4) + "*bIsExist= TRUE;" + "\n")
	fs.write(ttop(4) + "break;" + "\n")
	fs.write(ttop(3) + "case ERCD_SMDA_NO_DATA_SELECT:" + "\n")
	fs.write(ttop(4) + "*bIsExist= FALSE;" + "\n")
	fs.write(ttop(4) + "ClearErrorByDepth();" + "\n")
	fs.write(ttop(4) + "break;" + "\n")
	fs.write(ttop(3) + "default:" + "\n")
	fs.write(ttop(4) + "THROW_ERROR( rc, RTN);" + "\n")
	fs.write(ttop(4) + "break;" + "\n")
	fs.write(ttop(2) + "}" + "\n")
	writeTailBodyOfFunc(fs)

#产生插入内存表记录的函数
def genInsert(conf, fh, fs):
	struName = conf["MemStructName"]
	memVar = struName[2:-1]
	funVar = memVar + "Insert"
	argVar = "p" + memVar + "Info"

	writeFuncComment(fh, funVar, "插入一条" + memVar + "内存记录")
	writeFuncComment(fs, funVar, "插入一条" + memVar + "内存记录")
	fh.write("ResCodeT " + funVar + "(__IN "+ struName + " *" + argVar + ");" + "\n\n")
	fs.write("ResCodeT " + funVar + "(__IN "+ struName + " *" + argVar + ")" + "\n")
	writeHeadBodyOfFunc(fs, 0)
	fs.write(ttop(2) + "CSTHANDLE hTable = NULL;\n")
	fs.write(ttop(2) + "THROW_ERROR(" + memVar + "GetHandle(&hTable), RTN);" + "\n\n")
	fs.write(ttop(2) + "THROW_ERROR(SMDTInsertRecord(hTable, " + argVar + "), RTN);" + "\n")
	writeTailBodyOfFunc(fs)

#产生获取内存表最大记录数的函数
def genGetMaxItem(conf, fh, fs):
	memVar = conf["MemStructName"][2:-1]
	funVar = getShmGetMaxItemFuncName(conf)
	writeFuncComment(fh, funVar, "获取" + memVar + "内存表配置的记录数大小")
	writeFuncComment(fs, funVar, "获取" + memVar + "内存表配置的记录数大小")
	fh.write("ResCodeT " + funVar + "(size_t *iMaxItem);" + "\n\n")
	fs.write("ResCodeT " + funVar + "(size_t *iMaxItem)" + "\n")
	writeHeadBodyOfFunc(fs, 0)
	fs.write(ttop(2) + "CSTHANDLE hTable = NULL;\n")
	fs.write(ttop(2) + "THROW_ERROR(" + memVar + "GetHandle(&hTable), RTN);" + "\n\n")
	fs.write(ttop(2) + "*iMaxItem = SMDTGetCapacity(hTable);\n")
	writeTailBodyOfFunc(fs)

#产生获取内存表实际使用量的函数
def genGetLength(conf, fh, fs):
	memVar = conf["MemStructName"][2:-1]
	funVar = memVar + "GetLength"
	writeFuncComment(fh, funVar, "获取" + memVar + "内存表配置的实际使用量")
	writeFuncComment(fs, funVar, "获取" + memVar + "内存表配置的实际使用量")
	fh.write("ResCodeT " + funVar + "(size_t *iUsed);" + "\n\n")
	fs.write("ResCodeT " + funVar + "(size_t *iUsed)" + "\n")
	writeHeadBodyOfFunc(fs, 0)
	fs.write(ttop(2) + "CSTHANDLE hTable = NULL;\n")
	fs.write(ttop(2) + "THROW_ERROR(" + memVar + "GetHandle(&hTable), RTN);" + "\n\n")
	fs.write(ttop(2) + "*iUsed = SMDTGetLength(hTable);\n")
	writeTailBodyOfFunc(fs)

#产生获取内存表名的函数
def genGetName(conf, fh, fs):
	struName = conf["MemStructName"]
	tblName = conf["MemTableName"]
	memVar = struName[2:-1]
	funVar = memVar + "GetName"
	writeFuncComment(fh, funVar, "获取" + memVar + "内存表名")
	writeFuncComment(fs, funVar, "获取" + memVar + "内存表名")
	fh.write("const char* " + funVar + "();" + "\n\n")
	fs.write("const char* " + funVar + "()" + "\n")
	fs.write("{" + "\n")
	fs.write(ttop(1) + "return " + "\"" + tblName + "\";" + "\n");
	fs.write("}" + "\n\n")

#生成所有更新字段的函数
def genAllUpdFuncs(conf, fh, fs):
	memStruName = conf["MemStructName"]
	memVar = memStruName[2:-1]
	argVar = "p" + memVar + "Info"
	memKey = conf["MemStructFields"]
	allFieldsInfo = conf["MemStructFields"]
	_, _, keyType = getKeyFieldOffset(conf)

	for fieldInfo in allFieldsInfo:
		fieldNm = fieldInfo["Name"]
		fieldLen = fieldInfo["Length"]
		fieldTyp = fieldInfo["Type"]
		fieldMac = fieldInfo["LenMacro"]

		if fieldNm != memKey:
			funVar = memVar + "Upd" + fieldNm
			writeFuncComment(fh, funVar, "通过主索引修改" + fieldNm + "字段")
			writeFuncComment(fs, funVar, "通过主索引修改" + fieldNm + "字段")

			headFuncBody = "ResCodeT " + funVar + "(const " + keyType + "* szKey, "
			tailFuncBody = ""
			if fieldInfo["Type"] == "char" and fieldLen > 1:
				tailFuncBody += "const " + fieldTyp + "* " + fieldNm + ")"
			else:
				tailFuncBody += fieldTyp + " " + fieldNm + ")"
			fh.write(headFuncBody + tailFuncBody + ";" + "\n" * 2)
			fs.write(headFuncBody + tailFuncBody + "\n")

			writeHeadBodyOfFunc(fs, 1)
			fs.write(ttop(2) + "CSTHANDLE hTable = NULL;\n")
			fs.write(ttop(2) + memStruName + " *" + argVar + " = NULL;" + "\n" * 2)
			fs.write(ttop(2) + "THROW_ERROR(" + memVar + "GetHandle(&hTable), RTN);" + "\n" * 2)

			getHoldFuncHead = "rc = SMDTGetDirectRecordWithHold(hTable, "
			getHoldFuncTail = "szKey, (LPRECORD*)&" + argVar + ");"

			if keyType == "char":
				fs.write(ttop(2) + getHoldFuncHead + getHoldFuncTail + "\n")
			else:
				fs.write(ttop(2) + getHoldFuncHead + "(const char*)" + getHoldFuncTail + "\n")

			fs.write(ttop(2) + "THROW_ERROR(rc, RTN);" + "\n\n")
			cpStr = "memcpy(" + argVar + "->" + fieldNm + ", " + fieldNm + ", " + fieldMac + ");"
			asStr = argVar + "->" + fieldNm + " = " + fieldNm + ";"

			if fieldTyp == "char" and fieldLen > 1:
				fs.write(ttop(2) + cpStr + "\n" * 2)
			else:
				fs.write(ttop(2) + asStr + "\n" * 2)

			fs.write(ttop(2) + "rc = SMDTReleaseHold( hTable, szKey);" + "\n")
			fs.write(ttop(2) + "THROW_ERROR(rc, RTN);" + "\n")
			writeTailBodyOfFunc(fs)
#------------------------------------------------------------------------
#一个通用的代码Title生成函数
def genTitleOfCodeFile(filename, filepath, author):
	with open(filepath, "w") as f:
		f.write(genStarStartLine(73) + "\n");
		f.write("*\n" * 2)
		f.write("*                        COPYRIGHT(C) 2020 BY                        \n")
		f.write("*  SHANGHAI STOCK EXCHANGE TECHNOLOGY (SSETech), SHANGHAI, CHINA     \n")
		f.write("*                        ALL RIGHTS RESERVED.                        \n")
		f.write("*                                                                    \n")
		f.write(genStarEndLine(73) + "\n");
		f.write(genStarStartLine(73) + "\n");
		f.write("*  FILE NAME       : " + filename + "\n")
		f.write("*  DESCRIPTION     : " + "\n")
		f.write(genStarEndLine(73) + "\n");
		f.write("*  MODIFICATION HISTORY:\n")
		f.write("*\n")
		f.write("*     Date.     Prog.\n")
		f.write("*  DD-MMM-YYYY     Init.      SIR         Modification Description\n")
		f.write("*  ----------- ----------- ----------- -------------------------------\n")
		f.write("*  " + getCurrDateStr() + "     " + author + "                 \n")
		f.write(genStarEndLine(73) + "\n");

#一个通用的生成结构体定义的函数
def genStruct(f, struName, conf):
	f.write("typedef struct tag" + struName + "{\n")
	for fieldinfo in conf["MemStructFields"]:
		fieldName   = fieldinfo["Name"]
		fieldLenMac = fieldinfo["LenMacro"]
		fieldLen    = fieldinfo["Length"]
		fieldType   = fieldinfo["Type"]
		fieldMsg    = fieldinfo["Message"]
		fieldStr = ""
		if fieldType == "char" and fieldLen > 1:
			fieldStr += fieldName + "[" + fieldLenMac + "]"
		else:
			fieldStr += fieldName

		f.write("\t" + fieldType + "\t" + fieldStr + ";")

		if len(fieldStr) < 35:
			f.write((35 - len(fieldStr)) * " " + "//" + fieldMsg + "\n")
		else:
			f.write("\t" + "//" + fieldMsg + "\n")
	f.write("}" + struName + ";" + "\n")

#生成内存结构定义的源代码
def genStruSourceFile(conf, file):
	struName = conf["MemStructName"]
	allFields = conf["MemStructFields"]

	with open(file, "a+") as f:
		f.write("#include " + "\"" + getStruHeadFileName(conf) + "\"\n")
		f.write("#include <stdio.h>\n\n")

		#打印结构体的函数
		f.write("void " + struName[2:-1] + "PrintRecord(const " + struName + "* pInfo) {\n")
		fmt_str = ""
		arg_str = ""
		for i in range(len(allFields)):
			fix_begin = ""
			fix_end = ""

			if allFields[i]["Type"] == "char" and allFields[i]["Length"] > 1:
				fmt_str += "%*.*s"
			elif allFields[i]["Type"] == "char" and allFields[i]["Length"] == 1:
				fmt_str += "%c"
			elif "int32" in allFields[i]["Type"]:
				fmt_str += "%d"
			elif "uint32" in allFields[i]["Type"]:
				fmt_str += "%u"
			elif "int64" in allFields[i]["Type"]:
				fmt_str += "%ll"
			elif "uint64" in allFields[i]["Type"]:
				fmt_str += "%llu"
			else:
				fmt_str += ""

			if allFields[i]["Type"] == "char" and allFields[i]["Length"] > 1:
				fix_begin = "_FIX2_STR_ARGS("
				fix_end = ")"

			arg_str += ttop(2) + fix_begin + "pInfo->"
			arg_str += allFields[i]["Name"]
			arg_str += fix_end

			if i < (len(allFields) - 1):
				fmt_str += "|"
				arg_str += ",\n"
			else:
				fmt_str += "\\n"

		f.write(ttop(1) + "printf(" + "\"" + fmt_str + "\"" + ",\n" + arg_str + ");\n")
		f.write("}\n\n")

		#打印头字段的函数
		f.write("void " + struName[2:-1] + "PrintRecordHead() {\n");
		head_str = ""
		div_str = ""
		for i in range(len(allFields)):
			head_str += allFields[i]["Name"]
			div_str += len(allFields[i]["Name"]) * "-"

			if (i+1) % 8 == 0:
				head_str += "\\\n"
				div_str += "\\\n"

			if i < (len(allFields) - 1):
				head_str += " "
				div_str += " "
			else:
				head_str += "\\n"
				div_str += "\\n"

		f.write(ttop(1) + "printf(\"" + head_str + "\"" + ");\n") 
		f.write(ttop(1) + "printf(\"" + div_str  + "\"" + ");\n")
		f.write("}\n\n")

#生成ifm文件字段描述
def genFieldSpec(f, conf):
	ifm_hndl = getIfmHndlName(conf)
	encoding = conf["FileInfos"]["Encoding"]
	max_field_name = getMaxFieldStrLength(conf)
	f.write("DECLARE_STREAM_BEGIN(" + ifm_hndl + ")" + "\n")
	sep_str = ""
	if conf["FileInfos"]["BftType"] == "BFT_TXT":
		sep_str = "|"
	f.write("  {" + ifm_hndl + "," + "BFL_FIXED,")
	f.write("\'" + sep_str + "\'" + ",")
	f.write(str(getFileRecordSize(conf, sep_str)) + "," + encoding + "}" + "\n")
	f.write("DECLARE_STREAM_WITH_DETAIL(" + ifm_hndl + ")" + "\n")

	index = 1
	for fieldInfo in conf["MemStructFields"]:
		f.write("  { " + str(index) + ", ")
		f.write("\"" + fieldInfo["Name"] + "\"")
		f.write((max_field_name - len(fieldInfo["Name"])) * " ")
		f.write(", ")
		if "char" in fieldInfo["Type"]:
			f.write("C ,")
		else:
			f.write("N ,")
		f.write(" " + str(fieldInfo["Length"]) + " ,")
		f.write(" " + str(0) + " ,")
		f.write(" \"" + "Y00000000000000" + "\" ,")
		f.write(" " + str(1) + " ,")
		f.write(" " + str(1) + " ,")
		f.write(" " + str(0) + " ,")
		f.write(" " + "RMINFO( " + getIfmStruName(conf) + ",")

		if "char" in fieldInfo["Type"]:
			f.write("COLT_CHAR,")
		elif "int32" in fieldInfo["Type"]:
			f.write("COLT_SN32,")
		elif "int64" in fieldInfo["Type"]:
			f.write("COLT_SN64,")
		elif "uint32" in fieldInfo["Type"]:
			f.write("COLT_UN32,")
		elif "uint64" in fieldInfo["Type"]:
			f.write("COLT_UN64,")
		else:
			f.write("COLT_UNKNOW,")

		f.write(fieldInfo["Name"] + ")}," + "\n")
		index = index + 1
	f.write("DECLARE_STREAM_END(" + ifm_hndl + ")" + "\n")

def initHeaderFile(conf, fh):
	fh.write("#include \"smda.h\"\n\n")
	fh.write("#include \"" + getStruHeadFileName(conf) + "\""+ "\n")
	fh.write("#include \"err_biz.h\"\n\n")
	writeExternCHead(fh)

def initSourceFile(conf, fs):
	struName = conf["MemStructName"]
	tblName = conf["MemTableName"]
	memVar = struName[2:-1]
	funVar = memVar + "GetHandle"
	tbVar = "gTable" + memVar + "Info"

	#源文件初始化
	fs.write("#include \"err_pub.h\"\n")
	fs.write("#include \"log_std.h\"\n")
	fs.write("#include \"" + getStruHeadFileName(conf) + "\"" + "\n")
	fs.write("#include \"smda.h\"\n\n")
	fs.write("static CSTHANDLE " + tbVar + " = NULL;" + "\n\n")

	#生成原文件中静态的获取内存表句柄函数
	writeFuncComment(fs, funVar, "获取" + memVar + "内存表操作句柄")

	fs.write("static ResCodeT " + funVar + "(CSTHANDLE* pTable)" + "\n")
	writeHeadBodyOfFunc(fs, 0)
	fs.write(ttop(2) + "if(!" + tbVar + ")" + "\n")
	fs.write(ttop(2) + "{" + "\n")
	fs.write(ttop(3) + "THROW_ERROR(SMDTGetHandle(\"" + tblName +"\"," + "\n");
	fs.write(ttop(4) +"&" + tbVar + ")," + "\n");
	fs.write(ttop(4) + "RTN);" + "\n")
	fs.write(ttop(2) + "}" + "\n\n")
	fs.write(ttop(2) + "*pTable = " + tbVar + ";" + "\n")
	writeTailBodyOfFunc(fs)

def printFicherComment(f):
	f.write(genStarStartLine(85) + "\n")
	f.write("* DECLARE_FILE_BEGIN(接口文件索引)" + "\n")
	f.write("*   {接口文件索引,结构化数据流索引,文件类型,文件结束符,存放目录,存放文件,目录名称替换规则,文件名替换规则}" + "\n")
	f.write("*DECLARE_FILE_END(接口文件索引)" + "\n")
	f.write(genSepStarLine(85) + "\n")
	f.write("* 文件类型: 文本/DBF/二进制二维表(结构化二维表)" + "\n")
	f.write("* 文件结束符: DOS行尾/UNIX行尾/无行尾" + "\n")
	f.write("* 日期替换规则支持串:YYYYMMDD yyyymmdd yymmdd mmdd" + "\n")
	f.write("* 日替换换规则市场支持:A-沪市 H-港股 I-港股通" + "\n")
	f.write(genStarEndLine(85) + "\n")

def printIfmComment(f):
	f.write(genStarStartLine(95) + "\n")
	f.write("* DECLARE_STREAM_BEGIN(结构化数据流索引)" + "\n")
	f.write("*   {结构化数据流索引,记录定长还是变长,分隔符(没有填0),单行总长度/最大长度,字符集}" + "\n")
	f.write(" * DECLARE_STREAM_WITH_DETAIL(结构化数据流索引)" + "\n")
	f.write("*   {字段序号,字段1名称,原始类型,长度,小数位,校验参数,序列化方式,反序列化方式,放大系数,内存结构起始偏移,类型,长度}" + "\n")
	f.write("*   {字段序号,字段2名称,原始类型,长度,小数位,校验参数,序列化方式,反序列化方式,放大系数,内存结构起始偏移,类型,长度}" + "\n")
	f.write("*DECLARE_STREAM_END(结构化数据流索引)" + "\n")
	f.write(genSepStarLine(95) + "\n")
	f.write("* 序列化和反序列化的方式有三种:转化(默认)、原始拷贝、跳过(读入时忽略)。" + "\n")
	f.write("* 放大系数为从文件读入时，数据的放大系数。" + "\n")
	f.write("* 关于数据的原始类型,必须为N、C的衍生,当为浮点型数据时,必须要配置放大,否则小数部分舍去" + "\n")
	f.write(genStarEndLine(95) + "\n")

#----------------------------工具函数 BEGIN---------------------------------
def getShmClearFuncName(conf):
	memVar = conf["MemStructName"][2:-1]
	funVar = memVar + "Clear"
	return funVar

def genStarStartLine(n):
	return "/" + n * "*"

def genSepStarLine(n):
	return n * "*"

def genStarEndLine(n):
	return n * "*" + "/"

def getStruHeadFileName(conf):
	return conf["ReflibInterface"] + "_stru" + ".h"

def getStruHeadMacroName(conf):
	interFace = conf["ReflibInterface"]
	return "_" + interFace.upper() + "_stru".upper() + "_h_".upper()

def getStruDesc(conf):
	return conf["MemStructName"][2:-1] + "结构"

def getStruSourceFileName(conf):
	return conf["ReflibInterface"] + "_stru" + ".c"

def getDefHeadFileName(conf):
	return conf["ReflibInterface"] + "_def" + ".h"

def getDefMacroName(conf):
	interFace = conf["ReflibInterface"]
	return "_" + interFace.upper() + "_def".upper() + "_h_".upper()

def getIndexTableName(conf):
	return "PK_" + conf["MemTableName"]

def ttop(tabNum):
	spaces = ""
	for i in range(tabNum):
		spaces +="    "
	return spaces

def getMaxItem(num):
	if num >= 10000:
		return str(round(num/10000)) + "w"
	elif num >= 1000:
		return str(round(num/1000)) + "k"
	else:
		return str(num)

def getStoreSize(conf):
	space_size_in_byte = getRecordSize(conf) * conf["MemRecordMaxNum"]
	if space_size_in_byte > 1000000000:
		return str(round(space_size_in_byte / 500000000)) + "G"
	if space_size_in_byte > 1000000:
		return str(round(space_size_in_byte / 500000)) + "M"
	elif space_size_in_byte > 1000:
		return str(round(space_size_in_byte / 500)) + "K"
	else:
		return str(round(space_size_in_byte * 2)) + "B"

#计算单块内存结构所占用的内存大小
def getRecordSize(conf):
	size = 0
	for fieldinfo in conf["MemStructFields"]:
		size += fieldinfo["Length"]
	return size + 8

#计算单个文件记录长度
def getFileRecordSize(conf, sep):
	size = 0
	for fieldinfo in conf["MemStructFields"]:
		size += fieldinfo["Length"] 
	return size + len(sep) * (len(conf["MemStructFields"]) - 1)

#得到最长字段名称长度
def getMaxFieldStrLength(conf):
	maxlen = 0
	for fieldinfo in conf["MemStructFields"]:
		if maxlen < len(fieldinfo["Name"]):
			maxlen = len(fieldinfo["Name"])
	return maxlen

#计算key字段开始index和长度
def getKeyFieldOffset(conf):
	keyoffset = 0
	for fieldinfo in conf["MemStructFields"]:
		if conf["MemKeyField"] != fieldinfo["Name"]:
			keyoffset += fieldinfo["Length"]
		else:
			return keyoffset + 8, fieldinfo["Length"], fieldinfo["Type"]

def writeHeadBodyOfFunc(fhndl, flag):
	fhndl.write("{" + "\n")
	if flag == 1: 
		fhndl.write(ttop(1) + "ResCodeT rc = NO_ERR;" + "\n")
	fhndl.write(ttop(1) + "TRY" + "\n")
	fhndl.write(ttop(1) + "{" + "\n")

def writeTailBodyOfFunc(fhndl):
	fhndl.write(ttop(1) + "}" + "\n")
	fhndl.write(ttop(1) + "CATCH" + "\n")
	fhndl.write(ttop(1) + "{" + "\n")
	fhndl.write(ttop(1) + "}" + "\n")
	fhndl.write(ttop(1) + "FINALLY" + "\n")
	fhndl.write(ttop(1) + "{" + "\n")
	fhndl.write(ttop(2) + "RETURN_RESCODE;" + "\n")
	fhndl.write(ttop(1) + "}" + "\n")
	fhndl.write("}" + "\n\n")

def writeExternCHead(fhndl):
	fhndl.write("#ifdef __cplusplus\n")
	fhndl.write("extern \"C\"{\n")
	fhndl.write("#endif\n\n\n")

def writeExternCTail(fhndl):
	fhndl.write("\n\n")
	fhndl.write("#ifdef __cplusplus\n")
	fhndl.write("}\n")
	fhndl.write("#endif\n\n")

def writeFuncComment(fhndl, fname, fdesc):
	fhndl.write(genStarStartLine(73) + "\n");
	fhndl.write("* @func    : " + fname + "\n")
	fhndl.write("* @brief   : " + fdesc + "\n")
	fhndl.write("* @return  : 成功返回NO_ERR" + "\n")
	fhndl.write("* @history :" + "\n")
	fhndl.write(genStarEndLine(73) + "\n");

#自动得到当天日期信息
def getCurrDateStr():
    return datetime.today().strftime('%d-%b-%Y')

def getFicherHndlName(conf):
	msName = conf["MemStructName"]
	return "FROM_BPC_" + msName[8:-1].upper()

def getFicherFileName(conf):
	msName = conf["MemStructName"]
	return "from_bpc_" + msName[8:-1].lower() + ".h"

def getFicherFileMacro(conf):
	msName = conf["MemStructName"]
	return "BIZ_FROM_BPC_" + msName[8:-1].upper() + "_H_"

def getIfmHndlName(conf):
	msName = conf["MemStructName"]
	return "IFM_BPC_" + msName[8:-1].upper()

def getIfmFileName(conf):
	msName = conf["MemStructName"]
	return "ifm_bpc_" + msName[8:-1].lower() + ".h"

def getLoadShmFileName(conf):
	msName = conf["MemStructName"]
	return "load_" + msName[8:-1].lower() + ".cpp"

def getLoadClassName(conf):
	msName = conf["MemStructName"]
	return "CLoad" + msName[8:-1].lower().capitalize()

def getLoadFileObjName(conf):
	msName = conf["MemStructName"]
	return "m_" + msName[8:-1].lower().capitalize() + "File"

def getIfmFileMacro(conf):
	msName = conf["MemStructName"]
	return "IFM_BPC_" + msName[8:-1].upper() + "_H_"

def getIfmStruName(conf):
 	return "Rm" + conf["MemStructName"][8:-1] + "T"

def getAuthor(conf):
	return conf["Author"]

def emptylines(f, n):
	f.write("\n" * n)

def printIfdef(f, m):
	f.write("#ifndef " + m + "\n")
	f.write("#define " + m + "\n\n")

def printEndif(f, m):
	f.write("#endif " + "/** " + m + " */" + "\n")

def printInclude(f, h):
	f.write("#include " + "\"" + h + "\"" + "\n")
#----------------------------工具函数 END-----------------------------------

#------------------------------------------------------------------------
def genConsAndDesFuncs(f, conf):
	f.write("public:" + "\n")
	f.write(ttop(1) + getLoadClassName(conf) + "()" + "\n")
	f.write(ttop(1) + "{" + "\n")
	f.write(ttop(1) + "}" + "\n")
	f.write(ttop(1) + "~" + getLoadClassName(conf) + "()" + "\n")
	f.write(ttop(1) + "{" + "\n")
	f.write(ttop(1) + "}" + "\n\n")

def genBatchInitFunc(f, conf):
	genFirstHalfFunc(f, "JobInit", "", 1)
	f.write(ttop(3) + "// 1. 加载内存配置" + "\n")
	f.write(ttop(3) + "rc = InitHAPShmFactory();" + "\n");
	f.write(ttop(3) + "RAISE_ERRMSG(rc, RTN, \"Failed to init hap shm fatory\");" + "\n\n")
	
	f.write(ttop(3) + "// 2. 清空内存" + "\n")
	f.write(ttop(3) + "rc = " + getShmClearFuncName(conf) + "();" + "\n")
	f.write(ttop(3) + "RAISE_ERRMSG(rc, RTN, \"Failed to clear pbu memory.\");" + "\n\n")

	f.write(ttop(3) + "// 3. 输入文件不为空" + "\n")
	f.write(ttop(3) + "rc = IsFileEmpty(" + getFicherHndlName(conf) + ");" + "\n");
	f.write(ttop(3) + "RAISE_ERR(rc, RTN);" + "\n\n")
	
	f.write(ttop(3) + "// 4. 打开文件" + "\n")
	f.write(ttop(3) + "rc = " + getLoadFileObjName(conf) + ".Open(")
	f.write(getFicherHndlName(conf) + ", F_RD, DF_MASK_UNSERIAL | DF_MASK_FMTCHK);" + "\n")
	f.write(ttop(3) + "RAISE_ERR(rc, RTN);" + "\n")
	genSecondHalfFunc(f, 1)

#内存加载主处理
def genLoadMainFunc(f, conf):
	genFirstHalfFunc(f, "JobProcess", "", 1)
	mem_var = "memRec"
	file_var = "fileRec"
	f.write(ttop(3) + conf["MemStructName"] + " " + mem_var + ";" + "\n")
	f.write(ttop(3) + getIfmStruName(conf) + " " + file_var + ";" + "\n\n")
	f.write(ttop(3) + "int64_t iExceptCount = 0; //异常数量" + "\n")
	f.write(ttop(3) + "int iRecordCnt = 0; //记录数" + "\n\n")
	f.write(ttop(3) + "int iRecLen = 0; //记录长度" + "\n")
	f.write(ttop(3) + "char szValidResultMsg[MAX_BUFF_LEN] = {0}; // 校验异常信息" + "\n\n")
	f.write(ttop(3) + "//处理文件记录" + "\n")
	f.write(ttop(3) + "while(1)" + "\n")
	f.write(ttop(3) + "{" + "\n")
	f.write(ttop(4) + "memset(&" + mem_var + ", 0x00, " + "sizeof(" + conf["MemStructName"] + "));" + "\n")
	f.write(ttop(4) + "memset(&" + file_var + ", 0x00, " + "sizeof(" + getIfmStruName(conf) + "));" + "\n")
	f.write(ttop(4) + "iRecLen = sizeof(" + getIfmStruName(conf) + ")" + "\n\n")
	f.write(ttop(4) + "//读取数据" + "\n")
	f.write(ttop(4) + "rc = " + getLoadFileObjName(conf) + ".Read(&" + file_var + ",iRecLen);" + "\n")
	f.write(ttop(4) + "RAISE_ERROR(rc, RTN);" + "\n\n")
	f.write(ttop(4) + "//判断读结束" + "\n")
	f.write(ttop(4) + "if(" + getLoadFileObjName(conf) + ".IsEOF())" + "\n")
	f.write(ttop(4) + "{" + "\n")
	f.write(ttop(5) + "break;" + "\n")
	f.write(ttop(4) + "}" + "\n\n")
	f.write(ttop(4) + "//异常校验" + "\n")
	f.write(ttop(4) + "iRecordCnt += 1;" + "\n")
	f.write(ttop(4) + "if(!" + getLoadFileObjName(conf) + ".GetLastValidResult(szValidResultMsg, sizeof(szValidResultMsg)))" + "\n")
	f.write(ttop(4) + "{" + "\n")
	f.write(ttop(5) + "DEAL_MSG( LOG_SEV_ERROR," + "\n")
	f.write(ttop(6) + "\"Exception[%02ld]: Failed of valid record(%d), which is :%s\"," + "\n")
	f.write(ttop(6) + "iExceptCount," + "\n")
	f.write(ttop(6) + "iRecordCnt," + "\n")
	f.write(ttop(6) + "szValidResultMsg);" + "\n")
	f.write(ttop(5) + "continue;" + "\n")
	f.write(ttop(4) + "}" + "\n\n")
	f.write(ttop(4) + "//文件记录字段字典校验（You Implement Me!）" + "\n\n")
	f.write(ttop(4) + "//结构转换" + "\n")
	f.write(ttop(4) + "rc = " + "ConvFileRecToMemRec(&" + mem_var + ", &" + file_var + ");" + "\n")
	f.write(ttop(4) + "RAISE_ERRMSG(rc, RTN, \"Convert File Record To Mem Record Failed!\");" + "\n\n")
	f.write(ttop(4) + "//数据插入内存" + "\n")
	f.write(ttop(4) + "rc = " + getShmInsertFuncName(conf) + "(&" +mem_var + ");" + "\n")
	f.write(ttop(4) + "RAISE_ERRMSG(rc, RTN, \"Insert Memory Record Failed!\");" + "\n")
	f.write(ttop(3) + "}" + "\n\n")
	f.write(ttop(3) + "if(iExceptCount > 0)" + "\n")
	f.write(ttop(3) + "{" + "\n")
	f.write(ttop(4) + "DEAL_MSG(LOG_SEV_ERROR," + "\n")
	f.write(ttop(5) + "\"There is %d exceptions in file\"," + "\n")
	f.write(ttop(5) + "iExceptCount);" + "\n")
	f.write(ttop(4 ) + "SET_RESCODE(ERCD_BIZCHK_EXCEPTION);" + "\n")
	f.write(ttop(3) + "}" + "\n\n")
	f.write(ttop(3) + "DEAL_MSG(LOG_SEV_INFORMATION," + "\n")
	f.write(ttop(4) + "\"All file(%d) have been load.\"," + "\n")
	f.write(ttop(4) + "iRecordCnt);" + "\n")
	genSecondHalfFunc(f, 1)

#生成从文件结构转换到内存结构的函数
def genStructConvertFunc(f, conf):
	arg_str = conf["MemStructName"] + "* pMemRec" + ", " + getIfmStruName(conf) + "* pFileRec"
	genFirstHalfFunc(f, "ConvFileRecToMemRec", arg_str, 1)
	for fieldInfo in conf["MemStructFields"]:
		if "char" in fieldInfo["Type"] and fieldInfo["Length"] > 1:
			f.write(ttop(3) + "memcpy(pMemRec->" + fieldInfo["Name"])
			f.write(", pFileRec->" + fieldInfo["Name"] + ", ")
			f.write(fieldInfo["LenMacro"] + ");" + "\n")
		else:
			f.write(ttop(3) + "pMemRec->" + fieldInfo["Name"])
			f.write(" = pFileRec->" + fieldInfo["Name"] + ";" + "\n")
	genSecondHalfFunc(f, 1)

#生成扫尾函数
def genFinishFunc(f, conf):
	genFirstHalfFunc(f, "JobFinnal", "BOOL bSuccessFinnal=TRUE", 1)
	f.write(ttop(3) + "if(bSuccessFinnal)" + "\n")
	f.write(ttop(3) + "{" + "\n")
	f.write(ttop(4) + "size_t iMaxItem = 0;" + "\n\n")
	f.write(ttop(4) + "rc = " + getShmGetMaxItemFuncName(conf) + "(&iMaxItem);" + "\n")
	f.write(ttop(4) + "RAISE_ERR(rc, RTN);" + "\n\n")
	f.write(ttop(4) + "const char* szTableName = " + getShmGetTableNameFuncName(conf) + "();" + "\n")
	f.write(ttop(4) + "size_t iUsed = 0;" + "\n\n")
	f.write(ttop(4) + "rc = " + getShmGetLengthFuncName(conf) + "(&iUsed);" + "\n")
	f.write(ttop(4) + "RAISE_ERR(rc, RTN);" + "\n\n")
	f.write(ttop(4) + "DEAL_MSG(LOG_SEV_INFORMATION," + "\n")
	f.write(ttop(5) + "\"Share Memory Statistic, shmTableName=[%-24s],capicity=%10u,used=%10u,rate=%.2lf%%\"," + "\n")
	f.write(ttop(5) + "szTableName," + "\n")
	f.write(ttop(5) + "iMaxItem," + "\n")
	f.write(ttop(5) + "iUsed," + "\n")
	f.write(ttop(5) + "iUsed*100.0/iMaxItem);" + "\n")
	f.write(ttop(3) + "}" + "\n\n")
	f.write(ttop(3) + "rc = " + getLoadFileObjName(conf) + ".Close()" + "\n")
	f.write(ttop(3) + "RAISE_ERR(rc, RTN);" + "\n")
	genSecondHalfFunc(f, 1)

def getShmGetLengthFuncName(conf):
	memVar = conf["MemStructName"][2:-1]
	funVar = memVar + "GetLength"
	return funVar

def getShmGetTableNameFuncName(conf):
	memVar = conf["MemStructName"][2:-1]
	funVar = memVar + "MemName"
	return funVar

def getShmGetMaxItemFuncName(conf):
	memVar = conf["MemStructName"][2:-1]
	funVar = memVar + "GetMaxItem"
	return funVar

def getShmClearFuncName(conf):
	memVar = conf["MemStructName"][2:-1]
	funVar = memVar + "Clear"
	return funVar
			
def getShmInsertFuncName(conf):
	memVar = conf["MemStructName"][2:-1]
	funVar = memVar + "Insert"
	return funVar

def getFicherHndlName(conf):
	msName = conf["MemStructName"]
	return "FROM_BPC_" + msName[8:-1].upper()

def ttop(tabNum):
	spaces = ""
	for i in range(tabNum):
		spaces += " " * 4
	return spaces

def getLoadClassName(conf):
	msName = conf["MemStructName"]
	return "CLoad" + msName[8:-1].lower().capitalize()

def getFicherFileName(conf):
	ms_name = conf["MemStructName"]
	return "from_bpc_" + ms_name[8:-1].lower() + ".h"

def getLoadFileObjName(conf):
	msName = conf["MemStructName"]
	return "m_" + msName[8:-1].lower().capitalize() + "File"

def genFirstHalfFunc(f, funcName, argsStr, tabStart):
	f.write(ttop(tabStart) + "ResCodeT " + funcName + "(" + argsStr + ")" + "\n")
	f.write(ttop(tabStart) + "{" + "\n")
	f.write(ttop(tabStart + 1) + "ResCodeT rc = NO_ERR;" + "\n")
	emptylines(f,1)
	f.write(ttop(tabStart + 1) + "TRY" + "\n")
	f.write(ttop(tabStart + 1) + "{" + "\n")
	
def genSecondHalfFunc(f, tabStart):
	f.write(ttop(tabStart + 1) + "}" + "\n")
	f.write(ttop(tabStart + 1) + "CATCH" + "\n")
	f.write(ttop(tabStart + 1) + "{" + "\n")
	f.write(ttop(tabStart + 1) + "}" + "\n")
	f.write(ttop(tabStart + 1) + "FINALLY" + "\n")
	f.write(ttop(tabStart + 1) + "{" + "\n")
	f.write(ttop(tabStart + 2) + "RETURN_RESCODE;" + "\n")
	f.write(ttop(tabStart + 1) + "}" + "\n")
	f.write(ttop(tabStart) + "}" + "\n\n")

def emptylines(f, n):
	f.write("\n" * n)

def getIfmHndlName(conf):
	msName = conf["MemStructName"]
	return "IFM_BPC_" + msName[8:-1].upper()

#得到最长字段名称长度
def getMaxFieldStrLength(conf):
	maxlen = 0
	for fieldinfo in conf["MemStructFields"]:
		if maxlen < len(fieldinfo["Name"]):
			maxlen = len(fieldinfo["Name"])
	return maxlen

#计算单个文件记录长度
def getFileRecordSize(conf, sep):
	size = 0
	for fieldinfo in conf["MemStructFields"]:
		size += fieldinfo["Length"] 
	return size + len(sep) * (len(conf["MemStructFields"]) - 1)

def getIfmStruName(conf):
 	return "Rm" + conf["MemStructName"][8:-1] + "T"

def getStruHeadFileName(conf):
	return conf["ReflibInterface"] + "_stru" + ".h"

def getKeyFieldOffset(conf):
	keyoffset = 0
	for fieldinfo in conf["MemStructFields"]:
		if conf["MemKeyField"] != fieldinfo["Name"]:
			keyoffset += fieldinfo["Length"]
		else:
			return keyoffset + 8, fieldinfo["Length"], fieldinfo["Type"]

def writeFuncComment(fhndl, fname, fdesc):
	fhndl.write(genStarStartLine(73) + "\n");
	fhndl.write("* @func    : " + fname + "\n")
	fhndl.write("* @brief   : " + fdesc + "\n")
	fhndl.write("* @return  : 成功返回NO_ERR" + "\n")
	fhndl.write("* @history :" + "\n")
	fhndl.write(genStarEndLine(73) + "\n");

def genStarStartLine(n):
	return "/" + n * "*"

def genSepStarLine(n):
	return n * "*"

def genStarEndLine(n):
	return n * "*" + "/"

def writeHeadBodyOfFunc(fhndl, flag):
	fhndl.write("{" + "\n")
	if flag == 1: 
		fhndl.write(ttop(1) + "ResCodeT rc = NO_ERR;" + "\n")
	fhndl.write(ttop(1) + "TRY" + "\n")
	fhndl.write(ttop(1) + "{" + "\n")

def writeTailBodyOfFunc(fhndl):
	fhndl.write(ttop(1) + "}" + "\n")
	fhndl.write(ttop(1) + "CATCH" + "\n")
	fhndl.write(ttop(1) + "{" + "\n")
	fhndl.write(ttop(1) + "}" + "\n")
	fhndl.write(ttop(1) + "FINALLY" + "\n")
	fhndl.write(ttop(1) + "{" + "\n")
	fhndl.write(ttop(2) + "RETURN_RESCODE;" + "\n")
	fhndl.write(ttop(1) + "}" + "\n")
	fhndl.write("}" + "\n\n")

#自动得到当天日期信息
def getCurrDateStr():
    return datetime.today().strftime('%d-%b-%Y')

def writeExternCHead(fhndl):
	fhndl.write("#ifdef __cplusplus\n")
	fhndl.write("extern \"C\"{\n")
	fhndl.write("#endif\n\n\n")

def writeExternCTail(fhndl):
	fhndl.write("\n\n")
	fhndl.write("#ifdef __cplusplus\n")
	fhndl.write("}\n")
	fhndl.write("#endif\n\n")
