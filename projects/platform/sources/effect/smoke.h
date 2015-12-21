//*****************************************************************************
//
// smoke
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************
#pragma once
#ifndef _SMOKE_H_
#define _SMOKE_H_
#include "effect.h"

class Smoke : public Effect
{
public:
	Smoke(void);

	virtual ~Smoke(void);

private:
	virtual void Update_(void)override;
};

#endif // _SMOKE_H_

//---------------------------------- EOF --------------------------------------
