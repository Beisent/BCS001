#pragma once
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

namespace lcg
{
    class PPM
    {
    public:
        PPM(const std::filesystem::path &outputDirectory,
            const std::string &name, uint32_t width, uint32_t height);
        ~PPM();

        void writePixel(uint8_t r, uint8_t g, uint8_t b);
        void reset();
        void setData(const std::vector<uint8_t> &data);
        void setPixel(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b);

    private:
        std::string makeHeader() const;
        void writeHeader();

        uint32_t m_width;
        uint32_t m_height;
        std::filesystem::path m_outputDir;
        std::string m_filename;
        std::ofstream m_ppmFile;
        std::streamoff m_dataOffset;
    };

}
