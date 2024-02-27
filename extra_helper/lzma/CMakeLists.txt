project("lzma")

# 添加要编译的静态库源文件
set(SOURCES
	7zAlloc.c
	7zArcIn.c
	7zBuf.c
	7zBuf2.c
	7zCrc.c
	7zCrcOpt.c
	7zDec.c
	7zFile.c
	7zStream.c
	Aes.c
	AesOpt.c
	Alloc.c
	Bcj2.c
	Bcj2Enc.c
	Bra.c
	Bra86.c
	BraIA64.c
	CpuArch.c
	Delta.c
	DllSecur.c
	LzFind.c
	LzFindMt.c
	LzFindOpt.c
	lzma.cpp
	Lzma2Dec.c
	Lzma2DecMt.c
	Lzma2Enc.c
	Lzma86Dec.c
	Lzma86Enc.c
	LzmaDec.c
	LzmaEnc.c
	LzmaLib.c
	MtCoder.c
	MtDec.c
	Ppmd7.c
	Ppmd7Dec.c
	Ppmd7Enc.c
	Sha256.c
	Sha256Opt.c
	Sort.c
	SwapBytes.c
	Threads.c
	Xz.c
	XzCrc64.c
	XzCrc64Opt.c
	XzDec.c
	XzEnc.c
	XzIn.c
	lzma.cpp
)

# 生成静态库
add_library(lzma STATIC ${SOURCES})

