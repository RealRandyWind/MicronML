#pragma once
#include <map>
#include "ManagerInitializer.h"

namespace MicronML {
	class CResult
	{
		typedef std::map<result_id, CResult*> FInstanceMap;
	public:
		~CResult();
		static CResult* Make(FResultParameters Parameters);
		static CResult* Use(result_id ResultID);
		static void Drop(result_id ResultID);
		virtual result_id GetID() final;
		virtual FResult* GetRaw() final;
		virtual FMicron* Micron(micron_id MicronID, FCursor* CursorPointer);

	private:
		CResult(FResultParameters Parameters);
		static FInstanceMap InstanceMap;
		static result_id InstanceIDCounter;
		static CManagerInitializer* Initializer;
		static bool_t Initialize();
		static bool_t Terminate();

		result_id ID;
		FResult* Raw;

	public:
		FOnMicronEvent* OnMicronEvent;
	};
}

