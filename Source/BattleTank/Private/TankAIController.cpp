// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    
    auto PlayerPawn = GetPlayerController();
    
    if(!PlayerPawn)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player not spowand"))
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AI Says Player spwan is:  %s"), *(PlayerPawn->GetName()))
    }
    
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick( DeltaTime );

    if(GetAIController())
    {
        GetAIController()->AimAt(GetPlayerController()->GetActorLocation());
    }
}

ATank* ATankAIController::GetAIController() const
{
    return Cast<ATank>(GetPawn());
}


ATank* ATankAIController::GetPlayerController() const
{
    auto PlayerController = GetWorld()->GetFirstPlayerController()->GetPawn();
    
    return Cast<ATank>(PlayerController);
}
