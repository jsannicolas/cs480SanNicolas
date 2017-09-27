#include "object.h"
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

Object::Object()
{  
  /*
    # Blender File for a Cube
    o Cube
    v 1.000000 -1.000000 -1.000000
    v 1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 -1.000000
    v 1.000000 1.000000 -0.999999
    v 0.999999 1.000000 1.000001
    v -1.000000 1.000000 1.000000
    v -1.000000 1.000000 -1.000000
    s off
    f 2 3 4
    f 8 7 6
    f 1 5 6
    f 2 6 7
    f 7 8 4
    f 1 4 8
    f 1 2 4
    f 5 8 6
    f 2 1 6
    f 3 2 7
    f 3 7 4
    f 5 1 8*/
  

  Vertices = {
    {{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}},
    {{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
    {{-1.0f, -1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
    {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}},
    {{1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 0.0f}},
    {{1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}},
    {{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0f}},
    {{-1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}}
  };

  Indices = {
    2, 3, 4,
    8, 7, 6,
    1, 5, 6,
    2, 6, 7,
    7, 8, 4,
    1, 4, 8,
    1, 2, 4,
    5, 8, 6,
    2, 1, 6,
    3, 2, 7,
    3, 7, 4,
    5, 1, 8
  };

  // The index works at a 0th index
  for(unsigned int i = 0; i < Indices.size(); i++)
  {
    Indices[i] = Indices[i] - 1;
  }


	loadObj();
  angle = 0.0f;

  glGenBuffers(1, &VB);
  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &IB);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
}

Object::~Object()
{
  Vertices.clear();
  Indices.clear();
}

void Object::Update(unsigned int dt)
{
  angle += dt * M_PI/1000;
  //model = glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0, 1.0, 0.0));
  //model = glm::translate(model, glm::vec3(6.0, 0.0, 0.0));
  //model = glm::rotate(model, (angle), glm::vec3(0.0, 1.0, 0.0));
}

bool Object::loadObj()
{
	Vertices.clear();
	Indices.clear();

	vector<unsigned int> vertexIndicies, normalIndices;
	
	string line;
	ifstream file;
	file.open("../objects/board.obj");

	if(!file.is_open())
	{
		cout << "Object file could not be opened" << endl;
		return false;
	}

	while(file.good())
	{
		file >> line;
		if(line[0] == 'v' && line[1] != 'n') //checks if v, but not vn
		{
			glm::vec3 vertex;
			file >> vertex.x;
			file >> vertex.y;
			file >> vertex.z;
			Vertex tmp(vertex, vertex);
			Vertices.push_back(tmp);		
		}

		if(line[0] == 'f')
		{
			unsigned int vertexIndex[3], normalIndex[3];
			for(int i = 0; i < 3; i++)
			{
				file >> vertexIndex[i];
				file.ignore(1, '\n');
				if(	file.peek() == '/' )
				{
					file.ignore(1, '\n');
				}

				file >> normalIndex[i];
				Indices.push_back(vertexIndex[i]);
			}
		}

		else
		{
			file.ignore(300, '\n');
		}

	}

	file.close();

	for( unsigned int i = 0; i < Indices.size(); i++ )
	{
		Indices[i] = Indices[i] - 1;
	}
	
	return true;
}

glm::mat4 Object::GetModel()
{
  return model;
}

void Object::Render()
{
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,color));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

  glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}

