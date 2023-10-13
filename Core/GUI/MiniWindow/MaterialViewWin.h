#ifndef OE1_MATERIAL_VIEW_WIN_H_
#define OE1_MATERIAL_VIEW_WIN_H_


#include "BaseMiniWindw.h"

namespace OE1Core
{
	class MaterialViewWin : public BaseMiniWindow
	{
	public:
		MaterialViewWin(MasterMaterial* _material);
		~MaterialViewWin();

		virtual void Render() override;
		virtual void Update() override;
		inline MasterMaterial* GetMaterial() { return m_Material; }
		inline bool IsOpen() const { return m_Open; }

	protected:
		MasterMaterial* m_Material = nullptr;
		std::string m_WinName = "";
		bool m_Open = false;

	protected:
		void PrepareMaterialView();
		
	};
}

#endif // !OE1_MATERIAL_VIEW_WIN_H_
