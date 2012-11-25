// GameUtil.h
//

#pragma once

#include "DSUtil.h"

namespace GU {

// 注释没使用过变量或参数
#define GU_NOT_USED(x)  (x)

typedef std::basic_string<_TCHAR> String;

// 需要在用户程序 (特定游戏) 定义的功能
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
// MBCS/Unicode 转换函数
////////////////////////////////////////////////////////////////////////////////

// [说明]
//   CRT 函数 mbstowcs_s 的封装
//   将 MBCS 字符串 mbstr 转换为 wchar_t (UCS) 字符串 wcstr
//
// [参数]
//   mbstr          需要转换的 MBCS 字符串
//   wcstr [out]    存储转换为 wchar_t (UCS) 的字符串的输出缓冲区
//   sizeWcstr      输出缓冲区 wcstr 的大小, 以 wchar_t 为单位
//   loc            指定和 mbstr 的 MBCS 字符编码对应的 locale, 当 loc = 0 时, 使用全局 locale
//   numConverted [out]
//                  当 wcstr != 0 时, 表示转换了多少字符 (含 \0), 以 wchar_t 为单位
//                  当 wcstr = 0 且 sizeWcstr = 0 时, 表示转换整个 mbstr 时 (忽略 num),
//                  需要的输出缓冲区 wcstr 的大小 sizeWcstr, 以 wchar_t 为单位 (含 \0)
//   num            mbstr 中需要转换的最大字符个数 (不含 \0), 以 MBCS 字符为单位
//                  指定 _TRUNCATE 表示尝试转换整个 mbstr, 直到 mbstr 的
//                  \0 结尾, 或者因为输出缓冲区 wcstr 太小, mbstr 中字符串被截断
//
// [返回值]
//   0              成功
//   EINVAL         无效的参数错误
//   EILSEQ         字符映射错误: 当前 locale 下, mbstr 中含有无效的 MBCS 字符, 无法转换为 wchar_t 字符
//   STRUNCATE      输出缓冲区 wcstr 太小, 字符串 mbstr 被截断, 部分被转换
//
// [注意]
//   当 loc = 0 时, 需要设置合适的全局 locale, 才能转换出正确的 wchar_t 字符, 例如:
//   字符串 mbstr = "abc汉字", 如果全局 locale 为程序启动时的默认 C locale, 则只
//   有 ASCII 字符 "abc" 被正确转换, 而 "汉字" 转换为乱码
//   此时, 调用前应设置简体中文 locale: setlocale("chs"), 或中文系统默认 locale: setlocale("")
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

    // 字符映射错误: 当前 locale 下, 无法将 MBCS 字符转换为 wchar_t (UCS) 字符
    if (*numConverted == (size_t) -1)
        return EILSEQ;

    return err;
}

// 用 new 分配 wcstr 存储空间
// 调用 MbsToWcs, 将 MBCS 字符串 mbstr 转换为 wchar_t (UCS) 字符串 wcstr
// [注意]
//   用户负责释放 (delete) 用完的 wcstr 内存
inline
errno_t MbsToWcsNew(const char* mbstr, __out wchar_t*& wcstr, _locale_t loc = NULL, __out size_t* numConverted = &g_NumConverted, size_t num = _TRUNCATE) {
    // NOTE:
    // 1. mbstowcs_s 输出缓冲区参数 wcstr = 0 时, 缓冲区大小参数 sizeWcstr 必需为 0, 否则会报参数错误 Assert
    // 2. mbstowcs_s 得到的输出缓冲区大小是能装下整个 mbstr 转换后字符串的大小 (含 \0), 以 wchar_t 为单位, 无论 num 为多少

    // 得到需要的输出缓冲区的大小
    size_t sizeWcstr;
    errno_t err = MbsToWcs(mbstr, NULL, 0, loc, &sizeWcstr);
    if (err != 0)
        return err;

    // 因为 NOTE 2 的原因, 在需要的缓冲区大小 (以 wchar_t 为单位) 和 num (需要转换的字符数) 之间选择较小的值, 作为分配 wcstr 缓冲区的大小, 以节省内存
    if (num != _TRUNCATE)
        sizeWcstr = std::min(sizeWcstr, num + 1);

    wcstr = new(std::nothrow) wchar_t[sizeWcstr];
    if (wcstr == NULL)
        return ENOMEM;

    // 实际转换 mbstr 到 wcstr
    err = MbsToWcs(mbstr, wcstr, sizeWcstr, loc, numConverted, num);
    return err;
}

