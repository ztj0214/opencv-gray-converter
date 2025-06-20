#include <windows.h>
#include <iostream>
#include "recorder.h"

HHOOK hMouseHook = NULL;
HHOOK hKeyboardHook = NULL;
Recorder recorder;
bool recording = false;

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (recording && nCode == HC_ACTION) {
        MSLLHOOKSTRUCT* ms = (MSLLHOOKSTRUCT*)lParam;
        if (wParam == WM_LBUTTONDOWN) {
            recorder.addMouseEvent(EventType::MouseClick, ms->pt.x, ms->pt.y);
        }
        else if (wParam == WM_MOUSEMOVE) {
            recorder.addMouseEvent(EventType::MouseMove, ms->pt.x, ms->pt.y);
        }
    }
    return CallNextHookEx(hMouseHook, nCode, wParam, lParam);
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* kb = (KBDLLHOOKSTRUCT*)lParam;
        DWORD vk = kb->vkCode;

        // 快捷键处理
        if (GetAsyncKeyState(VK_CONTROL) & 0x8000) {
            if (vk == VK_F9 && wParam == WM_KEYDOWN) {
                if (!recording) {
                    std::cout << "[✓] 开始录制\n";
                    recorder.start();
                    recording = true;
                }
            }
            else if (vk == VK_F10 && wParam == WM_KEYDOWN) {
                if (recording) {
                    std::cout << "[✓] 停止录制\n";
                    recorder.stop();
                    recording = false;
                }
            }
            else if (vk == VK_F11 && wParam == WM_KEYDOWN) {
                std::cout << "[→] 回放中...\n";
                recorder.playback();
                std::cout << "[✓] 回放完毕\n";
            }
        }

        // 记录键盘操作
        if (recording) {
            if (wParam == WM_KEYDOWN)
                recorder.addKeyEvent(EventType::KeyDown, vk);
            else if (wParam == WM_KEYUP)
                recorder.addKeyEvent(EventType::KeyUp, vk);
        }

        // ESC 退出
        if (vk == VK_ESCAPE && wParam == WM_KEYDOWN) {
            PostQuitMessage(0);
        }
    }
    return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
}

int main() {
    std::cout << "录制键鼠操作（Ctrl+F9 开始录制 / Ctrl+F10 停止 / Ctrl+F11 回放 / ESC 退出）\n";

    hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, NULL, 0);
    hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {}

    UnhookWindowsHookEx(hMouseHook);
    UnhookWindowsHookEx(hKeyboardHook);
    return 0;
}
