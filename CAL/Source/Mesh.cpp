//*****************************************************************************
//	Filename: Mesh.cpp
//  Author:	  Hunter Smith
//  Date:	  08/07/2022
//  Description:
//		This is a wrapper class that will ahdnle all the data needed for
//		rendering meshes
//*****************************************************************************

#include "Mesh.h"

Mesh::Mesh() : vertices_()
	, edges_()
	, faces_()
{
}

Mesh::~Mesh()
{
	// If there are vertices, clear the vector
	if (vertices_.size())
		vertices_.clear();

	// If there are edges, clear the vector
	if (edges_.size())
		edges_.clear();

	// If there are faces, clear the vector
	if (faces_.size())
		faces_.clear();
}

// Member functions
void Mesh::AddVertex(glm::vec4 point, glm::vec2 uv)
{
	vertices_.push_back(point);
	uv_.push_back(uv);
}

void Mesh::AddEdge(unsigned v1, unsigned v2)
{
	Edge edgeToAdd(v1, v2);
	edges_.push_back(edgeToAdd);
}

void Mesh::AddEdge(Edge edge)
{
	edges_.push_back(edge);
}

void Mesh::AddFace(unsigned v1, unsigned v2, unsigned v3)
{
	Face faceToAdd(v1, v2, v3);
	faces_.push_back(faceToAdd);
}

void Mesh::AddFace(Face face)
{
	faces_.push_back(face);
}

glm::vec4* Mesh::GetVertices()
{
	if (vertices_.size() > 0)
		return &vertices_[0];
	return nullptr;
}

glm::vec2* Mesh::GetUV()
{
	if (uv_.size() > 0)
		return &uv_[0];
	return nullptr;
}

int Mesh::GetVertexCount()
{
	return vertices_.size();
}

Mesh::Face* Mesh::GetFaces()
{
	if (faces_.size() > 0)
		return &faces_[0];
	return nullptr;
}

int Mesh::GetFaceCount()
{
	return faces_.size();
}

//*****************************************************************************
//	Description
//		WRITE DESCRIPTION OF FUNCTION HERE
// 
//	Param MY_PARAM
//		WRITE WHAT PARAMETER DOES
// 
//	Return
//		SAY WHAT THE FUNCTION RETURNS IF NECESSARY
//*****************************************************************************
