#include "MG_PlayerController.h"

void AMG_PlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (IsLocalController())
    {
        // Camara fija
        AActor* CamaraFija = nullptr;
        for (TActorIterator<ACameraActor> It(GetWorld()); It; ++It)
        {
            CamaraFija = *It;
            break;
        }

        if (CamaraFija)
        {
            SetViewTarget(CamaraFija);
        }

        // Crear y mostrar el HUD
        if (HUDWidgetClass)
        {
            HUDWidgetInstance = CreateWidget<UUserWidget>(this, HUDWidgetClass);
            if (HUDWidgetInstance)
            {
                HUDWidgetInstance->AddToViewport();
            }
        }
    }
}

void AMG_PlayerController::Client_ShowVictoryScreen_Implementation(bool bWon)
{
    UE_LOG(LogTemp, Warning, TEXT("ShowVictoryScreen: %s"),
        bWon ? TEXT("Win") : TEXT("Lose"));
}

void AMG_PlayerController::Client_UpdateHUD_Implementation(int32 Score, float Time)
{
    UE_LOG(LogTemp, Warning, TEXT("HUD Update - Score: %d Time: %.1f"), Score, Time);
}