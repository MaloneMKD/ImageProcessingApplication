#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

#include "Functions.h"

#include <Shobjidl.h>
#include <wil/win32_helpers.h>
#include <microsoft.ui.xaml.window.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Pickers.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Microsoft.UI.Xaml.Media.Imaging.h>

using namespace winrt;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::ImageProcessingApplication::implementation
{
    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
}

void winrt::ImageProcessingApplication::implementation::MainWindow::ProcessComboBox_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e)
{
    // Hide all controls
    HideControls();

    // Reveal controls for specific processes
	winrt::hstring selectedProcess = ProcessComboBox().SelectedItem().as<winrt::Microsoft::UI::Xaml::Controls::ComboBoxItem>().Content().as<winrt::hstring>();

    if (selectedProcess == L"Merge" || selectedProcess == L"Logic AND" || selectedProcess == L"Logic OR" || selectedProcess == L"Logic XOR" || 
		selectedProcess == L"Logic NAND" || selectedProcess == L"Addition" || selectedProcess == L"Subtraction")
    {
		FileInput1Panel().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
		FileInput2Panel().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);

		// Show both input image panels
		if (ShowInputImages().IsChecked())
		{
			Input1ImageBorder().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
			Input2ImageBorder().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
			ImageGrid().ColumnDefinitions().GetAt(0).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(1, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
			ImageGrid().ColumnDefinitions().GetAt(1).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(1, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
		}
		m_bTwoImageInput = true;
    }
	else if (selectedProcess == L"Linear Contrast" || selectedProcess == L"Calculate Contrast" || selectedProcess == L"Luminance" || selectedProcess == L"Gauss Filter" ||
		     selectedProcess == L"Smoothing Filter" || selectedProcess == L"Sharpen" || selectedProcess == L"Edge Detect" || selectedProcess == L"Robert Filter" || 
		     selectedProcess == L"Prewitt Filter" || selectedProcess == L"Sobel Filter" || selectedProcess == L"Laplace Convolution" || selectedProcess == L"Erosion" ||
		     selectedProcess == L"H-Flip" || selectedProcess == L"V-Flip" || selectedProcess == L"R-Rotate" || selectedProcess == L"L-Rotate")
	{
		FileInput1Panel().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);

		// Show only one input image panel
		if (ShowInputImages().IsChecked())
		{
			Input1ImageBorder().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
			Input2ImageBorder().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
			ImageGrid().ColumnDefinitions().GetAt(0).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(1, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
			ImageGrid().ColumnDefinitions().GetAt(1).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(0, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
		}
		m_bTwoImageInput = false;
	}
	else if (selectedProcess == L"Brightness")
	{
		NumberInput1().Header(winrt::box_value(L"Brightness Level"));
		FileInput1Panel().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
		ArgumentsBorder().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
		NumberInput1().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);

		// Show only one input image panel
		if (ShowInputImages().IsChecked())
		{
			Input1ImageBorder().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
			Input2ImageBorder().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
			ImageGrid().ColumnDefinitions().GetAt(0).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(1, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
			ImageGrid().ColumnDefinitions().GetAt(1).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(0, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
		}
		m_bTwoImageInput = false;
	}
	else if (selectedProcess == L"Multiplication")
	{
		NumberInput1().Header(winrt::box_value(L"Multiplication Factor"));
		FileInput1Panel().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
		ArgumentsBorder().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
		NumberInput1().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);

		// Show only one input image panel
		if (ShowInputImages().IsChecked())
		{
			Input1ImageBorder().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
			Input2ImageBorder().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
			ImageGrid().ColumnDefinitions().GetAt(0).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(1, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
			ImageGrid().ColumnDefinitions().GetAt(1).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(0, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
		}
		m_bTwoImageInput = false;
	}
	else if (selectedProcess == L"Filtering")
	{
		NumberInput1().Header(winrt::box_value(L"Red"));
		NumberInput2().Header(winrt::box_value(L"Green"));
		NumberInput3().Header(winrt::box_value(L"Blue"));
		FileInput1Panel().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
		ArgumentsBorder().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
		NumberInput1().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
		NumberInput2().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
		NumberInput3().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);

		// Show only one input image panel
		if (ShowInputImages().IsChecked())
		{
			Input1ImageBorder().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
			Input2ImageBorder().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
			ImageGrid().ColumnDefinitions().GetAt(0).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(1, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
			ImageGrid().ColumnDefinitions().GetAt(1).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(0, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
		}
		m_bTwoImageInput = false;
	}
	else if (selectedProcess == L"Linear Contrast Saturation")
	{
		NumberInput1().Header(winrt::box_value(L"SMin"));
		NumberInput2().Header(winrt::box_value(L"SMax"));
		FileInput1Panel().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
		ArgumentsBorder().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
		NumberInput1().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
		NumberInput2().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);

		// Show only one input image panel
		if (ShowInputImages().IsChecked())
		{
			Input1ImageBorder().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
			Input2ImageBorder().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
			ImageGrid().ColumnDefinitions().GetAt(0).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(1, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
			ImageGrid().ColumnDefinitions().GetAt(1).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(0, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
		}
		m_bTwoImageInput = false;
	}
	else if (selectedProcess == L"ScalingNN")
	{
		NumberInput1().Header(winrt::box_value(L"X-Scale"));
		NumberInput2().Header(winrt::box_value(L"Y-Scale"));
		FileInput1Panel().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
		ArgumentsBorder().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
		NumberInput1().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
		NumberInput2().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);

		// Show only one input image panel
		if (ShowInputImages().IsChecked())
		{
			Input1ImageBorder().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
			Input2ImageBorder().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
			ImageGrid().ColumnDefinitions().GetAt(0).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(1, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
			ImageGrid().ColumnDefinitions().GetAt(1).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(0, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
		}
		m_bTwoImageInput = false;
	}
}

void winrt::ImageProcessingApplication::implementation::MainWindow::HideControls()
{
	FileInput1Panel().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
	FileInput2Panel().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);

    ArgumentsBorder().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
    NumberInput1().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
    NumberInput2().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
    NumberInput3().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);

	// Show only one input image panel
	if (ShowInputImages().IsChecked())
	{
		Input1ImageBorder().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
		Input2ImageBorder().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
		ImageGrid().ColumnDefinitions().GetAt(0).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(1, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
		ImageGrid().ColumnDefinitions().GetAt(1).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(0, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
	}
}

winrt::Windows::Foundation::IAsyncAction winrt::ImageProcessingApplication::implementation::MainWindow::DisplayOutputImage(std::vector<uint8_t>& outputPixelData, int width, int height, int depth)
{
	auto strongRef = get_strong();
	winrt::Microsoft::UI::Xaml::Media::Imaging::WriteableBitmap bitmap(width, height);
	winrt::Windows::Storage::Streams::IBuffer buffer = bitmap.PixelBuffer();
	auto data = buffer.data();

	// Show loading indicator and update UI
	BusyText().Text(L"Processing Output Image...");
	LoadingGrid().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);

	co_await winrt::resume_background();
	// ============================ BACKGROUND THREAD ============================

	// Copy pixel data to WriteableBitmap
	if (depth == 3) // RGB
	{
		for (int i = 0; i < width * height; ++i)
		{
			data[i * 4 + 0] = outputPixelData[i * 3 + 2];   // B
			data[i * 4 + 1] = outputPixelData[i * 3 + 1];	// G
			data[i * 4 + 2] = outputPixelData[i * 3 + 0];	// R
			data[i * 4 + 3] = 255;							// A
		}
	}
	else if (depth == 1) // Grayscale
	{
		for (int i = 0; i < width * height; ++i)
		{
			uint8_t grayValue = outputPixelData[i];
			data[i * 4 + 0] = grayValue; // B
			data[i * 4 + 1] = grayValue; // G
			data[i * 4 + 2] = grayValue; // R
			data[i * 4 + 3] = 255;       // A
		}
	}

	co_await wil::resume_foreground(this->DispatcherQueue());
	// ============================ UI THREAD ============================

	// Hide loading indicator
	BusyText().Text(L"");
	LoadingGrid().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);

	bitmap.Invalidate();
	OutputImage().Source(bitmap);
}

winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::StorageFile> winrt::ImageProcessingApplication::implementation::MainWindow::ShowFileDialog()
{
	auto picker = winrt::Windows::Storage::Pickers::FileOpenPicker();
	picker.ViewMode(winrt::Windows::Storage::Pickers::PickerViewMode::Thumbnail);
	picker.SuggestedStartLocation(winrt::Windows::Storage::Pickers::PickerLocationId::PicturesLibrary);
	picker.FileTypeFilter().Append(L".jpg");
	picker.FileTypeFilter().Append(L".png");
	picker.as<IInitializeWithWindow>()->Initialize(GetActiveWindow());

	if (winrt::Windows::Storage::StorageFile file = co_await picker.PickSingleFileAsync())
		co_return file;
	co_return nullptr;
}

winrt::Windows::Foundation::IAsyncAction winrt::ImageProcessingApplication::implementation::MainWindow::BrowseFilesButton1_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
	winrt::Windows::Storage::StorageFile file = co_await ShowFileDialog();
	if (file)
	{
		// Show loading indicator and update UI
		co_await wil::resume_foreground(this->DispatcherQueue());
		BusyText().Text(L"Loading Input...");
		LoadingGrid().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);

		// Open the file as a stream
		winrt::Windows::Storage::Streams::IRandomAccessStream stream = co_await file.OpenAsync(winrt::Windows::Storage::FileAccessMode::Read);
		winrt::Microsoft::UI::Xaml::Media::Imaging::BitmapImage bitmapImage;
		co_await bitmapImage.SetSourceAsync(stream);
		Input1Image().Source(bitmapImage);
		FileName1_textbox().Text(file.Name());

		auto image = Functions::readImage(winrt::to_string(file.Path()).c_str());
		co_await DisplayOutputImage(image.m_pixelData, image.m_cols, image.m_rows, 1);

		// Hide loading indicator
		BusyText().Text(L"");
		LoadingGrid().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
	}
}

winrt::Windows::Foundation::IAsyncAction winrt::ImageProcessingApplication::implementation::MainWindow::BrowseFilesButton2_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
	winrt::Windows::Storage::StorageFile file = co_await ShowFileDialog();
	if (file)
	{
		// Show loading indicator and update UI
		co_await wil::resume_foreground(this->DispatcherQueue());
		BusyText().Text(L"Loading Input...");
		LoadingGrid().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);

		// Open the file as a stream
		winrt::Windows::Storage::Streams::IRandomAccessStream stream = co_await file.OpenAsync(winrt::Windows::Storage::FileAccessMode::Read);
		winrt::Microsoft::UI::Xaml::Media::Imaging::BitmapImage bitmapImage;
		co_await bitmapImage.SetSourceAsync(stream);
		Input2Image().Source(bitmapImage);
		FileName2_textBox().Text(file.Name());

		// Hide loading indicator
		BusyText().Text(L"");
		LoadingGrid().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
	}
}

void winrt::ImageProcessingApplication::implementation::MainWindow::ShowInputImages_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
	if (m_bLoaded)
	{
		ImageGrid().ColumnDefinitions().GetAt(0).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(1.0, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
		ImageGrid().ColumnDefinitions().GetAt(1).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(1.0, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
		Input1ImageBorder().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
		ImageGrid().ColumnDefinitions().GetAt(0).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(1, winrt::Microsoft::UI::Xaml::GridUnitType::Star));

		if (m_bTwoImageInput)
		{
			Input2ImageBorder().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
			ImageGrid().ColumnDefinitions().GetAt(1).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(0, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
		}
	}
}

void winrt::ImageProcessingApplication::implementation::MainWindow::ShowInputImages_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
	if (m_bLoaded)
	{
		ImageGrid().ColumnDefinitions().GetAt(0).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(0.0, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
		ImageGrid().ColumnDefinitions().GetAt(1).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(0.0, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
		Input1ImageBorder().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
		Input2ImageBorder().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
	}
}

void winrt::ImageProcessingApplication::implementation::MainWindow::MainGrid_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
	m_bLoaded = true;
}

void winrt::ImageProcessingApplication::implementation::MainWindow::ProcessButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
	// Reveal controls for specific processes
	winrt::hstring selectedProcess = ProcessComboBox().SelectedItem().as<winrt::Microsoft::UI::Xaml::Controls::ComboBoxItem>().Content().as<winrt::hstring>();;

	if (selectedProcess == L"Merge")
	{

	}
	else if (selectedProcess == L"Logic AND")
	{

	}
	else if (selectedProcess == L"Logic OR")
	{

	}
	else if (selectedProcess == L"Logic XOR")
	{

	}
	else if (selectedProcess == L"Logic NAND")
	{

	}
	else if (selectedProcess == L"Addition")
	{

	}
	else if (selectedProcess == L"Subtraction")
	{

	}
	else if (selectedProcess == L"Multiplication")
	{

	}
	else if (selectedProcess == L"Linear Contrast")
	{

	}
	else if (selectedProcess == L"Calculate Contrast")
	{

	}
	else if (selectedProcess == L"Luminance")
	{

	}
	else if (selectedProcess == L"Gauss Filter")
	{

	}
	else if (selectedProcess == L"Smoothing Filter")
	{

	}
	else if (selectedProcess == L"Sharpen")
	{

	}
	else if (selectedProcess == L"Edge Detect")
	{

	}
	else if (selectedProcess == L"Robert Filter")
	{

	}
	else if (selectedProcess == L"Prewitt Filter")
	{

	}
	else if (selectedProcess == L"Sorbel Filter")
	{

	}
	else if (selectedProcess == L"Laplace Convolution")
	{

	}
	else if (selectedProcess == L"Erosion")
	{

	}
	else if (selectedProcess == L"H-Flip")
	{

	}
	else if (selectedProcess == L"V-Flip")
	{

	}
	else if (selectedProcess == L"R-Rotate")
	{

	}
	else if (selectedProcess == L"L-Rotate")
	{

	}
	else if (selectedProcess == L"Brightness")
	{

	}
	else if (selectedProcess == L"Filtering")
	{

	}
	else if (selectedProcess == L"Linear Contrast Saturation")
	{

	}
	else if (selectedProcess == L"ScalingNN")
	{

	}
}
