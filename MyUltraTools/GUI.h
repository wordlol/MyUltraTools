
void StyleGui()
{
		ImGuiStyle& style = ImGui::GetStyle();

		style.Alpha = 1.0f;
		style.DisabledAlpha = 0.6f;
		style.WindowPadding = ImVec2(8.0f, 8.0f);
		style.WindowRounding = 0.0f;
		style.WindowBorderSize = 1.0f;
		style.WindowMinSize = ImVec2(32.0f, 32.0f);
		style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
		style.WindowMenuButtonPosition = ImGuiDir_Left;
		style.ChildRounding = 0.0f;
		style.ChildBorderSize = 1.0f;
		style.PopupRounding = 0.0f;
		style.PopupBorderSize = 1.0f;
		style.FramePadding = ImVec2(4.0f, 3.0f);
		style.FrameRounding = 0.0f;
		style.FrameBorderSize = 1.0f;
		style.ItemSpacing = ImVec2(8.0f, 4.0f);
		style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
		style.CellPadding = ImVec2(4.0f, 2.0f);
		style.IndentSpacing = 21.0f;
		style.ColumnsMinSpacing = 6.0f;
		style.ScrollbarSize = 14.0f;
		style.ScrollbarRounding = 0.0f;
		style.GrabMinSize = 10.0f;
		style.GrabRounding = 0.0f;
		style.TabRounding = 0.0f;
		style.TabBorderSize = 0.0f;
		style.ColorButtonPosition = ImGuiDir_Right;
		style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
		style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

		style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.49803922f, 0.49803922f, 0.49803922f, 1.0f);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.28627452f, 0.3372549f, 0.25882354f, 1.0f);
		style.Colors[ImGuiCol_ChildBg] = ImVec4(0.28627452f, 0.3372549f, 0.25882354f, 1.0f);
		style.Colors[ImGuiCol_PopupBg] = ImVec4(0.23921569f, 0.26666668f, 0.2f, 1.0f);
		style.Colors[ImGuiCol_Border] = ImVec4(0.5372549f, 0.5686275f, 0.50980395f, 0.5f);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.13725491f, 0.15686275f, 0.10980392f, 0.52f);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(0.23921569f, 0.26666668f, 0.2f, 1.0f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26666668f, 0.29803923f, 0.22745098f, 1.0f);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.29803923f, 0.3372549f, 0.25882354f, 1.0f);
		style.Colors[ImGuiCol_TitleBg] = ImVec4(0.23921569f, 0.26666668f, 0.2f, 1.0f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.28627452f, 0.3372549f, 0.25882354f, 1.0f);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0f, 0.0f, 0.0f, 0.51f);
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.23921569f, 0.26666668f, 0.2f, 1.0f);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.34901962f, 0.41960785f, 0.30980393f, 1.0f);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.2784314f, 0.31764707f, 0.23921569f, 1.0f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.24705882f, 0.29803923f, 0.21960784f, 1.0f);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.22745098f, 0.26666668f, 0.20784314f, 1.0f);
		style.Colors[ImGuiCol_CheckMark] = ImVec4(0.5882353f, 0.5372549f, 0.1764706f, 1.0f);
		style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.34901962f, 0.41960785f, 0.30980393f, 1.0f);
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.5372549f, 0.5686275f, 0.50980395f, 0.5f);
		style.Colors[ImGuiCol_Button] = ImVec4(0.28627452f, 0.3372549f, 0.25882354f, 0.4f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.34901962f, 0.41960785f, 0.30980393f, 1.0f);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.5372549f, 0.5686275f, 0.50980395f, 0.5f);
		style.Colors[ImGuiCol_Header] = ImVec4(0.34901962f, 0.41960785f, 0.30980393f, 1.0f);
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.34901962f, 0.41960785f, 0.30980393f, 0.6f);
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.5372549f, 0.5686275f, 0.50980395f, 0.5f);
		style.Colors[ImGuiCol_Separator] = ImVec4(0.13725491f, 0.15686275f, 0.10980392f, 1.0f);
		style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.5372549f, 0.5686275f, 0.50980395f, 1.0f);
		style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.5882353f, 0.5372549f, 0.1764706f, 1.0f);
		style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.1882353f, 0.22745098f, 0.1764706f, 0.0f);
		style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.5372549f, 0.5686275f, 0.50980395f, 1.0f);
		style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.5882353f, 0.5372549f, 0.1764706f, 1.0f);
		style.Colors[ImGuiCol_Tab] = ImVec4(0.34901962f, 0.41960785f, 0.30980393f, 1.0f);
		style.Colors[ImGuiCol_TabHovered] = ImVec4(0.5372549f, 0.5686275f, 0.50980395f, 0.78f);
		style.Colors[ImGuiCol_TabActive] = ImVec4(0.5882353f, 0.5372549f, 0.1764706f, 1.0f);
		style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.23921569f, 0.26666668f, 0.2f, 1.0f);
		style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.34901962f, 0.41960785f, 0.30980393f, 1.0f);
		style.Colors[ImGuiCol_PlotLines] = ImVec4(0.60784316f, 0.60784316f, 0.60784316f, 1.0f);
		style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.5882353f, 0.5372549f, 0.1764706f, 1.0f);
		style.Colors[ImGuiCol_PlotHistogram] = ImVec4(1.0f, 0.7764706f, 0.2784314f, 1.0f);
		style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.0f, 0.6f, 0.0f, 1.0f);
		style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.1882353f, 0.1882353f, 0.2f, 1.0f);
		style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.30980393f, 0.30980393f, 0.34901962f, 1.0f);
		style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.22745098f, 0.22745098f, 0.24705882f, 1.0f);
		style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
		style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.06f);
		style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.5882353f, 0.5372549f, 0.1764706f, 1.0f);
		style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.7294118f, 0.6666667f, 0.23921569f, 1.0f);
		style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.5882353f, 0.5372549f, 0.1764706f, 1.0f);
		style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 0.7f);
		style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.8f, 0.8f, 0.8f, 0.2f);
		style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.8f, 0.8f, 0.8f, 0.35f);
}

