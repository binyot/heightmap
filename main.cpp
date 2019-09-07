#include <SFML/Graphics.hpp>
#include "Framebuffer.h"

const unsigned SCREEN_W = 128,
        SCREEN_H = 128,
        WINDOW_W = 800,
        WINDOW_H = 800;

const bool VSYNC = true;

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "");
    window.setVerticalSyncEnabled(VSYNC);

    auto fb = Framebuffer(SCREEN_W, SCREEN_H);
    sf::Texture texture;
    texture.create(fb.width(), fb.height());
    texture.update(fb.data());

    sf::VertexArray vao(sf::Quads, 4);
    vao[0].position = {0.f, 0.f};
    vao[1].position = {WINDOW_W, 0.f};
    vao[2].position = {WINDOW_W, WINDOW_H};
    vao[3].position = {0.f, WINDOW_H};
    vao[0].texCoords = {0.f, 0.f};
    vao[1].texCoords = {static_cast<float>(fb.width()), 0.f};
    vao[2].texCoords = {static_cast<float>(fb.width()), static_cast<float>(fb.height())};
    vao[3].texCoords = {0.f, static_cast<float>(fb.height())};

    fb.set(8, 16, Color32{255, 255, 255, 255});

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        texture.update(fb.data());

        window.clear();
        window.draw(vao, &texture);
        window.display();

    }


    return 0;
}