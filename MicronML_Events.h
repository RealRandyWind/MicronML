#pragma once

#ifdef MICRONML_EXPORTS
#define MICRONML_API __declspec(dllexport)
#else
#define MICRONML_API __declspec(dllimport)
#endif


#include <list>
#include <algorithm> 
#include "MicronML_Types.h"
#include "MicronML_Definitions.h"

#define AddOnceListener(...) MicronML_Macro_Expand(MicronML_Macro_Va_Select(AddOnceListener, __VA_ARGS__))
#define AddOnceListener_5(Event, ListenerClass, Listener, Function, ID) AddOnceDelegate(Event::Pack<ListenerClass, &ListenerClass::Function>(Listener), ID)
#define AddOnceListener_4(Event, ListenerClass, Listener, Function) AddOnceDelegate(Event::Pack<ListenerClass, &ListenerClass::Function>(Listener))

#define AddListener(...) MicronML_Macro_Expand(MicronML_Macro_Va_Select(AddListener, __VA_ARGS__))
#define AddListener_5(Event, ListenerClass, Listener, Function, ID) AddDelegate(Event::Pack<ListenerClass, &ListenerClass::Function>(Listener), ID)
#define AddListener_4(Event, ListenerClass, Listener, Function) AddDelegate(Event::Pack<ListenerClass, &ListenerClass::Function>(Listener))

#define RemoveListener(...) MicronML_Macro_Expand(MicronML_Macro_Va_Select(RemoveListener, __VA_ARGS__))
#define RemoveListener_5(Event, ListenerClass, Listener, Function, ID) RemoveDelegate(Event::Pack<ListenerClass, &ListenerClass::Function>(Listener), ID)
#define RemoveListener_4(Event, ListenerClass, Listener, Function) RemoveDelegate(Event::Pack<ListenerClass, &ListenerClass::Function>(Listener))

#define ClearListeners(...) MicronML_Macro_Expand(MicronML_Macro_Va_Select(ClearListeners, __VA_ARGS__))
#define ClearListeners_5(Event, ID) ClearDelegates<Event>(ID)
#define ClearListeners_4(Event) ClearDelegates<Event>()

namespace MicronML
{
	template<class ... TypeParameters>
	class MICRONML_API TEvent
	{
	public:
		TEvent() { DelegateList = new std::list<FDelegate>(); }
		~TEvent() { delete DelegateList;  }

		typedef void(*FFunction)(pointer_t, TypeParameters ...);
		
		template<class TypeClass>
		class MICRONML_API TResolver
		{
		public:
			typedef void (TypeClass::*FSignature)(TypeParameters ... Parameters);
		};

		class MICRONML_API FDelegate
		{
		public:
			pointer_t Listener;
			FFunction Function;
			void operator()(TypeParameters ... Parameters) { (*Function)(Listener, Parameters ...); }
			bool operator==(const FDelegate& Other) { return Other.Function == Function && Other.Listener == Listener; }
		};

		template<class TypeClass, typename TResolver<TypeClass>::FSignature Function>
		static void Caller(pointer_t Listener, TypeParameters ... Parameters)
		{
			(static_cast<TypeClass*>(Listener)->*Function)(Parameters ...);
		}

		template<class TypeClass, typename TResolver<TypeClass>::FSignature Function>
		static FDelegate Pack(TypeClass* Listener)
		{
			return { Listener , &Caller<TypeClass, Function> };
		}

		inline void Add(FDelegate Delegate)
		{
			auto It = std::find(DelegateList->begin(), DelegateList->end(), Delegate);
			if (It != DelegateList->end()) { return;  }
			DelegateList->push_back(Delegate);
		}

		inline void Remove(FDelegate Delegate)
		{
			auto It = std::find(DelegateList->begin(), DelegateList->end(), Delegate);
			if (It != DelegateList->end()) { DelegateList->erase(It); }
		}
		
		inline void Signal(TypeParameters ... Parameters)
		{
			for (auto &Delegate : *DelegateList) { Delegate(Parameters ...); }
		}

		inline void Clear()
		{
			DelegateList->clear();
		}
	private:
		std::list<FDelegate>* DelegateList;
	};

	typedef TEvent<FSample*, const FCursor> FOnSampleEvent;
	typedef TEvent<FMicron*, const FCursor> FOnMicronEvent;
	typedef TEvent<FCompound*, const FCursor> FOnCompoundEvent;

	typedef TEvent<const FDataParameters, FData*, data_id> FOnDataImportEvent;
	typedef TEvent<const FDataParameters, const FData, data_id> FOnDataImportDoneEvent;

	typedef TEvent<const struct FException> FOnExceptionEvent;
}