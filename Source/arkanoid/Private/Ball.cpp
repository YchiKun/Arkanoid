// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"
#include "Paddle.h"

// Sets default values
ABall::ABall()
	: Speed(300.0f), AddedSpeed(20.0f),MaxSpeed(2000.0f), Location(0.2f, 1.0f, 0.0f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	SetRootComponent(ItemMesh);

	ItemMesh->SetSimulatePhysics(true);
	ItemMesh->SetEnableGravity(false);
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
}

void ABall::Movement(float DeltaTime)
{
	const float DeltaSpeed{ Speed * DeltaTime };
	const FVector LocationOffset{ Location * DeltaSpeed };
	FHitResult HitResult{};

	AddActorWorldOffset(LocationOffset, true, &HitResult);

	FVector ReflectionVector{ FMath::GetReflectionVector(Location, HitResult.Normal)};
	ReflectionVector.Z = 0.0;
	if (HitResult.bBlockingHit)
	{
		Location = ReflectionVector;
		Speed = FMath::Min(Speed + AddedSpeed, MaxSpeed);
	}
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Movement(DeltaTime);

}
