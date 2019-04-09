// Fill out your copyright notice in the Description page of Project Settings.

#include "FasterRunSpeed_Pickup.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"

AFasterRunSpeed_Pickup::AFasterRunSpeed_Pickup() 
{
	SuperMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SuperMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MyMesh(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (MyMesh.Succeeded())
		SuperMesh->SetStaticMesh(MyMesh.Object);
	


}






