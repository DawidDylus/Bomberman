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
void USpawnNewActor::CreateActor(TSubclassOf<AActor> ClassType)
{
	//auto& ClassToUse = ;FVector(5.0f, 0.0f, 0.0f)
	
	// TODO Change Location and Rotation to Variables that can be edited before puting them into function
	FVector Location = this->GetOwner()->GetActorLocation();
	FRotator Rotation = this->GetOwner()->GetActorRotation();
	
	
	GetWorld()->SpawnActor<AActor>(ClassType, Location, Rotation);

}






