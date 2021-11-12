// GameUtil.h
//

#pragma once

#include "DSUtil.h"

namespace GU {

// ע��ûʹ�ù����������
#define GU_NOT_USED(x)  (x)

typedef std::basic_string<_TCHAR> String;

// ��Ҫ���û����� (�ض���Ϸ) ����Ĺ���
#define GU_USER extern

GU_USER const LPCTSTR APPTITLE;
GU_USER const int SCREENW;
GU_USER const int SCREENH;

extern String g_ResDir;
extern BOOL g_GameOver;
extern size_t g_NumConverted;

inline String GetResPath(LPCTSTR fname) {
    return (g_ResDir + _T("\\") + fname);
}

// macro to detect key presses
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

// Direct3D objects
extern LPDIRECT3D9 g_D3D;
extern LPDIRECT3DDEVICE9 g_D3DDev;
extern LPDIRECT3DSURFACE9 g_BackBuffer;
extern LPD3DXSPRITE g_SpriteObj;

// sprite structure
struct SPRITE {
    BOOL alive; // added ch14
    float x, y;
    int frame, columns;
    int width, height;
    float scaling, rotation;
    int startframe, endframe;
    int starttime, delay;
    int direction;
    float velx, vely;
    D3DCOLOR color;

    SPRITE() {
        frame = 0;
        columns = 1;
        width = height = 0;
        scaling = 1.0f;
        rotation = 0.0f;
        startframe = endframe = 0;
        direction = 1;
        starttime = delay = 0;
        velx = vely = 0.0f;
        color = D3DCOLOR_XRGB(255, 255, 255);
    }
};

template <class T>
inline void Release(__inout T*& p) {
    if (p != NULL) {
        p->Release();
        p = NULL;
    }
}

// Direct3D functions
BOOL Direct3D_Init(HWND hwnd, int width, int height, BOOL fullscreen);
void Direct3D_Shutdown();
LPDIRECT3DSURFACE9 LoadSurface(String fname);
void DrawSurface(LPDIRECT3DSURFACE9 dest, float x, float y, LPDIRECT3DSURFACE9 source);
LPDIRECT3DTEXTURE9 LoadTexture(String fname, D3DCOLOR transcolor = D3DCOLOR_XRGB(0, 0, 0));
void Sprite_Draw_Frame(LPDIRECT3DTEXTURE9 texture, int destx, int desty, int framenum, int framew, int frameh, int columns);
void Sprite_Animate(int &frame, int startframe, int endframe, int direction, int &starttime, int delay);

// added/modified in ch14
void Sprite_Transform_Draw(LPDIRECT3DTEXTURE9 image, int x, int y, int width, int height, int frame = 0, int columns = 1, float rotation = 0.0f, float scaleW = 1.0f, float scaleH = 1.0f, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
void Sprite_Transform_Draw(LPDIRECT3DTEXTURE9 image, int x, int y, int width, int height, int frame = 0, int columns = 1, float rotation = 0.0f, float scaling = 1.0f, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));

// bounding box collision detection
int Collision(SPRITE sprite1, SPRITE sprite2);

// distance based collision detection
BOOL CollisionD(SPRITE sprite1, SPRITE sprite2);

// DirectInput objects, devices, and states
extern LPDIRECTINPUT8 g_DInput;
extern LPDIRECTINPUTDEVICE8 g_DIMouse;
extern LPDIRECTINPUTDEVICE8 g_DIKeyboard;
extern DIMOUSESTATE g_MouseState;
extern XINPUT_GAMEPAD g_Controllers[4];

// DirectInput functions
BOOL DirectInput_Init(HWND);
void DirectInput_Update();
void DirectInput_Shutdown();
BOOL Key_Down(int);
int Mouse_Button(int);
int Mouse_X();
int Mouse_Y();
void XInput_Vibrate(int contNum = 0, int amount = 65535);
BOOL XInput_Controller_Found();

// game functions
GU_USER BOOL Game_Init(HWND window);
GU_USER void Game_Run(HWND window);
GU_USER void Game_End();

// font functions
LPD3DXFONT MakeFont(String name, int size);
void FontPrint(LPD3DXFONT font, int x, int y, String text, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));

