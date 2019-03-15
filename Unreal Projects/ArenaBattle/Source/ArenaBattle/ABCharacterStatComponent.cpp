// Fill out your copyright notice in the Description page of Project Settings.

#include "ABCharacterStatComponent.h"
#include "ABGameInstance.h"


// Sets default values for this component's properties
UABCharacterStatComponent::UABCharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;	// 이 설정을 해줘야 컴포넌트의 초기화가 이루어진다.

	Level = 15;
}

// Called when the game starts
void UABCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();
}

/*
	chapter 11

	액터의 PostInitializeComponents 에 대응하는 컴포넌트의 함수는 InitializeComponent 함수다.
	이 함수는 PostInitializeComponents 함수가 호출되기 바로 전에 호출된다.
*/
void UABCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetNewLevel(Level);
}

void UABCharacterStatComponent::SetNewLevel(int32 NewLevel)
{
	auto ABGameInstance = Cast<UABGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	ABCHECK(nullptr != ABGameInstance);
	CurrentStatData = ABGameInstance->GetABCharacterData(NewLevel);
	if (nullptr != CurrentStatData)
	{
		Level = NewLevel;
		CurrentHP = CurrentStatData->MaxHP;
		//SetHP(CurrentStatData->MaxHP);
	}
	else
	{
		ABLOG(Error, TEXT("Level (%d) data doesn't exist"), NewLevel);
	}
}

void UABCharacterStatComponent::SetDamage(float NewDamage)
{
	ABCHECK(nullptr != CurrentStatData);

	CurrentHP = FMath::Clamp<float>(CurrentHP - NewDamage, 0.0f, CurrentStatData->MaxHP);

	if (CurrentHP < KINDA_SMALL_NUMBER)
	{
		OnHPIsZero.Broadcast();
	}

	//SetHP(FMath::Clamp<float>(CurrentHP - NewDamage, 0.0f, CurrentStatData->MaxHP));
}

//void UABCharacterStatComponent::SetHP(float NewHP)
//{
//	CurrentHP = NewHP;
//	OnHPChanged.Broadcast();
//	if (CurrentHP < KINDA_SMALL_NUMBER)
//	{
//		CurrentHP = 0.0f;
//		OnHPIsZero.Broadcast();
//	}
//}

float UABCharacterStatComponent::GetAttack()
{
	ABCHECK(nullptr != CurrentStatData, 0.0f);
	return CurrentStatData->Attack;
}

//float UABCharacterStatComponent::GetHPRatio()
//{
//	ABCHECK(nullptr != CurrentStatData, 0.0f);
//
//	return (CurrentStatData->MaxHP < KINDA_SMALL_NUMBER) ? 0.0f : (CurrentHP / CurrentStatData->MaxHP);
//}
