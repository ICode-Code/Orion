#include "SceneQuickCull.h"

namespace OE1Core
{
	SceneQuickCull::SceneQuickCull()
	{

	}

	void SceneQuickCull::Register(DS::OTEntDiscriptor _data)
	{
		m_Buffer[_data.PackageID][_data.EntityID] = _data;
	}
	void SceneQuickCull::Purge(DS::OTEntDiscriptor _data)
	{
		if (m_Buffer.find(_data.PackageID) == m_Buffer.end())
			return;

		if (m_Buffer[_data.PackageID].find(_data.EntityID) == m_Buffer[_data.PackageID].end())
			return;

		m_Buffer[_data.PackageID].erase(_data.EntityID);
	}
	void SceneQuickCull::Update(DS::OTEntDiscriptor _dis)
	{
		m_Buffer[_dis.PackageID][_dis.EntityID] = _dis;
	}
	std::unordered_map<uint32_t, std::vector<DS::OTEntDiscriptor>>& SceneQuickCull::GetCulledBuffer(std::map<std::string, CameraParameters>& _cameras)
	{
		m_CulledList.clear();

		for (auto camera_iter = _cameras.begin(); camera_iter != _cameras.end(); camera_iter++)
		{
			Frustum& _camera_frust = camera_iter->second.Camera->GetCamera()->GetFrustum();

			if (camera_iter->second.Camera->GetCamera()->ShouldCull())
			{
				for (auto package_iter = m_Buffer.begin(); package_iter != m_Buffer.end(); package_iter++)
				{
					for (auto insta_iter = package_iter->second.begin(); insta_iter != package_iter->second.end(); insta_iter++)
					{
						if (FrustumIntersection(_camera_frust, insta_iter->second))
							m_CulledList[insta_iter->second.PackageID].push_back(insta_iter->second);
					}
				}
			}
			break;
		}

		return m_CulledList;
	}
	bool SceneQuickCull::FrustumIntersection(Frustum& _frustum, DS::OTEntDiscriptor& __discriptor)
	{

		glm::vec3 i_min = (__discriptor.Bound.Min * __discriptor.Scale) + __discriptor.Position;
		glm::vec3 i_max = (__discriptor.Bound.Max * __discriptor.Scale) + __discriptor.Position;
		// Iterate over each plane of the frustum
		for (int i = 0; i < 6; i++)
		{
			Plane& plane = _frustum.GetPlane(i);

			// Find the point in the bounding box that is furthest along the direction of the plane normal
			glm::vec3 pointInBox = i_min;
			if (plane.GetNormal().x >= 0)
				pointInBox.x = i_max.x;
			if (plane.GetNormal().y >= 0)
				pointInBox.y = i_max.y;
			if (plane.GetNormal().z >= 0)
				pointInBox.z = i_max.z;

			// If the furthest point is behind the plane, the entire bounding box is outside the frustum
			if (plane.GetSignedDistanceToPlace(pointInBox) < 0)
				return false;
		}

		return true;
	}
}