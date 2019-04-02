// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnNewActor.h"
#include "Bomb.h"
#include "Engine/World.h"

// Sets default values for this component's properties
USpawnNewActor::USpawnNewActor()
{
	
	// ...
}


// Takes Class Type and spawn that type of object into the world.
void USpawnNewActor::CreateActor(TSubclassOf<AActor> ClassType, FVector Location, FRotator Rotation)
{			
	GetWorld()->SpawnActor<AActor>(ClassType, Location, Rotation);
}






