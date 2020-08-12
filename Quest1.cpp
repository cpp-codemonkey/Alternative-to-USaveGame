#include "Quest1.h"

Quest1::Quest1()
{
	ActorProxy Proxy;
	Proxy.Location = FVector{-780.f, 100.f, 150.f};
	Proxy.Rotation = FRotator::ZeroRotator;
	Proxy.ActorClass = cidCone;
	Proxy.ActorObj = nullptr;
	AddActorProxy(Proxy);
}

void Quest1::Reset()
{
	Quest::Reset();
	NoOfBeers = NoOfCaviars = NoOfLipsticks = 0;
}

void Quest1::Print() const
{
	UE_LOG(LogTemp, Warning, TEXT("Quest1"));
	UE_LOG(LogTemp, Warning, TEXT("NoOfBeers: %d"), NoOfBeers);
	UE_LOG(LogTemp, Warning, TEXT("NoOfCaviars: %d"), NoOfCaviars);
	UE_LOG(LogTemp, Warning, TEXT("NoOfLipsticks: %d"), NoOfLipsticks);
}
