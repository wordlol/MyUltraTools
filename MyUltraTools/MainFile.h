#pragma once
#define LOG    "..\\MyUltraTools\\Log\\"
#define LOGL   L"..\\MyUltraTools\\Log\\"
#define IMAGE  "..\\MyUltraTools\\Images\\"
#define IMAGEL L"..\\MyUltraTools\\Images\\"

void StyleGui1()
{
	ImGuiStyle& style = ImGui::GetStyle();

	style.Alpha = 1.0f;
	style.DisabledAlpha = 0.6f;
	style.WindowPadding = ImVec2(8.0f, 8.0f);
	style.WindowRounding = 4.0f;
	style.WindowBorderSize = 1.0f;
	style.WindowMinSize = ImVec2(32.0f, 32.0f);
	style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
	style.WindowMenuButtonPosition = ImGuiDir_None;
	style.ChildRounding = 4.0f;
	style.ChildBorderSize = 1.0f;
	style.PopupRounding = 4.0f;
	style.PopupBorderSize = 1.0f;
	style.FramePadding = ImVec2(4.0f, 3.0f);
	style.FrameRounding = 4.0f;
	style.FrameBorderSize = 1.0f;
	style.ItemSpacing = ImVec2(8.0f, 4.0f);
	style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
	style.CellPadding = ImVec2(4.0f, 2.0f);
	style.IndentSpacing = 21.0f;
	style.ColumnsMinSpacing = 6.0f;
	style.ScrollbarSize = 14.0f;
	style.ScrollbarRounding = 4.0f;
	style.GrabMinSize = 10.0f;
	style.GrabRounding = 20.0f;
	style.TabRounding = 4.0f;
	style.TabBorderSize = 1.0f;
	style.ColorButtonPosition = ImGuiDir_Right;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

	style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.49803922f, 0.49803922f, 0.49803922f, 1.0f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.11372549f, 0.11372549f, 0.11372549f, 1.0f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.078431375f, 0.078431375f, 0.078431375f, 0.94f);
	style.Colors[ImGuiCol_Border] = ImVec4(1.0f, 1.0f, 1.0f, 0.16309011f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.08627451f, 0.08627451f, 0.08627451f, 1.0f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.15294118f, 0.15294118f, 0.15294118f, 1.0f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.1882353f, 0.1882353f, 0.1882353f, 1.0f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.11372549f, 0.11372549f, 0.11372549f, 1.0f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.105882354f, 0.105882354f, 0.105882354f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0f, 0.0f, 0.0f, 0.51f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.11372549f, 0.11372549f, 0.11372549f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.019607844f, 0.019607844f, 0.019607844f, 0.53f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.30980393f, 0.30980393f, 0.30980393f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40784314f, 0.40784314f, 0.40784314f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.50980395f, 0.50980395f, 0.50980395f, 1.0f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.8784314f, 0.8784314f, 0.8784314f, 1.0f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.98039216f, 0.98039216f, 0.98039216f, 1.0f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.14901961f, 0.14901961f, 0.14901961f, 1.0f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24705882f, 0.24705882f, 0.24705882f, 1.0f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.32941177f, 0.32941177f, 0.32941177f, 1.0f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.9764706f, 0.9764706f, 0.9764706f, 0.30980393f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.9764706f, 0.9764706f, 0.9764706f, 0.8f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.9764706f, 0.9764706f, 0.9764706f, 1.0f);
	style.Colors[ImGuiCol_Separator] = ImVec4(0.42745098f, 0.42745098f, 0.49803922f, 0.5f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.7490196f, 0.7490196f, 0.7490196f, 0.78039217f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.7490196f, 0.7490196f, 0.7490196f, 1.0f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.9764706f, 0.9764706f, 0.9764706f, 0.2f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.9372549f, 0.9372549f, 0.9372549f, 0.67058825f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.9764706f, 0.9764706f, 0.9764706f, 0.9490196f);
	style.Colors[ImGuiCol_Tab] = ImVec4(0.22352941f, 0.22352941f, 0.22352941f, 0.8627451f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.32156864f, 0.32156864f, 0.32156864f, 0.8f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.27450982f, 0.27450982f, 0.27450982f, 1.0f);
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.14509805f, 0.14509805f, 0.14509805f, 0.972549f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.42352942f, 0.42352942f, 0.42352942f, 1.0f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.60784316f, 0.60784316f, 0.60784316f, 1.0f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.0f, 0.42745098f, 0.34901962f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.8980392f, 0.69803923f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.0f, 0.6f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.1882353f, 0.1882353f, 0.2f, 1.0f);
	style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.30980393f, 0.30980393f, 0.34901962f, 1.0f);
	style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.22745098f, 0.22745098f, 0.24705882f, 1.0f);
	style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.06f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25882354f, 0.5882353f, 0.9764706f, 0.35f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.0f, 1.0f, 0.0f, 0.9f);
	style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.25882354f, 0.5882353f, 0.9764706f, 1.0f);
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 0.7f);
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.8f, 0.8f, 0.8f, 0.2f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.8f, 0.8f, 0.8f, 0.35f);
}

