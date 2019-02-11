// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "BattleTank.h"

void  ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController doesn't possess tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *(ControlledTank->GetName()));
	}
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));
}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void  ATankPlayerController::AimTowardsCrosshair() {
	if (!GetControlledTank()) {return;}
	FVector OutHitLocation; //Out Parameter
	if (GetSightRayHitLocation(OutHitLocation)) {
		//UE_LOG(LogTemp, Warning, TEXT("LookDirection: %s"), *OutHitLocation.ToString());
			//Tell tank aim at that point
	}
}
//Get world location of linetrace through crosshair, true if hits landscape
bool  ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const {
	//find crosshair pos
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	//Set screen position of crosshair to world direction
	//Line trace aloong that direction, and check what is hit

	return true;
}





