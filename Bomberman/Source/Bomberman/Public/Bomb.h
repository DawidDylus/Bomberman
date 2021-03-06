// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bomb.generated.h"

UCLASS(ClassGroup = (Custom))
class BOMBERMAN_API ABomb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABomb();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* SuperMesh;

	UPROPERTY(EditAnywhere)
		float TimeToExplode;

	UPROPERTY(VisibleAnywhere)
		TArray<FVector> ExplosionDirections;
		
	UFUNCTION(BlueprintCallable)
		void SetSpawnedCharacterBombRange(float x);

	UFUNCTION(BlueprintCallable)
		float GetSpawnedCharacterBombRange();
	
	
	
	

	UFUNCTION()
		void Explosion();

private:

	FTimerHandle TimerHandle;
	  	
	void ExplosionHits(TArray<FHitResult>&);
	bool ShouldHappen(int Percentage);
	float SpawnedCharacterBombRange;
	
	

};