void StyleGui2()
{
	ImGuiStyle& style = ImGui::GetStyle();

	style.Alpha = 1.0f;
	style.DisabledAlpha = 1.0f;
	style.WindowPadding = ImVec2(12.0f, 12.0f);
	style.WindowRounding = 11.5f;
	style.WindowBorderSize = 0.0f;
	style.WindowMinSize = ImVec2(20.0f, 20.0f);
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style.WindowMenuButtonPosition = ImGuiDir_Right;
	style.ChildRounding = 0.0f;
	style.ChildBorderSize = 1.0f;
	style.PopupRounding = 0.0f;
	style.PopupBorderSize = 1.0f;
	style.FramePadding = ImVec2(20.0f, 3.4f);
	style.FrameRounding = 11.9f;
	style.FrameBorderSize = 0.0f;
	style.ItemSpacing = ImVec2(4.3f, 5.5f);
	style.ItemInnerSpacing = ImVec2(7.1f, 1.8f);
	style.CellPadding = ImVec2(12.1f, 9.2f);
	style.IndentSpacing = 0.0f;
	style.ColumnsMinSpacing = 4.9f;
	style.ScrollbarSize = 11.6f;
	style.ScrollbarRounding = 15.9f;
	style.GrabMinSize = 3.7f;
	style.GrabRounding = 20.0f;
	style.TabRounding = 0.0f;
	style.TabBorderSize = 0.0f;
	style.ColorButtonPosition = ImGuiDir_Right;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

	style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.27450982f, 0.31764707f, 0.4509804f, 1.0f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.078431375f, 0.08627451f, 0.101960786f, 1.0f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.09411765f, 0.101960786f, 0.11764706f, 1.0f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.078431375f, 0.08627451f, 0.101960786f, 1.0f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.15686275f, 0.16862746f, 0.19215687f, 1.0f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.078431375f, 0.08627451f, 0.101960786f, 1.0f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.11372549f, 0.1254902f, 0.15294118f, 1.0f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.15686275f, 0.16862746f, 0.19215687f, 1.0f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.15686275f, 0.16862746f, 0.19215687f, 1.0f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.047058824f, 0.05490196f, 0.07058824f, 1.0f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.047058824f, 0.05490196f, 0.07058824f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.078431375f, 0.08627451f, 0.101960786f, 1.0f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.09803922f, 0.105882354f, 0.12156863f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.047058824f, 0.05490196f, 0.07058824f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.11764706f, 0.13333334f, 0.14901961f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.15686275f, 0.16862746f, 0.19215687f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.11764706f, 0.13333334f, 0.14901961f, 1.0f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.972549f, 1.0f, 0.49803922f, 1.0f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.972549f, 1.0f, 0.49803922f, 1.0f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(1.0f, 0.79607844f, 0.49803922f, 1.0f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.11764706f, 0.13333334f, 0.14901961f, 1.0f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.18039216f, 0.1882353f, 0.19607843f, 1.0f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.15294118f, 0.15294118f, 0.15294118f, 1.0f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.14117648f, 0.16470589f, 0.20784314f, 1.0f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.105882354f, 0.105882354f, 0.105882354f, 1.0f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.078431375f, 0.08627451f, 0.101960786f, 1.0f);
	style.Colors[ImGuiCol_Separator] = ImVec4(0.12941177f, 0.14901961f, 0.19215687f, 1.0f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.15686275f, 0.18431373f, 0.2509804f, 1.0f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.15686275f, 0.18431373f, 0.2509804f, 1.0f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.14509805f, 0.14509805f, 0.14509805f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.972549f, 1.0f, 0.49803922f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_Tab] = ImVec4(0.078431375f, 0.08627451f, 0.101960786f, 1.0f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.11764706f, 0.13333334f, 0.14901961f, 1.0f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.11764706f, 0.13333334f, 0.14901961f, 1.0f);
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.078431375f, 0.08627451f, 0.101960786f, 1.0f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.1254902f, 0.27450982f, 0.57254905f, 1.0f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.52156866f, 0.6f, 0.7019608f, 1.0f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.039215688f, 0.98039216f, 0.98039216f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.88235295f, 0.79607844f, 0.56078434f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.95686275f, 0.95686275f, 0.95686275f, 1.0f);
	style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.047058824f, 0.05490196f, 0.07058824f, 1.0f);
	style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.047058824f, 0.05490196f, 0.07058824f, 1.0f);
	style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.11764706f, 0.13333334f, 0.14901961f, 1.0f);
	style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(0.09803922f, 0.105882354f, 0.12156863f, 1.0f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.9372549f, 0.9372549f, 0.9372549f, 1.0f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.49803922f, 0.5137255f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.26666668f, 0.2901961f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.49803922f, 0.5137255f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.19607843f, 0.1764706f, 0.54509807f, 0.5019608f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.19607843f, 0.1764706f, 0.54509807f, 0.5019608f);
}

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <sstream>
#include <fstream>
#include <istream>
#include <shobjidl_core.h>
#include <filesystem>
#include <corecrt_math.h>
#include <sqlite3.h>
#include <unordered_map>
#include <numeric>

