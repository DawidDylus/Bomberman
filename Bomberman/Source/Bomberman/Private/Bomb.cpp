// Fill out your copyright notice in the Description page of Project Settings.

#include "Bomb.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Public/TimerManager.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Containers/Array.h"
#include "DrawDebugHelpers.h"


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

//Create one TArray<FHitResult> From different LineTraceMultiByChannel
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
	for (FHitResult Results : OutHits)
	{
		GEngine->AddOnScreenDebugMessage(-1, 100000000000.0f, FColor::Red, Results.GetActor()->GetName());
	}






	// TODO Refactor Function	
	/*
	TArray<FHitResult> OutHitsRightRay;
	TArray<FHitResult> OutHitsLeftRay;
	TArray<FHitResult> OutHitsUpRay;
	TArray<FHitResult> OutHitsDownRay;
	*/
	// create array of direction and then go throu it in funcions (difrent directions will have difrent outpust[htis] and then add all of those arrays into one and get it back)

	/*FVector ExplosionDirectionRight = FVector(-1.0f, 0.0f, 0.0f);
	FVector ExplosionDirectionLeft = FVector(1.0f, 0.0f, 0.0f);
	FVector ExplosionDirectionUp = FVector(0.0f, 1.0f, 0.0f);
	FVector ExplosionDirectionDown = FVector(0.0f, -1.0f, 0.0f);
	*/
	/*
	TArray<FVector> ExplosionDirections;
	Directions.Add(ExplosionDirectionRight);
	Directions.Add(ExplosionDirectionLeft);
	Directions.Add(ExplosionDirectionUp);
	Directions.Add(ExplosionDirectionDown);
	*/
	
	/*
	ExplosionHits(OutHitsRightRay, ExplosionDirectionRight);
	ExplosionHits(OutHitsLeftRay, ExplosionDirectionLeft);
	ExplosionHits(OutHitsUpRay, ExplosionDirectionUp);
	ExplosionHits(OutHitsDownRay, ExplosionDirectionDown);
	*/

		
	
	

	


	

	

	
	
	
	

	/*
	

	CollisionParams.bIgnoreTouches = false;
	// Ignoring thic so that it will not hit itself.
	
	


	
	FVector EndUp = Start + (ExplosionDirectionUp  * Range);
	DrawDebugLine(GetWorld(), Start, EndUp, FColor::Green, false, 30, 10, 5);
	bool isHitUp = GetWorld()->LineTraceMultiByChannel(OutHits3, Start, EndUp, ECC_Visibility, CollisionParams);

	

	

	FVector EndDown = Start + (ExplosionDirectionDown  * Range);
	DrawDebugLine(GetWorld(), Start, EndDown, FColor::Orange, false, 30, 10, 5);
	bool isHitDown = GetWorld()->LineTraceMultiByChannel(OutHits4, Start, EndDown, ECC_Visibility, CollisionParams);

	//change to function
	

	if (isHitLeft)
	{
		FHitResult RR2;
		FString RRRes2 = RR2.GetFirstBlockingHit(OutHits2)->GetActor()->GetName();
		GEngine->AddOnScreenDebugMessage(-1, 100000000000.0f, FColor::Blue, RRRes2);
	}

	if (isHitUp)
	{
		FHitResult RR3;
		FString RRRes3 = RR3.GetFirstBlockingHit(OutHits3)->GetActor()->GetName();
		GEngine->AddOnScreenDebugMessage(-1, 100000000000.0f, FColor::Green, RRRes3);
	}

	if (isHitDown)
	{ 
		FHitResult RR4;
		FString RRRes4 = RR4.GetFirstBlockingHit(OutHits4)->GetActor()->GetName();
		GEngine->AddOnScreenDebugMessage(-1, 100000000000.0f, FColor::Orange, RRRes4);
	}
	
	// TODO Print OuthHits on screan 
	/*for (FHitResult Result : OutHits1)
	{
		
		
		
		
		GEngine->AddOnScreenDebugMessage(-1, 100000000000.0f, FColor::Purple, Res);
	}
	
	

	
	for (FHitResult Result : OutHits2)
	{
		FString Res = Result.GetActor()->GetName();
		GEngine->AddOnScreenDebugMessage(-1, 100000000000.0f, FColor::Red, Res);
	}
	
	for (FHitResult Result : OutHits3)
	{
		FString Res = Result.GetActor()->GetName();
		GEngine->AddOnScreenDebugMessage(-1, 100000000000.0f, FColor::Red, Res);
	}
	
	for (FHitResult Result : OutHits4)
	{
		FString Res = Result.GetActor()->GetName();
		GEngine->AddOnScreenDebugMessage(-1, 100000000000.0f, FColor::Red, Res);
	}
	*/
}

