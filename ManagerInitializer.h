#pragma once

namespace MicronML
{
	class CManagerInitializer final
	{
	public:
		CManagerInitializer(pointer_t What, bool_t(*OnInitialize)(), bool_t(*OnTerminate)());
		~CManagerInitializer();
		bool_t IsInitialized();
	private:
		pointer_t Subject;
		bool_t(*Initialize)();
		bool_t(*Terminate)();
		bool_t bInitialized;
		bool_t bTerminated;
	};
}

