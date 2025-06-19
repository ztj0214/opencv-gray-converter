# OpenCV Gray Image Converter

A simple C++ program that reads an image, converts it to grayscale using OpenCV, and saves the output.

## 🔧 Requirements

- C++11 or later
- OpenCV 4.x installed
- A sample image named `sample.jpg` placed in the same directory

## 🧪 How to Run

### Windows (with Visual Studio):

1. Open a new C++ project.
2. Add `main.cpp` to the project.
3. Link against OpenCV libraries.
4. Place `sample.jpg` in the same folder as `.exe`.
5. Run and check `output.jpg`.

### Linux (g++ example):

```bash
g++ main.cpp -o gray_converter `pkg-config --cflags --libs opencv4`
./gray_converter
