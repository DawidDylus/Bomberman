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
	
	

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:

	UPROPERTY(EditAnywhere)
		int32 Lives = 3;
	
};
