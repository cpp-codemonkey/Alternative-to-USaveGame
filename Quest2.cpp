#include "Quest2.h"

Quest2::Quest2()
{
	ActorProxy Proxy;
	Proxy.Location = FVector{-780.f, -500.f, 150.f};
	Proxy.Rotation = FRotator::ZeroRotator;
	Proxy.ActorClass = cidSphere;
	Proxy.ActorObj = nullptr;
	AddActorProxy(Proxy);
}

void Quest2::Reset()
{
	Quest::Reset();
	NoOfCheeses = 0;
	RatsDead = false;
}

void Quest2::Print() const
{
	UE_LOG(LogTemp, Warning, TEXT("Quest2"));
	UE_LOG(LogTemp, Warning, TEXT("RatsDead: %s"), RatsDead ? TEXT("true") : TEXT("false"));
	UE_LOG(LogTemp, Warning, TEXT("NoOfCheeses: %d"), NoOfCheeses);
}
