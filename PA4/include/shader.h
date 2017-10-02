#ifndef SHADER_H
#define SHADER_H

#include <vector>

#include "graphics_headers.h"

using namespace std;

class Shader
{
  public:
    Shader();
    ~Shader();
    bool Initialize();
    void Enable();
    bool AddShader(GLenum ShaderType, string shadeFile);
    bool Finalize();
    GLint GetUniformLocation(const char* pUniformName);
	

  private:
    GLuint m_shaderProg;    
    std::vector<GLuint> m_shaderObjList;
};

#endif  /* SHADER_H */
