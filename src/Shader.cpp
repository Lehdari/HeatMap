#include "Shader.hpp"

#include <cstdio>
#include <memory>


Shader::Shader(const std::string& vsFileName, const std::string& fsFileName) {
	FILE* vsf;
	fopen_s(&vsf, vsFileName.c_str(), "rb");
	if (!vsf)
		fprintf(stderr, "Unable to open vertex shader from file\n", vsFileName.c_str());

	FILE* fsf;
	fopen_s(&fsf, fsFileName.c_str(), "rb");
	if (!fsf)
		fprintf(stderr, "Unable to open fragment shader from file\n", vsFileName.c_str());

	fseek(vsf, 0L, SEEK_END);
	auto vsfs = ftell(vsf);
	std::unique_ptr<char> vsBufUnique(new char[vsfs + 1]);
	fseek(vsf, 0L, SEEK_SET);
	fread(vsBufUnique.get(), sizeof(char), vsfs, vsf);
	vsBufUnique.get()[vsfs] = '\0';
	fclose(vsf);
	const char* vsSrcPtr = vsBufUnique.get();

	fseek(fsf, 0L, SEEK_END);
	auto fsfs = ftell(fsf);
	std::unique_ptr<char> fsBufUnique(new char[fsfs + 1]);
	fseek(fsf, 0L, SEEK_SET);
	fread(fsBufUnique.get(), sizeof(char), fsfs, fsf);
	fsBufUnique.get()[fsfs] = '\0';
	fclose(fsf);
	const char* fsSrcPtr = fsBufUnique.get();

	GLuint vsObjectId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fsObjectId = glCreateShader(GL_FRAGMENT_SHADER);

	GLint compileStatus, infoLogLength;

	glShaderSource(vsObjectId, 1, &vsSrcPtr, NULL);
	glCompileShader(vsObjectId);

	glGetShaderiv(vsObjectId, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus == GL_FALSE) {
		glGetShaderiv(vsObjectId, GL_INFO_LOG_LENGTH, &infoLogLength);

		char* infoLog = new char[infoLogLength];
		glGetShaderInfoLog(vsObjectId, infoLogLength, NULL, &infoLog[0]);
		fprintf(stderr, "%s", infoLog);
		//throw infoLog; // TODO_EXCEPTION: throw a proper exception
	}

	glShaderSource(fsObjectId, 1, &fsSrcPtr, NULL);
	glCompileShader(fsObjectId);

	glGetShaderiv(fsObjectId, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus == GL_FALSE) {
		glGetShaderiv(fsObjectId, GL_INFO_LOG_LENGTH, &infoLogLength);

		char* infoLog = new char[infoLogLength];
		glGetShaderInfoLog(fsObjectId, infoLogLength, NULL, &infoLog[0]);
		fprintf(stderr, "%s", infoLog);
		//throw infoLog; // TODO_EXCEPTION: throw a proper exception
	}

	_programId = glCreateProgram();

	glAttachShader(_programId, fsObjectId);
	glAttachShader(_programId, vsObjectId);

	GLint linkStatus;

	glLinkProgram(_programId);

	glGetProgramiv(_programId, GL_LINK_STATUS, &linkStatus);
	if (linkStatus == GL_FALSE) {
		glGetShaderiv(_programId, GL_INFO_LOG_LENGTH, &infoLogLength);

		char* infoLog = new char[infoLogLength];
		glGetProgramInfoLog(_programId, infoLogLength, NULL, &infoLog[0]);
		fprintf(stderr, "%s", infoLog);
		//throw infoLog; // TODO_EXCEPTION: throw a proper exception
	}

	if (vsObjectId)
		glDeleteShader(vsObjectId);

	if (fsObjectId)
		glDeleteShader(fsObjectId);
}

Shader::~Shader(void) {
	if (_programId)
		glDeleteProgram(_programId);
}

Shader::Shader(Shader&& other) :
	_programId(other._programId)
{
	other._programId = 0;
}

Shader& Shader::operator=(Shader&& other) {
	if (_programId)
		glDeleteProgram(_programId);

	_programId = other._programId;
	other._programId = 0;

	return *this;
}

Shader::operator GLuint() const {
	return _programId;
}

GLuint Shader::getId(void) const {
	return _programId;
}

void Shader::use(void) {
	glUseProgram(_programId);
}