// primary DirectSound object
extern CSoundManager* g_DSound;

// function prototypes
BOOL DirectSound_Init(HWND hwnd);
void DirectSound_Shutdown();
CSound* LoadSound(String fname);
void PlaySound(CSound* sound);
void LoopSound(CSound* sound);
void StopSound(CSound* sound);

// 3D Mesh code added in chapter 13

// define the MODEL struct
struct MODEL {
    LPD3DXMESH mesh;
    D3DMATERIAL9* materials;
    LPDIRECT3DTEXTURE9* textures;
    DWORD material_count;
    D3DXVECTOR3 translate;
    D3DXVECTOR3 rotate;
    D3DXVECTOR3 scale;

    MODEL() {
        material_count = 0;
        mesh = NULL;
        materials = NULL;
        textures = NULL;
        translate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        rotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
    }
};

// 3D mesh function prototypes
void DrawModel(MODEL* model);
void DeleteModel(MODEL* model);
MODEL* LoadModel(String fname);
BOOL FindFile(String* fname);
BOOL DoesFileExist(const String &fname);
void SplitPath(const String& inputPath, String* pathOnly, String* fnameOnly);
void SetCamera(float posx, float posy, float posz, float lookx = 0.0f, float looky = 0.0f, float lookz = 0.0f);

////////////////////////////////////////////////////////////////////////////////
// MBCS/Unicode ת������
////////////////////////////////////////////////////////////////////////////////

// [˵��]
//   CRT ���� mbstowcs_s �ķ�װ
//   �� MBCS �ַ��� mbstr ת��Ϊ wchar_t (UCS) �ַ��� wcstr
//
// [����]
//   mbstr          ��Ҫת���� MBCS �ַ���
//   wcstr [out]    �洢ת��Ϊ wchar_t (UCS) ���ַ��������������
//   sizeWcstr      ��������� wcstr �Ĵ�С, �� wchar_t Ϊ��λ
//   loc            ָ���� mbstr �� MBCS �ַ������Ӧ�� locale, �� loc = 0 ʱ, ʹ��ȫ�� locale
//   numConverted [out]
//                  �� wcstr != 0 ʱ, ��ʾת���˶����ַ� (�� \0), �� wchar_t Ϊ��λ
//                  �� wcstr = 0 �� sizeWcstr = 0 ʱ, ��ʾת������ mbstr ʱ (���� num),
//                  ��Ҫ����������� wcstr �Ĵ�С sizeWcstr, �� wchar_t Ϊ��λ (�� \0)
//   num            mbstr ����Ҫת��������ַ����� (���� \0), �� MBCS �ַ�Ϊ��λ
//                  ָ�� _TRUNCATE ��ʾ����ת������ mbstr, ֱ�� mbstr ��
//                  \0 ��β, ������Ϊ��������� wcstr ̫С, mbstr ���ַ������ض�
//
// [����ֵ]
//   0              �ɹ�
//   EINVAL         ��Ч�Ĳ�������
//   EILSEQ         �ַ�ӳ�����: ��ǰ locale ��, mbstr �к�����Ч�� MBCS �ַ�, �޷�ת��Ϊ wchar_t �ַ�
//   STRUNCATE      ��������� wcstr ̫С, �ַ��� mbstr ���ض�, ���ֱ�ת��
//
// [ע��]
//   �� loc = 0 ʱ, ��Ҫ���ú��ʵ�ȫ�� locale, ����ת������ȷ�� wchar_t �ַ�, ����:
//   �ַ��� mbstr = "abc����", ���ȫ�� locale Ϊ��������ʱ��Ĭ�� C locale, ��ֻ
//   �� ASCII �ַ� "abc" ����ȷת��, �� "����" ת��Ϊ����
//   ��ʱ, ����ǰӦ���ü������� locale: setlocale("chs"), ������ϵͳĬ�� locale: setlocale("")
//
inline
errno_t MbsToWcs(const char* mbstr, __out wchar_t* wcstr, size_t sizeWcstr, _locale_t loc = NULL, __out size_t* numConverted = &g_NumConverted, size_t num = _TRUNCATE) {
    if (mbstr == NULL || numConverted == NULL)
        return EINVAL;

    errno_t err;
    if (loc == NULL)
        err = mbstowcs_s(numConverted, wcstr, sizeWcstr, mbstr, num);
    else
        err = _mbstowcs_s_l(numConverted, wcstr, sizeWcstr, mbstr, num, loc);

    // �ַ�ӳ�����: ��ǰ locale ��, �޷��� MBCS �ַ�ת��Ϊ wchar_t (UCS) �ַ�
    if (*numConverted == (size_t) -1)
        return EILSEQ;

    return err;
}

