// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBombermanCharacter.h"
#include "ConstructorHelpers.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Bomb.h"

// Sets default values
AMyBombermanCharacter::AMyBombermanCharacter()
{			
	BombRange = 200.0f;
	DistanceToNewSpawnedBomb = FVector(50.0f, 50.0f, 0.0f); // Set default range to new spawned object(Bomb)
	Lives = 3;  // Set default lives number
	DistanceToGround = FVector(0.0f, 0.0f, 21.0f); // Set default z axis (should be little above ground);

	
	

		//  Set default SkeletalMesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>MySkeletalMesh(TEXT("/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin"));
	if (MySkeletalMesh.Succeeded())
	{		
		GetMesh()->SetSkeletalMesh(MySkeletalMesh.Object);
		GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -97.0f));	// Set Location to match CapsuleComponent	
		GetMesh()->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));	// Set Rotation to match animation correctly
	}

	
	// Set default Animation
	static ConstructorHelpers::FObjectFinder<UClass>AnimObj(TEXT("/Game/Mannequin/Animations/ThirdPerson_AnimBP.ThirdPerson_AnimBP_C"));	
	if (AnimObj.Succeeded())
	{		
		GetMesh()->SetAnimInstanceClass(AnimObj.Object);
	}
		

	// Set collision responce on visibility channet to overlap 
	// Overlap channel is used to get hits from bomb explosion and also to not stop TraceLine, so more  that one character can be Hit.
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Overlap);	

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);	
	

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AMyBombermanCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("PlaceBomb", IE_Pressed, this, &AMyBombermanCharacter::PlaceBombA);
	

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyBombermanCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyBombermanCharacter::MoveRight);
	
}

void AMyBombermanCharacter::SetLives(int x)
{
	Lives = x;
}

int32 AMyBombermanCharacter::GetLives()
{
	return Lives;
}

void AMyBombermanCharacter::SetBombRange(float x)
{
	BombRange = x;
}

float AMyBombermanCharacter::GetBombRange()
{
	return BombRange;
}

void AMyBombermanCharacter::SetBombQuantity(int x)
{
	BombQuantity = x;
}

int32 AMyBombermanCharacter::GetQuantity()
{
	return BombQuantity;
}





void AMyBombermanCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		
		// get forward vector
		const FVector Direction = FVector(0.0f, 2.0f, 0.0f);
		AddMovementInput(Direction, Value);
	}
}

void AMyBombermanCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{		

		// get right vector 
		const FVector Direction = FVector(-2.0f, 0.0f, 0.0f);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

// TODO Place bomb on space
FVector AMyBombermanCharacter::FindPlaceForBomb(FVector DistanceToNewSpawnedActor, FVector DistanceToGround)
{
	FVector ActorLocationXY = this->GetActorLocation() * FVector(1.0f, 1.0f, 0.0f); // reseting Z to 0
	FVector NewBombLocation(this->GetActorForwardVector() * DistanceToNewSpawnedActor); // Actor Spawn in front of actor
	
	return ActorLocationXY + NewBombLocation + DistanceToGround;
}

void AMyBombermanCharacter::PlaceBombA()
{			 
	// ActorRotation take care of rotation of new spawned object so that if it have some more specialised mesh
	// it will be placed with the same rotation as Actor that place it
	
	ABomb* SpawnedBomb = (ABomb*) GetWorld()->SpawnActor<ABomb>(FindPlaceForBomb(DistanceToNewSpawnedBomb, DistanceToGround), GetActorRotation());	
	SpawnedBomb->SetSpawnedCharacterBombRange(GetBombRange());
	

}
