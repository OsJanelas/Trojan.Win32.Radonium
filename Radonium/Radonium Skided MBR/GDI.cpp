#include <windows.h>
#include <iostream>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <vector>

// --- TEXT, SHAKE AND INVERTING ---

void TextoRadonium() {
    int signX = 1, signY = 1, x = 10, y = 10;
    while (true) {
        HDC hdc = GetDC(0);
        x += 10 * signX; y += 10 * signY;
        SetBkMode(hdc, TRANSPARENT);
        SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
        HFONT font = CreateFontA(43, 32, 0, 0, FW_BLACK, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, "Arial Black");
        SelectObject(hdc, font);
        TextOutA(hdc, x, y, "RADONIUM", 8);
        if (y >= GetSystemMetrics(1) || y <= 0) signY *= -1;
        if (x >= GetSystemMetrics(0) || x <= 0) signX *= -1;
        Sleep(10);
        DeleteObject(font);
        ReleaseDC(0, hdc);
    }
}

void EfeitoTremor() {
    while (true) {
        HDC hdc = GetDC(0);
        BitBlt(hdc, rand() % 2, rand() % 2, GetSystemMetrics(0), GetSystemMetrics(1), hdc, rand() % 2, rand() % 2, SRCCOPY);
        ReleaseDC(0, hdc);
        Sleep(10);
    }
}

void InversaoCores() {
    while (true) {
        HDC hdc = GetDC(0);
        PatBlt(hdc, 0, 0, GetSystemMetrics(0), GetSystemMetrics(1), PATINVERT);
        ReleaseDC(0, hdc);
        Sleep(100);
    }
}

// --- MORE EFFECTS ---

// MELT
void EfeitoCatarata() {
    Sleep(5000);
    while (true) {
        HDC hdc = GetDC(NULL);
        int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
        int rx = rand() % w;
        BitBlt(hdc, rx, 5, 100, h, hdc, rx, 0, SRCCOPY);
        ReleaseDC(NULL, hdc);
        Sleep(5);
    }
}

// MINI TEXTS
void TextoAleatorioRadonium() {
    Sleep(15000);
    while (true) {
        HDC hdc = GetWindowDC(GetDesktopWindow());
        SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
        SetBkColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
        TextOutW(hdc, rand() % GetSystemMetrics(0), rand() % GetSystemMetrics(1), L"Radonium.exe", 12);
        ReleaseDC(GetDesktopWindow(), hdc);
        Sleep(10);
    }
}

// PLGBLT AND CUBES
void EfeitoDistorcaoEZoom() {
    Sleep(40000);
    while (true) {
        HDC hdc = GetDC(0);
        int x = GetSystemMetrics(0), y = GetSystemMetrics(1);

        // CUBES
        StretchBlt(hdc, -5, -5, x + 5, y + 5, hdc, 0, 0, x, y, SRCCOPY);
        StretchBlt(hdc, 5, 5, x - 5, y - 5, hdc, 0, 0, x, y, SRCCOPY);

        // PLGBLT
        HDC hdcMem = CreateCompatibleDC(hdc);
        HBITMAP bm = CreateCompatibleBitmap(hdc, x, y);
        SelectObject(hdcMem, bm);
        POINT pt[3] = { {rand() % 10, rand() % 10}, {x - rand() % 10, rand() % 10}, {rand() % 10, y - rand() % 10} };
        PlgBlt(hdcMem, pt, hdc, 0, 0, x, y, 0, 0, 0);
        BitBlt(hdc, rand() % 20, rand() % 20, x, y, hdcMem, rand() % 20, rand() % 20, 0x123456);

        DeleteObject(bm); DeleteObject(hdcMem);
        ReleaseDC(0, hdc);
        Sleep(10);
    }
}

// CIRCLES
void ci(int x, int y, int w, int h) {
    HDC hdc = GetDC(0);
    HRGN hrgn = CreateEllipticRgn(x, y, w + x, h + y);
    SelectClipRgn(hdc, hrgn);
    BitBlt(hdc, x, y, w, h, hdc, x, y, NOTSRCCOPY);
    DeleteObject(hrgn);
    ReleaseDC(NULL, hdc);
}

void EfeitoCirculos() {
    Sleep(50000);
    int w = GetSystemMetrics(0) - 500, h = GetSystemMetrics(1) - 500;
    while (true) {
        const int size = 1000;
        int x = rand() % (w + size) - size / 2, y = rand() % (h + size) - size / 2;
        for (int i = 0; i < size; i += 100) {
            ci(x - i / 2, y - i / 2, i, i);
            Sleep(25);
        }
    }
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    std::thread t1(TextoRadonium);
    std::thread t2(EfeitoTremor);
    std::thread t3(InversaoCores);
    std::thread t4(EfeitoCatarata);
    std::thread t5(TextoAleatorioRadonium);
    std::thread t6(EfeitoDistorcaoEZoom);
    std::thread t7(EfeitoCirculos);

    t1.detach(); t2.detach(); t3.detach(); t4.detach();
    t5.detach(); t6.detach(); t7.detach();

    Sleep(INFINITE);
    return 0;
}