std::string OpenFileDialog(const std::wstring& filter = L"All Files (*.*)\0*.*\0")
{
	std::wstring result;

	HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (FAILED(hr) && hr != S_FALSE)
		return "";

	IFileOpenDialog* pFileOpen = nullptr;

	hr = CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_ALL,
		IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

	if (SUCCEEDED(hr))
	{
		COMDLG_FILTERSPEC rgSpec[] = {
			{ L"Auctionator (*.lua)", L"*.lua" },
		};
		hr = pFileOpen->SetFileTypes(ARRAYSIZE(rgSpec), rgSpec);
		if (SUCCEEDED(hr))
			hr = pFileOpen->SetFileTypeIndex(0);

		if (SUCCEEDED(hr))
			pFileOpen->SetTitle(L"Выберите файл");

		hr = pFileOpen->Show(Window.hWND);

		if (SUCCEEDED(hr))
		{
			IShellItem* pItem = nullptr;
			hr = pFileOpen->GetResult(&pItem);
			if (SUCCEEDED(hr))
			{
				PWSTR pszFilePath = nullptr;
				hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
				if (SUCCEEDED(hr))
				{
					result = pszFilePath;
					CoTaskMemFree(pszFilePath);
				}
				pItem->Release();
			}
		}
		pFileOpen->Release();
	}

	CoUninitialize();
	std::filesystem::path filePath = result;
	return filePath.string();
}
std::string SaveFileDialog(const std::wstring& defaultFileName = L"logfile.log", const std::wstring& filter = L"All Files (*.*)\0*.*\0")
{
	std::wstring result;
	HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (FAILED(hr) && hr != S_FALSE)
		return "";

	IFileSaveDialog* pFileSave = nullptr;
	hr = CoCreateInstance(CLSID_FileSaveDialog, nullptr, CLSCTX_ALL,
		IID_IFileSaveDialog, reinterpret_cast<void**>(&pFileSave));
	if (SUCCEEDED(hr))
	{

		COMDLG_FILTERSPEC rgSpec[] = {
			{ L"logfile (*.log)", L"*.log" }
		};
		hr = pFileSave->SetFileTypes(ARRAYSIZE(rgSpec), rgSpec);
		if (SUCCEEDED(hr))
			pFileSave->SetFileTypeIndex(0);

		if (!defaultFileName.empty())
		{
			hr = pFileSave->SetFileName(defaultFileName.c_str());
		}

		pFileSave->SetTitle(L"Сохранить проект как...");

		hr = pFileSave->Show(Window.hWND);

		if (SUCCEEDED(hr))
		{
			IShellItem* pItem = nullptr;
			hr = pFileSave->GetResult(&pItem);
			if (SUCCEEDED(hr))
			{
				PWSTR pszFilePath = nullptr;
				hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
				if (SUCCEEDED(hr))
				{
					result = pszFilePath;
					CoTaskMemFree(pszFilePath);
				}
				pItem->Release();
			}
		}
		pFileSave->Release();
	}

	CoUninitialize();

	std::filesystem::path filePath = result;
	return filePath.string();
}


