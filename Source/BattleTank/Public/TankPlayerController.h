// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"


class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
    

protected:
    
        /// on game start plaing
        virtual void BeginPlay() override;
    
public:
    
    /// called in every frame
    virtual void Tick(float DeltaTime) override;
    
    // get player controlls
    ATank* GetPlayerController() const;
    
private:
    /// dot point sanpper
    void AimTowredsCrossHairLocation();
    bool GetSightRayHitLocation(FVector OutHitResult) const;
    
    UPROPERTY(EditAnywhere)
    float CrossHairXLocation = 0.5f;
    
    UPROPERTY(EditAnywhere)
    float CrossHairYLocation = 0.33333f;
	
    UPROPERTY(EditAnywhere)
    float LineTraceRange = 100000;
    
    bool GetPlayerAimPosition(FVector2D ScreenLocation, FVector &LookDirection) const;
    
    bool GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const;
};
