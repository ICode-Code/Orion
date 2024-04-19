#ifndef OE1_SCENE_QUICK_CULL_H_
#define OE1_SCENE_QUICK_CULL_H_

#include "../../CameraPackage/CameraPackage.h"
#include "../../DS/TurboOT/OTEntDiscriptor.h"

#include <map>
#include <unordered_map>
#include <vector>

namespace OE1Core
{
	class SceneQuickCull
	{
		friend class Scene;
	public:
		SceneQuickCull();
		~SceneQuickCull() = default;


		void Register(DS::OTEntDiscriptor _data);
		void Purge(DS::OTEntDiscriptor _dis);
		void Update(DS::OTEntDiscriptor _entity);
		std::unordered_map<uint32_t, std::vector<DS::OTEntDiscriptor>>& GetCulledBuffer(std::map<std::string, CameraParameters>& _camera);

	private:
		std::unordered_map<uint32_t, std::unordered_map<uint32_t, DS::OTEntDiscriptor>> m_Buffer;
		std::unordered_map<uint32_t, std::vector<DS::OTEntDiscriptor>> m_CulledList;

	private: // Util
		/// <summary>
		/// this function return true if the __discriptor intersect with _frustum or if it is inside _frustum
		/// </summary>
		/// <param name="_frustum"></param>
		/// <param name="_bound"></param>
		/// <param name="__discriptor"></param>
		/// <returns></returns>
		bool FrustumIntersection(Frustum& _frustum, DS::OTEntDiscriptor& __discriptor);
	};
}

#endif // !OE1_SCENE_QUICK_CULL_H_