int MaxLots = 0;

#include <fstream>
#include <unordered_map>
#include <string>
#include <iostream>
#include <cctype>
#include <regex>
#include <ctime>

std::string formatTimestamp(time_t timestamp) {
	struct tm timeinfo;
	if (localtime_s(&timeinfo, &timestamp) != 0) {
		return "Invalid time";
	}
	char buffer[80];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
	return std::string(buffer);
}

time_t lastScan = 0;


std::unordered_map<int, std::string> g_itemNames;

#include <windows.h>
#include <string>

std::string cp1251_to_utf8(const std::string& cp1251_str) {
	if (cp1251_str.empty()) return "";
	// Определяем размер буфера для широких символов
	int wide_len = MultiByteToWideChar(1251, 0, cp1251_str.c_str(), -1, nullptr, 0);
	if (wide_len == 0) return "";
	std::wstring wide_str(wide_len, L'\0');
	MultiByteToWideChar(1251, 0, cp1251_str.c_str(), -1, &wide_str[0], wide_len);
	// Конвертируем широкие символы в UTF-8
	int utf8_len = WideCharToMultiByte(CP_UTF8, 0, wide_str.c_str(), -1, nullptr, 0, nullptr, nullptr);
	if (utf8_len == 0) return "";
	std::string utf8_str(utf8_len, '\0');
	WideCharToMultiByte(CP_UTF8, 0, wide_str.c_str(), -1, &utf8_str[0], utf8_len, nullptr, nullptr);
	// Убираем завершающий нулевой символ (WideCharToMultiByte добавляет его)
	if (!utf8_str.empty() && utf8_str.back() == '\0') utf8_str.pop_back();
	return utf8_str;
}
std::string trim(const std::string& str) {
	size_t first = str.find_first_not_of(" \t\n\r\f\v\"");
	if (first == std::string::npos) return "";
	size_t last = str.find_last_not_of(" \t\n\r\f\v\"");
	return str.substr(first, last - first + 1);
}
std::unordered_map<int, std::string> loadItemsFromCSV(const std::string& filename) {
	std::unordered_map<int, std::string> map;
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Не удалось открыть файл: " << filename << std::endl;
		return map;
	}

	std::string line;
	std::getline(file, line);

	while (std::getline(file, line)) {
		if (line.empty()) continue;
		size_t comma = line.find(',');
		if (comma == std::string::npos) continue;
		std::string idStr = trim(line.substr(0, comma));
		std::string name = trim(line.substr(comma + 1));
		try {
			int id = std::stoi(idStr);
			if (id != 0)
			{
				std::string name = trim(line.substr(comma + 1));
				map[id] = cp1251_to_utf8(name);
			}
		}
		catch (...) {}
	}
	file.close();
	std::cout << "Загружено предметов: " << map.size() << std::endl;
	return map;
}
std::string getItemName(int itemID) {
	auto it = g_itemNames.find(itemID);
	return (it != g_itemNames.end()) ? it->second : "Unknown";
}

std::string trimLua(const std::string& str) {
	size_t first = str.find_first_not_of(" \t\n\r\f\v\"\"[");
	if (first == std::string::npos) return "";
	size_t last = str.find_last_not_of(" \t\n\r\f\v\"\"]\{\=\'\"\,");
	return str.substr(first, last - first + 1);
}



enum MOD
{
	MAIN_MENU,
	TEXT_MENU,
	CRAFT_MENU,
	LIDER_MENU,
	GENERAL_MENU,
};

