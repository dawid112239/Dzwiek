#include<Windows.h>
#include<stdio.h>
#include "res.h"
#include <cstdlib>
#include <ctime>
#include <math.h>
#pragma comment(lib,"dsound.lib")

#include"dsound.h"
#define Pi 3.141592
#define czas 35
char *snotes = "D C C E F G A H C H A A A A G F E D F E E D C E D G C E E E E A H C H A H A G A E E E A H C H A H A G H C G F E";
char *stime = "4 16 16 8 4 16 16 16 16 8 4 16 16 16 16 8 4 16 16 16 16 8 4 16 16 16 16 8 4 16 16 16 16 8 4 16 16 16 16 8 4 16 16 16 16 8 4 16 16 16 16 8 4 16 16 16";
void muzyka(BYTE *pBufferForAudio, WAVEFORMATEX pcmWaveFormat, char *snotes, char *stime);
int Note(BYTE* pBufferForAudio, int iStart, int iDuration, float fNote, float fDiv);
int echo(BYTE* pBufferForAudio, int iStart, int iDuration, int iDelay, float iAttenaute);
int echo3(BYTE* pBufferForAudio, int iStart, int iDuration, int iDelay1, float fAttenaute1, int iDelay2, float fAttenaute2, int iDelay3, float fAttenaute3);
CHAR szText[5];
float f1 = 440;
float f2 = 880;
float f;

float fC = 261.626;
float fD = 293.7;
float fE = 329.628;
float fF = 349.228;
float fG = 391.995;
float fA = 444.000;
float fH = 493.883;

bool isGameOnn = true;
bool isFirstPlayer = true;
int pola[3][3];
bool krzyzykWygral = false;
int licznik = 0;
HINSTANCE hthinstance;
HBITMAP Plansza;
HBITMAP kolko;
HBITMAP krzyzyk;
HDC Okno;
void OdswiezPlansze(HWND hwndMainWindow);
void RysujRuch(HWND hwndMainWindow, int x, int y);
void UsunBitmapki();

bool wygrana()
{
  int zmienna = -10;
  for (int i = 0; i < 3; i++)
  {
    if ((pola[i][0]==pola[i][1]) && (pola[i][0]==pola[i][2]) && (pola[i][0] != -1))
    {
      isGameOnn = false;
      if (pola[i][0] == 1)
      {
        krzyzykWygral = true;
      }
      return true;
    }
  }
  for (int i = 0; i < 3; i++)
  {
    if ((pola[0][i] == pola[1][i]) && (pola[0][i] == pola[2][i]) && (pola[0][i] != -1))
    {
      isGameOnn = false;
      if (pola[0][i] == 1)
      {
        krzyzykWygral = true;
      }
      return true;
    }
  }
  if ((pola[0][0] == pola[1][1]) && (pola[0][0] == pola[2][2]) && (pola[1][1] != -1))
  {
    isGameOnn = false;
    if (pola[0][0] == 1)
    {
      krzyzykWygral = true;
    }
    return true;
  }
  if ((pola[2][0] == pola[1][1]) && (pola[2][0] == pola[0][2]) && (pola[1][1] != -1))
  {
    isGameOnn = false;
    if (pola[1][1] == 1)
    {

      krzyzykWygral = true;
    }
    return true;
  }
  return false;
}

void OdswiezPlansze(HWND hwndMainWindow)
{
  HBRUSH PendzelBialy, Pudelko;
  PendzelBialy = CreateSolidBrush(0xFFFFFF);
  Pudelko = (HBRUSH)SelectObject(Okno, PendzelBialy);
  const RECT dolny = { 20,20,320,320 };
  FillRect(Okno, &dolny, PendzelBialy);
  SelectObject(Okno, Pudelko);
  DeleteObject(PendzelBialy);
  DeleteObject(Pudelko);

  HDC hdcNowy = CreateCompatibleDC(Okno);
  HDC hdc = GetDC(hwndMainWindow);
  SelectObject(hdcNowy, Plansza);
  HBITMAP hbmOld = (HBITMAP)SelectObject(hdcNowy, Plansza);
  BITMAP bmInfo;
  GetObject(Plansza, sizeof(bmInfo), &bmInfo);
  StretchBlt(hdc, 20, 20, 300, 300, hdcNowy, 0, 0, 300, 300, SRCCOPY);
  ReleaseDC(hwndMainWindow, hdc);
  SelectObject(hdcNowy, hbmOld);
  DeleteDC(hdcNowy);
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if (pola[i][j] != -1)
        RysujRuch(hwndMainWindow, i, j);
    }
  }
}