// �� new ���� wcstr �洢�ռ�
// ���� MbsToWcs, �� MBCS �ַ��� mbstr ת��Ϊ wchar_t (UCS) �ַ��� wcstr
// [ע��]
//   �û������ͷ� (delete) ����� wcstr �ڴ�
inline
errno_t MbsToWcsNew(const char* mbstr, __out wchar_t*& wcstr, _locale_t loc = NULL, __out size_t* numConverted = &g_NumConverted, size_t num = _TRUNCATE) {
    // NOTE:
    // 1. mbstowcs_s ������������� wcstr = 0 ʱ, ��������С���� sizeWcstr ����Ϊ 0, ����ᱨ�������� Assert
    // 2. mbstowcs_s �õ��������������С����װ������ mbstr ת�����ַ����Ĵ�С (�� \0), �� wchar_t Ϊ��λ, ���� num Ϊ����

    // �õ���Ҫ������������Ĵ�С
    size_t sizeWcstr;
    errno_t err = MbsToWcs(mbstr, NULL, 0, loc, &sizeWcstr);
    if (err != 0)
        return err;

    // ��Ϊ NOTE 2 ��ԭ��, ����Ҫ�Ļ�������С (�� wchar_t Ϊ��λ) �� num (��Ҫת�����ַ���) ֮��ѡ���С��ֵ, ��Ϊ���� wcstr �������Ĵ�С, �Խ�ʡ�ڴ�
    if (num != _TRUNCATE)
        sizeWcstr = std::min(sizeWcstr, num + 1);

    wcstr = new(std::nothrow) wchar_t[sizeWcstr];
    if (wcstr == NULL)
        return ENOMEM;

    // ʵ��ת�� mbstr �� wcstr
    err = MbsToWcs(mbstr, wcstr, sizeWcstr, loc, numConverted, num);
    return err;
}

// [˵��]
//   CRT ���� wcstombs_s �ķ�װ
//   �� wchar_t (UCS) �ַ��� wcstr ת��Ϊ MBCS �ַ��� mbstr
//   �ο� MbsToWcs ˵��
//
// [����]
//   wcstr          ��Ҫת���� wchar_t (UCS) �ַ���
//   mbstr [out]    �洢ת��Ϊ MBCS ���ַ��������������
//   sizeMbstr      ��������� mbstr �Ĵ�С, �� byte Ϊ��λ
//   loc            ָ��ת��Ϊ MBCS �ַ�ʹ�õ��ַ��������Ӧ�� locale �� loc = 0 ʱ, ʹ��ȫ�� locale
//   numConverted [out]
//                  �� mbstr != 0 ʱ, ��ʾת��Ϊ MBCS ��, ռ����������� mbstr ���� byte (�� \0)
//                  �� mbstr = 0 �� sizeMbstr = 0 ʱ, ��ʾת������ wcstr ʱ (���� num), ��Ҫ����������� mbstr �Ĵ�С sizeMbstr, �� byte Ϊ��λ (�� \0)
//   num            ת����, ��������� mbstr ����Ҫ�洢����� byte ��
//                  ָ�� _TRUNCATE ��ʾ����ת������ wcstr, ֱ�� wcstr �� \0 ��β
//
// [ע��]
//   �� num = _TRUNCATE ʱ, �����ֽضϺ���:
//   1. ��Ϊ��������� mbstr ̫С, ֻ�в��� wcstr ��ת��, ����ת�����ַ���������
//      ��, ��ʱ WcsToMbs ���� 0, �����������ֽض�, ��Ҫ�û������ж�
//   2. ��ֻ�в��� wcstr ��ת��ʱ (1 ���ͽض�), �п��ܵ��µ����� ASCII �ַ��Ľ�
//      ��, ��ʱ WcsToMbs ���� STRUNCATE
//      ���� UCS �ַ��� "abc����" ת�� MBCS �ַ���
//      ��� sizeMbstr = 5, num = _TRUNCATE, �� locale ��Ӧ GBK �ַ���,
//      ����������� mbstr �н����� {0x61, 0x62, 0x63, 0xba, 0x00}
//      ���� 0xba �� GBK ����� "��" (0xbaba) �Ľض��ֽ�
//
inline
errno_t WcsToMbs(const wchar_t* wcstr, __out char* mbstr, size_t sizeMbstr, _locale_t loc = NULL, __out size_t* numConverted = &g_NumConverted, size_t num = _TRUNCATE) {
    if (wcstr == NULL || numConverted == NULL)
        return EINVAL;

    errno_t err;
    if (loc == NULL)
        err = wcstombs_s(numConverted, mbstr, sizeMbstr, wcstr, num);
    else
        err = _wcstombs_s_l(numConverted, mbstr, sizeMbstr, wcstr, num, loc);

    // �ַ�ӳ�����: ��ǰ locale ��, �޷��� wchar_t (UCS) �ַ�ת��Ϊ MBCS �ַ�
    // wcstombs_s ʵ�ʷ���ֵ�� VC 2005 MSDN �ο��г���, ӳ�����᷵�� EILSEQ
    if (*numConverted == (size_t) -1 || err == EILSEQ)
        return EILSEQ;

    return err;
}

