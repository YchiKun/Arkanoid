// Fill out your copyright notice in the Description page of Project Settings.


#include "Paddle.h"
#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"
#include "Components/ArrowComponent.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "Bonus.h"
#include "Ball.h"

// Sets default values
APaddle::APaddle()
	:Lives(3), MaxScale(6.0), MainScore(0)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	SetRootComponent(ItemMesh);

	ItemMesh->SetSimulatePhysics(false);
	ItemMesh->SetEnableGravity(false);
	ItemMesh->SetIsReplicated(true);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(ItemMesh);

}


// Called when the game starts or when spawned
void APaddle::BeginPlay()
{
	Super::BeginPlay();
	ItemMesh->OnComponentBeginOverlap.AddDynamic(this, &APaddle::OnBoxOverlap);
	Ball = nullptr;
}

void APaddle::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		auto bonus = Cast<ABonus>(OtherActor);
		if (bonus)
		{
			const double ScaleX = FMath::Min(ItemMesh->GetRelativeScale3D().X * 1.2f, MaxScale.X);
			const FVector Scale{ ScaleX, ItemMesh->GetRelativeScale3D().Y, ItemMesh->GetRelativeScale3D().Z };
			FVector LocationBall{ Arrow->GetComponentLocation() };
			const FRotator Rotation{ GetActorRotation() };

			if (IsValid(Ball))
			{
				LocationBall = FVector(Ball->GetActorLocation().X + 120, Ball->GetActorLocation().Y, Ball->GetActorLocation().Z);
			}

			switch (bonus->GetBonusType())
			{
			case EBonusType::EBT_Max:
				ItemMesh->SetRelativeScale3D(Scale);
				break;
			case EBonusType::EBT_Ball:
				GetWorld()->SpawnActor<ABall>(SpawnedBall, LocationBall, Rotation)->SetReplicates(true);
				break;
			case EBonusType::EBT_Live:
				ChangeLives(1);
				break;
			default:
				break;
			}
			bonus->Destroy();
		}
	}
}

void APaddle::ChangeLives(int32 Amount)
{
	Lives += Amount;
	LivesChangeDelegate.Broadcast(Amount);
}

// Called every frame
void APaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	//PlayerInputComponent->BindAxis("HorizontalMovement", this, &APaddle::MoveHorizontal);
	//PlayerInputComponent->BindAction("SpawnBall", IE_Pressed, this, &APaddle::SpawnBall);

}

void APaddle::MoveHorizontal(float Value)
{
	if ((Controller != nullptr) && Value != 0.0f)
	{
		const float DeltaSpeed{ Value * Speed * GetWorld()->GetDeltaSeconds()};
		const FVector LocationOffset{DeltaSpeed, 0.0, 0.0};

		AddActorWorldOffset(LocationOffset, true);
	}
}

void APaddle::SpawnBall()
{
	if (!IsValid(Ball) && SpawnedBall && Lives > 0)
	{
		const FVector LocationBall{ Arrow->GetComponentLocation() };
		const FRotator Rotation{ GetActorRotation() };
		Ball = GetWorld()->SpawnActor<ABall>(SpawnedBall, LocationBall, Rotation);
		Ball->SetReplicates(true);
		Ball->SetReplicateMovement(true);
	}
}