struct
{
	MOD mod = MAIN_MENU;
}Data;


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>
#include <algorithm>

enum FOCUSMARKET
{
	EMPTY,
	AUCTIONATOR_PRICE_DATABASE,
	AUCTIONATOR_POSTING_HISTORY
};

struct Item
{
	std::string Name = "Unknown";

	int id = 0;

	//AUCTIONATOR_PRICE_DATABASE
	std::vector<int> Lots; //а
	std::vector<int> MinPrice; //l
	int MidlePrice = 0; //m
	std::vector<int> MaxPrice; //h

	//AUCTIONATOR_POSTING_HISTORY
	std::vector<int> Price_History;
	std::vector<int> Quantity_History;
	std::vector<int> Time_History;

	float Score = 0;
};

std::vector<Item> sortedItems;
std::unordered_map<int, Item> Items;
std::unordered_map<int, Item> loadItemfromLua(const std::string& filename)
{
	Item TempItem;

	bool ID = false;
	bool a = false;
	bool l = false;
	bool h = false;

	bool exit = false;

	FOCUSMARKET Focus = EMPTY;
	std::unordered_map<int, Item> map;
	std::ifstream file(filename);
	std::string line;
	std::getline(file, line);
	while (std::getline(file, line)) 
	{
		if (line == "AUCTIONATOR_SAVEDVARS = {")
		{
			std::getline(file, line);
			for (int j = 0; j < line.size(); j++)
			{
				if (line[j] == ' ')
				{
					line.erase(0, j + 2);
					lastScan = std::stoi(line);
					break;
				}
			}
			continue;
		}
		if (line == "AUCTIONATOR_PRICE_DATABASE = {")
		{
			std::getline(file, line);
			std::getline(file, line);
			std::getline(file, line);
			Focus = FOCUSMARKET::AUCTIONATOR_PRICE_DATABASE;
		}
		else if (line == "AUCTIONATOR_POSTING_HISTORY = {")
		{
			std::getline(file, line);
			Focus = FOCUSMARKET::AUCTIONATOR_POSTING_HISTORY;
		}
		if (exit)
			break;

		switch (Focus)
		{
			case FOCUSMARKET::EMPTY:
			{
				continue;
			}
			case FOCUSMARKET::AUCTIONATOR_PRICE_DATABASE:
			{
				line = trimLua(line);
				if (line == "__dbversion\"] = 1")
				{
					std::getline(file, line);
					line = trimLua(line);
				}

				if(line == "a")
				{ 
					a = true;
					l = false;
					h = false;
					continue;
				}
				else if (line == "l")
				{
					a = false;
					l = true;
					h = false;
					continue;
				}
				else if (line[0] == 'm')
				{
					for (int j = 0; j < line.size(); j++)
					{
						if (line[j] == ' ')
						{
							line.erase(0, j + 2);
							TempItem.MidlePrice = std::stoi(line);
							break;
						}
						TempItem.MidlePrice = -1;
					}
					a = false;
					l = false;
					h = false;
					continue;
				}
				else if (line == "h")
				{
					a = false;
					l = false;
					h = true;
					continue;
				}
				else if (line == "}" && TempItem.MaxPrice.size() != 0 && TempItem.MidlePrice != 0 && TempItem.MinPrice.size() != 0)
				{
					int CountLots = 0;
					for (int i = 0; i < TempItem.Lots.size(); i++)
					{
						CountLots += TempItem.Lots[i];
					}
					if (CountLots > MaxLots)
						MaxLots = CountLots;

					map[TempItem.id] = TempItem;
					TempItem = {  };
					ID = false;
					a = false;
					l = false;
					h = false;
					continue;
				}
				
				if (ID == false && line != "}")
				{
					
					if (line[0] == 'g')
						line.erase(0, 2);
					
					TempItem.Name = getItemName(std::stoi(line));
					ID = true;
					TempItem.id = std::stoi(line);
					continue;
				}
				if (a)
				{
					for (int j = 0; j < line.size(); j++)
					{
						if (line[j] == ' ')
						{
							line.erase(0, j+2);
							TempItem.Lots.push_back(std::stoi(line));
							break;
						}
					}
					if(TempItem.Lots.size() == 0)
					TempItem.Lots.push_back(0);
				}
				else if (l)
				{
					for (int j = 0; j < line.size(); j++)
					{
						if (line[j] == ' ')
						{
							line.erase(0, j + 2);
							TempItem.MinPrice.push_back(std::stoi(line));
							break;
						}
					}
					if (TempItem.MinPrice.size() == 0)
					TempItem.MinPrice.push_back(0);
				}
				else if (h)
				{
					for (int j = 0; j < line.size(); j++)
					{
						if (line[j] == ' ')
						{
							line.erase(0, j + 2);
							TempItem.MaxPrice.push_back(std::stoi(line));
							break;
						}
					}
					if (TempItem.MaxPrice.size() == 0)
					TempItem.MaxPrice.push_back(0);
				}
				
				continue;
			}
			case FOCUSMARKET::AUCTIONATOR_POSTING_HISTORY:
			{
				line = trimLua(line);
				if (line == "__dbversion\"] = 1")
				{
					std::getline(file, line);
					line = trimLua(line);
				}

				if (ID == false && line != "}")
				{
					if (line[0] == 'g')
						line.erase(0, 2);

					ID = true;
					TempItem = map.find(std::stoi(line))->second;
					continue;
				}

				if (line[0] == 'p')
				{
					for (int j = 0; j < line.size(); j++)
					{
						if (line[j] == ' ')
						{
							line.erase(0, j + 2);
							TempItem.Price_History.push_back(std::stoi(line));
							break;
						}
					}
					if(TempItem.Price_History.size() == 0)
					TempItem.Price_History.push_back(0);
				}
				else if (line[0] == 'q')
				{
					for (int j = 0; j < line.size(); j++)
					{
						if (line[j] == ' ')
						{
							line.erase(0, j + 2);
							TempItem.Quantity_History.push_back(std::stoi(line));
							break;
						}
					}
					if (TempItem.Quantity_History.size() == 0)
						TempItem.Quantity_History.push_back(0);
				}
				else if (line[0] == 't')
				{
					for (int j = 0; j < line.size(); j++)
					{
						if (line[j] == ' ')
						{
							line.erase(0, j + 2);
							TempItem.Time_History.push_back(std::stoi(line));
							break;
						}
					}
					if (TempItem.Time_History.size() == 0)
						TempItem.Time_History.push_back(0);
				}

				if (line[0] == '}')
				{
					std::getline(file, line);
					line = trimLua(line);
					if (line == "AUCTIONATOR_VENDOR_PRICE_CACHE")
						exit = true;

					if (line[0] == '}')
					{			

						ID = false;
						continue;
					}
				}


				continue;
			}
		}
	}

	return map;
}
int Size_ = 0;



