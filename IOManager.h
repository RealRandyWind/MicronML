#pragma once

#ifdef MICRONML_EXPORTS
#define MICRONML_API __declspec(dllexport)
#else
#define MICRONML_API __declspec(dllimport)
#endif

namespace MicronML
{
	class MICRONML_API CIOManager final
	{
	public:
		~CIOManager();
		static CIOManager* GetInstance();

	private:
		CIOManager();
		static CIOManager* Instance;

	};
}
