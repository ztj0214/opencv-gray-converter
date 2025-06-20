#pragma once
#include <windows.h>
#include <vector>
#include <chrono>

enum class EventType { MouseClick, MouseMove, KeyDown, KeyUp };

struct Event {
    EventType type;
    int x = 0, y = 0;       // �������
    DWORD vkCode = 0;       // ����
    DWORD delay = 0;        // ����һ���¼���ʱ���
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
