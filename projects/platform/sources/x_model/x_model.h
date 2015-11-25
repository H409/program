//*****************************************************************************
//
// x model
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************
#pragma once
#ifndef _X_MODEL_H_
#define _X_MODEL_H_

class XModel
{
public:
	XModel(LPDIRECT3DDEVICE9 in_direct3ddevice9,const std::string& in_filepath);
	virtual ~XModel(void);

	void Draw(void);
	void Draw(int part_number);

	DWORD GetPartCount(void)const;
	LPD3DXMATERIAL GetMaterial(void)const;
private:

	LPDIRECT3DDEVICE9 direct3ddevice9_;
	DWORD part_count_;
	LPD3DXMESH d3dxmesh_;
	LPD3DXMATERIAL d3dxmaterial_;
	LPD3DXBUFFER material_buffer_;
};

#endif	// _X_MODEL_H_

//---------------------------------- EOF --------------------------------------
