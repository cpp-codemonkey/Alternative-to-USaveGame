#include "Quest.h"

#include "Engine/World.h"

THIRD_PARTY_INCLUDES_START
#include <UE4Serialization.hpp>
THIRD_PARTY_INCLUDES_END

void Quest::SpawnActors(UWorld* W)
{
	for (auto& Proxy : ActorProxies)
	{
		TSubclassOfType classType = TSubclassOfRegistration::instance().GetTSubclassOfFromId(Proxy.ActorClass);
		Proxy.ActorObj = W->SpawnActor<AActor>(classType, Proxy.Location, Proxy.Rotation);
	}
}

void Quest::DeleteActors()
{
	for (auto Proxy : ActorProxies)
	{
		if (Proxy.ActorObj)
		{
			Proxy.ActorObj->Destroy();
			Proxy.ActorObj = nullptr;
		}
	}
}

void Quest::AddActorProxy(ActorProxy const& Proxy)
{
	ActorProxies.push_back(Proxy);
}

void Quest::Reset()
{
	ActorProxies.clear();
}

Quest::~Quest()
{
}

void Quest::Print() const
{
	UE_LOG(LogTemp, Warning, TEXT("Quest"));
}
