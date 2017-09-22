#pragma once
#include <map>
#include "ManagerInitializer.h"

namespace MicronML {
	class CData
	{
		typedef std::map<data_id, CData*> FInstanceMap;
	public:
		~CData();
		static CData* Make(FDataParameters Parameters);
		static CData* Use(data_id DataID);
		static void Drop(data_id DataID);
		virtual data_id GetID() final;
		virtual FData* GetRaw() final;
		virtual FSample* Sample(sample_id SampleID, FCursor* CursorPointer);

	private:
		CData(FDataParameters Parameters);
		static FInstanceMap InstanceMap;
		static data_id InstanceIDCounter;
		static CManagerInitializer* Initializer;
		static bool_t Initialize();
		static bool_t Terminate();

		data_id ID;
		FData* Raw;

	public:
		FOnSampleEvent* OnSampleEvent;
	};
}