void RysujRuch(HWND hwndMainWindow, int x, int y)
{
  int wspx=(x  * 100) + 20;
  int wspy= (y * 100) + 20;
  if (pola[x][y] == 1)
  {
    HDC hdcNowy = CreateCompatibleDC(Okno);
    HDC hdc = GetDC(hwndMainWindow);
    SelectObject(hdcNowy, krzyzyk);
    HBITMAP hbmOld = (HBITMAP)SelectObject(hdcNowy, krzyzyk);
    BITMAP bmInfo;
    GetObject(krzyzyk, sizeof(bmInfo), &bmInfo);
    StretchBlt(hdc, wspx, wspy, 100, 100, hdcNowy, 0, 0, 100, 100, SRCCOPY);
    ReleaseDC(hwndMainWindow, hdc);
    SelectObject(hdcNowy, hbmOld);
    DeleteDC(hdcNowy);
  }
  if (pola[x][y] == 0)
  {
    HDC hdcNowy = CreateCompatibleDC(Okno);
    HDC hdc = GetDC(hwndMainWindow);
    SelectObject(hdcNowy, kolko);
    HBITMAP hbmOld = (HBITMAP)SelectObject(hdcNowy, kolko);
    BITMAP bmInfo;
    GetObject(kolko, sizeof(bmInfo), &bmInfo);
    StretchBlt(hdc, wspx, wspy, 100, 100, hdcNowy, 0, 0, 100, 100, SRCCOPY);
    ReleaseDC(hwndMainWindow, hdc);
    SelectObject(hdcNowy, hbmOld);
    DeleteDC(hdcNowy);
  }
}

void UsunBitmapki()
{
  DeleteObject(Plansza);
  DeleteObject(kolko);
  DeleteObject(krzyzyk);
}


