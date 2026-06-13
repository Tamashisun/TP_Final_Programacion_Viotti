#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraActor.h"
#include "EngineUtils.h"
#include "Blueprint/UserWidget.h"
#include "MG_PlayerController.generated.h"

UCLASS()
class RECOLECTARYENTREGAR_API AMG_PlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;

    UFUNCTION(Client, Reliable)
    void Client_ShowVictoryScreen(bool bWon);

    UFUNCTION(Client, Reliable)
    void Client_UpdateHUD(int32 Score, float Time);

    // Clase del Widget HUD, asignar en BP_MG_PlayerController o BP_GMode
    UPROPERTY(EditDefaultsOnly, Category = "HUD")
    TSubclassOf<UUserWidget> HUDWidgetClass;

private:
    UPROPERTY()
    UUserWidget* HUDWidgetInstance;
};