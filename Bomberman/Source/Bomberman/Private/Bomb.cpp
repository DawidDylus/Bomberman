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
	//TODO Create function MultiRayTracing and check for colisions
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "BOOOM");
	
	TArray<FHitResult> OutHits;
	FCollisionQueryParams CollisionParams;
	FVector Start = GetActorLocation();	

	// TODO Change function to draw only 2 lines

	// Checking for colisions by drawing LineTraces to 4 sides
	FVector ExplosionDirectionRight = FVector(-1.0f, 0.0f, 0.0f);	
	FVector EndRight = Start + (ExplosionDirectionRight  * Range);		
	DrawDebugLine(GetWorld(), Start, EndRight, FColor::Red, true, 30, 10, 5);
	bool isHitRight = GetWorld()->LineTraceMultiByObjectType(OutHits, Start, EndRight, ECC_Visibility, CollisionParams);
	
	
	FVector ExplosionDirectionLeft = FVector(1.0f, 0.0f, 0.0f);
	FVector EndLeft = Start + (ExplosionDirectionLeft  * Range);
	DrawDebugLine(GetWorld(), Start, EndLeft, FColor::Blue, true, 30, 10, 5);
	bool isHitLeft = GetWorld()->LineTraceMultiByObjectType(OutHits, Start, EndLeft, ECC_Visibility, CollisionParams);


	FVector ExplosionDirectionUp = FVector(0.0f, 1.0f, 0.0f);
	FVector EndUp = Start + (ExplosionDirectionUp  * Range); 
	DrawDebugLine(GetWorld(), Start, EndUp, FColor::Green, true, 30, 10, 5);
	bool isHitUp = GetWorld()->LineTraceMultiByObjectType(OutHits, Start, EndUp, ECC_Visibility, CollisionParams);
		

	FVector ExplosionDirectionDown = FVector(0.0f, -1.0f, 0.0f);
	FVector EndDown = Start + (ExplosionDirectionDown  * Range);
	DrawDebugLine(GetWorld(), Start, EndDown, FColor::Orange, true, 30, 10, 5);
	bool isHitDown = GetWorld()->LineTraceMultiByObjectType(OutHits, Start, EndDown, ECC_Visibility, CollisionParams);



	
}

