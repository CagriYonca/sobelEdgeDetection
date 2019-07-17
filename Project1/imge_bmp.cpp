#include "stdafx.h"
#include <windows.h>
#include <iostream>

int row1 = 0, col1 = 0, row2 = 0, col2 = 0, i = 0, seviye = 1;
double deger, *PixelGradient;
BYTE* newbuf, *nonMaximum, *histerize;
int *kutleMerkezi, *alan, *feature;
//Pikselleri iceren bufferi dosyadan al
BYTE* LoadBMP(int% width, int% height, long% size, LPCTSTR bmpfile)	//pixelleri tutmak icin LPCTSTR kullanilir
{
	// declare bitmap structures
	BITMAPFILEHEADER bmpheader;
	BITMAPINFOHEADER bmpinfo;
	// value to be used in ReadFile funcs
	DWORD bytesread;
	// HANDLE ile yazılacak dosyayı çağır
	HANDLE file = CreateFile(bmpfile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (NULL == file)
		return NULL; // coudn't open file

					 // read file header
	if (ReadFile(file, &bmpheader, sizeof(BITMAPFILEHEADER), &bytesread, NULL) == false) {
		CloseHandle(file);
		return NULL;
	}
	//read bitmap info
	if (ReadFile(file, &bmpinfo, sizeof(BITMAPINFOHEADER), &bytesread, NULL) == false) {
		CloseHandle(file);
		return NULL;
	}
	// check if file is actually a bmp
	if (bmpheader.bfType != 'MB') {
		CloseHandle(file);
		return NULL;
	}
	// get image measurements
	width = bmpinfo.biWidth;
	height = abs(bmpinfo.biHeight);

	// check if bmp is uncompressed
	if (bmpinfo.biCompression != BI_RGB) {
		CloseHandle(file);
		return NULL;
	}
	// check if we have 24 bit bmp
	if (bmpinfo.biBitCount != 24) {
		CloseHandle(file);
		return NULL;
	}

	// create buffer to hold the data
	size = bmpheader.bfSize - bmpheader.bfOffBits;
	BYTE* Buffer = new BYTE[size];		//buffer pixel size kadar uretilir
										// move file pointer to start of bitmap data
	SetFilePointer(file, bmpheader.bfOffBits, NULL, FILE_BEGIN);
	// read bmp data
	if (ReadFile(file, Buffer, size, &bytesread, NULL) == false) {
		delete[] Buffer;
		CloseHandle(file);
		return NULL;
	}
	// everything successful here: close file and return buffer
	CloseHandle(file);

	return Buffer;
}//LOADPMB
 //Bufferdeki pikselleri dosyaya yaz
bool SaveBMP(BYTE* Buffer, int width, int height, long paddedsize, LPCTSTR bmpfile)
{
	// declare bmp structures 
	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER info;

	// andinitialize them to zero
	memset(&bmfh, 0, sizeof(BITMAPFILEHEADER));
	memset(&info, 0, sizeof(BITMAPINFOHEADER));

	// fill the fileheader with data
	bmfh.bfType = 0x4d42;       // 0x4d42 = 'BM'
	bmfh.bfReserved1 = 0;
	bmfh.bfReserved2 = 0;
	bmfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + paddedsize;
	bmfh.bfOffBits = 0x36;		// number of bytes to start of bitmap bits

								// fill the infoheader

	info.biSize = sizeof(BITMAPINFOHEADER);
	info.biWidth = width;
	info.biHeight = height;
	info.biPlanes = 1;			// we only have one bitplane
	info.biBitCount = 24;		// RGB mode is 24 bits
	info.biCompression = BI_RGB;
	info.biSizeImage = 0;		// can be 0 for 24 bit images
	info.biXPelsPerMeter = 0x0ec4;     // paint and PSP use this values
	info.biYPelsPerMeter = 0x0ec4;
	info.biClrUsed = 0;			// we are in RGB mode and have no palette
	info.biClrImportant = 0;    // all colors are important

								// now we open the file to write to
	HANDLE file = CreateFile(bmpfile, GENERIC_WRITE, FILE_SHARE_READ,
		NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (file == NULL) {
		CloseHandle(file);
		return false;
	}
	// write file header
	unsigned long bwritten;
	if (WriteFile(file, &bmfh, sizeof(BITMAPFILEHEADER), &bwritten, NULL) == false) {
		CloseHandle(file);
		return false;
	}
	// write infoheader
	if (WriteFile(file, &info, sizeof(BITMAPINFOHEADER), &bwritten, NULL) == false) {
		CloseHandle(file);
		return false;
	}
	// write image data
	if (WriteFile(file, Buffer, paddedsize, &bwritten, NULL) == false) {
		CloseHandle(file);
		return false;
	}

	// and close file
	CloseHandle(file);

	return true;
} // SaveBMP
  //Resmi grilestir
BYTE* ConvertBMPToIntensity(BYTE* Buffer, int width, int height)
{
	// first make sure the parameters are valid
	if ((NULL == Buffer) || (width == 0) || (height == 0))
		return NULL;

	// find the number of padding bytes

	int padding = 0;
	int scanlinebytes = width * 3;
	while ((scanlinebytes + padding) % 4 != 0)     // DWORD = 4 bytes
		padding++;
	// get the padded scanline width
	int psw = scanlinebytes + padding;

	// create new buffer
	newbuf = new BYTE[width*height];

	// now we loop trough all bytes of the original buffer, 
	// swap the R and B bytes and the scanlines
	long bufpos = 0;
	long newpos = 0;
	for (row1 = 0; row1 < height; row1++)
		for (col1  = 0; col1  < width; col1 ++) {	//Resmin degerlerini grilestir
			newpos = row1 * width + col1 ;
			bufpos = (height - row1 - 1) * psw + col1  * 3;
			newbuf[newpos] = BYTE(0.11*Buffer[bufpos + 2] + 0.59*Buffer[bufpos + 1] + 0.3*Buffer[bufpos]);
		}

	return newbuf;
}//ConvertBMPToIntensity
 //Resmi parcala
BYTE* ResmiBuyut(BYTE* Buffer, int width, int height, int type[]) {
	int new_width = 2 * width + 1;
	int new_height = 2 * height + 1;

	newbuf = new BYTE[new_height * new_width];
	long newpos = 0;
	int deger = 0;
	for (row1 = 0; row1 < new_height; row1++) {
		for (col1  = 0; col1  < new_width; col1 ++) {
				newpos = row1 * new_width + col1 ;
			if (col1  % 2 == 0 || row1 % 2 == 0) {
				newbuf[newpos] = 0;
			}
			else {
				newbuf[newpos] = BYTE(Buffer[deger++]);
			}
		}
	}
	return newbuf;
}
//Parcalarin arasindaki bosluklari doldur 
BYTE* TaraBMP(BYTE* Buffer, int width, int height, int maske[]) {
	newbuf = new BYTE[(width - 2) * (height - 2)];
	for (row1 = 0; row1 < (height - 2); row1++) {
		for (col1 = 0; col1 < (width - 2); col1++) {
			deger = 0;
			i = 0; 
			for (row2 = row1; row2 < row1 + 3; row2++) {
				for (col2 = col1; col2 < col1 + 3; col2++) {
					deger += Buffer[row2*width + col2] * maske[i++];
				}
			}
			newbuf[row1 * (width - 2) + col1] = BYTE(deger);
			
		}
	}

	return newbuf;
}

BYTE* Temizle(BYTE* Buffer, int width, int height) {
	int new_width = width - 2, new_height = height - 2;
	newbuf = new BYTE[new_width * new_height];

	for (row1 = 0; row1 < new_height - 1; row1++) {
		for (col1 = 0; col1< new_width - 1; col1++) {
			if (Buffer[(row1 + 1)*new_width + new_height + 1] > Buffer[row1*new_width + new_height]) {
				newbuf[row1*new_width + new_height] = 0;
			}
			else {
				newbuf[row1*new_width + new_height] = Buffer[row1*new_width + new_height];
			}
		}
	}

	return newbuf;
}
//Bufferdeki piksel sayilarini renk dizisinde tut
BYTE* histogramEq(BYTE* Buffer, int width, int height) {
	newbuf = new BYTE[width*height];
	int* hist = new int[256];				//Renk tablosu olusturuldu
	
	//Dizileri sıfırlar
	for (i = 0; i < 256; i++) {
		hist[i] = 0;						//Bize buffer ile gelen degerler renk bilgisi
	}

	for (i = 0; i < width*height; i++) {
		hist[Buffer[i]]++;					//Gelen renklerin hangi renk oldugunu bolumledik
	}

	int onceki_sayi = 0;
	for (i = 0; i < 256; i++) {			//Renklerin olması gereken renkleri bulduk
		onceki_sayi += hist[i];				//Bunda 255 ile carpmaz ve önceki sayiyi tutmazsan PMF bulunur
		hist[i] = (onceki_sayi * 255) / (width*height);
	}

	for (i = 0; i < width*height; i++) {
		newbuf[i] = hist[Buffer[i]];
	}
	
	return newbuf;
}
//Bufferdeki bilgileri BMPye cevir
int* histogramGonder(BYTE* Buffer, int width, int height) {
	int* hist = new int[256];
	for (i = 0; i < 256; i++) {
		hist[i] = 0;
	}

	for (i = 0; i < width*height; i++) {
		hist[Buffer[i]]++;
	}
	return hist;
}

BYTE* Mahalanobis(BYTE* Buffer, int width, int height) {
	int* hist = new int[256];				//Renk tablosu olusturuldu

	for (i = 0; i < 256; i++) {
		hist[i] = 0;
	}

	for (i = 0; i < width*height; i++) {
		hist[Buffer[i]]++;
	}

	/* T değerleri atanıyor */
	int t1 = rand() % 256,
		t2 = rand() % 256,
		t1onceki = 0,
		t2onceki = 0,
		t1Sayisi,
		t2Sayisi;

	while (t1 != t1onceki) {
		t1onceki = t1;
		t1 = 0;
		t2onceki = t2;
		t2 = 0;
		t1Sayisi = 0;
		t2Sayisi = 0;
		for (i = 0; i < 256; i++) {
			if (fabs(t1onceki - i) < fabs(t2onceki - i)) {
				t1 += i * hist[i];
				t1Sayisi += hist[i];
			}
			else {
				t2 += i * hist[i];
				t2Sayisi += hist[i];
			}
		}
		t1 /= t1Sayisi;
		t2 /= t2Sayisi;
	}
	int sapma1 = 0, sapma2 = 0;
	t1Sayisi = 0, t2Sayisi = 0;
	for (i = 0; i < 256; i++) {
		if (fabs(t1 - i) < fabs(t2 - i)) {
			sapma1 += (hist[i] - hist[t1])*(hist[i] - hist[t1]);
			++t1Sayisi;
		}
		else {
			sapma2 += (hist[i] - hist[t2])*(hist[i] - hist[t2]);
			++t2Sayisi;
		}
	}
	sapma1 = (int) (sqrt(sapma1 /= (t1Sayisi - 1)));
	sapma2 = (int) (sqrt(sapma2 /= (t2Sayisi - 1)));
	
	return Buffer;
}

BYTE* Euclid(BYTE* Buffer, int width, int height) {
	long unsigned int* hist = new long unsigned int[256];				//Renk tablosu olusturuldu

	for (i = 0; i < 256; i++) {
		hist[i] = 0;
	}

	for (i = 0; i < width*height; i++) {
		hist[Buffer[i]]++;
	}

	newbuf = new BYTE[width*height];

	/* T değerleri atanıyor */
	int t1 = 50, 
		t2 = 200, 
		t1onceki = 0,
		t2onceki = 0,
		t1Sayisi = 0,
		t2Sayisi = 0;
	
	while (t1 != t1onceki) {
		t1onceki = t1;
		t2onceki = t2;
		t1 = 0;
		t2 = 0;
		for (i = 0; i < 256; i++) {
			if (fabs(i - t1onceki) < fabs(i - t2onceki)) {
				t1 += i*hist[i];
				t1Sayisi += hist[i];
			}
			else {
				t2 += i*hist[i];
				t2Sayisi += hist[i];
			}
		}
		t1 /= t1Sayisi;
		t2 /= t2Sayisi;
		t1Sayisi = 0;
		t2Sayisi = 0;
	}

	for (i = 0; i < width*height; i++) {
		if (fabs(t1onceki - Buffer[i]) < fabs(t2onceki - Buffer[i])) {
			newbuf[i] = 0;
		}
		else {
			newbuf[i] = 255;
		}
	}
	
	return newbuf;
}

BYTE* Dilation(BYTE* Buffer, int width, int height) {
	newbuf = new BYTE[width*height];
	for (i = 0; i < width*height; i++) {
		newbuf[i] = Buffer[i];
	}

	for (row1 = 1; row1 < (height - 1); row1++) {
		for (col1 = 1; col1 < (width - 1); col1++) {
			if (Buffer[row1*width + col1] == 0) {
				for (row2 = row1 - 1; row2 < row1 + 2; row2++) {
					for (col2 = col1 - 1; col2 < col1 + 2; col2++) {
						newbuf[row2*width + col2] = 0;
					}
				}
				//Dilation ve erotion ekleyip sınırlarını çiz, ardından feature ekleyip bitir.
			}
		}
	}
	

	return newbuf;
}

BYTE* Erotion(BYTE* Buffer, int width, int height) {
	newbuf = new BYTE[width*height];
	int bayrak;
	for (i = 0; i < width*height; i++) {
		newbuf[i] = Buffer[i];
	}

	for (row1 = 1; row1 < (height - 1); row1++) {
		for (col1 = 1; col1 < (width - 1); col1++) {
			if (Buffer[row1*width + col1] == 0) {
				bayrak = 0;
				for (row2 = row1 - 1; row2 < row1 + 2; row2++) {
					for (col2 = col1 - 1; col2 < col1 + 2; col2++) {
						if (Buffer[row2*width + col2] != 0) {
							++bayrak;
						}
					}
				}
				if (bayrak != 0) {
					newbuf[row1*width + col1] = 255;
				}
			}
		}
	}

	return newbuf;
}

int* Etiketle(BYTE* Buffer, int width, int height) {

	int *ilketiket = new int[8];

	int komsuSayisi,
		minSeviye,
		j;

	for (i = 0; i < 8; i++) {
		ilketiket[i] = 0;
	}

	int *etiketTutucu = new int[width*height];
	int *collisionTutucu = new int[width*height];

	newbuf = new BYTE[width*height];
	for (i = 0; i < width*height; i++) {
		/* Gelen nesneler güzel gözükmesi için 0 olarak geliyor, onları 255'e cevir */
		newbuf[i] = 255 - Buffer[i];
		etiketTutucu[i] = 0;
		collisionTutucu[i] = 0;
	}

	/* Etiketleme */
	for (row1 = 1; row1 < height - 1; row1++) {
		for (col1 = 1; col1 < width - 1; col1++) {
			if (newbuf[row1*width + col1] == 255) {
				minSeviye = width * height;
				komsuSayisi = 0;
				for (row2 = row1 - 1; row2 < row1 + 1; row2++) {
					for (col2 = col1 - 1; col2 < col1 + 2; col2++) {
						if (etiketTutucu[row2*width + col2] != 0) {
							komsuSayisi++;
							if (minSeviye > etiketTutucu[row2*width + col2]) {
								minSeviye = etiketTutucu[row2*width + col2];
							}
						}
					}
				}

				if (komsuSayisi == 0) {
					etiketTutucu[row1*width + col1] = seviye++;
				}

				else if (komsuSayisi == 1) {
					etiketTutucu[row1*width + col1] = minSeviye;
				}

				else {
					collisionTutucu[row1*width + col1] = 1;
					etiketTutucu[row1*width + col1] = minSeviye;
				}
			}
		}
	}


	// Collision Detection
	for (row1 = 1; row1 < height - 1; row1++) {
		for (col1 = 1; col1 < width - 1; col1++) {
			if (collisionTutucu[row1*width + col1] == 1) {
				//Çevresindeki etiketlere bak
				j = 0;
				minSeviye = width * height;
				for (row2 = row1 - 1; row2 < row1 + 2; row2++) {
					for (col2 = col1 - 1; col2 < col1 + 2; col2++, j++) {
						if (etiketTutucu[row2*width + col2] != 0) {
							ilketiket[j] = etiketTutucu[row2*width + col2];
							if (minSeviye > etiketTutucu[row2*width + col2]) {
								minSeviye = etiketTutucu[row2*width + col2];
							}
						}
					}
				}

				//Etiketleri işle
				for (i = 0; i < 8; i++) {
					if (ilketiket[i] > minSeviye) {
						for (row2 = 1; row2 < height - 1; row2++) {
							for (col2 = 1; col2 < width - 1; col2++) {
								if (etiketTutucu[row2*width + col2] == ilketiket[i]) {
									etiketTutucu[row2*width + col2] = minSeviye;
								}
							}
						}
					}
					ilketiket[i] = 0;
				}
			}
		}
	}
	seviye = 1;
	return etiketTutucu;
}

int* EtiketSirala(int* etiketli, int width, int height) {
	int* newbuf = new int[width*height];
	int k = 1, flag = 0;

	for (i = 0; i < seviye + 1; i++) {
		if (flag == 0) {
			for (int j = 0; j < width*height; j++) {
				if (etiketli[j] == i)	flag = 1;
			}
		}
		if (flag == 1) {
			for (int j = 0; j < width*height; j++) {
				if (etiketli[j] == i)	newbuf[j] = k;
			}
			++k;
			--flag;
		}
	}

	return newbuf;
}

int* Feature(int* etiketli, int width, int height, int nesneSayisi, int tipSayisi) {
	//Nesnelerin cevresini, alanini ve kutle merkezini hesapla
	alan = new int[nesneSayisi];
	for (row1 = 0; row1 < height; row1++) {
		for (col1 = 0; col1 < width; col1++) {
			if (etiketli[row1*width + col1] != 0) {
				alan[etiketli[row1*width + col1] - 1]++;
			}
		}
	}

	feature = new int[nesneSayisi];
	for (i = 0; i < nesneSayisi; i++) {
		feature[i] = alan[i] * kutleMerkezi[i];
	}

	int* tip = new int[tipSayisi];
	for (i = 0; i < tipSayisi; i++) {
		tip[i] = i * 50;
	}

	for (row1 = 0; row1 < nesneSayisi; row1++) {
		for (col1 = 0; col1 < nesneSayisi; col1++) {

		}
	}

	return feature;
}

BYTE* MutlakToplam(BYTE* Buffer1, BYTE* Buffer2, int width, int height) {
	newbuf = new BYTE[width*height];

	for (i = 0; i < width*height; i++) {
		newbuf[i] = fabs(Buffer1[i]) + fabs(Buffer2[i]);
	}

	return newbuf;
}

double* KenarYonu(BYTE* Buffer1, BYTE* Buffer2, int width, int height) {
	double* newbuf = new double[width*height];

	for (i = 0; i < width*height; i++) {
		if ((Buffer1[i] != 0) && (Buffer2[i] != 0)) {
			newbuf[i] = atan2(Buffer1[i], Buffer2[i]);		//y/x
		}
		else {
			newbuf[i] = 0;
		}
	}

	return newbuf;
}

BYTE* LoGFilter(BYTE* Buffer, int width, int height) {

	newbuf = new BYTE[(width - 4) * (height - 4)];
	int filter[25] = {0,0,-1,0,0,0,-1,-2,-1,0,-1,-2,16,-2,-1,0,-1,-2,-1,0,0,0,-1,0,0};
	for (row1 = 0; row1 < height - 4; row1++) {
		for (col1 = 0; col1 < width - 4; col1++) {
			i = 0;
			deger = 0;
			for (row2 = row1; row2 < row1 + 5; row2++) {
				for (col2 = col1; col2 < col1 + 5; col2++) {
					deger += (Buffer[row2*width + col2] * filter[i++]);
				}
			}
			newbuf[row1*(width - 4) + col1] = BYTE(deger);
		}
	}

	return newbuf;
}

BYTE* Smooth(BYTE* Buffer, int width, int height) {
	newbuf = new BYTE[(width - 4) * (height - 4)];
	int filter[25] = {1/26,1/16,1/7,1/16,1/26,1/16,1/4,1,1/4,1/16,1/7,1,2,1,1/7,1/16,1/4,1,1/4,1/16,1/26,1/16,1/7,1/16,1/26};
	for (row1 = 0; row1 < height - 4; row1++) {
		for (col1 = 0; col1 < width - 4; col1++) {
			i = 0;
			deger = 0;
			for (row2 = row1; row2 < row1 + 5; row2++) {
				for (col2 = col1; col2 < col1 + 5; col2++) {
					deger += Buffer[row2*width + col2] * filter[i++];
				}
			}
			newbuf[row1*(width - 4) + col1] = BYTE(deger);
		}
	}

	return newbuf;
}

BYTE* HoughUzayi(BYTE* Buffer, int width, int height) {
	double* HoughSpace = new double[width*height];
	
	for (i = 0; i < width*height; i++) {
		HoughSpace[i] = 0;
	}

	for (row1 = 0; row1 < height; row1++) {
		for (col1 = 0; col1 < width; col1++) {
			if (Buffer[row1*width + col1] != 0) {
				if ((PixelGradient[row1*width + height] < 55) && (PixelGradient[row1*width + height] > 35)) {			//egim dikey, kenar yatay
					HoughSpace[row1*width + col1] = row1 * cos(45) + col1 * sin(45);
				}
				else if ((PixelGradient[row1*width + height] < 100) && (PixelGradient[row1*width + height] > 80)) {													//egim yatay, kenar dikey
					HoughSpace[row1*width + col1] = row1 * cos(90) + col1 * sin(90);
				}
				else if ((PixelGradient[row1*width + height] < 145) && (PixelGradient[row1*width + height] > 125)) {			//egim dikey, kenar yatay
					HoughSpace[row1*width + col1] = row1 * cos(135) + col1 * sin(135);
				}
				else if ((PixelGradient[row1*width + height] < 20) && (PixelGradient[row1*width + height] >= 0)) {													//egim yatay, kenar dikey
					HoughSpace[row1*width + col1] = row1 * cos(0) + col1 * sin(0);
				}
			}
		}
	}
	int j;
	double *degerSayisi = new double[width*height];
	for (i = 0;i < width*height; i++) {
		degerSayisi[i] = 0;
		if (HoughSpace[i] != 0) {
			for (j = i; j < width*height; j++) {
				if (HoughSpace[j] == HoughSpace[i]) {
					degerSayisi[i]++;
					HoughSpace[j] = 0;
				}
			}
		}
	}

	for (i = 0; i < width*height; i++) {
		if (degerSayisi[i] > 50) {
			newbuf[i] = 255;
		}
		else {
			newbuf[i] = 0;
		}
	}

	return newbuf;
}

BYTE* ikiDusur(BYTE* Buffer, int width, int height) {
	for (row1 = 1; row1 < height - 1; row1++) {
		for (col1 = 1; col1 < width - 1; col1++) {
			newbuf[row1*width + col1] = Buffer[row1*width + col1];
		}
	}

	return newbuf;
}

BYTE* Birlestir(BYTE* Buffer, BYTE* Buffer2, int width, int height) {
	//raw intensityden 6 cikart, width height uyusmuyor
	for (row1 = 0; row1 < height; row1++) {
		for (col1 = 0; col1 < width; col1++) {
			if (Buffer2[row1*width + col1] != 0) {
				newbuf[row1*width + col1] = 255;
			}
			else {
			//	newbuf[row1*width + col1] = Buffer[row1*width + col1];
			}
		}
	}

	return newbuf;
}

BYTE* Gradient(BYTE* Buffer, int width, int height) {
	BYTE* Smoothed = Smooth(Buffer, width, height);
	width -= 4;
	height -= 4;
	int xYonunde[9] = {1,2,1,0,0,0,-1,-2,-1};			//Burdan gelen matristeki degerler 256dan buyuk
	BYTE* xYonu = TaraBMP(Smoothed, width, height, xYonunde);
	int yYonunde[9] = { -1,0,1,-2,0,2,-1,0,1 };
	BYTE* yYonu = TaraBMP(Smoothed, width, height, yYonunde);
	width -= 2;
	height -= 2;
	BYTE* Mutlak = MutlakToplam(xYonu, yYonu, width, height);			//gradient buyuklugu
	PixelGradient = KenarYonu(xYonu, yYonu, width, height);		//gradient yonunu bulduk, 1'den buyukse dikey, degilse yatay
	
	//Nonmaximum suppression, gradient yonunde kendinden buyuk olmayanlari sil
	for (row1 = 0; row1 < height; row1++) {
		for (col1 = 0; col1 < width; col1++) {
			if (Mutlak[row1*width + col1] != 0) {
				if ((PixelGradient[row1*width + height] < 55) && (PixelGradient[row1*width + height] > 35)) {			//egim dikey, kenar yatay
					if ((Mutlak[(row1 + 1)*width + col1 - 1] < Mutlak[row1*width + col1])) {
						Mutlak[(row1 + 1)*width + col1 - 1] = 0;
					}
					if ((Mutlak[(row1 - 1)*width + col1 + 1] < Mutlak[row1*width + col1])) {
						Mutlak[(row1 - 1)*width + col1 + 1] = 0;
					}
				}
				else if ((PixelGradient[row1*width + height] < 100) && (PixelGradient[row1*width + height] > 80)) {													//egim yatay, kenar dikey
					if ((Mutlak[(row1 - 1)*width + col1] < Mutlak[row1*width + col1])) {
						Mutlak[(row1 - 1)*width + col1] = 0;
					}
					if ((Mutlak[(row1 + 1)*width + col1] < Mutlak[row1*width + col1])) {
						Mutlak[(row1 + 1)*width + col1] = 0;
					}
				}
				else if ((PixelGradient[row1*width + height] < 145) && (PixelGradient[row1*width + height] > 125)) {			//egim dikey, kenar yatay
					if ((Mutlak[(row1 - 1)*width + col1 - 1] < Mutlak[row1*width + col1])) {
						Mutlak[(row1 - 1)*width + col1 - 1] = 0;
					}
					if ((Mutlak[(row1 + 1)*width + col1 + 1] < Mutlak[row1*width + col1])) {
						Mutlak[(row1 + 1)*width + col1 + 1] = 0;
					}
				}
				else if ((PixelGradient[row1*width + height] < 20) && (PixelGradient[row1*width + height] >= 0)) {													//egim yatay, kenar dikey
					if ((Mutlak[row1*width + col1 + 1] < Mutlak[row1*width + col1])) {
						Mutlak[row1*width + col1 + 1] = 0;
					}
					if ((Mutlak[row1*width + col1 - 1] < Mutlak[row1*width + col1])) {
						Mutlak[row1*width + col1 - 1] = 0;
					}
				}
			}
		}
	}
	
	
	//Hysteresis Threshold
	for (row1 = 0; row1 < height; row1++) {
		for (col1 = 0; col1 < width; col1++) {
			if (Mutlak[row1*width + col1] != 0) {
				if ((fabs(Mutlak[row1*width + col1] - 255)) < fabs(Mutlak[row1*width + col1 - 0])) {
					Mutlak[row1*width + col1] = 255;
				}
				else {
					Mutlak[row1*width + col1] = 0;
				}
			}
		}
	}
	


	return Mutlak;
}

BYTE* NonMaximum(BYTE* Buffer,int width, int height) {
	BYTE* Smoothed = Smooth(Buffer, width, height);
	width -= 4;
	height -= 4;
	int xYonunde[9] = { 1,2,1,0,0,0,-1,-2,-1 };			//Burdan gelen matristeki degerler 256dan buyuk
	BYTE* xYonu = TaraBMP(Smoothed, width, height, xYonunde);
	int yYonunde[9] = { -1,0,1,-2,0,2,-1,0,1 };
	BYTE* yYonu = TaraBMP(Smoothed, width, height, yYonunde);
	width -= 2;
	height -= 2;
	BYTE* Mutlak = MutlakToplam(xYonu, yYonu, width, height);			//gradient buyuklugu
	PixelGradient = KenarYonu(xYonu, yYonu, width, height);		//gradient yonunu bulduk, 1'den buyukse dikey, degilse yatay

																//Nonmaximum suppression, gradient yonunde kendinden buyuk olmayanlari sil
	for (row1 = 0; row1 < height; row1++) {
		for (col1 = 0; col1 < width; col1++) {
			if (Mutlak[row1*width + col1] != 0) {
				if ((PixelGradient[row1*width + height] < 55) && (PixelGradient[row1*width + height] > 35)) {			//egim dikey, kenar yatay
					if ((Mutlak[(row1 + 1)*width + col1 - 1] < Mutlak[row1*width + col1])) {
						Mutlak[(row1 + 1)*width + col1 - 1] = 0;
					}
					if ((Mutlak[(row1 - 1)*width + col1 + 1] < Mutlak[row1*width + col1])) {
						Mutlak[(row1 - 1)*width + col1 + 1] = 0;
					}
				}
				else if ((PixelGradient[row1*width + height] < 100) && (PixelGradient[row1*width + height] > 80)) {													//egim yatay, kenar dikey
					if ((Mutlak[(row1 - 1)*width + col1] < Mutlak[row1*width + col1])) {
						Mutlak[(row1 - 1)*width + col1] = 0;
					}
					if ((Mutlak[(row1 + 1)*width + col1] < Mutlak[row1*width + col1])) {
						Mutlak[(row1 + 1)*width + col1] = 0;
					}
				}
				else if ((PixelGradient[row1*width + height] < 145) && (PixelGradient[row1*width + height] > 125)) {			//egim dikey, kenar yatay
					if ((Mutlak[(row1 - 1)*width + col1 - 1] < Mutlak[row1*width + col1])) {
						Mutlak[(row1 - 1)*width + col1 - 1] = 0;
					}
					if ((Mutlak[(row1 + 1)*width + col1 + 1] < Mutlak[row1*width + col1])) {
						Mutlak[(row1 + 1)*width + col1 + 1] = 0;
					}
				}
				else if ((PixelGradient[row1*width + height] < 20) && (PixelGradient[row1*width + height] >= 0)) {													//egim yatay, kenar dikey
					if ((Mutlak[row1*width + col1 + 1] < Mutlak[row1*width + col1])) {
						Mutlak[row1*width + col1 + 1] = 0;
					}
					if ((Mutlak[row1*width + col1 - 1] < Mutlak[row1*width + col1])) {
						Mutlak[row1*width + col1 - 1] = 0;
					}
				}
			}
		}
	}

	return Mutlak;
}


int Say(int* Buffer, int width, int height) {
	int* max = new int[width*height];
	int maxDeger = 0;
	for (i = 0; i < width*height; i++) {
		max[i] = 0;
	}

	for (row1 = 0; row1 < height; row1++) {
		for (col1 = 0; col1 < width; col1++) {
			if (Buffer[row1*width + col1] != 0) {
				if (max[Buffer[row1*width + col1]] == 0) {
					max[Buffer[row1*width + col1]]++;
					maxDeger++;
				}
			}
		}
	}

	return maxDeger;
}

BYTE* Boundary(int* Buffer, int width, int height, int nesneSayisi) {
	newbuf = new BYTE[width*height];
	kutleMerkezi = new int[nesneSayisi];
	for (i = 0; i < width*height; i++) {
		if (Buffer[i] != 0) {
			newbuf[i] = 0;
		}
		else {
			newbuf[i] = 255;
		}
	}
	int minX, maxX, minY, maxY;

	for (int etiket = 1; etiket < nesneSayisi*4; etiket++) {
		minX = width;
		maxX = 0;
		minY = height;
		maxY = 0;
		for (row1 = 0; row1 < height; row1++) {
			for (col1 = 0; col1 < width; col1++) {
				if (Buffer[row1*width + col1] == etiket) {
					if (row1 < minY) minY = row1;
					if (row1 > maxY) maxY = row1;
					if (col1 < minX) minX = col1;
					if (col1 > maxX) maxX = col1;
				}
			}
		}

		for (row1 = 4; row1 < (height - 4); row1++) {
			for (col1 = 4; col1 < (width - 4); col1++) {
				if ( ( ((row1 == (minY - 4)) || (row1 == (maxY + 4))) && ((col1 > minX) && (col1 < maxX)) ) || ( ((col1 == (minX - 4)) || (col1 == (maxX + 4))) && ((row1 > minY) && (row1 < maxY)) ) ) {
					newbuf[row1*width + col1] = 0;
				}
			}
		}
		
	}

	return newbuf;
}


// Normalde farklı renk verme işlemi burada yapılacak
BYTE* Yazdir(int* Buffer, int width, int height) {
	newbuf = new BYTE[width*height];

	for (row1 = 0; row1 < height; row1++) {
		for (col1 = 0; col1 < width; col1++) {
			if (Buffer[row1*width + col1] != 0) {
				newbuf[row1*width + col1] = 0;	//nesneleri siyah yazdir
			}
			else {
				newbuf[row1*width + col1] = 255;
			}
		}
	}

	return newbuf;
}

BYTE* Negative(BYTE* Buffer, int width, int height) {
	for (i = 0; i < width*height; i++) {
		Buffer[i] = 255 - Buffer[i];
	}

	return Buffer;
}

BYTE* Logative(BYTE* Buffer, int width, int height, int constant) {
	for (i = 0; i < width*height; i++) {
		Buffer[i] = (int)(constant * log(Buffer[i] + 1));
	}

	return Buffer;
}

BYTE* Powerative(BYTE* Buffer, int width, int height,int constant) {
	for (i = 0; i < width*height; i++) {
		Buffer[i] = (int)(constant*pow(Buffer[i],(1/2.5)));
	}

	return Buffer;
}

BYTE* BlurBMP(BYTE* Buffer, int width, int height) {
	newbuf = new BYTE[(width - 2) * (height - 2)];
	int deger = 0;
	long newpos = 0;

	for (row1 = 1; row1 < height - 1; row1++) {
		for (col1 = 1; col1 < width - 1; col1++) {
			newpos = (row1 - 1) * (width - 2) + (col1 - 1);
			for (row2 = row1 - 1; row2 < row1 + 2; row2++) {
				for (col2 = col1 - 1; col2 < col1 + 2; col2++) {
					deger += Buffer[row2*width + col2] / 9;
				}
			}
			newbuf[newpos] = BYTE(deger);
			deger = 0;
		}
	}
	return newbuf;
}

BYTE* ConvertIntensityToBMP(BYTE* Buffer, int width, int height, long* newsize)
{
	// first make sure the parameters are valid
	if ((NULL == Buffer) || (width == 0) || (height == 0))
		return NULL;

	// now we have to find with how many bytes
	// we have to pad for the next DWORD boundary	

	int padding = 0;
	int scanlinebytes = (width) * 3;
	while ((scanlinebytes + padding) % 4 != 0)     // DWORD = 4 bytes
		padding++;
	// get the padded scanline width
	int psw = scanlinebytes + padding;
	// we can already store the size of the new padded buffer
	*newsize = (height)* psw;

	// and create new buffer
	newbuf = new BYTE[*newsize];

	// fill the buffer with zero bytes then we dont have to add
	// extra padding zero bytes later on
	memset(newbuf, 0, *newsize);

	// now we loop trough all bytes of the original buffer, 
	// swap the R and B bytes and the scanlines
	long bufpos = 0;
	long newpos = 0;
	for (row1 = 0; row1 < (height); row1++)
		for (col1  = 0; col1  < (width); col1 ++) {
			bufpos = row1 * (width)+col1 ;     // bulundugu koordinati bulur
			newpos = ((height)-row1 - 1) * psw + col1  * 3;           // position in padded buffer
			newbuf[newpos] = Buffer[bufpos];       //  blue
			newbuf[newpos + 1] = Buffer[bufpos];   //  green
			newbuf[newpos + 2] = Buffer[bufpos];   //  red
		}

	return newbuf;
} //ConvertIntensityToBMP
