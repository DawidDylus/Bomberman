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


// Sets default values
ABomb::ABomb()
{
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

		FVector EndLocation = StartLocation + (ExplosionDirection * Range);

		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 30, 10, 5);

		GetWorld()->LineTraceMultiByChannel(OutHitsTemp, StartLocation, EndLocation, ECC_Visibility, CollisionParams);		

		OutHits.Append(OutHitsTemp);

	}	
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
			// Have To change Character node class to c++ class
			

			GEngine->AddOnScreenDebugMessage(-1, 100000000000.0f, FColor::Red, Hit.GetActor()->GetName());
		}

		else if (Hit.GetActor()->GetClass()->IsChildOf<ANormalBoxes>())
		{
			GEngine->AddOnScreenDebugMessage(-1, 100000000000.0f, FColor::Red, Hit.GetActor()->GetName());
		}

		
	}

	



	
}

