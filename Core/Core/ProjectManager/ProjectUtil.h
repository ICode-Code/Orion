#ifndef OE1_PROJECT_UTIL_H_
#define OE1_PROJECT_UTIL_H_



namespace OE1Core 
{
	// This list are just for now it future it will change
	enum class ProjectType
	{
		Empty = 0,
		PBR_Template,
		FPS_Template
	};

	struct ProjectConfig
	{
		ProjectConfig() {}
		std::string Name;
		std::string Version;
		std::string LastOpen;
		std::string Type;
		std::string ActiveRenderer;
		std::string API;
		std::string EngineVersion;

		template <class Archive>
		void serialize(Archive& ar, const unsigned int version) {
			ar& Name;
			ar& Version;
			ar& LastOpen;
			ar& Type;
			ar& ActiveRenderer;
			ar& API;
			ar& EngineVersion;
		}
	};
}

#endif // !OE1_PROJECT_UTIL_H_
