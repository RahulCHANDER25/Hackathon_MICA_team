#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include "Walnut/Image.h"

#include "Request.h"

#include <iostream>

using namespace WinHttpWrapper;

struct User
{
	char Name[256];
	char Age[256];
	char BloodType[256];
	char Country[256];
	char Arrangement[256];
	char Expiration[256];
};

std::string to_ansi(std::wstring string)
{
	return std::string(string.begin(), string.end());
}

class ExampleLayer : public Walnut::Layer
{
public:
	void OnAttach()
	{
		ImGui::StyleColorsLight();

		// Clé: string en ascii
		// L'addresse: l'adrese de mon smart contract
		// Les resultats sont en ascii
		std::wstring url = L"https://test.massa.net/api/v2";
		std::wstring header = L"Content-Type: application/json";

		HttpRequest request(url, 33035, true);
		HttpResponse response;
		request.Post(L"", 
			header, 
			R"(
				{
					"jsonrpc": "2.0", 
					"method": "get_status", 
					"id": 1, 
					"params": [
					]}
			)", 
			response);
		std::cout << "Returned status: " << response.statusCode << std::endl;
		std::cout << "Error: " << to_ansi(response.error) << std::endl;
		response.Reset();
	}

	void OnDetach()
	{

	}

	void RenderProfile()
	{
		ImGui::Begin("Profil", NULL, ImGuiWindowFlags_NoCollapse);
		ImGui::InputText("Name", mCurrentUser.Name, 256);
		ImGui::InputText("Age", mCurrentUser.Age, 256);
		ImGui::InputText("BloodType", mCurrentUser.BloodType, 256);
		ImGui::InputText("Country", mCurrentUser.Country, 256);
		ImGui::InputText("Arrangement", mCurrentUser.Arrangement, 256);
		ImGui::InputText("Expiration", mCurrentUser.Expiration, 256);
		ImGui::End();
	}

	void RenderSettings()
	{
		ImGui::Begin("Parametres", NULL, ImGuiWindowFlags_NoCollapse);
		ImGui::Checkbox("Dark Mode", &mTheme);
		ImGui::End();
	}

	virtual void OnUIRender() override
	{
		RenderProfile();
		RenderSettings();

		if (mTheme == true)
			ImGui::StyleColorsDark();
		else
			ImGui::StyleColorsLight();
	}

private:
	User mCurrentUser = {};
	bool mTheme = true;
};

Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "MICA";
	spec.IconPath = "Assets/Logo.png";

	Walnut::Application* app = new Walnut::Application(spec);
	app->PushLayer<ExampleLayer>();
	app->SetMenubarCallback([app]()
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
			{
				app->Close();
			}
			ImGui::EndMenu();
		}
	});
	return app;
}