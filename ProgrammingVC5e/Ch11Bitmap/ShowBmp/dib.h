////////////////////////////////////////////////////////////////////////////////
// ��    �� : dib.h
// ����˵�� :
//   �豸�޹�λͼ DIB ����
//   ���� "Programming VC++, 5Ed", Ch11 Bitmaps �� CDib ��, ʾ�� ex11c
//
// ��    �� : 1.0
// ��    �� : David Kruglinski, George Shepherd, Scot Wingo
// �޸����� : Breaker Zhao <breaker.zy_AT_gmail>
// ��    �� : 2010-10
////////////////////////////////////////////////////////////////////////////////

#ifndef __DIB_H__
#define __DIB_H__

////////////////////////////////////////////////////////////////////////////////
// DIB ������ CDib
////////////////////////////////////////////////////////////////////////////////

class CDibError : public CException {
};

class CDib : public CObject {
    enum ALLOC { ALLOC_NO, ALLOC_CRT, ALLOC_HEAP };
    DECLARE_SERIAL(CDib)

public:
    CDib();
    CDib(CSize size, int nBitCount);    // builds BITMAPINFOHEADER
    ~CDib();
    void Empty();

    int GetSizeImage() {
        return m_dwSizeImage;
    }
    int GetSizeHeader() {
        return sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * m_nColorTableEntries;
    }
    CSize GetDimensions();
    BOOL AttachMapFile(const TCHAR* strPathname, BOOL bShare = FALSE);
    BOOL CopyToMapFile(const TCHAR* strPathname);
    BOOL AttachMemory(LPVOID lpvMem, BOOL bMustDelete = FALSE, HGLOBAL hGlobal = 0);
    BOOL Draw(CDC* pDC, CPoint origin, CSize size);  // until we implemnt CreateDibSection
    HBITMAP CreateSection(CDC* pDC = 0);
    UINT UsePalette(CDC* pDC, BOOL bBackground = FALSE);
    BOOL MakePalette();
    BOOL SetSystemPalette(CDC* pDC);
    BOOL Compress(CDC* pDC, BOOL bCompress = TRUE); // FALSE means decompress
    HBITMAP CreateBitmap(CDC* pDC);
    BOOL Read(CFile* pFile);
    BOOL ReadSection(CFile* pFile, CDC* pDC = 0);
    BOOL Write(CFile* pFile);
    void Serialize(CArchive& ar);

private:
    void DetachMapFile();
    void ComputePaletteSize(int nBitCount);
    void ComputeMetrics();

public:
    LPVOID              m_lpvColorTable;
    HBITMAP             m_hBitmap;
    LPBYTE              m_lpImage;      // starting address of DIB bits
    LPBITMAPINFOHEADER  m_lpBMIH;       //  buffer containing the BITMAPINFOHEADER

private:
    static const WORD BMP_MAGIC = 0x4d42;   // BM header magic in .bmp

    HGLOBAL     m_hGlobal;      // For external windows we need to free; could be allocated by this class or allocated externally
    ALLOC       m_nBmihAlloc;
    ALLOC       m_nImageAlloc;
    DWORD       m_dwSizeImage;  // of bits, not BITMAPINFOHEADER or BITMAPFILEHEADER
    int         m_nColorTableEntries;

    HANDLE      m_hFile;
    HANDLE      m_hMap;
    LPVOID      m_lpvFile;
    HPALETTE    m_hPalette;
};

#endif  // __DIB_H__
