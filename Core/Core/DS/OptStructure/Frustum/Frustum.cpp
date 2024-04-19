#include "Frustum.h"


namespace OE1Core
{
	Plane& Frustum::Front() { return m_Plane[0]; }
	Plane& Frustum::Back() { return m_Plane[1]; }

	Plane& Frustum::Right() { return m_Plane[2]; }
	Plane& Frustum::Left() { return m_Plane[3]; }

	Plane& Frustum::Top() { return m_Plane[4]; }
	Plane& Frustum::Bottom() { return m_Plane[5]; }

	Plane& Frustum::GetPlane(int _idx) { return m_Plane[_idx]; }
}