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
void Mesh::AddVertex(glm::vec3 point)
{
	vertices_.push_back(point);
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
