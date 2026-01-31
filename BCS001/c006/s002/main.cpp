#include <iostream>
#include <vector>
#include <limits>
#include "ppm.h"
#include "Vec3.h"
#include "Rasterizer.h"

int main()
{
    uint32_t width = 400;
    uint32_t height = 400;
    lcg::PPM ppm(".", "z-buffer", width, height);
    std::vector<uint8_t> colorBuffer(width * height * 3, 0);
    std::vector<float> depthBuffer(width * height, std::numeric_limits<float>::infinity());

    lcg::Vec3 A2{100, 100, 0.8f};     
    lcg::Vec3 B2{180, 300, 0.2f};  
    lcg::Vec3 C2{150, 80, 0.8f};   
    lcg::Color color2{200, 200, 200};
    lcg::draw_triangle(colorBuffer, depthBuffer, width, height, A2, B2, C2, color2);


    lcg::Vec3 A1{80, 160, 0.5f};      
    lcg::Vec3 B1{350, 160, 0.5f};     
    lcg::Vec3 C1{250, 100, 0.2f};     
    lcg::Color color1{150, 150, 150};
    lcg::draw_triangle(colorBuffer, depthBuffer, width, height, A1, B1, C1, color1);


    lcg::Vec3 A0{100, 300, 0.5f}; 
    lcg::Vec3 B0{300, 100, 0.2f}; 
    lcg::Vec3 C0{220, 280, 0.5f};  
    lcg::Color color0{80, 80, 80}; 
    lcg::draw_triangle(colorBuffer, depthBuffer, width, height, A0, B0, C0, color0);

    ppm.setData(colorBuffer);
    std::cout << "创建 z-buffer 成功" << std::endl;
    return 0;
}
