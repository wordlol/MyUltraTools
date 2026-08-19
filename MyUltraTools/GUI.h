#pragma once
#pragma comment	(lib, "d3d11.lib")
#pragma comment	(lib, "d3dx11.lib")
#pragma comment (lib, "DXGI.lib")

#include <windows.h>
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>
#include <string>

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
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::Button("Export Log"))
					ExportLog();
				if (ImGui::Button("Export Debug Log"))
					ExportDebugLog();
				if (ImGui::Button("Import Lua")) {
					std::string filename;
					std::string savedPath = ReadMemoryURL();

					if (!savedPath.empty() && std::filesystem::exists(savedPath)) {
						filename = savedPath;
					}
					else {
						filename = OpenFileDialog();
						if (filename.empty()) return;
					}

					LoadItems(filename);
					WriteMemoryURL(filename);
				}
				if (ImGui::Button("Clear Path")) {
					std::filesystem::remove("MemoryURL.mr");
				}

				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}

		ImGui::Begin("Panel Tools");
		{
			if (ImGui::Button("Analize Menu"))
				Data.mod = MOD::MAIN_MENU;
			ImGui::SameLine();
			if (ImGui::Button("Craft Menu"))
				Data.mod = MOD::CRAFT_MENU;
			ImGui::SameLine();
			if (IsBuyMode == true)
				ImGui::Checkbox("Сейчас режим ПРОДАЖИ", &IsBuyMode);
			else
				ImGui::Checkbox("Сейчас режим ПОКУПКИ", &IsBuyMode);

			ImGui::SameLine();
			ImGui::Text("%s", formatTimestampWithWeekday(lastScan).c_str());
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
					ImGui::TableSetupColumn("Profit", ImGuiTableColumnFlags_WidthFixed, 0.0f);
					ImGui::TableSetupScrollFreeze(0, 1);
					ImGui::TableHeadersRow();
					for (int i = 0; i < Size_; i++)
					{
						int lastMin = sortedItems[i].MinPrice.empty() ? 0 : sortedItems[i].MinPrice.back();
						int mid = sortedItems[i].MidlePrice;
						int profitCopper = 0;
						if (!sortedItems[i].Name.find(str0))
						{
							ImGui::PushID(sortedItems[i].id);
							ImGui::TableNextRow();
							ImGui::TableNextColumn();
							ImGui::Text("%04d", sortedItems[i].id);
							ImGui::TableNextColumn();
							ImGui::TextUnformatted(sortedItems[i].Name.c_str());
							ImGui::TableNextColumn();
							if (ImGui::SmallButton("Look"))
							{
								PickItem = i;
							}
							ImGui::TableNextColumn();

							if (IsBuyMode) {
								profitCopper = mid - lastMin;   // покупаем по минимальной, продаём по средней
							}
							else {
								profitCopper = lastMin - mid;   // продаём по средней (если она выше минимальной)
							}

							float profitGold = profitCopper / 10000.0f;
							if (profitGold > 0)
								ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "%.2f", profitGold);
							else
								ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "%.2f", profitGold);

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
			ImGui::SameLine();
			ImGui::SliderInt("Слайдер истории", &i1, 0, 10);
			switch (Data.mod)
			{
			case MOD::MAIN_MENU:
			{
				if (sortedItems.empty())
				{
					ImGui::Text("Нужно открыть файл по пути ../World of Warcraft Sirus/WTF/Account/USERNAME/SavedVariables/Auctionator.lua");
					ImGui::Text("Используй кнопку Import Lua в разделе File");
				}

				if (PickItem != -1)
				{
					ImGui::Text(sortedItems[PickItem].Name.c_str());
					ViewMidlePrice();
					ViewScore();
					ViewIndicators();
					ImGui::SeparatorText("Общие показатели о товаре");
					ViewLots();
					ViewMinPrice();
					ViewMaxPrice();
					ViewPriceHistory();
					ViewQuantityHistory();
					ViewTimeHistory();
				}
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
