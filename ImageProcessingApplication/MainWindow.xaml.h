#pragma once

#include "MainWindow.g.h"

#include <winrt/Microsoft.UI.Windowing.h>
#include "Image.h"

namespace winrt::ImageProcessingApplication::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow()
        {
            // Maximize window
            auto presenter = this->AppWindow().Presenter().as<winrt::Microsoft::UI::Windowing::OverlappedPresenter>();
            presenter.Maximize();
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

    private:
        // Private Variables
		bool m_bLoaded = false; 
        bool m_bTwoImageInput = true;
        
        enum DISPLAY_DEPTH
        {
            GRAYSCALE,
            RGB
        };

        DISPLAY_DEPTH m_displayDepth = DISPLAY_DEPTH::RGB;
        DISPLAY_DEPTH m_bLastOutDepth = DISPLAY_DEPTH::RGB;

        Image m_image1;
        Image m_image2;
        Image m_OutputImage;

        // Private Functions
        void HideControls();
        winrt::Windows::Foundation::IAsyncAction DisplayOutputImage(int depth);
        winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::StorageFile> ShowFileDialog();
        winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::UI::Xaml::Media::Imaging::WriteableBitmap> GetWritableBitmap(Image& im, int depth);
    public:
        // Event handlers
        void ProcessComboBox_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
        winrt::Windows::Foundation::IAsyncAction BrowseFilesButton1_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        winrt::Windows::Foundation::IAsyncAction BrowseFilesButton2_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void ShowInputImages_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void ShowInputImages_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void MainGrid_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        winrt::Windows::Foundation::IAsyncAction ProcessButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        winrt::fire_and_forget SaveButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::ImageProcessingApplication::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
