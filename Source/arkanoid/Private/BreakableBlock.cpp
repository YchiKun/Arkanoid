// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakableBlock.h"
#include "Components/BoxComponent.h"
#include "Ball.h"
#include "Materials/MaterialInstance.h"
#include "Engine/World.h"

// Sets default values
ABreakableBlock::ABreakableBlock()
	: Lives(1), Score(100), RandomSpawnBonus(0.2f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	SetRootComponent(ItemMesh);
	ItemMesh->SetIsReplicated(true);
}

void ABreakableBlock::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	OtherActor = Cast<ABall>(OtherActor);
	if (OtherActor)
	{
		if (Lives <= 1)
		{
			ChangeScore(Score);
		}
		else
		{
			Lives -= 1; 
			switch (Lives)
			{
			case 1:
				if (MatInsWhite)
				{
					ItemMesh->SetMaterial(0, MatInsWhite);
				}
				break;
			case 2:
				if (MatInsRed)
				{
					ItemMesh->SetMaterial(0, MatInsRed);
				}
				break;
			case 3:
				if (MatInsBlue)
				{
					ItemMesh->SetMaterial(0, MatInsBlue);
				}
				break;
			default:
				break;
			}
		}
	}
}

// Called when the game starts or when spawned
void ABreakableBlock::BeginPlay()
{
	Super::BeginPlay();
    ItemMesh->OnComponentHit.AddDynamic(this, &ABreakableBlock::OnHit);
}

void ABreakableBlock::SpawnBonus()
{
	float Random = FMath::RandRange(0.0f, 1.0f);
	if (BonusToSpawn && Random < RandomSpawnBonus)
	{
		const FVector Location{ GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 100.0 };
		GetWorld()->SpawnActor<AActor>(BonusToSpawn, Location, GetActorRotation());
	}
}

// Called every frame
void ABreakableBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABreakableBlock::ChangeScore(int32 Amount)
{
	ScoreChangeDelegate.Broadcast(Amount);
}


