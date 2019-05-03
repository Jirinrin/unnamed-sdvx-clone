#pragma once

#include <Shared/Vector.hpp>
#include <Shared/Rect.hpp>
#include "VertexFormat.hpp"

using Shared::Rect;
using Shared::Rect3D;
namespace Graphics
{
	/* The type that tells how a mesh is drawn */
	enum class PrimitiveType
	{
		TriangleList = 0, TriangleStrip, TriangleFan, LineList, LineStrip, PointList,
	};

	// Generates meshes based on certain parameters
	// generated attributes are always in the following order:
	//	- Position
	//	- Texture Coordinates
	//	- Color
	//	- Normal
	struct SimpleVertex : public VertexFormat<Vector3, Vector2>
	{
		SimpleVertex() = default;

		SimpleVertex(Vector3 pos, Vector2 tex) : pos(pos), tex(tex)
		{
		};
		Vector3 pos;
		Vector2 tex;
	};

	/*
		Simple mesh object
	*/
	class IMesh
	{
	public:
		virtual ~IMesh() = default;

		// Generates vertices for a quad from a given rectangle, with given uv coordinate rectangle
		// the position top = +y
		// the uv has bottom = +y
		// Triangle List
		static void GenerateSimpleXYQuad(Rect3D r, Rect uv, Vector<SimpleVertex>& out);

		static void GenerateSimpleXZQuad(Rect3D r, Rect uv, Vector<SimpleVertex>& out);

		// Sets the vertex point data for this mesh
		// must be set before drawing
		// the vertex type must inherit from VertexFormat to automatically detect the correct format
		template<typename T>
		void SetData(const Vector<T>& verts)
		{
			SetData(verts.data(), verts.size(), T::GetDescriptors());
		}

		// Sets how the point data is interpreted and drawn
		// must be set before drawing
		virtual void SetPrimitiveType(PrimitiveType pt) = 0;

		virtual PrimitiveType GetPrimitiveType() const = 0;

		// Draws the mesh
		virtual void Draw() = 0;

		// Draws the mesh after if has already been drawn once, reuse of bound objects
		virtual void Redraw() = 0;

	private:
		virtual void SetData(const void* pData, size_t vertexCount, const VertexFormatList& desc) = 0;
	};


}