// Выгода – оставляем как есть (использует последнюю минимальную цену)
float Benefit(const int& MidlePrice, const std::vector<int>& MinPrice) {
	if (MinPrice.empty()) return 0.0f;
	int lastMin = MinPrice.back();
	if (lastMin == 0) return 0.0f;
	return static_cast<float>(MidlePrice) / lastMin;
}
// Коэффициент вариации – добавлена проверка на размер < 2
double СalculateCV(const std::vector<int>& prices) {
	if (prices.size() < 2) return 0.0;
	double sum = std::accumulate(prices.begin(), prices.end(), 0.0);
	double mean = sum / prices.size();
	if (mean == 0.0) return 0.0;
	double sqSum = 0.0;
	for (int p : prices) {
		double diff = p - mean;
		sqSum += diff * diff;
	}
	double variance = sqSum / (prices.size() - 1);
	double stddev = std::sqrt(variance);
	return stddev / mean;
}
// Нормализованное количество лотов (требует глобальной MaxLots)
float Lots(const std::vector<int>& LotsVec) {
	int total = 0;
	for (int v : LotsVec) total += v;
	return static_cast<float>(total) / MaxLots; // MaxLots – глобальная переменная
}
// Тренд – исправлено деление и использование последней минимальной цены
float Trend(const std::vector<int>& MinPrice, const std::vector<int>& Price_History) {
	if (MinPrice.empty() || Price_History.empty()) return 0.0f;
	int lastMin = MinPrice.back();
	float sum = std::accumulate(Price_History.begin(), Price_History.end(), 0.0f);
	float mean = sum / Price_History.size();
	if (mean == 0.0f) return 0.0f;
	return static_cast<float>(lastMin) / mean;
}
// Абсолютное количество лотов (для редкости)
int CountLots(const std::vector<int>& LotsVec) {
	int total = 0;
	for (int v : LotsVec) total += v;
	return total;
}

