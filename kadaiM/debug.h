//���d��`�h�~
#ifndef __DEBUG_H__
#define __DEBUG_H__

//���������[�N�`�F�b�N
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


//���������[�N�ꏊ�`�F�b�N
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW	new(_NORMAL_BLOCK,__FILE__,__LINE__)
#define new DBG_NEW
#endif
#endif	//�QDEBUG

#endif