// Created by Bionic Ape. All Rights Reserved.

#include "UI/Elements/DisButton.h"
#include "Components/ButtonSlot.h"
#include "UI/Elements/SDisButton.h"
#include "Components/PanelWidget.h"

TSharedRef<SWidget> UDisButton::RebuildWidget()
{
	MyButton = SNew(USDisButton)
		.OnClicked(BIND_UOBJECT_DELEGATE(FOnClicked, SlateHandleClicked))
		.OnPressed(BIND_UOBJECT_DELEGATE(FSimpleDelegate, SlateHandlePressed))
		.OnReleased(BIND_UOBJECT_DELEGATE(FSimpleDelegate, SlateHandleReleased))
		.OnHovered_UObject(this, &ThisClass::SlateHandleHovered)
		.OnUnhovered_UObject(this, &ThisClass::SlateHandleUnhovered)
		.ButtonStyle(&WidgetStyle)
		.ClickMethod(ClickMethod)
		.TouchMethod(TouchMethod)
		.PressMethod(PressMethod)
		.IsFocusable(IsFocusable)
		;

	if (GetChildrenCount() > 0)
	{
		Cast<UButtonSlot>(GetContentSlot())->BuildSlot(MyButton.ToSharedRef());
	}

	OnRebuildWidget();

	return MyButton.ToSharedRef();
}