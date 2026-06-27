#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

#include "Functions.h"

#include <chrono>
#include <Shobjidl.h>
#include <wil/win32_helpers.h>
#include <microsoft.ui.xaml.window.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Pickers.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Microsoft.UI.Xaml.Media.Imaging.h>

using namespace winrt;
using namespace std::chrono_literals;

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
			OutputImageBorder().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
			ImageGrid().ColumnDefinitions().GetAt(0).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(1, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
			ImageGrid().ColumnDefinitions().GetAt(1).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(1, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
			ImageGrid().ColumnDefinitions().GetAt(2).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(1, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
		}
		m_bTwoImageInput = true;
    }
	else if (selectedProcess == L"Linear Contrast" || selectedProcess == L"Gauss Filter" || selectedProcess == L"Histogram Equalization" ||
		     selectedProcess == L"Smoothing Filter" || selectedProcess == L"Sharpen" || selectedProcess == L"Edge Detect" || selectedProcess == L"Robert Filter" || 
		     selectedProcess == L"Prewitt Filter" || selectedProcess == L"Sobel Filter" || selectedProcess == L"Laplace Convolution" || selectedProcess == L"Erosion" ||
		     selectedProcess == L"H-Flip" || selectedProcess == L"V-Flip" || selectedProcess == L"R-Rotate" || selectedProcess == L"L-Rotate" || 
		     selectedProcess == L"Otsu Binarization")
	{
		FileInput1Panel().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);

		// Show only one input image panel
		if (ShowInputImages().IsChecked())
		{
			Input1ImageBorder().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
			Input2ImageBorder().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
			OutputImageBorder().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
			ImageGrid().ColumnDefinitions().GetAt(0).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(1, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
			ImageGrid().ColumnDefinitions().GetAt(1).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(0, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
			ImageGrid().ColumnDefinitions().GetAt(2).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(1, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
		}
		m_bTwoImageInput = false;
	}
	else if (selectedProcess == L"Calculate Contrast" || selectedProcess == L"Luminance")
	{
		FileInput1Panel().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
		Input1ImageBorder().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
		Input2ImageBorder().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
		OutputImageBorder().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
		ImageGrid().ColumnDefinitions().GetAt(0).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(1, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
		ImageGrid().ColumnDefinitions().GetAt(1).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(0, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
		ImageGrid().ColumnDefinitions().GetAt(2).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(0, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
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
			OutputImageBorder().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
			ImageGrid().ColumnDefinitions().GetAt(0).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(1, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
			ImageGrid().ColumnDefinitions().GetAt(1).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(0, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
			ImageGrid().ColumnDefinitions().GetAt(2).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(1, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
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
			OutputImageBorder().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
			ImageGrid().ColumnDefinitions().GetAt(0).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(1, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
			ImageGrid().ColumnDefinitions().GetAt(1).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(0, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
			ImageGrid().ColumnDefinitions().GetAt(2).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(1, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
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
			OutputImageBorder().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
			ImageGrid().ColumnDefinitions().GetAt(0).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(1, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
			ImageGrid().ColumnDefinitions().GetAt(1).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(0, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
			ImageGrid().ColumnDefinitions().GetAt(2).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(1, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
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
			OutputImageBorder().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
			ImageGrid().ColumnDefinitions().GetAt(0).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(1, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
			ImageGrid().ColumnDefinitions().GetAt(1).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(0, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
			ImageGrid().ColumnDefinitions().GetAt(2).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(1, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
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
			OutputImageBorder().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
			ImageGrid().ColumnDefinitions().GetAt(0).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(1, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
			ImageGrid().ColumnDefinitions().GetAt(1).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(0, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
			ImageGrid().ColumnDefinitions().GetAt(2).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(1, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
		}
		m_bTwoImageInput = false;
	}
}

void winrt::ImageProcessingApplication::implementation::MainWindow::HideControls()
{
	StatusText().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
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
		OutputImageBorder().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
		ImageGrid().ColumnDefinitions().GetAt(0).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(1, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
		ImageGrid().ColumnDefinitions().GetAt(1).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(0, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
		ImageGrid().ColumnDefinitions().GetAt(2).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(1, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
	}
}

winrt::Windows::Foundation::IAsyncAction winrt::ImageProcessingApplication::implementation::MainWindow::DisplayOutputImage(std::vector<uint8_t>& outputPixelData, int width, int height, int depth)
{
	if (outputPixelData.size() == 0)
		co_return;

	auto strongRef = get_strong();
	winrt::Microsoft::UI::Xaml::Media::Imaging::WriteableBitmap bitmap(width, height);
	winrt::Windows::Storage::Streams::IBuffer buffer = bitmap.PixelBuffer();
	auto data = buffer.data();

	// Show loading indicator and update UI
	BusyText().Text(L"Processing Output Image...");
	LoadingGrid().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);

	auto localOutData = outputPixelData;

	co_await winrt::resume_background();
	// ============================ BACKGROUND THREAD ============================

	// Copy pixel data to WriteableBitmap
	if (depth == 3) // RGB
	{
		for (int i = 0; i < width * height; ++i)
		{
			data[i * 4 + 0] = localOutData[i * 3 + 2];   // B
			data[i * 4 + 1] = localOutData[i * 3 + 1];	// G
			data[i * 4 + 2] = localOutData[i * 3 + 0];	// R
			data[i * 4 + 3] = 255;							// A
		}
	}
	else if (depth == 1) // Grayscale
	{
		for (int i = 0; i < width * height; ++i)
		{
			uint8_t grayValue = localOutData[i];
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

		m_image1 = Functions::readImage(winrt::to_string(file.Path()).c_str());
		//co_await DisplayOutputImage(m_image1.m_pixelData, m_image1.m_cols, m_image1.m_rows, 1);

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

		m_image2 = Functions::readImage(winrt::to_string(file.Path()).c_str());

		// Hide loading indicator
		BusyText().Text(L"");
		LoadingGrid().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
	}
}

void winrt::ImageProcessingApplication::implementation::MainWindow::ShowInputImages_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
	if (m_bLoaded)
	{
		Input1ImageBorder().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
		ImageGrid().ColumnDefinitions().GetAt(0).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(1.0, winrt::Microsoft::UI::Xaml::GridUnitType::Star));

		if (m_bTwoImageInput)
		{
			Input2ImageBorder().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
			ImageGrid().ColumnDefinitions().GetAt(1).Width(winrt::Microsoft::UI::Xaml::GridLengthHelper::FromValueAndType(1.0, winrt::Microsoft::UI::Xaml::GridUnitType::Star));
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

winrt::Windows::Foundation::IAsyncAction winrt::ImageProcessingApplication::implementation::MainWindow::ProcessButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
	Image imgOut;
	int result = 0;

	// Reveal controls for specific processes
	winrt::hstring selectedProcess = ProcessComboBox().SelectedItem().as<winrt::Microsoft::UI::Xaml::Controls::ComboBoxItem>().Content().as<winrt::hstring>();
	m_displayDepth = DISPLAY_DEPTH::RGB; // RGB default

	// Show loading indicator and update UI
	co_await wil::resume_foreground(this->DispatcherQueue());
	BusyText().Text(L"Processing: " + selectedProcess);
	LoadingGrid().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
	co_await 10ms;
	co_await wil::resume_foreground(this->DispatcherQueue());

	if (selectedProcess == L"Merge")
	{
		co_await Functions::merge(m_image1, m_image2, imgOut);
	}
	else if (selectedProcess == L"Logic AND")
	{
		m_displayDepth = DISPLAY_DEPTH::GRAYSCALE;
		co_await Functions::logicAnd(m_image1, m_image2, imgOut);
	}
	else if (selectedProcess == L"Logic OR")
	{
		m_displayDepth = DISPLAY_DEPTH::GRAYSCALE;
		co_await Functions::logicOr(m_image1, m_image2, imgOut);
	}
	else if (selectedProcess == L"Logic XOR")
	{
		m_displayDepth = DISPLAY_DEPTH::GRAYSCALE;
		co_await Functions::logicXor(m_image1, m_image2, imgOut);
	}
	else if (selectedProcess == L"Logic NAND")
	{
		m_displayDepth = DISPLAY_DEPTH::GRAYSCALE;
		co_await Functions::logicNand(m_image1, m_image2, imgOut);
	}
	else if (selectedProcess == L"Addition")
	{
		m_displayDepth = DISPLAY_DEPTH::GRAYSCALE;
		co_await Functions::addition(m_image1, m_image2, imgOut);
	}
	else if (selectedProcess == L"Subtraction")
	{
		m_displayDepth = DISPLAY_DEPTH::GRAYSCALE;
		co_await Functions::subtraction(m_image1, m_image2, imgOut);
	}
	else if (selectedProcess == L"Multiplication")
	{
		m_displayDepth = DISPLAY_DEPTH::GRAYSCALE;
		int factor = static_cast<int>(std::stoi(winrt::to_string(NumberInput1().Text())));
		co_await Functions::multiplication(m_image1, imgOut, factor);
	}
	else if (selectedProcess == L"Linear Contrast")
	{
		m_displayDepth = DISPLAY_DEPTH::GRAYSCALE;
		co_await Functions::linearContrast(m_image1, imgOut);
	}
	else if (selectedProcess == L"Calculate Contrast")
	{
		result = Functions::calculateContrast(m_image1);

		// Hide loading indicator
		BusyText().Text(L"");
		LoadingGrid().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);

		// Update status text
		StatusText().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
		StatusText().Text(L"Contrast: " + winrt::to_hstring(result));
		co_return;
	}
	else if (selectedProcess == L"Luminance")
	{
		m_displayDepth = DISPLAY_DEPTH::GRAYSCALE;
		int result =  Functions::luminance(m_image1);

		// Hide loading indicator
		BusyText().Text(L"");
		LoadingGrid().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);

		// Update status text
		StatusText().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
		StatusText().Text(L"Luminance: " + winrt::to_hstring(result));
		co_return;
	}
	else if (selectedProcess == L"Gauss Filter")
	{
		co_await Functions::gaussFilter(m_image1, imgOut);
	}
	else if (selectedProcess == L"Smoothing Filter")
	{
		co_await Functions::smoothingFilter(m_image1, imgOut);
	}
	else if (selectedProcess == L"Histogram Equalization")
	{
		m_displayDepth = DISPLAY_DEPTH::GRAYSCALE;
		co_await Functions::histogramEqualization(m_image1, imgOut);
	}
	else if (selectedProcess == L"Sharpen")
	{
		co_await Functions::sharpen(m_image1, imgOut);
	}
	else if (selectedProcess == L"Edge Detect")
	{
		co_await Functions::edgeDetect(m_image1, imgOut);
	}
	else if (selectedProcess == L"Robert Filter")
	{
		co_await Functions::robertFilter(m_image1, imgOut);
	}
	else if (selectedProcess == L"Prewitt Filter")
	{
		co_await Functions::prewittFilter(m_image1, imgOut);
	}
	else if (selectedProcess == L"Sorbel Filter")
	{
		co_await Functions::sobelFilter(m_image1, imgOut);
	}
	else if (selectedProcess == L"Laplace Convolution")
	{
		co_await Functions::laplacienConvo(m_image1, imgOut);
	}
	else if (selectedProcess == L"Erosion")
	{
		co_await Functions::erosion(m_image1, imgOut);
	}
	else if (selectedProcess == L"H-Flip")
	{
		co_await Functions::hFlip(m_image1, imgOut);
	}
	else if (selectedProcess == L"V-Flip")
	{
		co_await Functions::vFlip(m_image1, imgOut);
	}
	else if (selectedProcess == L"R-Rotate")
	{
		co_await Functions::rRotate(m_image1, imgOut);
	}
	else if (selectedProcess == L"L-Rotate")
	{
		co_await Functions::lRotate(m_image1, imgOut);
	}
	else if (selectedProcess == L"Otsu Binarization")
	{
		m_displayDepth = DISPLAY_DEPTH::GRAYSCALE;
		int threshold;
		co_await Functions::otsuBinarization(m_image1, imgOut, threshold);
		co_await wil::resume_foreground(this->DispatcherQueue());

		// Update status text
		StatusText().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
		StatusText().Text(L"Threshold: " + winrt::to_hstring(threshold));
	}
	else if (selectedProcess == L"Brightness")
	{
		m_displayDepth = DISPLAY_DEPTH::GRAYSCALE;
		int level = static_cast<int>(std::stoi(winrt::to_string(NumberInput1().Text())));
		co_await Functions::brightness(m_image1, imgOut, level);
	}
	else if (selectedProcess == L"Filtering")
	{
		int r = static_cast<int>(std::stoi(winrt::to_string(NumberInput1().Text())));
		int g = static_cast<int>(std::stoi(winrt::to_string(NumberInput2().Text())));
		int b = static_cast<int>(std::stoi(winrt::to_string(NumberInput3().Text())));
		co_await Functions::filtering(m_image1, imgOut, r, g, b);
	}
	else if (selectedProcess == L"Linear Contrast Saturation")
	{
		m_displayDepth = DISPLAY_DEPTH::GRAYSCALE;
		int smin = static_cast<int>(std::stoi(winrt::to_string(NumberInput1().Text())));
		int smax = static_cast<int>(std::stoi(winrt::to_string(NumberInput2().Text())));
		co_await Functions::linearContrastSaturation(m_image1, imgOut, smin, smax);
	}
	else if (selectedProcess == L"ScalingNN")
	{
		float scaleX = std::stof(winrt::to_string(NumberInput1().Text()));	
		float scaleY = std::stof(winrt::to_string(NumberInput2().Text()));
		co_await Functions::scalingNN(m_image1, imgOut, scaleX, scaleY);
	}

	co_await wil::resume_foreground(this->DispatcherQueue());

	// Hide loading indicator
	BusyText().Text(L"");
	LoadingGrid().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);

	// Display output image
	if(m_displayDepth == DISPLAY_DEPTH::RGB)
		DisplayOutputImage(imgOut.m_pixelDataRGB, imgOut.m_cols, imgOut.m_rows, imgOut.m_depth);
	else if(m_displayDepth == DISPLAY_DEPTH::GRAYSCALE)
		DisplayOutputImage(imgOut.m_pixelData, imgOut.m_cols, imgOut.m_rows, 1);
}
