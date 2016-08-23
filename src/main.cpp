#include "Shader.hpp"
#include "Texture.hpp"
#include "Canvas.hpp"
#include "RandomWalker.hpp"

#include <SFML/Graphics.hpp>


void genHeatMapData(unsigned char* data, uint64_t width, uint64_t height,
                    const std::vector<RandomWalker::Pos>& log,
                    uint64_t firstEntry, uint64_t lastEntry) {
    auto it = log.begin() + firstEntry;
    auto itEnd = log.begin() + lastEntry;

    for (uint64_t j=0; j<height; ++j)
        for (uint64_t i=0; i<width; ++i)
            data[j*width + i] = 0;

    uint64_t i, j;
    for (; it != itEnd; ++it) {
        i = (uint64_t)it->x;
        j = (uint64_t)it->y;
        if (data[j*width + i] < 255)
            ++data[j*width + i];
    }
}

int main(void) {
    sf::Window window(sf::VideoMode(1024, 1024), "HeatMap", sf::Style::Default,
                      sf::ContextSettings{8, 0, 4, 3, 3});
    window.setFramerateLimit(60);
    window.setActive();

    glewInit();

    Shader shader("src/shaders/VS_Texture.glsl", "src/shaders/FS_Texture.glsl");
    Canvas canvas;
    Texture datapoints(1024, 1024);

    RandomWalker walker(1024, 1024);
    const uint64_t nSteps = 2000000;
    for (auto i=0u; i<nSteps; ++i)
        walker.step();

    std::vector<unsigned char> heatMapPixData(1024*1024, 0);
    genHeatMapData(&heatMapPixData[0], 1024, 1024, walker.getLog(), 0, 100000);

    datapoints.update(&heatMapPixData[0], GL_RED, GL_RED);

    double t = 0.0;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        genHeatMapData(&heatMapPixData[0], 1024, 1024, walker.getLog(), nSteps*0.25+nSteps*0.24*sinf(t*0.2178635), nSteps*0.75+nSteps*0.24*sinf(t*0.435634));
    datapoints.update(&heatMapPixData[0], GL_RED, GL_RED);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        canvas.draw(shader, datapoints, datapoints);

        window.display();

        t += 0.01;
    }
}
