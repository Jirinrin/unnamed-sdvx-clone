#pragma once
#include <Graphics/Keys.hpp>
#include "IImage.hpp"
#include "../../../Main/Gamepad/Gamepad.hpp"
#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>

#endif

namespace Graphics
{
	// Windowed or bordered window style
	enum class WindowStyle
	{
		Windowed, Borderless
	};

	// Text input data
	struct TextComposition
	{
		WString composition;
		int32 cursor;
		int32 selectionLength;
	};

	// Simple window class that manages window messages, window style
	class Window : Unique
	{
	public:
		explicit Window(Vector2i size = Vector2i{800, 600}, uint8 samplecount = 0);
		~Window();

		void Show();
		void Hide();
		void Close();

		// On windows: returns the HWND
		void* Handle();

		// Set the window title (caption)
		void SetCaption(const WString& cap);

		Vector2i GetMousePos();
		void SetMousePos(const Vector2i& pos);
		void SetRelativeMouseMode(bool enabled);
		bool GetRelativeMouseMode();

		// Sets cursor to use
		void SetCursor(const IImage& image, Vector2i hotspot = Vector2i(0,0));
		void SetCursorVisible(bool visible);

		// Switches between borderless and windowed
		void SetWindowStyle(WindowStyle style);

		// Get full window position
		Vector2i GetWindowPos() const;
		// Set full window position
		void SetWindowPos(const Vector2i& pos);

		// Window Client area size
		Vector2i GetWindowSize() const;

		// Set vsync setting
		void SetVSync(int8 setting);

		// Window is active
		bool IsActive() const;
		// Set window client area size
		void SetWindowSize(const Vector2i& size);
		void SwitchFullscreen(int w, int h, int fsw = -1, int fsh = -1, uint32 monitorID = -1, bool windowedFullscreen = false);
		bool IsFullscreen() const;

		int GetDisplayIndex() const;

		// Start allowing text input
		void StartTextInput();
		// Stop allowing text input
		void StopTextInput();
		// Used to get current IME working data
		const TextComposition& GetTextComposition() const;

		// Show a simple message box
		// level 0 = error, 1 = warning, 2 = info
		void ShowMessageBox(const String& title, const String& message, int severity);

		// Get the text currently in the clipboard
		WString GetClipboard() const;

	private:
		SDL_Window* m_window;
		SDL_Cursor* currentCursor = nullptr;

		// Window Input State
		Map<SDL_Keycode, uint8> m_keyStates;
		ModifierKeys m_modKeys = ModifierKeys::None;

		// Text input / IME stuff
		TextComposition m_textComposition;

		// Update loop
		Timer t;

		// Various window state
		bool m_active = true;
		bool m_closed = false;
		bool m_fullscreen = false;
		uint32 m_style;
		Vector2i m_clntSize;
		WString m_caption;

		void HandleKeyEvent(SDL_Keycode code, uint8 newState, int32 repeat);
	};
}