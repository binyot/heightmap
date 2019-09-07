#ifndef HEIGHTMAP_SURFACE_H
#define HEIGHTMAP_SURFACE_H

#include <cstdint>
#include <cmath>
#include <array>
#include <vector>

template<typename UnitT = uint8_t, size_t Stride = 4>
struct Color {
    std::array<UnitT, Stride> data;

    static constexpr size_t size() noexcept { return Stride; }

    template<typename...Types, typename std::enable_if<sizeof...(Types) == Stride, unsigned>::type = 0>
    explicit Color(const Types &...Values) {
        data = {static_cast<UnitT>(Values)...};
    }
};

typedef Color<uint8_t, 4> Color32;

template<typename UnitT = uint8_t, size_t Stride = 4>
class Surface {
private:
    std::size_t m_width;
    std::size_t m_height;
    std::vector<UnitT> m_data;

public:
    using ColorT = Color<UnitT, Stride>;

    Surface() = delete;

    Surface(std::size_t width, std::size_t height)
            : m_width(width), m_height(height) {
        m_data.resize(m_width * m_height * Stride);
    }

    constexpr void set(int x, int y, const ColorT &color) {
        auto position = m_data.data() + (x + y * m_width) * Stride;
        std::copy(begin(color.data), end(color.data), position);
    }

    constexpr void set(int x, int y, ColorT &&color) {
        auto position = m_data.data() + (x + y * m_width) * Stride;
        std::copy(begin(color.data), end(color.data), position);
    }

    constexpr void clear(const ColorT &color) {
        auto current = m_data.data();
        auto last = current + m_data.size();
        for (auto i = m_data.data(); i < m_data.data() + m_data.size(); i += color.data.size()) {
            std::copy(begin(color.data), end(color.data), i);
        }
    }

    constexpr void clear(ColorT &&color) {
        auto current = m_data.data();
        auto last = current + m_data.size();
        for (auto i = m_data.data(); i < m_data.data() + m_data.size(); i += color.data.size()) {
            std::copy(begin(color.data), end(color.data), i);
        }
    }

    constexpr auto data() noexcept { return m_data.data(); }

    constexpr auto data() const noexcept { return m_data.data(); }

    constexpr auto size() const noexcept { return m_data.size(); }

    constexpr auto width() const noexcept { return m_width; }

    constexpr auto height() const noexcept { return m_height; }
};

#endif //HEIGHTMAP_SURFACE_H
