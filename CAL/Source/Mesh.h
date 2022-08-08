//*****************************************************************************
//	Filename: Mesh.h
//  Author:	  Hunter Smith
//  Date:	  08/07/2022
//  Description:
//		This is a wrapper class that will ahdnle all the data needed for
//		rendering meshes
//*****************************************************************************
#pragma once

#include "glm/glm.hpp"
#include <vector>

class Mesh {
public:

	struct Edge {
		unsigned v1, v2;
		Edge(unsigned v1, unsigned v2) : v1(v1), v2(v2) {}
	};

	struct Face {
		unsigned v1, v2, v3;
		Face(unsigned v1, unsigned v2, unsigned v3) : v1(v1), v2(v2), v3(v3) {}
	};

	// Constructor and Destructor
	Mesh();
	~Mesh();

	// Member functions
	void AddVertex(glm::vec4 point, glm::vec2 uv);

	void AddEdge(unsigned v1, unsigned v2);
	void AddEdge(Edge edge);

	void AddFace(unsigned v1, unsigned v2, unsigned v3);
	void AddFace(Face face);

	glm::vec4* GetVertices();
	glm::vec2* GetUV();
	int GetVertexCount();

	Face* GetFaces();
	int GetFaceCount();

private:

	std::vector<glm::vec4> vertices_;
	std::vector<glm::vec2> uv_;
	std::vector<Edge> edges_;
	std::vector<Face> faces_;

};