// [说明]
//   CRT 函数 wcstombs_s 的封装
//   将 wchar_t (UCS) 字符串 wcstr 转换为 MBCS 字符串 mbstr
//   参考 MbsToWcs 说明
//
// [参数]
//   wcstr          需要转换的 wchar_t (UCS) 字符串
//   mbstr [out]    存储转换为 MBCS 的字符串的输出缓冲区
//   sizeMbstr      输出缓冲区 mbstr 的大小, 以 byte 为单位
//   loc            指定转换为 MBCS 字符使用的字符集编码对应的 locale 当 loc = 0 时, 使用全局 locale
//   numConverted [out]
//                  当 mbstr != 0 时, 表示转换为 MBCS 后, 占用输出缓冲区 mbstr 多少 byte (含 \0)
//                  当 mbstr = 0 且 sizeMbstr = 0 时, 表示转换整个 wcstr 时 (忽略 num), 需要的输出缓冲区 mbstr 的大小 sizeMbstr, 以 byte 为单位 (含 \0)
//   num            转换后, 输出缓冲区 mbstr 中需要存储的最多 byte 数
//                  指定 _TRUNCATE 表示尝试转换整个 wcstr, 直到 wcstr 的 \0 结尾
//
// [注意]
//   当 num = _TRUNCATE 时, 有两种截断含义:
//   1. 因为输出缓冲区 mbstr 太小, 只有部分 wcstr 被转换, 但已转换的字符都保持完
//      整, 此时 WcsToMbs 返回 0, 即不报告这种截断, 需要用户自行判断
//   2. 当只有部分 wcstr 被转换时 (1 类型截断), 有可能导致单个非 ASCII 字符的截
//      断, 此时 WcsToMbs 返回 STRUNCATE
//      例如 UCS 字符串 "abc汉字" 转换 MBCS 字符串
//      如果 sizeMbstr = 5, num = _TRUNCATE, 且 locale 对应 GBK 字符集,
//      则输出缓冲区 mbstr 中将包含 {0x61, 0x62, 0x63, 0xba, 0x00}
//      其中 0xba 是 GBK 编码的 "汉" (0xbaba) 的截断字节
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

    // 字符映射错误: 当前 locale 下, 无法将 wchar_t (UCS) 字符转换为 MBCS 字符
    // wcstombs_s 实际返回值和 VC 2005 MSDN 参考有出入, 映射错误会返回 EILSEQ
    if (*numConverted == (size_t) -1 || err == EILSEQ)
        return EILSEQ;

    return err;
}

// 用 new 分配 mbstr 存储空间
// 调用 WcsToMbs, 将 wchar_t (UCS) 字符串 wcstr 转换为 MBCS 字符串 mbstr
// [注意]
//   用户负责释放 (delete) 用完的 mbstr 内存
inline
errno_t WcsToMbsNew(const wchar_t* wcstr, __out char*& mbstr, _locale_t loc = NULL, __out size_t* numConverted = &g_NumConverted, size_t num = _TRUNCATE) {
    // 得到需要的输出缓冲区的大小
    size_t sizeMbstr;   // 以 byte 为单位
    errno_t err = WcsToMbs(wcstr, NULL, 0, loc, &sizeMbstr);
    if (err != 0)
        return err;

    if (num != _TRUNCATE)
        sizeMbstr = std::min(sizeMbstr, num + 1);

    mbstr = new(std::nothrow) char[sizeMbstr];
    if (mbstr == NULL)
        return ENOMEM;

    // 实际转换 wcstr 到 mbstr
    err = WcsToMbs(wcstr, mbstr, sizeMbstr, loc, numConverted, num);
    return err;
}

