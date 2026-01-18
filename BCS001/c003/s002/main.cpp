#include <iostream>
#include "ppm.h"
#include <cmath>
void draw_4x4_grid()
{
    // 图像宽度和高度
    uint32_t width = 2;
    uint32_t height = 2;

    // 创建 PPM 对象
    lcg::PPM ppm(".", "test", width, height);

    // 每个像素3个字节 (RGB) 一共是 width*height*3 个字节
    std::vector<uint8_t> data(width * height * 3);

    // 填充数据
    // Red,Green
    // Blue,White
    data[0] = 255,data[1] = 0,data[2] = 0;  data[3] = 0,data[4] = 255,data[5] = 0;

    data[6] = 0,data[7] = 0,data[8] = 255;  data[9] = 255,data[10] = 255,data[11] = 255;

    // 设置图像数据
    ppm.setData(data);

    std::cout << "创建 test.ppm 成功" << std::endl;
}

void draw_rectangle()
{
    uint32_t width = 300;
    uint32_t height = 300;

    lcg::PPM ppm(".", "rectangle", width, height);

    std::vector<uint8_t> data(width * height * 3);
    for (uint32_t i = 0; i < height; i++)
    {
        for (uint32_t j = 0; j < width; j++)
        {
            if (i < 250 && j < 250 && i >= 50 && j >= 50)
            {
                data[(i * width + j) * 3 + 0] = 255; // R
                data[(i * width + j) * 3 + 1] = 0;   // G
                data[(i * width + j) * 3 + 2] = 0;   // B
            }
            else
            {
                data[(i * width + j) * 3 + 0] = 255; // R
                data[(i * width + j) * 3 + 1] = 255; // G
                data[(i * width + j) * 3 + 2] = 255; // B
            }
        }
    }
    ppm.setData(data);
    std::cout << "创建 rectangle.ppm 成功" << std::endl;
}
int main()
{
    draw_4x4_grid();

    draw_rectangle();
    return 0;
}
