#include "Component/BackpackComponent.h"

UBackpackComponent::UBackpackComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}
void UBackpackComponent::BeginPlay()
{
	Super::BeginPlay();
	//BackpackWidget->Call();
}

void UBackpackComponent::PickItem(FPickItemData ItemData)
{
	
}

void UBackpackComponent::UseItem()
{
}

void UBackpackComponent::ThrowItem()
{
}

void UBackpackComponent::SwitchBackpackOpen()
{
	
}

