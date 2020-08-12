// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereActor.h"

#include "Components/StaticMeshComponent.h"

// Sets default values
ASphereActor::ASphereActor() : PickupMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh")))
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = PickupMesh;
}

// Called when the game starts or when spawned
void ASphereActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASphereActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

