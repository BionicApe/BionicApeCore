// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "Widgets/Input/SButton.h"

class BIONICAPEUI_API USDisButton : public SButton
{
	/** @return True if this widget hovered */
	virtual bool IsHovered() const
	{
		return bIsHovered || HasKeyboardFocus();
	}
};
