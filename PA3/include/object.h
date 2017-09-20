#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"

class Object
{
  public:
    Object();
    ~Object();
    void Update(unsigned int dt, bool reverse, bool pause);
    void Render();

    glm::mat4 GetPlanet();
	glm::mat4 GetMoon();

  private:
    glm::mat4 planet;
	glm::mat4 moon;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

    float angle;
	float moonAngle;
	float orbit;
	float rotate;
};

#endif /* OBJECT_H */
