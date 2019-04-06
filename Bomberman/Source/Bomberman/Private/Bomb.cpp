// Fill out your copyright notice in the Description page of Project Settings.

#include "Bomb.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Public/TimerManager.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Containers/Array.h"
#include "DrawDebugHelpers.h"
#include "NormalBoxes.h"
#include "MyBombermanCharacter.h"
#include "Public/Math/UnrealMathUtility.h"
#include "Random_Pickup.h"


// Sets default values
ABomb::ABomb()
{	
	SpawnedCharacterBombRange = 50.0f;

	ExplosionDirections =
	{
		FVector(-1.0f, 0.0f, 0.0f),	// Right
		FVector(1.0f, 0.0f, 0.0f),	// Left
		FVector(0.0f, 1.0f, 0.0f),	// Up
		FVector(0.0f, -1.0f, 0.0f)  // Down 
	};

	
	TimeToExplode = 3.0f;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setting up default mesh 
	SuperMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SuperMesh"));	
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MyMesh(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if(MyMesh.Succeeded())
	SuperMesh->SetStaticMesh(MyMesh.Object);
	
	
}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();
	
	// Execute (Explosion) function after some Time (TimeToExplode) 
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABomb::Explosion, TimeToExplode, false);


}

bool ABomb::ShouldHappen(int Percentage)
{
	return (FMath::RandRange(1, 100) <= Percentage ? true : false);
}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Create one TArray<FHitResult> from different arrays created by LineTraceMultiByChannel 
//Quantity of linesTrace is specified by number of elements in ExplosionDirections array
void ABomb::ExplosionHits(TArray<FHitResult>& OutHits)
{
	
	for (FVector ExplosionDirection : ExplosionDirections)
	{

		TArray<FHitResult> OutHitsTemp;

		FVector StartLocation = GetActorLocation() + FVector(0.0f, 0.0f, 50.0f); //adding hight to be near center of actor

		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this->GetUniqueID());	// Ignore itself so that ABomb will not block LineTrace
		CollisionParams.bIgnoreTouches = false;					// Dont ingore overlaping

		FVector EndLocation = StartLocation + (ExplosionDirection * GetSpawnedCharacterBombRange());

		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 30, 10, 5);

		GetWorld()->LineTraceMultiByChannel(OutHitsTemp, StartLocation, EndLocation, ECC_Visibility, CollisionParams);		

		OutHits.Append(OutHitsTemp);

	}	
}

void ABomb::SetSpawnedCharacterBombRange(float x)
{
	SpawnedCharacterBombRange = x;
}

float ABomb::GetSpawnedCharacterBombRange()
{
	return SpawnedCharacterBombRange;
}

void ABomb::Explosion()
{	
	// Checking for colisions by drawing LineTraces to 4 sides 

	TArray<FHitResult> OutHits;

	ExplosionHits(OutHits);

	
	// TODO function that handle interaction with characters and boxes
	for (FHitResult Hit : OutHits)
	{
		if (Hit.GetActor()->GetClass()->IsChildOf<APawn>())
		{
			// Set ActprHit to specific Object in the world
			auto PawnHit = Cast<AMyBombermanCharacter>(Hit.GetActor());
			PawnHit->SetLives(PawnHit->GetLives()-1);

			if (PawnHit->GetLives() <= 0)
			{
				GEngine->AddOnScreenDebugMessage(-1, 100000000000.0f, FColor::Red,"YOU ARE DEAD!");
			}

			
		}

		else if (Hit.GetActor()->GetClass()->IsChildOf<ANormalBoxes>())
		{
			auto BoxHit = Cast<ANormalBoxes>(Hit.GetActor());

			// TODO Call function on box to spawn Pickups
			if (ShouldHappen(30))
			{
				GetWorld()->SpawnActor<ARandom_Pickup>(BoxHit->GetActorLocation(), BoxHit->GetActorRotation());
			}
			BoxHit->Destroy();
			GetWorld()->ForceGarbageCollection();			

		}

		
	}

	
}