// Структура для хранения сырых метрик
struct RawMetrics {
	float benefit;
	float cv;
	float rarity;
	float trend;
};

void LoadItems(const std::string& filename)
{
	Items.clear();
	Items = loadItemfromLua(filename);

	std::vector<std::pair<Item, RawMetrics>> itemsWithMetrics;
	itemsWithMetrics.reserve(Items.size());

	float maxBenefit = 0.0f;
	float maxCV = 0.0f;
	float maxRarity = 0.0f;
	float maxTrend = 0.0f;

	for (auto& pair : Items) {
		const Item& item = pair.second;
		if (item.id == 0 || item.Name == "Unknown") continue; // пропускаем некорректные

		RawMetrics metrics;
		metrics.benefit = Benefit(item.MidlePrice, item.MinPrice);
		// Ограничиваем Benefit, чтобы избежать выбросов
		if (metrics.benefit > 10.0f) metrics.benefit = 10.0f;

		metrics.cv = static_cast<float>(СalculateCV(item.Price_History));
		// Редкость: чем меньше лотов, тем выше редкость
		int totalLots = CountLots(item.Lots);
		metrics.rarity = 1.0f / (totalLots + 1);

		metrics.trend = Trend(item.MinPrice, item.Price_History);

		// Обновляем максимумы
		if (metrics.benefit > maxBenefit) maxBenefit = metrics.benefit;
		if (metrics.cv > maxCV) maxCV = metrics.cv;
		if (metrics.rarity > maxRarity) maxRarity = metrics.rarity;
		if (metrics.trend > maxTrend) maxTrend = metrics.trend;

		itemsWithMetrics.emplace_back(item, metrics);
	}

	if (maxBenefit == 0.0f) maxBenefit = 1.0f;
	if (maxCV == 0.0f) maxCV = 1.0f;
	if (maxRarity == 0.0f) maxRarity = 1.0f;
	if (maxTrend == 0.0f) maxTrend = 1.0f;

	sortedItems.clear();
	sortedItems.reserve(itemsWithMetrics.size());

	for (auto& pair : itemsWithMetrics) {
		const Item& item = pair.first;
		RawMetrics& m = pair.second;

		float normBenefit = m.benefit / maxBenefit;
		float normCV = 1.0f - (m.cv / maxCV);
		float normRarity = m.rarity / maxRarity;
		float normTrend = m.trend / maxTrend;

		// Вычисляем Score с весами
		Item scoredItem = item;
		scoredItem.Score =
			0.4f * normBenefit +
			0.2f * normCV +
			0.1f * normRarity +
			0.2f * normTrend;

		sortedItems.push_back(scoredItem);
	}
	//0.1f * (1.0f / (CountLots(item.Lots) + 1))
	std::sort(sortedItems.begin(), sortedItems.end(), [](const Item& a, const Item& b) {
		return a.Score > b.Score;
		});

	Size_ = sortedItems.size();
}




class Craft
{
public:
	Craft() {}
	~Craft() {}
};

class AnalizeMarket
{
public:
	AnalizeMarket() {}
	~AnalizeMarket() {}
};

class UserInterface
{
public:

	static void ViewGUI()
	{
		ImGuiID dockspace_id = ImGui::GetID("My Dockspace");
		ImGuiViewport* viewport = ImGui::GetMainViewport();

		if (ImGui::DockBuilderGetNode(dockspace_id) == nullptr)
		{
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
		

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("View"))
			{
				ImGui::RadioButton("100",  &Size_, 100);
				ImGui::RadioButton("500",  &Size_, 500);
				ImGui::RadioButton("1000", &Size_, 1000);
				ImGui::RadioButton("FULL", &Size_, sortedItems.size());

				ImGui::EndMenu();
			}
			
			ImGui::EndMainMenuBar();
		}