// �� new ���� mbstr �洢�ռ�
// ���� WcsToMbs, �� wchar_t (UCS) �ַ��� wcstr ת��Ϊ MBCS �ַ��� mbstr
// [ע��]
//   �û������ͷ� (delete) ����� mbstr �ڴ�
inline
errno_t WcsToMbsNew(const wchar_t* wcstr, __out char*& mbstr, _locale_t loc = NULL, __out size_t* numConverted = &g_NumConverted, size_t num = _TRUNCATE) {
    // �õ���Ҫ������������Ĵ�С
    size_t sizeMbstr;   // �� byte Ϊ��λ
    errno_t err = WcsToMbs(wcstr, NULL, 0, loc, &sizeMbstr);
    if (err != 0)
        return err;

    if (num != _TRUNCATE)
        sizeMbstr = std::min(sizeMbstr, num + 1);

    mbstr = new(std::nothrow) char[sizeMbstr];
    if (mbstr == NULL)
        return ENOMEM;

    // ʵ��ת�� wcstr �� mbstr
    err = WcsToMbs(wcstr, mbstr, sizeMbstr, loc, numConverted, num);
    return err;
}

////////////////////////////////////////////////////////////////////////////////
// ת��Ϊ _TCHAR �ĺ���
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// �� char* �� basic_string<char> ת��Ϊ _TCHAR*
//
// ��ЩΪ inline ����, include ���û����̺�, �����ַ������ü� _UNICODE �������,
// ʹ�ò�ͬ�Ĵ���:
// 1. ���� _UNICODE ʱ, _TCHAR=wchar_t
//    ���� MbsToWcs �� mbstr ת��Ϊ wchar_t, �洢����������� tchar ��
//    ����ת������ mbstr, ֱ�� \0 ��β, ������Ϊ������ tchar ̫С, mbstr ���ض�
//    ����ֵ: ������������� tchar
//      a. ת���ɹ�, ���� mbstr ���ض�, tchar �д洢��ת�����ַ���
//      b. ת��ʧ��, tchar Ϊ���ַ���
// 2. δ���� _UNICODE ʱ, _TCHAR=char
//    ����ֵ: ֱ�ӷ��� char �ַ��� mbstr
////////////////////////////////////////////////////////////////////////////////

