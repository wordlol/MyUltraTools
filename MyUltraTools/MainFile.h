#pragma once
#define LOG    "..\\MyUltraTools\\Log\\"
#define LOGL   L"..\\MyUltraTools\\Log\\"
#define IMAGE  "..\\MyUltraTools\\Images\\"
#define IMAGEL L"..\\MyUltraTools\\Images\\"

void StyleGui()
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
			{ L"logfile (*.log)", L"*.log" },
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

class LOGManager
{
public:
	LOGManager() {}
	~LOGManager() {}

	//std::ostringstream configStream;

//ifstream in("input.txt"); // открытие файла для чтения
//if (in.is_open()) {
//	string line;
//	while (getline(in, line)) { // чтение по строкам
//		cout << line << endl;
//	}
//	in.close();
//}


//ofstream out("output.txt"); // открытие файла для записи
//if (out.is_open()) {
//	out << "Привет, мир!" << endl; // выгрузка данных
//	out.close();
//}
};

class UserInterface
{
public:

	inline void ViewGUI()
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
			ImGui::DockBuilderDockWindow("Game", dock_id_main);
			ImGui::DockBuilderDockWindow("Properties", dock_id_left_top);
			ImGui::DockBuilderDockWindow("Explorer", dock_id_left_bottom);
			ImGui::DockBuilderDockWindow("Console", dock_id_left_bottom);
			ImGui::DockBuilderDockWindow("Amimation", dock_id_left_bottom);
			ImGui::DockBuilderDockWindow("Shader Editor", dock_id_left_bottom);
			ImGui::DockBuilderDockWindow("Materials", dock_id_left_bottom);
			ImGui::DockBuilderDockWindow("Particle System", dock_id_left_bottom);
			ImGui::DockBuilderDockWindow("GameEngine v1", dock_id_left_bottom);
			ImGui::DockBuilderDockWindow("Info", dock_id_left_bottom);
			ImGui::DockBuilderDockWindow("Physics System", dock_id_left_bottom);
			ImGui::DockBuilderFinish(dockspace_id);
		}

		ImGui::DockSpaceOverViewport(dockspace_id, viewport, ImGuiDockNodeFlags_PassthruCentralNode);

		ImGui::Begin("GameEngine v1");
		{
			if (ImGui::BeginMainMenuBar())
			{
			
			};
			ImGui::End();

		}
		ImGui::End();

	}


};



void Init()
{
	StyleGui();
	




}


void Update()
{
	UserInterface::ViewGUI;


	

}