#include <imgui.h>
#include <cstdio>
#include <cstdlib>

static bool stopwatchRunning = false;      // запущен ли отсчёт
static bool stopwatchPaused = false;       // на паузе (если running)
static double stopwatchTime = 0.0;         // накопленное время в секундах

void UpdateStopwatch(float deltaTime) {
	if (stopwatchRunning && !stopwatchPaused) {
		stopwatchTime += deltaTime;
	}
}

static void ShowStopwatchWindow() {
	ImGuiWindowFlags flags =
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoDocking;

	static bool firstTime = true;
	static ImVec2 windowPos(100, 100);
	if (firstTime) {
		// Центрируем окно на экране
		RECT rect;
		GetClientRect(GetDesktopWindow(), &rect);
		ImVec2 size(300, 80); // примерный размер
		windowPos.x = (rect.right - size.x) / 2;
		windowPos.y = (rect.bottom - size.y) / 2;
		firstTime = false;
	}
	ImGui::SetNextWindowPos(windowPos, ImGuiCond_FirstUseEver);

	bool open = true;
	if (ImGui::Begin("Stopwatch", &open, flags)) {

		// Перетаскивание
		if (ImGui::IsWindowHovered() && ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
			ImVec2 delta = ImGui::GetMouseDragDelta(ImGuiMouseButton_Left);
			windowPos.x += delta.x;
			windowPos.y += delta.y;
			ImGui::SetWindowPos(windowPos);
			ImGui::ResetMouseDragDelta(ImGuiMouseButton_Left);
		}

		// Время
		int hours = (int)(stopwatchTime / 3600);
		int minutes = (int)((stopwatchTime - hours * 3600) / 60);
		int seconds = (int)(stopwatchTime - hours * 3600 - minutes * 60);
		char timeText[32];
		sprintf_s(timeText, sizeof(timeText), "%02d:%02d:%02d", hours, minutes, seconds);
		ImGui::Text("%s", timeText);

		// Кнопки
		ImGui::SameLine();
		if (ImGui::Button("Пауза")) {
			if (!stopwatchRunning) {
				stopwatchRunning = true;
				stopwatchPaused = false;
			}
			else if (stopwatchPaused) {
				stopwatchPaused = false;
			}
			else {
				stopwatchPaused = true;
			}
		}
		ImGui::SameLine();
		if (ImGui::Button("Сброс")) {
			stopwatchTime = 0.0;
			stopwatchRunning = false;
			stopwatchPaused = false;
		}
		ImGui::SameLine();
		if (ImGui::Button("Выход")) {
			std::exit(0);
		}

		// ---------- Применяем стиль и показываем окно ----------
		ImGuiViewport* viewport = ImGui::GetWindowViewport();
		if (viewport && viewport->PlatformHandle) {
			HWND hwnd = (HWND)viewport->PlatformHandle;

			// Убираем рамки и системное меню (делаем один раз, но можно и каждый кадр)
			static bool styleApplied = false;
			if (!styleApplied) {
				LONG_PTR style = GetWindowLongPtr(hwnd, GWL_STYLE);
				style &= ~(WS_CAPTION | WS_THICKFRAME | WS_SYSMENU);
				SetWindowLongPtr(hwnd, GWL_STYLE, style);

				SetWindowLongPtr(hwnd, GWL_EXSTYLE, WS_EX_TOOLWINDOW | WS_EX_TOPMOST);
				SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0,
					SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
				styleApplied = true;
			}

			// ----- ЯВНО ПОКАЗЫВАЕМ ОКНО -----
			if (!IsWindowVisible(hwnd)) {
				ShowWindow(hwnd, SW_SHOW);
				SetForegroundWindow(hwnd);
			}
		}
	}
	ImGuiViewport* viewport = ImGui::GetWindowViewport();
	if (viewport && viewport->PlatformHandle) {
		HWND hwndStopwatch = (HWND)viewport->PlatformHandle;
		// Применяем стили (без рамок, поверх всех)
		static bool styleApplied = false;
		if (!styleApplied) {
			SetWindowLong(hwndStopwatch, GWL_STYLE, GetWindowLong(hwndStopwatch, GWL_STYLE) & ~(WS_CAPTION | WS_THICKFRAME | WS_SYSMENU));
			SetWindowLong(hwndStopwatch, GWL_EXSTYLE, GetWindowLong(hwndStopwatch, GWL_EXSTYLE) | WS_EX_TOOLWINDOW | WS_EX_TOPMOST);
			SetWindowPos(hwndStopwatch, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
			styleApplied = true;
		}
		// Принудительно показываем, если скрыто
		if (!IsWindowVisible(hwndStopwatch)) {
			ShowWindow(hwndStopwatch, SW_SHOW);
			SetForegroundWindow(hwndStopwatch);
		}
	}

	ImGui::End();
}


class UserInterface {
public:
	static void ViewGUI() {
		ImGuiID dockspace_id = ImGui::GetID("My Dockspace");
		ImGuiViewport* viewport = ImGui::GetMainViewport();

		if (ImGui::DockBuilderGetNode(dockspace_id) == nullptr) {
			ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);
			ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);
			ImGuiID dock_id_left = 0;
			ImGuiID dock_id_main = dockspace_id;
			ImGui::DockBuilderSplitNode(dock_id_main, ImGuiDir_Left, 0.20f, &dock_id_left, &dock_id_main);
			ImGuiID dock_id_left_top = 0;
			ImGuiID dock_id_left_bottom = 0;
			ImGui::DockBuilderSplitNode(dock_id_left, ImGuiDir_Up, 0.50f, &dock_id_left_top, &dock_id_left_bottom);
			ImGui::DockBuilderDockWindow("Market UI", dock_id_left_bottom);
			ImGui::DockBuilderFinish(dockspace_id);
		}

		ImGui::DockSpaceOverViewport(dockspace_id, viewport, ImGuiDockNodeFlags_PassthruCentralNode);

		ShowStopwatchWindow();
	}
};

void Update() {
	static float deltaTime = 0.0f;
	deltaTime = ImGui::GetIO().DeltaTime;
	UpdateStopwatch(deltaTime);
	UserInterface::ViewGUI();
}


void Init()
{
	ImGuiIO& io = ImGui::GetIO();
	ImFont* font = io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/arial.ttf", 16.0f, nullptr, io.Fonts->GetGlyphRangesCyrillic());
	if (!font)
	{
		font = io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/tahoma.ttf", 16.0f, nullptr, io.Fonts->GetGlyphRangesCyrillic());
	}
	io.Fonts->Build();
	StyleGui();
}