INT_PTR CALLBACK DialogProc(HWND hwndDig, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
  case WM_COMMAND:
    
    switch (HIWORD(wParam))
    {
    case BN_CLICKED:
      switch (LOWORD(wParam))
      {

      case IDC_BUTTON1:
      case IDC_BUTTON2:
      case IDC_BUTTON3:
      case IDC_BUTTON4:
      case IDC_BUTTON5:
      case IDC_BUTTON6:
      case IDC_BUTTON7:
      case IDC_BUTTON8:
      case IDC_BUTTON9:
      { 
      
        if (isGameOnn == true)
        {
          int znacznik = LOWORD(wParam);
          znacznik = znacznik - 1007;
          int x = znacznik % 3;
          int y = znacznik / 3;
          if (pola[x][y] == -1)
          {
            if (isFirstPlayer == true)
            {
              HWND hwndButton = (HWND)lParam;
              if (GetWindowTextLength(hwndButton) == 0)
              {
                licznik++;
                //  CHAR szText[500];
                 // wsprintf(szText, "X");
                 // SetWindowText(hwndButton, szText);
                isFirstPlayer = false;
                CheckRadioButton(hwndDig, IDC_RADIO1, IDC_RADIO2, IDC_RADIO2);

              }
            }
            else
            {
              HWND hwndButton = (HWND)lParam;
              if (GetWindowTextLength(hwndButton) == 0)
              {
                licznik++;
                // CHAR szText[500];
                // wsprintf(szText, "O");
                // SetWindowText(hwndButton, szText);
                isFirstPlayer = true;
                CheckRadioButton(hwndDig, IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
              }
            }

            if (isFirstPlayer == false)
              pola[x][y] = 1;
            else
              pola[x][y] = 0;
            OdswiezPlansze(hwndDig);




            if (wygrana() == true)
            {
              isGameOnn = false;
              if (krzyzykWygral == true)
              {
                HWND hwndStatic = GetDlgItem(hwndDig, IDC_STATIC1);
                CHAR szText[500];
                wsprintf(szText, "Brawo pierwszy gracz wygra³, aby zagraæ ponownie - restart");
                SetWindowText(hwndStatic, szText);
              }
              else
              {
                HWND hwndStatic = GetDlgItem(hwndDig, IDC_STATIC1);
                CHAR szText[500];
                wsprintf(szText, "Brawo drugi gracz wygra³, aby zagraæ ponownie - restart");
                SetWindowText(hwndStatic, szText);
              }
            }
          }
          if ((licznik == 9) && (wygrana() == false))
          {
            isGameOnn = false;
            HWND hwndStatic = GetDlgItem(hwndDig, IDC_STATIC1);
            CHAR szText[500];
            wsprintf(szText, "Brak roztrzygniêcia - restart");
            SetWindowText(hwndStatic, szText);
          }
        }
        return TRUE;
      }

      case IDC_BUTTON10:
        krzyzykWygral = false;
        isGameOnn = true;
        licznik = 0;
        CheckRadioButton(hwndDig, IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
        HWND hwndStatic = GetDlgItem(hwndDig, IDC_STATIC1);
        CHAR szText[500];
        wsprintf(szText, "");
        SetWindowText(hwndStatic, szText);
        isFirstPlayer = true;
        for (int i = 0; i < 9; i++) 
        {
          HWND hwndButton = GetDlgItem(hwndDig, IDC_BUTTON1 + i);
          CHAR szText[500];
          wsprintf(szText, "");
          SetWindowText(hwndButton, szText);
          if (i < 3)
          {
            for (int j = 0; j < 3; j++)
            {
              pola[i][j]=-1;
            }
          }

        }
        OdswiezPlansze(hwndDig);
        return TRUE;

      }

      return FALSE;

    }


    return FALSE;
    case WM_INITDIALOG:
      Plansza = LoadBitmap(hthinstance, MAKEINTRESOURCE(105));
      krzyzyk = LoadBitmap(hthinstance, MAKEINTRESOURCE(106));
      kolko = LoadBitmap(hthinstance, MAKEINTRESOURCE(107));
      return TRUE;
    case WM_PAINT:
      OdswiezPlansze(hwndDig);
      return FALSE;
  case WM_CLOSE:
    DestroyWindow(hwndDig);
    PostQuitMessage(0);
    UsunBitmapki();
    return TRUE;
  }
  return FALSE;
}



int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevinstance, PSTR szCmdLIne, int iCmdShow)
{
  srand((unsigned int)time(NULL));
  hthinstance = hinstance;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      pola[i][j] = -1;
    }
  }
  HWND hwndMainWindow = CreateDialog(hinstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);
  ShowWindow(hwndMainWindow, iCmdShow);
  MSG msg = {};
  CheckRadioButton(hwndMainWindow, IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
  Okno = GetDC(hwndMainWindow);

  WAVEFORMATEX pcmWaveFormat;
  pcmWaveFormat.wFormatTag = WAVE_FORMAT_PCM;
  pcmWaveFormat.nChannels = 1;
  pcmWaveFormat.nSamplesPerSec = 44100L;
  pcmWaveFormat.wBitsPerSample = 8;
  pcmWaveFormat.nAvgBytesPerSec = pcmWaveFormat.nSamplesPerSec*pcmWaveFormat.wBitsPerSample / 8;
  pcmWaveFormat.nBlockAlign = 1; 
  pcmWaveFormat.cbSize = 0;

  MMRESULT mmResult;
  HWAVEOUT hwo = 0;
  UINT devId;
  IDirectSound8 *DS8 = NULL;
  BYTE *pBufferForAudio = new BYTE[pcmWaveFormat.nAvgBytesPerSec * czas];


  WAVEHDR whdr;

  ZeroMemory(&whdr, sizeof(WAVEHDR));
  whdr.lpData = (LPSTR)pBufferForAudio;
  whdr.dwBufferLength = czas * pcmWaveFormat.nAvgBytesPerSec;
  muzyka(pBufferForAudio, pcmWaveFormat, snotes, stime);
  echo3(pBufferForAudio, 0, whdr.dwBufferLength, 44000 / 3.0, 0.5, 44000 / 2.0, 0.4, 34000, 0.3);
  DirectSoundCreate8(NULL, &DS8, NULL);
  if (DS8 == NULL)
  {
    MessageBox(0, TEXT("Nie mozna  ..."), TEXT("Error"), MB_OK);
  }
  if (DS8->SetCooperativeLevel(hwndMainWindow, DSSCL_NORMAL) != DS_OK)
  {
    MessageBox(0, TEXT("qqq"), TEXT("Komunikat"), MB_OK);
    return true;
  }

  IDirectSoundBuffer *DSB;
  DSBUFFERDESC DSBD;
  memset(&DSBD, 0, sizeof(DSBUFFERDESC));
  DSBD.dwSize = sizeof(DSBUFFERDESC);
  DSBD.dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY;
  DSBD.dwBufferBytes = whdr.dwBufferLength;
  DSBD.lpwfxFormat = &pcmWaveFormat;
  if (DS8->CreateSoundBuffer(&DSBD, &DSB, NULL) != DS_OK)
  {
    MessageBox(0, TEXT("aaa"), TEXT("Komunikat"), MB_OK);
    return true;
  }

  DSB->SetVolume(0xFFFF);
  void *ptr1 = NULL, *ptr2 = NULL;
  DWORD l1, l2;
  DSB->Lock(0, whdr.dwBufferLength, &ptr1, &l1, &ptr2, &l2, DSBLOCK_ENTIREBUFFER);//blokowanie bufora
  if (ptr1) memcpy(ptr1, pBufferForAudio, l1);
  if (ptr2) memcpy(ptr2, pBufferForAudio + l1, l2);
  DSB->Unlock(ptr1, l1, ptr2, l2);

  DSB->Play(0, 0, 0);



  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  DSB->Release();
  delete[] pBufferForAudio;

  return 0;
}

