#pragma once
#include <windows.h>
#include <vector>
#include <chrono>

enum class EventType { MouseClick, MouseMove, KeyDown, KeyUp };

struct Event {
    EventType type;
    int x = 0, y = 0;       // 鼠标坐标
    DWORD vkCode = 0;       // 键码
    DWORD delay = 0;        // 与上一次事件的时间差
};

class Recorder {
public:
    void start();
    void stop();
    void playback();

    void addMouseEvent(EventType type, int x, int y);
    void addKeyEvent(EventType type, DWORD vkCode);
private:
    std::vector<Event> events;
    std::chrono::steady_clock::time_point lastTime;
};
