// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyBombermanCharacter.generated.h"

UCLASS()
class BOMBERMAN_API AMyBombermanCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMyBombermanCharacter();
	

protected:
	
	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	// Called for placing new bomb actor
	FVector FindPlaceForBomb(FVector DistanceToNewSpawnedActor, FVector DistanceToGround);

	
	void PlaceBombA();
	
	

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:		

	UFUNCTION(BlueprintCallable)
		void SetLives(int x);

	UFUNCTION(BlueprintCallable)
		int32 GetLives();	

	UFUNCTION(BlueprintCallable)
		void SetBombRange(float x);

	UFUNCTION(BlueprintCallable)
		float GetBombRange();

	UFUNCTION(BlueprintCallable)
		void SetBombQuantity(int x);

	UFUNCTION(BlueprintCallable)
		int32 GetQuantity();


	UPROPERTY(EditAnywhere)
		FVector DistanceToNewSpawnedBomb;

	UPROPERTY(EditAnywhere)
		FVector DistanceToGround;

		
private:	
		float BombRange;
		int32 Lives;
		int32 BombQuantity;

};
