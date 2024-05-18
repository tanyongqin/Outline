// Fill out your copyright notice in the Description page of Project Settings.


#include "ImpactEffects.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"

void UImpactEffects::ApplyEffect()
{
	for (FEffects EffectToApply : Effects)
	{
		if (EffectToApply.SurfaceType == UGameplayStatics::GetSurfaceType(HitResult))
		{

			for (FImpactVFX VFXToApply : EffectToApply.ImpactVFXs)
			{
				ApplyVFX(VFXToApply);
			}

			for (FImpactSFX SFXToApply : EffectToApply.ImpactSFXs)
			{
				ApplySFX(SFXToApply);
			}
			return;
		}
	}
}

void UImpactEffects::ApplyVFX(FImpactVFX VFXToApply)
{
	if (HitResult.BoneName.IsNone())
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			VFXToApply.Emitter,
			HitResult.Location,
			VFXToApply.EmitterRotation,
			VFXToApply.EmitterScale
		);
	}
	else
	{
		UNiagaraFunctionLibrary::SpawnSystemAttached(
			VFXToApply.Emitter,
			HitResult.GetComponent(),
			HitResult.BoneName,
			HitResult.GetComponent()->GetSocketLocation(HitResult.BoneName),
			VFXToApply.EmitterRotation,
			VFXToApply.EmitterScale,
			EAttachLocation::KeepWorldPosition,
			true,
			ENCPoolMethod::None
		);
	}
}

void UImpactEffects::ApplySFX(FImpactSFX SFXToApply)
{
	if (HitResult.BoneName.IsNone())
	{
		UGameplayStatics::SpawnSoundAtLocation(
			GetWorld(),
			SFXToApply.Sound,
			HitResult.Location
		);
	}
	else
	{
		UGameplayStatics::SpawnSoundAttached(
			SFXToApply.Sound,
			HitResult.GetComponent(),
			HitResult.BoneName,
			HitResult.Location,
			EAttachLocation::KeepWorldPosition
		);
	}
}
