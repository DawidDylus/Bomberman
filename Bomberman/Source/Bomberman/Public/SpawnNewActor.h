// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/ActorComponent.h"
#include "SpawnNewActor.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOMBERMAN_API USpawnNewActor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawnNewActor();


protected:
	
private:
	

		

public:	
		

	UFUNCTION(BlueprintCallable)
		void CreateActor(TSubclassOf<AActor> ClassType, FVector Location, FRotator Rotation);
	
		
		
};