		ImGui::Begin("Panel Tools");
		{
			if (ImGui::Button("Analize Menu"))
				Data.mod = MOD::MAIN_MENU;
			ImGui::SameLine();
			if (ImGui::Button("Context Menu"))
				Data.mod = MOD::TEXT_MENU;
			ImGui::SameLine();
			if (ImGui::Button("Craft Menu"))
				Data.mod = MOD::CRAFT_MENU;
			ImGui::SameLine();
			if (ImGui::Button("Lider Price"))
				Data.mod = MOD::LIDER_MENU;
			ImGui::SameLine();
			if (ImGui::Button("General Price"))
				Data.mod = MOD::GENERAL_MENU;
			ImGui::SameLine();
			if (ImGui::Button("Import Lua"))
			{
				std::string filename = OpenFileDialog();
				if(filename != "")
					LoadItems(filename);
			}
			ImGui::SameLine();
			ImGui::Text(formatTimestamp(lastScan).c_str());
		}
		ImGui::End();


		ImGui::Begin("List Items");
		{
			static ImGuiTableFlags flags =
				ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_Sortable | ImGuiTableFlags_SortMulti
				| ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_NoBordersInBody
				| ImGuiTableFlags_ScrollY;
			static char str0[128] = "";
			ImGui::InputText("Find Item", str0, IM_COUNTOF(str0));
			if (!sortedItems.empty())
			{
				if (ImGui::BeginTable("table_sorting", 4, flags, ImVec2(0.0f, 40 * 15), 0.0f))
				{
					ImGui::TableSetupColumn("ID", ImGuiTableColumnFlags_DefaultSort | ImGuiTableColumnFlags_WidthFixed, 0.0f);
					ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed, 0.0f);
					ImGui::TableSetupColumn("Action", ImGuiTableColumnFlags_NoSort | ImGuiTableColumnFlags_WidthFixed, 0.0f);
					ImGui::TableSetupColumn("Score", ImGuiTableColumnFlags_WidthFixed, 0.0f);
					ImGui::TableSetupScrollFreeze(0, 1);
					ImGui::TableHeadersRow();
					for (int i = 0; i < Size_; i++)
					{
						if (!sortedItems[i].Name.find(str0))
						{
							
								ImGui::PushID(sortedItems[i].id);
								ImGui::TableNextRow();
								ImGui::TableNextColumn();
								ImGui::Text("%04d", sortedItems[i].id);
								ImGui::TableNextColumn();
								ImGui::TextUnformatted(sortedItems[i].Name.c_str());
								ImGui::TableNextColumn();
								ImGui::SmallButton("None");
								ImGui::TableNextColumn();
								ImGui::Text("%.2f", sortedItems[i].Score);
								ImGui::PopID();
						}
					}
				ImGui::EndTable();
				}
			}
		}
		ImGui::End();


		ImGui::Begin("Analize Market");
		{
			switch (Data.mod)
			{
				case MOD::MAIN_MENU:
				{
					if (sortedItems.empty())
					{
						ImGui::Text("Нужно открыть файл по пусти ../World of Warcraft Sirus/WTF/Account/USERNAME/SavedVariables/Auctionator.lua");
						ImGui::Text("Используй кнопку Import Lua");
					}
				break;
				}
				case MOD::TEXT_MENU:
				{


				break;
				}
				case MOD::CRAFT_MENU:
				{

					break;
				}
				case MOD::LIDER_MENU:
				{

					break;
				}
				case MOD::GENERAL_MENU:
				{

					break;
				}
			
			}
		}
		ImGui::End();

	}
};



void Init()
{
	g_itemNames = loadItemsFromCSV("items_ru.csv");

	ImGuiIO& io = ImGui::GetIO();
	ImFont* font = io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/arial.ttf", 16.0f, nullptr, io.Fonts->GetGlyphRangesCyrillic());
	if (!font)
	{
		font = io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/tahoma.ttf", 16.0f, nullptr, io.Fonts->GetGlyphRangesCyrillic());
	}
	io.Fonts->Build();
	StyleGui1();
}


void Update()
{
	UserInterface::ViewGUI();


	

}