// �����ַ�������Ϊ const char*
inline
const _TCHAR* ToTchar(const char* mbstr, __out _TCHAR* tchar, size_t sizeTchar, _locale_t loc = NULL) {
#ifdef _UNICODE
    errno_t err;
    err = MbsToWcs(mbstr, tchar, sizeTchar, loc);
    if (err != 0 && err != STRUNCATE)
        *tchar = _T('\0');
    return tchar;
#else
    // _UNICODE NOT defined
    SIMP_NOT_USED(tchar);
    SIMP_NOT_USED(sizeTchar);
    return mbstr;
#endif
}

// �����ַ�������Ϊ const char*
// ģ���Զ��Ƶ���������� tchar ��С
//
// [Ҫ��]
//   tchar ������ _TCHAR[], ����ָ�� _TCHAR*
template <size_t SizeTchar>
inline
const _TCHAR* ToTchar(const char* mbstr, __out _TCHAR (&tchar)[SizeTchar], _locale_t loc = NULL) {
    return ToTchar(mbstr, tchar, SizeTchar, loc);
}

// �����ַ�������Ϊ basic_string<char>
inline
const _TCHAR* ToTchar(const std::string& mbstr, __out _TCHAR* tchar, size_t sizeTchar, _locale_t loc = NULL) {
    return ToTchar(mbstr.c_str(), tchar, sizeTchar, loc);
}

// �����ַ�������Ϊ basic_string<char>
// ģ���Զ��Ƶ���������� tchar ��С
//
// [Ҫ��]
//   tchar ������ _TCHAR[], ����ָ�� _TCHAR*
template <size_t SizeTchar>
inline
const _TCHAR* ToTchar(const std::string& mbstr, __out _TCHAR (&tchar)[SizeTchar], _locale_t loc = NULL) {
    return ToTchar(mbstr.c_str(), tchar, SizeTchar, loc);
}

////////////////////////////////////////////////////////////////////////////////
// �� wchar_t* �� basic_string<wchar_t> ת��Ϊ _TCHAR*
//
// ��ʹ�� SBCS/MBCS ����ʱ, sizeTchar Ϊ��������� tchar �� byte ��
//
// �����к���ʹ�� WcsToMbs �� wchar_t �ַ���ת��Ϊ char �ַ���ʱ, �޷����
// �� WcsToMbs �� 1 ���ͽض� (�ο� WcsToMbs ˵��), ��Ҫ�û������ж�
////////////////////////////////////////////////////////////////////////////////

// �����ַ�������Ϊ const wchar_t*
inline
const _TCHAR* ToTchar(const wchar_t* wcstr, __out _TCHAR* tchar, size_t sizeTchar, _locale_t loc = NULL) {
#ifdef _UNICODE
    GU_NOT_USED(tchar);
    GU_NOT_USED(sizeTchar);
    return wcstr;
#else
    // _UNICODE NOT defined
    errno_t err;
    err = WcsToMbs(wcstr, tchar, sizeTchar, loc);
    if (err != 0 && err != STRUNCATE)
        *tchar = _T('\0');
    return tchar;
#endif
}

// �����ַ�������Ϊ const wchar_t*
// ģ���Զ��Ƶ���������� tchar ��С
//
// [Ҫ��]
//   tchar ������ _TCHAR[], ����ָ�� _TCHAR*
template <size_t SizeTchar>
inline
const _TCHAR* ToTchar(const wchar_t* wcstr, __out _TCHAR (&tchar)[SizeTchar], _locale_t loc = NULL) {
    return ToTchar(wcstr, tchar, SizeTchar, loc);
}

// �����ַ�������Ϊ basic_string<wchar_t>
inline
const _TCHAR* ToTchar(const std::wstring& wcstr, __out _TCHAR* tchar, size_t sizeTchar, _locale_t loc = NULL) {
    return ToTchar(wcstr.c_str(), tchar, sizeTchar, loc);
}

// �����ַ�������Ϊ basic_string<wchar_t>
// ģ���Զ��Ƶ���������� tchar ��С
//
// [Ҫ��]
//   tchar ������ _TCHAR[], ����ָ�� _TCHAR*
template <size_t SizeTchar>
inline
const _TCHAR* ToTchar(const std::wstring& wcstr, __out _TCHAR (&tchar)[SizeTchar], _locale_t loc = NULL) {
    return ToTchar(wcstr.c_str(), tchar, SizeTchar, loc);
}

}   // namespace GU
