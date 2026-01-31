#include "ppm.h"
#include <stdexcept>

namespace lcg
{
    PPM::PPM(const std::filesystem::path &outputDirectory,
             const std::string &name, uint32_t width, uint32_t height)
        : m_width(width),
          m_height(height),
          m_outputDir(outputDirectory),
          m_filename(name),
          m_ppmFile(),
          m_dataOffset(0)
    {
        std::filesystem::create_directories(m_outputDir);

        m_ppmFile.open(m_outputDir / (m_filename + ".ppm"), std::ios::out | std::ios::binary);
        if (!m_ppmFile.is_open())
        {
            throw std::runtime_error("Failed to open file for writing.");
        }

        writeHeader();
    }

    PPM::~PPM()
    {
        if (m_ppmFile.is_open())
        {
            m_ppmFile.close();
        }
    }

    void PPM::writePixel(uint8_t r, uint8_t g, uint8_t b)
    {
        m_ppmFile.write(reinterpret_cast<const char *>(&r), 1);
        m_ppmFile.write(reinterpret_cast<const char *>(&g), 1);
        m_ppmFile.write(reinterpret_cast<const char *>(&b), 1);
    }

    void PPM::reset()
    {
        m_ppmFile.seekp(m_dataOffset);
        m_ppmFile.flush();
        writeHeader();
    }

    void PPM::setData(const std::vector<uint8_t> &data)
    {
        const size_t expected = static_cast<size_t>(m_width) * static_cast<size_t>(m_height) * 3;
        if (data.size() != expected)
        {
            throw std::runtime_error("Data size does not match image dimensions.");
        }

        m_ppmFile.write(reinterpret_cast<const char *>(data.data()), data.size());
    }

    void PPM::setPixel(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b)
    {
        if (x >= m_width || y >= m_height)
        {
            throw std::out_of_range("Pixel coordinates are out of bounds.");
        }

        const std::streamoff pixelIndex = static_cast<std::streamoff>((static_cast<uint64_t>(y) * m_width + x) * 3);
        const std::streamoff pos = m_dataOffset + pixelIndex;

        m_ppmFile.seekp(pos);
        m_ppmFile.write(reinterpret_cast<const char *>(&r), 1);
        m_ppmFile.write(reinterpret_cast<const char *>(&g), 1);
        m_ppmFile.write(reinterpret_cast<const char *>(&b), 1);
    }

    std::string PPM::makeHeader() const
    {
        std::ostringstream header;
        header << "P6\n"
               << m_width << " " << m_height << "\n255\n";
        return header.str();
    }

    void PPM::writeHeader()
    {
        const std::string header = makeHeader();
        m_dataOffset = static_cast<std::streamoff>(header.size());
        m_ppmFile.write(header.c_str(), static_cast<std::streamsize>(header.size()));
    }
    uint32_t PPM::getWidth() const
    {
        return m_width;
    }
    uint32_t PPM::getHeight() const
    {
        return m_height;
    }
}