#include <iostream>
#include "..\includes\stdafx.h"
#include "dllmain.h"
#include "cfgMenu.h"
#include "WndProcHook.h"
#include "Settings.h"
#include "ConsoleWnd.h"
#include "../external/imgui/imgui.h"

WNDPROC oWndProc;
HWND hWindow;

void processRawMouse(RAWMOUSE rawMouse)
{
	ImGuiIO& io = ImGui::GetIO();

	switch (rawMouse.usButtonFlags)
	{
	case RI_MOUSE_LEFT_BUTTON_DOWN:
		io.MouseDown[0] = true;
		break;
	case RI_MOUSE_RIGHT_BUTTON_DOWN:
		io.MouseDown[1] = true;
		break;
	case RI_MOUSE_MIDDLE_BUTTON_DOWN:
		io.MouseDown[2] = true;
		break;
	case RI_MOUSE_LEFT_BUTTON_UP:
		io.MouseDown[0] = false;
		break;
	case RI_MOUSE_RIGHT_BUTTON_UP:
		io.MouseDown[1] = false;
		break;
	case RI_MOUSE_MIDDLE_BUTTON_UP:
		io.MouseDown[2] = false;
		break;
	case RI_MOUSE_WHEEL:
		io.MouseWheel += (float)(short)rawMouse.usButtonData / (float)WHEEL_DELTA;
		break;
	case RI_MOUSE_HWHEEL:
		io.MouseWheelH += (float)(short)rawMouse.usButtonData / (float)WHEEL_DELTA;
		break;
	default:
		break;
	}
}

// Our new hooked WndProc function
int curPosX;
int curPosY;
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
		case WM_KEYDOWN:
			if (wParam == cfg.KeyMap(cfg.flip_item_left.data(), "vk") || wParam == cfg.KeyMap(cfg.flip_item_right.data(), "vk"))
			{
				bShouldFlipX = true;
				Sleep(1);
			}
			else if (wParam == cfg.KeyMap(cfg.flip_item_up.data(), "vk") || wParam == cfg.KeyMap(cfg.flip_item_down.data(), "vk"))
			{
				bShouldFlipY = true;
				Sleep(1);
			}
			if (wParam == VK_F1)
			{
				bCfgMenuOpen ^= 1;
				// Send WM_ACTIVATE to make the game immediately respond to mouse messages
				SendMessage(hWnd, WM_ACTIVATE, (WPARAM)lParam, 0);
			}
			#ifdef VERBOSE
			if (wParam == VK_F2)
			{
				bConsoleOpen ^= 1;
			}
			else if (wParam == VK_NUMPAD3)
			{
				con.AddLogChar("Sono me... dare no me?");
			}
			#endif
			break;

		case WM_MOVE:
			// Get current window position
			curPosX = (int)(short)LOWORD(lParam);   // horizontal position 
			curPosY = (int)(short)HIWORD(lParam);   // vertical position 
			break;

		case WM_EXITSIZEMOVE:
			if (cfg.bRememberWindowPos)
			{
				// Write new window position
				#ifdef VERBOSE
				con.AddConcatLog("curPosX = ", curPosY);
				con.AddConcatLog("curPosY = ", curPosX);
				#endif

				CIniReader iniReader("");

				cfg.iWindowPositionX = curPosX;
				cfg.iWindowPositionY = curPosY;

				iniReader.WriteInteger("DISPLAY", "WindowPositionX", curPosX);
				iniReader.WriteInteger("DISPLAY", "WindowPositionY", curPosY);
			}
			break;

		case WM_CLOSE:
			ExitProcess(0);
			break;

		// Raw input stuff for ImGui
		case WM_INPUT: {
			HRAWINPUT rawInput = (HRAWINPUT)lParam;
			UINT dwSize = 0;
			if (GetRawInputData((HRAWINPUT)rawInput, RID_INPUT, nullptr, &dwSize, sizeof(RAWINPUTHEADER)) == -1) {
				break;
			}

			LPBYTE lpb = new BYTE[dwSize];
			if (lpb == nullptr) {
				break;
			}

			if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER)) != dwSize) {
				con.AddLogChar("GetRawInputData returned an incorrect size");
			}

			RAWINPUT* raw = (RAWINPUT*)lpb;

			if (raw->header.dwType == RIM_TYPEMOUSE) {
				if (raw->data.mouse.usButtonFlags)
					processRawMouse(raw->data.mouse);
			}

			delete[]lpb;
			break;
		}
	}

	if (bCfgMenuOpen) {
		return ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
	}
	else {
		return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
	}
}

// CreateWindowExA hook to get the hWindow and set up the WndProc hook
HWND __stdcall CreateWindowExA_Hook(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
	int windowX = cfg.iWindowPositionX < 0 ? CW_USEDEFAULT : cfg.iWindowPositionX;
	int windowY = cfg.iWindowPositionY < 0 ? CW_USEDEFAULT : cfg.iWindowPositionY;

	HWND result = CreateWindowExA(dwExStyle, lpClassName, lpWindowName, cfg.bWindowBorderless ? WS_POPUP : dwStyle, windowX, windowY, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
	hWindow = result;

	oWndProc = (WNDPROC)SetWindowLongPtr(hWindow, GWL_WNDPROC, (LONG_PTR)WndProc);

	return result;
}

void Init_WndProcHook()
{
	//CreateWindowEx hook
	auto pattern = hook::pattern("68 00 00 00 80 56 68 ? ? ? ? 68 ? ? ? ? 6A 00");
	injector::MakeNOP(pattern.get_first(0x12), 6);
	injector::MakeCALL(pattern.get_first(0x12), CreateWindowExA_Hook, true);
}