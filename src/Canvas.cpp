#include "Canvas.hpp"
#include "Shader.hpp"
#include "Texture.hpp"


Canvas::Canvas(void) {
    const GLfloat quads[] = {
        QUAD(-1.0f, -1.0f, 2.0f, 2.0f)
    };

    glGenVertexArrays(1, &_vertexArrayId);
    glBindVertexArray(_vertexArrayId);

    glGenBuffers(1, &_vertexArrayId);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quads), quads, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayId);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindVertexArray(0);
}

void Canvas::draw(Shader& shader, Texture& tex1, Texture& tex2) const {
    glBindVertexArray(_vertexArrayId);

    shader.use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex1);
    glUniform1i(glGetUniformLocation(shader, "tex1"), 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex2);
    glUniform1i(glGetUniformLocation(shader, "tex2"), 1);

    glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
