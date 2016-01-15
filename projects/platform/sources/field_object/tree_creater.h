//*****************************************************************************
//
// tree creater
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************
#pragma once
#ifndef _TREE_CREATER_H_
#define _TREE_CREATER_H_

class TreeCreater
{
public:
	TreeCreater(void);
	virtual ~TreeCreater(void);

	void Update(void);

	void Death(void);

	void SetNumber(u32 in_number);
	void SetPosition(const float3& in_position);

	u32 GetNumber(void)const;

	const float3& GetPosition(void)const;

	bool IsCreate(void)const;
	bool IsDeath(void)const;

private:
	u32 number_;
	float3 position_;
	u32 frame_count_;
	bool is_create_;
	bool is_death_;
};

#endif // _TREE_CREATER_H_

//---------------------------------- EOF --------------------------------------
