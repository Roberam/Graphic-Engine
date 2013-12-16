#include "../include/InputManager.h"
#include "windows.h"

InputManager::InputManager()
{
	_init = false;
	_mouseX = 0;
	_mouseY = 0;
}

InputManager::~InputManager()
{

}

bool InputManager::Init()
{
	_myVirtualAxis = Array<VirtualAxis>();
	_myVirtualButtons = Array<VirtualButton>();
	_init = true;
	//deteccción de dispostivos, inicialización de los mismos
	if (GetKeyboardType(0) != 0)
		bool prueba = true;
	if (GetSystemMetrics(SM_MOUSEPRESENT))
		bool prueba = true;

	return true;
}

void InputManager::End()
{
	_init = false;
}

bool InputManager::IsOk()
{
	return _init;
}

void InputManager::Update()
{
	bool pressed;
	int newMouseX = Screen::Instance().GetMouseX();
	int newMouseY = Screen::Instance().GetMouseY();

	for (uint32 i = 0; i < _myVirtualButtons.Size(); i++)
	{
		pressed = IsKeyPressed(_myVirtualButtons[i].button);
		_myVirtualButtons[i].keyDown = _myVirtualButtons[i].keyUp = false;
		
		if (!_myVirtualButtons[i].keyPress && pressed)
			_myVirtualButtons[i].keyDown = true;
		else if (_myVirtualButtons[i].keyPress && !pressed)
			_myVirtualButtons[i].keyUp = true;
		
		_myVirtualButtons[i].keyPress = pressed;
	}

	for (uint32 i = 0; i < _myVirtualAxis.Size(); i++)
	{
		if (!_myVirtualAxis[i].isMouse)
		{
			if (IsKeyPressed(_myVirtualAxis[i].positiveAxis))
				_myVirtualAxis[i].state = 1;
			else if (IsKeyPressed(_myVirtualAxis[i].negativeAxis))
				_myVirtualAxis[i].state = -1;
			else
				_myVirtualAxis[i].state = 0;
		}
		else
		{
			if (_myVirtualAxis[i].positiveAxis == Mouse_Up || _myVirtualAxis[i].positiveAxis == Mouse_Down)
			{
				if (_mouseY > newMouseY)
					_myVirtualAxis[i].state = -1;
				else if (_mouseY < newMouseY)
					_myVirtualAxis[i].state = 1;
				else
					_myVirtualAxis[i].state = 0;

				if (_myVirtualAxis[i].positiveAxis == Mouse_Down)
					_myVirtualAxis[i].state = -_myVirtualAxis[i].state;
			}
			else if (_myVirtualAxis[i].positiveAxis == Mouse_Right || _myVirtualAxis[i].positiveAxis == Mouse_Left)
			{
				if (_mouseX > newMouseX)
					_myVirtualAxis[i].state = -1;
				else if (_mouseX < newMouseX)
					_myVirtualAxis[i].state = 1;
				else
					_myVirtualAxis[i].state = 0;

				if (_myVirtualAxis[i].positiveAxis == Mouse_Left)
					_myVirtualAxis[i].state = -_myVirtualAxis[i].state;
			}
		}
	}
	_mouseX = newMouseX;
	_mouseY = newMouseY;
}

void InputManager::CreateVirtualButton( const String& name, eInputCode button )
{
	int i = 0;
	if (!existsVButton(i,name))
	{
		VirtualButton auxVB;
		auxVB.name = name;
		auxVB.button = button;
		auxVB.keyDown = false;
		auxVB.keyUp = false;
		auxVB.keyPress = false;
		_myVirtualButtons.Add(auxVB);
	}
}

void InputManager::CreateVirtualAxis( const String& name, eInputCode positiveAxis, eInputCode negativeAxis )
{
	int i = 0;
	if (!existsVAxis(i,name))
	{
		VirtualAxis auxA;
		auxA.name = name;
		auxA.negativeAxis = negativeAxis;
		auxA.positiveAxis = positiveAxis;
		auxA.state = 0;
		if (positiveAxis >= Mouse_Down && positiveAxis <= Mouse_Right)
			auxA.isMouse = true;
		else
			auxA.isMouse = false;
		_myVirtualAxis.Add(auxA);
	}
}

bool InputManager::IsVirtualButtonPressed( const String& name ) const
{
	int i = 0;
	return (existsVButton(i,name) && _myVirtualButtons[i].keyPress);
}

bool InputManager::IsVirtualButtonDown( const String& name ) const
{
	int i = 0;
	return (existsVButton(i,name) && _myVirtualButtons[i].keyDown);
}

bool InputManager::IsVirtualButtonUp( const String& name ) const
{
	int i = 0;
	return (existsVButton(i,name) && _myVirtualButtons[i].keyUp);
}

float InputManager::GetVirtualAxis( String name ) const
{
	int i = 0;
	float aux = 0.0;
	if (existsVAxis(i,name))
		aux = _myVirtualAxis[i].state;
	return aux;
}

bool InputManager::IsKeyPressed( eInputCode vkCode )
{
	return Screen::Instance().KeyPressed(vkCode);
}

bool InputManager::IsKeyDown( eInputCode vkCode )
{
	return false;
}

bool InputManager::IsKeyUp( eInputCode vkCode )
{
	return false;
}

bool InputManager::IsMouseButtonPressed( eInputCode button )
{
	return false;
}

bool InputManager::GetMouseButtonDown( eInputCode button )
{
	return false;
}

bool InputManager::GetMouseButtonUp( eInputCode button )
{
	return false;
}

bool InputManager::existsVButton(int& index, const String name) const
{
	bool found = false;
	index = 0;
	if (_myVirtualButtons.Size() > 0)
		while (!found && index < (int)_myVirtualButtons.Size())
		{
			if (_myVirtualButtons[index].name == name)
				found = true;
			else
				index++;
		}
	return found;
}

bool InputManager::existsVAxis(int& index, const String name) const
{
	bool found = false;
	index = 0;
	if (_myVirtualAxis.Size() > 0)
		while (!found && index < (int)_myVirtualAxis.Size())
		{
			if (_myVirtualAxis[index].name == name)
				found = true;
			else
				index++;
		}
	return found;
}
