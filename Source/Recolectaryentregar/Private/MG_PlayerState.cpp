#include "MG_PlayerState.h"
#include "Net/UnrealNetwork.h"

void AMG_PlayerState::GetLifetimeReplicatedProps(
    TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AMG_PlayerState, IndividualScore);
    DOREPLIFETIME(AMG_PlayerState, TeamID);
    DOREPLIFETIME(AMG_PlayerState, bIsAlive);
}

void AMG_PlayerState::OnRep_PlayerAlive()
{
    UE_LOG(LogTemp, Warning, TEXT("PlayerAlive changed: %s"),
        bIsAlive ? TEXT("Alive") : TEXT("Dead"));
}