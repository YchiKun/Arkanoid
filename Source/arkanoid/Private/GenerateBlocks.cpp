// Fill out your copyright notice in the Description page of Project Settings.


#include "GenerateBlocks.h"
#include "Math/UnrealMathUtility.h"
#include <BreakableBlock.h>

// Sets default values
AGenerateBlocks::AGenerateBlocks()
	:MinCountX(1),MaxCountX(10), MinCountY(1), MaxCountY(10), Size(100), PaddingX(100), PaddingY(100)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AGenerateBlocks::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AGenerateBlocks::SpawnBlock()
{
	const int32 CountX = FMath::RandRange(MinCountX, MaxCountX);
	const int32 CountY = FMath::RandRange(MinCountY, MaxCountY);
	for (int32 i = 0; i < CountX; ++i)
	{
		for (int32 k = 0; k < CountY; ++k)
		{
			PaddingX = (MaxCountX * Size) / CountX;
			PaddingY = (MaxCountY * Size) / CountY;
			const FVector Location{ this->GetActorLocation().X + (double)i * PaddingX,this->GetActorLocation().Y + (double)k * -PaddingY, this->GetActorLocation().Z };
			const FRotator Rotation{ GetActorRotation() };
			BlockArray.Add(GetWorld()->SpawnActor<AActor>(BlockToSpawn, Location, Rotation));
		}
	}
}

// Called when the game starts or when spawned
void AGenerateBlocks::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGenerateBlocks::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

