// Fill out your copyright notice in the Description page of Project Settings.


#include "BufferingBase.h"
#include "Outline/Objects/PlayerStateBase.h"

void UBufferingBase::TrySaveAsInputBuffer(FName InputAction)
{
	if (AllowedInputActions.Contains(InputAction))
	{
		switch (BufferingState)
		{
		case EInputBufferType::NO_BUFFER:
			break;		
		case EInputBufferType::INSTANT_FIRE:
			BufferedInput = InputAction;
			if (EffectedPlayerState->GetBufferingObjects().Contains(this))
			{
				EffectedPlayerState->SetBufferedInput(BufferedInput);
				EffectedPlayerState->FireBufferedInput();
				// like NO_BUFFER
				EffectedPlayerState->RemoveBufferingObject(this);
			}
			break;
		case EInputBufferType::LAST_REGISTERED:
			BufferedInput = InputAction;
			break;
		case EInputBufferType::HIGHEST_PRIORITY:
			if (!BufferedInput.IsNone())
			{
				// priority form high to lower : 0, 1, 2, 3, ...
				if (AllowedInputActions.Find(InputAction) < AllowedInputActions.Find(BufferedInput))
				{
					BufferedInput = InputAction;
				}
			}
			else
			{
				BufferedInput = InputAction;
			}
			break;
		}
	}
}

void UBufferingBase::EndBufferingObject()
{
	switch (BufferingState)
	{
	case EInputBufferType::NO_BUFFER:	
	case EInputBufferType::INSTANT_FIRE:
		EffectedPlayerState->RemoveBufferingObject(this);
		break;
	case EInputBufferType::LAST_REGISTERED:
	case EInputBufferType::HIGHEST_PRIORITY:
		if (BufferedInput.IsValid() && EffectedPlayerState->GetBufferingObjects().Contains(this))
		{
			EffectedPlayerState->SetBufferedInput(BufferedInput);			
			EffectedPlayerState->FireBufferedInput();
			EffectedPlayerState->RemoveBufferingObject(this);
		}
		break;
	}
}
