#include "object.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>

using namespace std;

Object::Object()
{

}

Object::Object(string file)
{  
	loadObj(file);
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

bool Object::loadObj(string objFile)
{
	Vertices.clear();
	Indices.clear();

	vector<unsigned int> vertexIndicies, normalIndices;
	
	string line;
	ifstream file;
	file.open( objFile );

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

