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

void ABomb::Explosion()
{	
	
	// Checking for colisions by drawing LineTraces to 4 sides 
	// TODO Refactor Function
	TArray<FHitResult> OutHits1;
	
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this->GetUniqueID());
	CollisionParams.bIgnoreTouches = false;

	FVector Start = GetActorLocation() + FVector(0.0f, 0.0f, 50.0f);	//adding hight to be near center of actor
	FVector ExplosionDirectionRight = FVector(-1.0f, 0.0f, 0.0f);
	FVector EndRight = Start + (ExplosionDirectionRight  * Range);

	


	DrawDebugLine(GetWorld(), Start, EndRight, FColor::Red, false, 30, 10, 5);

	bool isHitRight = GetWorld()->LineTraceMultiByChannel(OutHits1, Start, EndRight, ECC_Visibility, CollisionParams);


	// TODO function that handle interaction with characters and boxes
	for(FHitResult Results : OutHits1)
	{		
		GEngine->AddOnScreenDebugMessage(-1, 100000000000.0f, FColor::Red, Results.GetActor()->GetName());
	}
	
	

	/*
	TArray<FHitResult> OutHits2;
	TArray<FHitResult> OutHits3;
	TArray<FHitResult> OutHits4;

	CollisionParams.bIgnoreTouches = false;
	// Ignoring thic so that it will not hit itself.
	

	FVector ExplosionDirectionLeft = FVector(1.0f, 0.0f, 0.0f);
	FVector EndLeft = Start + (ExplosionDirectionLeft  * Range);
	DrawDebugLine(GetWorld(), Start, EndLeft, FColor::Blue, false, 30, 10, 5);
	bool isHitLeft = GetWorld()->LineTraceMultiByChannel(OutHits2, Start, EndLeft, ECC_Visibility, CollisionParams);


	FVector ExplosionDirectionUp = FVector(0.0f, 1.0f, 0.0f);
	FVector EndUp = Start + (ExplosionDirectionUp  * Range);
	DrawDebugLine(GetWorld(), Start, EndUp, FColor::Green, false, 30, 10, 5);
	bool isHitUp = GetWorld()->LineTraceMultiByChannel(OutHits3, Start, EndUp, ECC_Visibility, CollisionParams);

	

	FVector ExplosionDirectionDown = FVector(0.0f, -1.0f, 0.0f);

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