////////////////////////////////////////////////////////////////////////////////
// 转换为 _TCHAR 的函数
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// 将 char* 或 basic_string<char> 转换为 _TCHAR*
//
// 这些为 inline 函数, include 到用户工程后, 根据字符集设置即 _UNICODE 定义与否,
// 使用不同的代码:
// 1. 定义 _UNICODE 时, _TCHAR=wchar_t
//    调用 MbsToWcs 将 mbstr 转换为 wchar_t, 存储到输出缓冲区 tchar 中
//    尝试转换整个 mbstr, 直到 \0 结尾, 或者因为缓冲区 tchar 太小, mbstr 被截断
//    返回值: 返回输出缓冲区 tchar
//      a. 转换成功, 或者 mbstr 被截断, tchar 中存储已转换的字符串
//      b. 转换失败, tchar 为空字符串
// 2. 未定义 _UNICODE 时, _TCHAR=char
//    返回值: 直接返回 char 字符串 mbstr
////////////////////////////////////////////////////////////////////////////////

// 输入字符串类型为 const char*
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

// 输入字符串类型为 const char*
// 模板自动推导输出缓冲区 tchar 大小
//
// [要求]
//   tchar 是数组 _TCHAR[], 而非指针 _TCHAR*
template <size_t SizeTchar>
inline
const _TCHAR* ToTchar(const char* mbstr, __out _TCHAR (&tchar)[SizeTchar], _locale_t loc = NULL) {
    return ToTchar(mbstr, tchar, SizeTchar, loc);
}

// 输入字符串类型为 basic_string<char>
inline
const _TCHAR* ToTchar(const std::string& mbstr, __out _TCHAR* tchar, size_t sizeTchar, _locale_t loc = NULL) {
    return ToTchar(mbstr.c_str(), tchar, sizeTchar, loc);
}

// 输入字符串类型为 basic_string<char>
// 模板自动推导输出缓冲区 tchar 大小
//
// [要求]
//   tchar 是数组 _TCHAR[], 而非指针 _TCHAR*
template <size_t SizeTchar>
inline
const _TCHAR* ToTchar(const std::string& mbstr, __out _TCHAR (&tchar)[SizeTchar], _locale_t loc = NULL) {
    return ToTchar(mbstr.c_str(), tchar, SizeTchar, loc);
}

////////////////////////////////////////////////////////////////////////////////
// 将 wchar_t* 或 basic_string<wchar_t> 转换为 _TCHAR*
//
// 当使用 SBCS/MBCS 配置时, sizeTchar 为输出缓冲区 tchar 的 byte 数
//
// 当下列函数使用 WcsToMbs 从 wchar_t 字符串转换为 char 字符串时, 无法检测
// 出 WcsToMbs 的 1 类型截断 (参考 WcsToMbs 说明), 需要用户自行判断
////////////////////////////////////////////////////////////////////////////////

// 输入字符串类型为 const wchar_t*
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

// 输入字符串类型为 const wchar_t*
// 模板自动推导输出缓冲区 tchar 大小
//
// [要求]
//   tchar 是数组 _TCHAR[], 而非指针 _TCHAR*
template <size_t SizeTchar>
inline
const _TCHAR* ToTchar(const wchar_t* wcstr, __out _TCHAR (&tchar)[SizeTchar], _locale_t loc = NULL) {
    return ToTchar(wcstr, tchar, SizeTchar, loc);
}

// 输入字符串类型为 basic_string<wchar_t>
inline
const _TCHAR* ToTchar(const std::wstring& wcstr, __out _TCHAR* tchar, size_t sizeTchar, _locale_t loc = NULL) {
    return ToTchar(wcstr.c_str(), tchar, sizeTchar, loc);
}

// 输入字符串类型为 basic_string<wchar_t>
// 模板自动推导输出缓冲区 tchar 大小
//
// [要求]
//   tchar 是数组 _TCHAR[], 而非指针 _TCHAR*
template <size_t SizeTchar>
inline
const _TCHAR* ToTchar(const std::wstring& wcstr, __out _TCHAR (&tchar)[SizeTchar], _locale_t loc = NULL) {
    return ToTchar(wcstr.c_str(), tchar, SizeTchar, loc);
}

}   // namespace GU
