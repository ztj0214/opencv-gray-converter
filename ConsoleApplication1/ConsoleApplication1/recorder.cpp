#include "recorder.h"
#include <thread>

void Recorder::start() {
    events.clear();
    lastTime = std::chrono::steady_clock::now();
}

void Recorder::stop() {
    // ½áÊø¼ÇÂ¼
}

void Recorder::addMouseEvent(EventType type, int x, int y) {
    auto now = std::chrono::steady_clock::now();
    DWORD delay = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastTime).count();
    lastTime = now;

    events.push_back(Event{ type, x, y, 0, delay });
}

void Recorder::addKeyEvent(EventType type, DWORD vkCode) {
    auto now = std::chrono::steady_clock::now();
    DWORD delay = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastTime).count();
    lastTime = now;

    events.push_back(Event{ type, 0, 0, vkCode, delay });
}

void Recorder::playback() {
    for (const auto& e : events) {
        std::this_thread::sleep_for(std::chrono::milliseconds(e.delay));

        INPUT input = {};
        if (e.type == EventType::KeyDown || e.type == EventType::KeyUp) {
            input.type = INPUT_KEYBOARD;
            input.ki.wVk = e.vkCode;
            input.ki.dwFlags = (e.type == EventType::KeyUp) ? KEYEVENTF_KEYUP : 0;
        }
        else if (e.type == EventType::MouseClick || e.type == EventType::MouseMove) {
            SetCursorPos(e.x, e.y);
            input.type = INPUT_MOUSE;
            if (e.type == EventType::MouseClick) {
                input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
                SendInput(1, &input, sizeof(INPUT));
                input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
            }
            else {
                continue; // MouseMove handled via SetCursorPos
            }
        }
        SendInput(1, &input, sizeof(INPUT));
    }
}
