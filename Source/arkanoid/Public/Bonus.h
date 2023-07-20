// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bonus.generated.h"

UENUM(BlueprintType)
enum  class EBonusType : uint8
{
	EBT_Max UMETA(DisplayName = "MAX"),
	EBT_Live UMETA(DisplayName = "LIVE"),
	EBT_Ball UMETA(DisplayName = "BALL"),
};

UCLASS()
class ARKANOID_API ABonus : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABonus();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SetBonusType();
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bonus, meta = (AllowPrivateAccess = "true"))
		int32 Type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bonus, meta = (AllowPrivateAccess = "true"))
		EBonusType BonusType;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE EBonusType GetBonusType() const { return BonusType; }

};
