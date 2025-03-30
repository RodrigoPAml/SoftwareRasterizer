#include <Rasterizer.hpp>
#include "OpenModelModal.hpp"
#include <windows.h>
#include <shobjidl.h>

namespace Rasterizer {
	
	std::string OpenModelModal::Draw()
	{
		using GUI = Window::GUI;
		using Window = Window::Window;

		while (Window::ShouldRun())
		{
			GPU::Command::Clear();
			GUI::BeginFrame();

			if (GUI::BeginMainMenuBar())
			{
				if (GUI::BeginMenu("File", true))
				{
					if (GUI::MenuItem("Load"))
					{
						this->fileDialogOpen = true;
					}

					GUI::EndMenu();
				}

				GUI::EndMainMenuBar();
			}

			// 2. File dialog
			if (this->fileDialogOpen)
			{
				std::wstring filePath = OpenFileDialog();

                if (filePath.empty()) return std::string();

                int size_needed = WideCharToMultiByte(CP_UTF8, 0, filePath.c_str(), (int)filePath.length(), nullptr, 0, nullptr, nullptr);
                std::string str(size_needed, 0);
                WideCharToMultiByte(CP_UTF8, 0, filePath.c_str(), (int)filePath.length(), &str[0], size_needed, nullptr, nullptr);

                return str;
			}

			GUI::EndFrame();
			Window::SwapAndPollEvents();
		}
	}

    std::wstring OpenModelModal::OpenFileDialog()
    {
        std::wstring filePath;
        HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
        if (SUCCEEDED(hr))
        {
            IFileOpenDialog* pFileOpen;
            hr = CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

            if (SUCCEEDED(hr))
            {
                COMDLG_FILTERSPEC fileTypes[] =
                {
                    { L"Wavefront OBJ (*.obj)", L"*.obj" },
                    { L"Filmbox FBX (*.fbx)", L"*.fbx" },
                    { L"Stereolithography STL (*.stl)", L"*.stl" },
                    { L"GL Transmission Format (*.gltf;*.glb)", L"*.gltf;*.glb" },
                    { L"All Supported Formats", L"*.obj;*.fbx;*.stl;*.gltf;*.glb" }
                };

                pFileOpen->SetFileTypes(ARRAYSIZE(fileTypes), fileTypes);
                pFileOpen->SetFileTypeIndex(5);

                hr = pFileOpen->Show(nullptr);
                if (SUCCEEDED(hr))
                {
                    IShellItem* pItem;
                    hr = pFileOpen->GetResult(&pItem);
                    if (SUCCEEDED(hr))
                    {
                        PWSTR pszFilePath;
                        hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
                        if (SUCCEEDED(hr))
                        {
                            filePath = pszFilePath;
                            CoTaskMemFree(pszFilePath);
                        }
                        pItem->Release();
                    }
                }
                pFileOpen->Release();
            }
            CoUninitialize();
        }
        return filePath;
    }
}