#include"stdafx.h"
#include<iostream>
using namespace std;
#include"./gdal/gdal_priv.h"
#pragma comment(lib,"gdal_i.lib")

int main() {
	//����ͼ��
	GDALDataset* poSrcDS;
	//���ͼ��
	GDALDataset* poDstDS;
	//ͼ��Ŀ�Ⱥ͸߶�
	int imgXlen, imgYlen;
	//��ʼλ������
	int StartX, StartY;
	//���򳤶ȺͿ��
	int tmpXlen, tmpYlen;
	//����ͼ���·��
	char* srcPath = "square.jpg";
	//���ͼ���·��
	char* dstPath = "square_1.tif";
	//ͼ���ڴ�洢
	GByte* buffTmp;
	//ͼ�񲨶���
	int i, j, bandNum;

	//ע������
	GDALAllRegister();

	//��ͼ��
	poSrcDS = (GDALDataset*)GDALOpenShared(srcPath, GA_ReadOnly);
	//��ȡͼ���ȣ��߶ȺͲ�������
	imgXlen = poSrcDS->GetRasterXSize();
	imgYlen = poSrcDS->GetRasterYSize();
	bandNum = poSrcDS->GetRasterCount();
	//����ͼ��ĸ߶ȺͿ�ȷ����ڴ�
	buffTmp = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));
	//�������ͼ��
	poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(dstPath, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);
	//һ�����ε����룬һ�����ε����
	for (i = 0;i < bandNum;i++) {
		poSrcDS->GetRasterBand(i + 1)->RasterIO(GF_Read, 0, 0, imgXlen, imgYlen, buffTmp, imgXlen, imgYlen, GDT_Byte,0, 0);
		poDstDS->GetRasterBand(i + 1)->RasterIO(GF_Write, 0, 0, imgXlen, imgYlen, buffTmp, imgXlen, imgYlen, GDT_Byte, 0, 0);
	}
	//��ʼλ������
	StartX = 300;
	StartY = 300;
	//�����Ⱥ͸߶�
	tmpXlen = 100;
	tmpYlen = 50;
	//�����ڴ�
	buffTmp = (GByte*)CPLMalloc(tmpXlen*tmpYlen * sizeof(GByte));
	//��ȡ��ɫͨ��������buffTmp��
	poSrcDS->GetRasterBand(1)->RasterIO(GF_Read, StartX, StartY, tmpXlen, tmpYlen, buffTmp, tmpXlen, tmpYlen, GDT_Byte, 0, 0);
	for (j = 0;j < tmpYlen;j++) {
		for (i = 0;i < tmpXlen;i++) {
			buffTmp[j*tmpXlen + i] = (GByte)255;
		}
	}
	//����д��poDstDS
	poDstDS->GetRasterBand(1)->RasterIO(GF_Write, StartX, StartY, tmpXlen, tmpYlen, buffTmp, tmpXlen, tmpYlen, GDT_Byte, 0, 0);
	//��ȡ��ɫͨ��������buffTmp��
	poSrcDS->GetRasterBand(2)->RasterIO(GF_Read, StartX, StartY, tmpXlen, tmpYlen, buffTmp, tmpXlen, tmpYlen, GDT_Byte, 0, 0);
	for (j = 0;j < tmpYlen;j++) {
		for (i = 0;i < tmpXlen;i++) {
			buffTmp[j*tmpXlen + i] = (GByte)255;
		}
	}
	//����д��poDstDS
	poDstDS->GetRasterBand(2)->RasterIO(GF_Write, StartX, StartY, tmpXlen, tmpYlen, buffTmp, tmpXlen, tmpYlen, GDT_Byte, 0, 0);
	//��ȡ��ɫͨ��������buffTmp��
	poSrcDS->GetRasterBand(3)->RasterIO(GF_Read, StartX, StartY, tmpXlen, tmpYlen, buffTmp, tmpXlen, tmpYlen, GDT_Byte, 0, 0);
	for (j = 0;j < tmpYlen;j++) {
		for (i = 0;i < tmpXlen;i++) {
			buffTmp[j*tmpXlen + i] = (GByte)255;
		}
	}
	//����д��poDstDS
	poDstDS->GetRasterBand(3)->RasterIO(GF_Write, StartX, StartY, tmpXlen, tmpYlen, buffTmp, tmpXlen, tmpYlen, GDT_Byte, 0, 0);
	
	//������ʼλ��
	StartX = 500;
	StartY = 500;
	//�����Ⱥ͸߶�
	tmpXlen = 50;
	tmpYlen = 100;
	//�����ڴ�
	buffTmp = (GByte*)CPLMalloc(tmpXlen*tmpYlen * sizeof(GByte));

	//��ɫͨ��
	//��ȡ��ɫͨ����buffTmp��
	poSrcDS->GetRasterBand(1)->RasterIO(GF_Read, StartX, StartY, tmpXlen, tmpYlen, buffTmp, tmpXlen, tmpYlen, GDT_Byte, 0, 0);
	//����������������Ϊ255
	for (i = 0;i < tmpXlen*tmpYlen;i++) {
		buffTmp[i] = (GByte)0;
	}

	//��ɫͨ��
	//����д��poDstDS
	poDstDS->GetRasterBand(1)->RasterIO(GF_Write, StartX, StartY, tmpXlen, tmpYlen, buffTmp, tmpXlen, tmpYlen, GDT_Byte, 0, 0);
	//��ȡ��ɫͨ����buffTmp��
	poSrcDS->GetRasterBand(2)->RasterIO(GF_Read, StartX, StartY, tmpXlen, tmpYlen, buffTmp, tmpXlen, tmpYlen, GDT_Byte, 0, 0);
	//���¸�ֵ
	for (i = 0;i < tmpXlen*tmpYlen;i++) {
		buffTmp[i]=(GByte)0;
	}
	//����д��
	poDstDS->GetRasterBand(2)->RasterIO(GF_Write, StartX, StartY, tmpXlen, tmpYlen, buffTmp, tmpXlen, tmpYlen, GDT_Byte, 0, 0);
	//��ɫͨ��
	//���ݶ��뻺��buffTmp��
	poSrcDS->GetRasterBand(3)->RasterIO(GF_Read, StartX, StartY, tmpXlen, tmpYlen, buffTmp, tmpXlen, tmpYlen, GDT_Byte, 0, 0);
	//���¸�ֵ
	for (i = 0;i < tmpXlen*tmpYlen;i++) {
		buffTmp[i] = (GByte)0;
	}
	//д��ͼƬ
	poDstDS->GetRasterBand(3)->RasterIO(GF_Write, StartX, StartY, tmpXlen, tmpYlen, buffTmp, tmpXlen, tmpYlen, GDT_Byte, 0, 0);
	
	
	
	
	//����ڴ�
	CPLFree(buffTmp);
	//�ر�dataset
	GDALClose(poDstDS);
	GDALClose(poSrcDS);

	system("PAUSE");
	return 0;

}
