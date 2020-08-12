// Fill out your copyright notice in the Description page of Project Settings.


#include "CerealDemoGameInstance.h"

#include "ConstructorHelpers.h"
#include "Quest1.h"
#include "Quest2.h"
#include "QuestManager.h"
#include "Quest.h"

THIRD_PARTY_INCLUDES_START
#include <UE4Serialization.hpp>
THIRD_PARTY_INCLUDES_END

UCerealDemoGameInstance::UCerealDemoGameInstance()
{
	TSubclassOfRegistration::instance().UnregsterAll();
	static ConstructorHelpers::FClassFinder<AActor> ConeClass(TEXT("Blueprint'/Game/ThirdPersonCPP/Blueprints/BP_ConeActor'"));
	if (ConeClass.Succeeded())
	{
		TSubclassOfRegistration::instance().RegisterTSubclassOf(cidCone, ConeClass.Class);
	}

	static ConstructorHelpers::FClassFinder<AActor> SphereClass(TEXT("Blueprint'/Game/ThirdPersonCPP/Blueprints/BP_SphereActor'"));

	if (SphereClass.Succeeded())
	{
		TSubclassOfRegistration::instance().RegisterTSubclassOf(cidSphere, SphereClass.Class);
	}
	//
	// QuestManager::instance().DeleteQuests();
	// {
	// 	QuestPtr quest(new Quest1);
	// 	ActorProxy Proxy;
	// 	Proxy.Location = FVector{-780.f, 100.f, 150.f};
	// 	Proxy.Rotation = FRotator::ZeroRotator;
	// 	Proxy.ActorClass = cidCone;
	// 	Proxy.ActorObj = nullptr;
	// 	quest->AddActorProxy(Proxy);
	// 	QuestManager::instance().AddQuest(quest);
	// }
	// {
	// 	QuestPtr quest(new Quest2);
	// 	ActorProxy Proxy;
	// 	Proxy.Location = FVector{-780.f, -500.f, 150.f};
	// 	Proxy.Rotation = FRotator::ZeroRotator;
	// 	Proxy.ActorClass = cidSphere;
	// 	Proxy.ActorObj = nullptr;
	// 	quest->AddActorProxy(Proxy);
	// 	QuestManager::instance().AddQuest(quest);
	// }
}
