#ifndef SHADER_HPP
#define SHADER_HPP


#include <string>
#include <GL/glew.h>


class Shader {
public:
    Shader(const std::string& vsFileName, const std::string& fsFileName);
    ~Shader(void);

    Shader(const Shader&) = delete;
    Shader(Shader&&);
    Shader& operator=(const Shader&) = delete;
    Shader& operator=(Shader&&);

    operator GLuint() const;

    GLuint getId(void) const;
    void use(void);

private:
    GLuint _programId;
};


#endif // SHADER_HPP
