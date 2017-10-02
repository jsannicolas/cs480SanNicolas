#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <cstring>
#include "graphics_headers.h"

using namespace std;

class Object
{
  public:
    Object();
	Object(string file);
    ~Object();
    void Update(unsigned int dt);
    void Render();
	bool loadObj(string objFile);

    glm::mat4 GetModel();

  private:
    glm::mat4 model;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

    float angle;
};

#endif /* OBJECT_H */
