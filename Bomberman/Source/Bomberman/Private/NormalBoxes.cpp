// Fill out your copyright notice in the Description page of Project Settings.

#include "NormalBoxes.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"


// Sets default values
ANormalBoxes::ANormalBoxes()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Sets default mesh 
	SuperMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SuperMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MyMesh(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	if(MyMesh.Succeeded())
	SuperMesh->SetStaticMesh(MyMesh.Object);	
	
	
	
}



// Called when the game starts or when spawned
void ANormalBoxes::BeginPlay()
{
	Super::BeginPlay();	
	
	
}

// Called every frame
void ANormalBoxes::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

