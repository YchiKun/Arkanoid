// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BreakableBlock.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScoreChangeDelegate, int32, Score);

UCLASS()
class ARKANOID_API ABreakableBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABreakableBlock();


	UPROPERTY(BlueprintAssignable)
		FScoreChangeDelegate ScoreChangeDelegate;

	UFUNCTION(BlueprintCallable)
		void ChangeScore(int32 Amount);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
		int32 Lives;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
		int32 Score;

	UPROPERTY(EditAnywhere, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
	float RandomSpawnBonus;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
		class UMaterialInstance* MatInsRed;
	UPROPERTY(EditAnywhere, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
		UMaterialInstance* MatInsBlue;
	UPROPERTY(EditAnywhere, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
		UMaterialInstance* MatInsWhite;
	UPROPERTY(EditAnywhere, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AActor> BonusToSpawn;

	UFUNCTION(BlueprintCallable)
	void SpawnBonus();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
