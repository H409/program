//*****************************************************************************
//
// windows main
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

#ifdef WIN32
//*****************************************************************************
// include
//*****************************************************************************
#include <Windows.h>

//=============================================================================
// �G���g���[�|�C���g�̃v���g�^�C�v�錾
//=============================================================================
int main(int argc,char* argv);

//=============================================================================
// win32�G���g���[�|�C���g
//=============================================================================
int APIENTRY WinMain(HINSTANCE hinstance,HINSTANCE preview_hinstance,LPSTR command_line,int command_show)
{
	main(0,nullptr);
}

#endif // WIN32

//---------------------------------- EOF --------------------------------------