
#include "AICharacter.h"

#include "FPGGameInstance.h"
#include "RemakeAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

DEFINE_LOG_CATEGORY_STATIC(AAICharacterLog, All,All);

AAICharacter::AAICharacter(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ARemakeAIController::StaticClass();

	bUseControllerRotationYaw = false;

	if(GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0, 200, 0);
	}
}

void AAICharacter::OnDeath()
{
	Super::OnDeath();

	UE_LOG(AAICharacterLog, Warning, TEXT("AI Dead"));
	Cast<UFPGGameInstance>(GetGameInstance())->AddScore();
}
