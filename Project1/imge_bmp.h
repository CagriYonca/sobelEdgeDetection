#include <windows.h>
#include <math.h>

BYTE* LoadBMP(int% width, int% height, long% size, LPCTSTR bmpfile);
bool  SaveBMP(BYTE* Buffer, int width, int height, long paddedsize, LPCTSTR bmpfile);
BYTE* ConvertBMPToIntensity(BYTE* Buffer, int width, int height);
BYTE* ConvertIntensityToBMP(BYTE* Buffer, int width, int height, long* newsize);
BYTE* ResmiBuyut(BYTE* Buffer, int width, int height,int type[]);
BYTE* TaraBMP(BYTE* Buffer, int width, int height, int maske[]);
BYTE* Temizle(BYTE* Buffer, int width, int height);
BYTE* histogramEq(BYTE* Buffer, int width, int height);
BYTE* Negative(BYTE* Buffer, int width, int height);
BYTE* Logative(BYTE* Buffer, int width, int height, int constant);
BYTE* Powerative(BYTE* Buffer, int width, int height, int constant);
BYTE* BlurBMP(BYTE* Buffer, int width, int height);
BYTE* Birlestir(BYTE* Buffer, BYTE* Buffer2, int width, int height);
BYTE* Euclid(BYTE* Buffer, int width, int height);
BYTE* Mahalanobis(BYTE* Buffer, int width, int height);
int* histogramGonder(BYTE* Buffer, int width, int height);
int* Etiketle(BYTE* Buffer, int width, int height);
int* EtiketSirala(int* etiketli, int width, int height, int nesneSayisi);
BYTE* Yazdir(int* Buffer, int width, int height);
int Say(int* Buffer, int width, int height);
BYTE* Dilation(BYTE* Buffer, int width, int height);
BYTE* Erotion(BYTE* Buffer, int width, int height);
BYTE* Boundary(int* Buffer, int width, int height, int size);
BYTE* Gradient(BYTE* Buffer, int width, int height);
BYTE* HoughUzayi(BYTE* Buffer, int width, int height);
int* Feature(int* etiket, int width, int height, int nesneSayisi, int tipSayisi);
BYTE* MutlakToplam(BYTE* Buffer1, BYTE* Buffer2, int width, int height);
double* KenarYonu(BYTE* Buffer1, BYTE* Buffer2, int width, int height);
BYTE* LoGFilter(BYTE* Buffer, int width, int height);
BYTE* Smooth(BYTE* Buffer, int width, int height);
BYTE* ikiDusur(BYTE* Buffer, int width, int height);
BYTE* NonMaximum(BYTE* Buffer, int width, int height);
