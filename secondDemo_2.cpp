#include"stdafx.h"
#include<iostream>
using namespace std;
#include"./gdal/gdal_priv.h"
#pragma comment(lib,"gdal_i.lib")

int main() {
	//输入图像
	GDALDataset* poSrcDS;
	//输出图像
	GDALDataset* poDstDS;
	//图像的宽度和高度
	int imgXlen, imgYlen;
	//起始位置坐标
	int StartX, StartY;
	//区域长度和宽度
	int tmpXlen, tmpYlen;
	//输入图像的路径
	char* srcPath = "square.jpg";
	//输出图像的路径
	char* dstPath = "square_1.tif";
	//图像内存存储
	GByte* buffTmp;
	//图像波段数
	int i, j, bandNum;

	//注册驱动
	GDALAllRegister();

	//打开图像
	poSrcDS = (GDALDataset*)GDALOpenShared(srcPath, GA_ReadOnly);
	//获取图像宽度，高度和波段数量
	imgXlen = poSrcDS->GetRasterXSize();
	imgYlen = poSrcDS->GetRasterYSize();
	bandNum = poSrcDS->GetRasterCount();
	//根据图像的高度和宽度分配内存
	buffTmp = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));
	//创建输出图像
	poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(dstPath, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);
	//一个波段的输入，一个波段的输出
	for (i = 0;i < bandNum;i++) {
		poSrcDS->GetRasterBand(i + 1)->RasterIO(GF_Read, 0, 0, imgXlen, imgYlen, buffTmp, imgXlen, imgYlen, GDT_Byte,0, 0);
		poDstDS->GetRasterBand(i + 1)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, buffTmp, imgXlen, imgYlen, GDT_Byte, 0, 0);
	}
	//起始位置坐标
	StartX = 300;
	StartY = 300;
	//区域宽度和高度
	tmpXlen = 100;
	tmpYlen = 50;
	//分配内存
	buffTmp = (GByte*)CPLMalloc(tmpXlen*tmpYlen * sizeof(GByte));
	//读取红色通道缓存在buffTmp中
	poSrcDS->GetRasterBand(1)->RasterIO(GF_Read, StartX, StartY, tmpXlen, tmpYlen, buffTmp, tmpXlen, tmpYlen, GDT_Byte, 0, 0);
	for (j = 0;j < tmpYlen;j++) {
		for (i = 0;i < tmpXlen;i++) {
			buffTmp[j*tmpXlen + i] = (GByte)255;
		}
	}
	//数据写入poDstDS
	poDstDS->GetRasterBand(1)->RasterIO(GF_Write, StartX, StartY, tmpXlen, tmpYlen, buffTmp, tmpXlen, tmpYlen, GDT_Byte, 0, 0);
	//读取绿色通道缓存在buffTmp中
	poSrcDS->GetRasterBand(2)->RasterIO(GF_Read, StartX, StartY, tmpXlen, tmpYlen, buffTmp, tmpXlen, tmpYlen, GDT_Byte, 0, 0);
	for (j = 0;j < tmpYlen;j++) {
		for (i = 0;i < tmpXlen;i++) {
			buffTmp[j*tmpXlen + i] = (GByte)255;
		}
	}
	//数据写入poDstDS
	poDstDS->GetRasterBand(2)->RasterIO(GF_Write, StartX, StartY, tmpXlen, tmpYlen, buffTmp, tmpXlen, tmpYlen, GDT_Byte, 0, 0);
	//读取蓝色通道缓存在buffTmp中
	poSrcDS->GetRasterBand(3)->RasterIO(GF_Read, StartX, StartY, tmpXlen, tmpYlen, buffTmp, tmpXlen, tmpYlen, GDT_Byte, 0, 0);
	for (j = 0;j < tmpYlen;j++) {
		for (i = 0;i < tmpXlen;i++) {
			buffTmp[j*tmpXlen + i] = (GByte)255;
		}
	}
	//数据写入poDstDS
	poDstDS->GetRasterBand(3)->RasterIO(GF_Write, StartX, StartY, tmpXlen, tmpYlen, buffTmp, tmpXlen, tmpYlen, GDT_Byte, 0, 0);
	
	//输入起始位置
	StartX = 500;
	StartY = 500;
	//区域宽度和高度
	tmpXlen = 50;
	tmpYlen = 100;
	//分配内存
	buffTmp = (GByte*)CPLMalloc(tmpXlen*tmpYlen * sizeof(GByte));

	//红色通道
	//读取红色通道在buffTmp中
	poSrcDS->GetRasterBand(1)->RasterIO(GF_Read, StartX, StartY, tmpXlen, tmpYlen, buffTmp, tmpXlen, tmpYlen, GDT_Byte, 0, 0);
	//遍历区域，逐像素置为255
	for (i = 0;i < tmpXlen*tmpYlen;i++) {
		buffTmp[i] = (GByte)0;
	}

	//绿色通道
	//数据写入poDstDS
	poDstDS->GetRasterBand(1)->RasterIO(GF_Write, StartX, StartY, tmpXlen, tmpYlen, buffTmp, tmpXlen, tmpYlen, GDT_Byte, 0, 0);
	//读取绿色通道在buffTmp中
	poSrcDS->GetRasterBand(2)->RasterIO(GF_Read, StartX, StartY, tmpXlen, tmpYlen, buffTmp, tmpXlen, tmpYlen, GDT_Byte, 0, 0);
	//重新赋值
	for (i = 0;i < tmpXlen*tmpYlen;i++) {
		buffTmp[i]=(GByte)0;
	}
	//数据写入
	poDstDS->GetRasterBand(2)->RasterIO(GF_Write, StartX, StartY, tmpXlen, tmpYlen, buffTmp, tmpXlen, tmpYlen, GDT_Byte, 0, 0);
	//蓝色通道
	//数据读入缓存buffTmp中
	poSrcDS->GetRasterBand(3)->RasterIO(GF_Read, StartX, StartY, tmpXlen, tmpYlen, buffTmp, tmpXlen, tmpYlen, GDT_Byte, 0, 0);
	//重新赋值
	for (i = 0;i < tmpXlen*tmpYlen;i++) {
		buffTmp[i] = (GByte)0;
	}
	//写入图片
	poDstDS->GetRasterBand(3)->RasterIO(GF_Write, StartX, StartY, tmpXlen, tmpYlen, buffTmp, tmpXlen, tmpYlen, GDT_Byte, 0, 0);
	
	
	
	
	//清除内存
	CPLFree(buffTmp);
	//关闭dataset
	GDALClose(poDstDS);
	GDALClose(poSrcDS);

	system("PAUSE");
	return 0;

}