void muzyka(BYTE *pBufferForAudio, WAVEFORMATEX pcmWaveFormat, char *snotes, char *stime)
{
  float S = pcmWaveFormat.nAvgBytesPerSec;
  float nuta;
  float czasNuty;
  int i = 0;
  int k = 0;
  for (int j = 0; j < 2 * sizeof(snotes); j += 2)
  {
    czasNuty = ((int)stime[j]) / 16.0;
    switch (snotes[j])
    {
    case 'C': nuta = fC; break;
    case 'D': nuta = fD; break;
    case 'E': nuta = fE; break;
    case 'F': nuta = fF; break;
    case 'G': nuta = fG; break;
    case 'A': nuta = fA; break;
    case 'H': nuta = fH; break;
    }
    // i= Note(pBufferForAudio, i, 0.25*S, fC, pcmWaveFormat.nSamplesPerSec);
    // i = Note(pBufferForAudio, i, 0.125*S, fG, pcmWaveFormat.nSamplesPerSec);
    //i = Note(pBufferForAudio, i, 0.5*S, fE, pcmWaveFormat.nSamplesPerSec);

    k = Note(pBufferForAudio, k, czasNuty*S, nuta, pcmWaveFormat.nSamplesPerSec);
  }
}

int Note(BYTE* pBufferForAudio, int iStart, int iDuration, float fNote, float fDiv)
{
  int i;
  for (i = iStart; i < iStart + iDuration - 200; i++)
  {
    float t = i / fDiv;
    // pBufferForAudio[i] = ((128 * sin(2 * Pi*fNote*t) + 128) + (128 * sin(2 * Pi*fNote*t*2.0 / 3.0) + 128)) / 2;//dwa rozne tony
    pBufferForAudio[i] = ((128 * sin(2 * Pi*fNote*t) + 128) + (128 * sin(2 * Pi*fNote*t*1.0 / 2.0) + 128)) / 2;//dwie rozne gamy
  }
  for (; i < iStart + iDuration; i++)
  {
    float t = i / fDiv;
    pBufferForAudio[i] = 128;
  }
  return i;
}

int echo(BYTE* pBufferForAudio, int iStart, int iDuration, int iDelay, float iAttenaute)
{
  //zrobic 3 echa
  BYTE *tmp = new BYTE[iDuration];
  memcpy(tmp, pBufferForAudio, iDuration);
  for (int i = 0; i < iDuration; i++)
  {
    if (i - iDelay > 0)
      //pBufferForAudio[i] = (tmp[i] + tmp[i - iDelay] * iAttenaute / (1.0 + iAttenaute));
      pBufferForAudio[i] = ((tmp[i] - 128.0) + (tmp[i - iDelay] - 128.0) * iAttenaute) / (1.0 + iAttenaute) + 128;
    else
    {
      pBufferForAudio[i] = tmp[i];
    }
  }
  delete[]tmp;
  return 0;
}

int echo3(BYTE* pBufferForAudio, int iStart, int iDuration, int iDelay1, float fAttenaute1,int iDelay2, float fAttenaute2, int iDelay3, float fAttenaute3)
{
  BYTE *tmp = new BYTE[iDuration];
  int iSample1 = 0;
  int iSample2 = 0;
  int iSample3 = 0;
  memcpy(tmp, pBufferForAudio, iDuration);
  for (int i = 0; i < iDuration; i++)
  {
    if (i - iDelay1 > 0)
      iSample1 = tmp[i - iDelay1] - 128.0;
    if (i - iDelay2 > 0)
    {
      iSample2 = tmp[i - iDelay2] - 128.0;
    }
    if (i - iDelay3 > 0)
    {
      iSample3 = tmp[i - iDelay3] - 128.0;
    }
    //pBufferForAudio[i] = (tmp[i] + tmp[i - iDelay] * iAttenaute / (1.0 + iAttenaute));
    pBufferForAudio[i] = ((tmp[i] - 128.0) + iSample1*fAttenaute1 + iSample2*fAttenaute2 + iSample3*fAttenaute3)
      / (1.0 + fAttenaute1 + fAttenaute2 + fAttenaute3) + 128;
  }
  delete[]tmp;
  return 0;
}