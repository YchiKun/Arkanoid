// Fill out your copyright notice in the Description page of Project Settings.


#include "Bonus.h"
#include "Math/UnrealMathUtility.h"


// Sets default values
ABonus::ABonus()
	:Speed(1000), Type(1)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	SetRootComponent(ItemMesh);

	ItemMesh->SetSimulatePhysics(true);
	ItemMesh->SetEnableGravity(false);
}

void ABonus::SetBonusType()
{
	switch (Type)
	{
	case 0:
		BonusType = EBonusType::EBT_Max;
		break;
	case 1:
		BonusType = EBonusType::EBT_Live;
		break;
	case 2:
		BonusType = EBonusType::EBT_Ball;
		break;
	default:
		BonusType = EBonusType::EBT_Max;
		break;
	}
}

void ABonus::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABonus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const float DeltaSpeed{ Speed * DeltaTime };
	const FVector LocationOffset{0.0, -DeltaSpeed, 0.0 };

	AddActorWorldOffset(LocationOffset, true);

}

