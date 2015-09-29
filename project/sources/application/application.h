//*****************************************************************************
//
// application
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

//*****************************************************************************
// include
//*****************************************************************************

//*****************************************************************************
// forward declaration
//*****************************************************************************
class ApplicationSystem;
class Scene;

//*****************************************************************************
// class definition
//*****************************************************************************
class Application
{
private:
	using UScene = std::unique_ptr<Scene>;
	using UApplicationSystem = std::shared_ptr<ApplicationSystem>;

public:
	// constructor
	Application(ApplicationSystem* application_system);

	// destructor
	virtual ~Application(void);

	// update
	void Update(void);

	// accessor
	bool __is_stop(void)const { return is_stop_; }

private:
	UApplicationSystem application_system_;
	UScene current_scene_;
	bool is_stop_;
};

#endif // _APPLICATION_H_

//---------------------------------- EOF --------------------------------------
