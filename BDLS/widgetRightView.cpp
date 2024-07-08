#include "widgetRightView.h"
#include <QPdfBookmarkModel>
#include <QtWidgets>
#include "VideoWidget.h"
#include "playercontrols.h"
#include <QAudioDevice>
#include <QMediaDevices>
#include "BDLS.h"
//#include <QPdfNavigationStack>
#include "ddecomm.h"
#include "Windows.h"

const qreal zoomMultiplier = qSqrt(2.0);
#define DDEAPP      QString::fromUtf8("SUMATRA")
#define DDETOPIC    QString::fromUtf8("control")
#define DDEITEM     QString::fromUtf8("R1C1")
#define DDEPOKE     QString::fromUtf8("1234ABCD")
#define DDECOMMAND  QString::fromUtf8("[SELECT(\"R1C1:R2C2\")]")

widgetRightView::widgetRightView(QWidget *parent)
	: QWidget(parent)
	//, m_zoomSelector(new ZoomSelector(this))
	//, m_pageSelector(new QSpinBox(this))
	//, m_document(new QPdfDocument(this))
{
	ui.setupUi(this);

	//	page1
	//m_document = new QPdfDocument(this);

	//QHBoxLayout* layout_0 = new QHBoxLayout(ui.bookmarkTab);
	//layout_0->addWidget(ui.bookmarkView);

	//m_zoomSelector->setMaximumWidth(150);
	//ui.widget->layout()->addWidget(m_zoomSelector);

	//m_pageSelector->setMaximumWidth(150);
	//ui.widget->layout()->addWidget(m_pageSelector);

	//connect(m_pageSelector, &QSpinBox::valueChanged, this, &widgetRightView::pageSelected);
	//auto nav = ui.pdfView->pageNavigation();
	//connect(nav, &QPdfNavigationStack::currentPageChanged, m_pageSelector, &QSpinBox::setValue);
	//connect(nav, &QPdfNavigationStack::backAvailableChanged, ui.pushButton_3, &QPushButton::setEnabled);
	//connect(nav, &QPdfNavigationStack::forwardAvailableChanged, ui.pushButton_4, &QPushButton::setEnabled);

	//connect(m_zoomSelector, &ZoomSelector::zoomModeChanged, ui.pdfView, &QPdfView::setZoomMode);
	//connect(m_zoomSelector, &ZoomSelector::zoomFactorChanged, ui.pdfView, &QPdfView::setZoomFactor);
	//m_zoomSelector->reset();

	//QPdfBookmarkModel* bookmarkModel = new QPdfBookmarkModel(this);
	//bookmarkModel->setDocument(m_document);

	//ui.bookmarkView->setModel(bookmarkModel);
	//connect(ui.bookmarkView, SIGNAL(activated(QModelIndex)), this, SLOT(bookmarkSelected(QModelIndex)));
	//connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(on_actionZoom_In_triggered()));
	//connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(on_actionZoom_Out_triggered()));
	//connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(on_actionPrevious_Page_triggered()));
	//connect(ui.pushButton_4, SIGNAL(clicked()), this, SLOT(on_actionNext_Page_triggered()));
	//connect(ui.pushButton_5, SIGNAL(clicked()), this, SLOT(on_actionContinuous_triggered()));
	//connect(ui.pdfView, SIGNAL(pageModeChanged(QPdfView::PageMode)), this, SLOT(on_actionPageModeChanged(QPdfView::PageMode)));

	////ui.tabWidget->setTabEnabled(1, false); // disable 'Pages' tab for now

	//ui.pdfView->setDocument(m_document);

	//connect(ui.pdfView, &QPdfView::zoomFactorChanged, m_zoomSelector, &ZoomSelector::setZoomFactor);

	//	page2

	m_player = new QMediaPlayer(this);
	m_audioOutput = new QAudioOutput(this);
	m_player->setAudioOutput(m_audioOutput);
	//! [create-objs]
	connect(m_player, &QMediaPlayer::durationChanged, this, &widgetRightView::durationChanged);
	connect(m_player, &QMediaPlayer::positionChanged, this, &widgetRightView::positionChanged);
	connect(m_player, QOverload<>::of(&QMediaPlayer::metaDataChanged), this, &widgetRightView::metaDataChanged);
	connect(m_player, &QMediaPlayer::mediaStatusChanged, this, &widgetRightView::statusChanged);
	connect(m_player, &QMediaPlayer::bufferProgressChanged, this, &widgetRightView::bufferingProgress);
	connect(m_player, &QMediaPlayer::hasVideoChanged, this, &widgetRightView::videoAvailableChanged);
	connect(m_player, &QMediaPlayer::errorChanged, this, &widgetRightView::displayErrorMessage);
	//connect(m_player, &QMediaPlayer::tracksChanged, this, &widgetRightView::tracksChanged);

	//! [2]
	m_videoWidget = new VideoWidget(this);
	m_videoWidget->resize(128, 72);
	m_player->setVideoOutput(m_videoWidget);

	// player layout
	QBoxLayout* layout = new QVBoxLayout(ui.pageMV);

	// display
	QBoxLayout* displayLayout = new QHBoxLayout;
	displayLayout->addWidget(m_videoWidget, 2);
	layout->addLayout(displayLayout);

	// duration slider and label
	QHBoxLayout* hLayout = new QHBoxLayout;

	m_slider = new QSlider(Qt::Horizontal, this);
	m_slider->setRange(0, m_player->duration());
	connect(m_slider, &QSlider::sliderMoved, this, &widgetRightView::seek);
	hLayout->addWidget(m_slider);

	m_labelDuration = new QLabel();
	m_labelDuration->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	hLayout->addWidget(m_labelDuration);
	layout->addLayout(hLayout);

	// controls
	QBoxLayout* controlLayout = new QHBoxLayout;
	controlLayout->setContentsMargins(0, 0, 0, 0);

	PlayerControls* controls = new PlayerControls();
	controls->setState(m_player->playbackState());
	controls->setVolume(m_audioOutput->volume());
	controls->setMuted(controls->isMuted());

	connect(controls, &PlayerControls::play, m_player, &QMediaPlayer::play);
	connect(controls, &PlayerControls::pause, m_player, &QMediaPlayer::pause);
	connect(controls, &PlayerControls::stop, m_player, &QMediaPlayer::stop);
	//connect(controls, &PlayerControls::previous, this, &widgetRightView::previousClicked);
	connect(controls, &PlayerControls::changeVolume, m_audioOutput, &QAudioOutput::setVolume);
	connect(controls, &PlayerControls::changeMuting, m_audioOutput, &QAudioOutput::setMuted);
	connect(controls, &PlayerControls::changeRate, m_player, &QMediaPlayer::setPlaybackRate);
	connect(controls, &PlayerControls::stop, m_videoWidget, QOverload<>::of(&QVideoWidget::update));

	connect(m_player, &QMediaPlayer::playbackStateChanged, controls, &PlayerControls::setState);
	connect(m_audioOutput, &QAudioOutput::volumeChanged, controls, &PlayerControls::setVolume);
	connect(m_audioOutput, &QAudioOutput::mutedChanged, controls, &PlayerControls::setMuted);

	controlLayout->addWidget(controls);
	controlLayout->addStretch(1);

	m_fullScreenButton = new QPushButton(tr("FullScreen"), this);
	m_fullScreenButton->setCheckable(true);
	controlLayout->addWidget(m_fullScreenButton);

//#if !defined(Q_OS_ANDROID) && !defined(Q_OS_IOS)
//    m_audioOutputCombo = new QComboBox(this);
//    m_audioOutputCombo->addItem(QString::fromUtf8("Default"), QVariant::fromValue(QAudioDevice()));
//    for (auto& deviceInfo : QMediaDevices::audioOutputs())
//        m_audioOutputCombo->addItem(deviceInfo.description(), QVariant::fromValue(deviceInfo));
//    connect(m_audioOutputCombo, QOverload<int>::of(&QComboBox::activated), this,
//        &widgetRightView::audioOutputChanged);
//    controlLayout->addWidget(m_audioOutputCombo);
//#endif

	layout->addLayout(controlLayout);

	////	page3

	//layout = new QVBoxLayout(ui.pagePDF);

	//qmlView1 = new QQuickWidget;
	//qmlView1->setResizeMode(QQuickWidget::SizeRootObjectToView);
	//qmlView1->setSource(QUrl("qrc:///BDLS/viewer.qml"));

	//layout->addWidget(qmlView1);

	////qmlView->rootObject()->setProperty("source", QUrl::fromLocalFile("D:/test/1.pdf"));
	//qmlView1->show();

	//qmlRoot1 = (QObject*)qmlView1->rootObject();
	//connect(qmlRoot1, SIGNAL(qmlSignal(int)), this, SLOT(onPageSelected1(int)));
	//connect(qmlRoot1, SIGNAL(qmlSignal1()), this, SLOT(onPageModeChanged1()));
	//connect(qmlRoot1, SIGNAL(qmlSignalPrint()), this, SLOT(OnQmlPrint()));

	////	page4

	//layout = new QVBoxLayout(ui.pagePDF2);

	//qmlView2 = new QQuickWidget;
	//qmlView2->setResizeMode(QQuickWidget::SizeRootObjectToView);
	//qmlView2->setSource(QUrl("qrc:///BDLS/viewer2.qml"));

	//layout->addWidget(qmlView2);

	////qmlView->rootObject()->setProperty("source", QUrl::fromLocalFile("D:/test/1.pdf"));
	//qmlView2->show();

	//qmlRoot2 = (QObject*)qmlView2->rootObject();
	//connect(qmlRoot2, SIGNAL(qmlSignal(int)), this, SLOT(onPageSelected2(int)));
	//connect(qmlRoot2, SIGNAL(qmlSignal1()), this, SLOT(onPageModeChanged2()));

	//views.append(qmlView1);
	//views.append(qmlView2);
	//roots.append(qmlRoot1);
	//roots.append(qmlRoot2);
	//is_read_pdf.append(false);
	//is_read_pdf.append(false);
	//QLabel* metaDataLabel = new QLabel(tr("Metadata for file:"));
	//layout->addWidget(metaDataLabel);

	//QGridLayout* metaDataLayout = new QGridLayout;
	//int key = QMediaMetaData::Title;
	//for (int i = 0; i < (QMediaMetaData::NumMetaData + 2) / 3; i++) {
	//    for (int j = 0; j < 6; j += 2) {
	//        m_metaDataLabels[key] = new QLabel(
	//            QMediaMetaData::metaDataKeyToString(static_cast<QMediaMetaData::Key>(key)));
	//        if (key == QMediaMetaData::ThumbnailImage || key == QMediaMetaData::CoverArtImage)
	//            m_metaDataFields[key] = new QLabel;
	//        else
	//            m_metaDataFields[key] = new QLineEdit;
	//        m_metaDataLabels[key]->setDisabled(true);
	//        m_metaDataFields[key]->setDisabled(true);
	//        metaDataLayout->addWidget(m_metaDataLabels[key], i, j);
	//        metaDataLayout->addWidget(m_metaDataFields[key], i, j + 1);
	//        key++;
	//        if (key == QMediaMetaData::NumMetaData)
	//            break;
	//    }
	//}

	//layout->addLayout(metaDataLayout);

	//  초기 설정
	QList<int> sizes;
	sizes.append(0);
	sizes.append(100);
	ui.splitter->setSizes(sizes);

	//pdf_check_time = new QTimer(this);
	//connect(pdf_check_time, SIGNAL(timeout()), this, SLOT(checkPdfLoading()));
	//pdf_check_time->start(500);

}

widgetRightView::~widgetRightView()
{
}

void widgetRightView::resizeEvent(QResizeEvent* i_pEvent)
{
	QSize size = i_pEvent->size();
	SetWindowPos(Sumatra_FrameHandle(), 0, 0, 0, size.width(), size.height(), 0x0016 /*SWP_NOACTIVATE|SWP_NOZORDER|SWP_NOMOVE*/);
}

void widgetRightView::SearchText(QString search_text, int search_index)
{
	//HWND hFrame = Sumatra_FrameHandle();
	//if (hFrame)
	//{
	//	PostMessage(hFrame, 273 /*WM_COMMAND*/, 435, 0);
	//}
	//QMetaObject::invokeMethod(roots[m_iCurrentPDFView], "goSearch"
	//	, Q_ARG(QString, search_text)
	//	, Q_ARG(int, search_index));
}

HWND widgetRightView::GetFormHandle()
{
	HWND m_hWnd = (HWND)(ui.stackedWidget->widget(0)->winId());
	return m_hWnd;
}

HWND widgetRightView::Sumatra_FrameHandle()
{
	QString frame("SUMATRA_PDF_FRAME");
	return FindWindowEx(GetFormHandle(), 0, reinterpret_cast<LPCSTR>(frame.utf16()), 0);
}

BOOL CALLBACK EnumProc(HWND hwnd, LPARAM lParam)
{
	wchar_t strvar[255];
	GetClassName(hwnd, (LPSTR)strvar, 255);
	QString str_string = QString::fromWCharArray(strvar);
	if (str_string == "Edit")
	{
		*(HWND*)lParam = hwnd;
		return FALSE;
	}
	else
		return TRUE;
}

int widgetRightView::Sumatra_PageNumber()
{
	int page_no = -1;
	HWND hFrame = Sumatra_FrameHandle();
	if (hFrame)
	{
		QString rebar("ReBarWindow32");
		HWND nHReBar = FindWindowEx(hFrame, 0, reinterpret_cast<LPCSTR>(rebar.utf16()), 0);
		if (nHReBar)
		{
			HWND aHWnd;
			EnumChildWindows(nHReBar, EnumProc, (LPARAM)&aHWnd);
			wchar_t strvar[255];
			SendMessage(aHWnd, WM_GETTEXT, (WPARAM)255, (LPARAM)strvar);
			//int return_no = GetWindowTextW(aHWnd, (LPWSTR)strvar, 255);
			QString str_string = QString::fromWCharArray(strvar);
			page_no = str_string.toInt();
			if (page_no > 0)
				page_no--;
			return page_no;
		}
	}
	return page_no;
}

void widgetRightView::ViewPDF(QString file_path, QString file_info, bool update_memo)
{
	m_player->stop();

	//ui.stackedWidget->setCurrentIndex(m_iCurrentPDFView + 2);
	ui.stackedWidget->setCurrentIndex(0);

	int page_no = 0;
	if (file_info != "")
	{
		page_no = file_info.toInt();
	}

	int current_page_no = getPageNo();

	if (m_currentPDFPath != file_path || current_page_no != page_no)
	{

		//set_pdf_path = true;
		//is_read_pdf[0] = false;
		//is_read_pdf[1] = false;

		m_currentPDFPath = file_path;

		//if (pdf_load_time.isValid())
		//{
		//	if (pdf_load_time.elapsed() > pdf_loading_time)
		//	{
		//		//	이전 파일 로딩 후 시간이 지났나?
		//		if (pdf_set_time.elapsed() > pdf_setting_time)
		//		{
		//			//	이전 파일 설정 후 시간이 지났나?
		//			pdf_load_time.start();

		//			roots[m_iCurrentPDFView]->setProperty("source", QUrl::fromLocalFile(file_path));
		//			is_read_pdf[m_iCurrentPDFView] = true;
		//			QMetaObject::invokeMethod(roots[m_iCurrentPDFView], "fitPage");
		//		}
		//		else
		//		{
		//			pdf_set_time.start();
		//		}
		//	}
		//}
		//else
		//{
		//	pdf_load_time.start();
		//	pdf_set_time.start();

		//	roots[m_iCurrentPDFView]->setProperty("source", QUrl::fromLocalFile(file_path));
		//	is_read_pdf[m_iCurrentPDFView] = true;
		//	QMetaObject::invokeMethod(roots[m_iCurrentPDFView], "fitPage");
		//}

		{
			QString cmdLine;
			//if (thumbnail)
			//    cmdLine = QString("-plugin -reuse-instance %1 \"%2\" -page %3 -view \"continuous facing\" -zoom \"fit content\"").arg((int)m_hWnd).arg(target_path).arg(page_no);
			//else
			QString verb("open");
			QString file(QCoreApplication::applicationDirPath() + "/SumatraPDF.exe");
			cmdLine = QString("-plugin -reuse-instance %1 \"%2\" -page %3").arg((int)GetFormHandle()).arg(file_path).arg(page_no + 1);
			//cmdLine = QString("-plugin -reuse-instance %1 \"%2\" -page %3 -zoom \"fit page\"").arg((int)GetFormHandle()).arg(file_path).arg(page_no + 1);
			//cmdLine.Format(_T("\"%s\""), target_path);
			//ShellExecute(0, reinterpret_cast<const WCHAR*>(verb.utf16()), reinterpret_cast<const WCHAR*>(file.utf16()), reinterpret_cast<const WCHAR*>(cmdLine.utf16()), NULL, 10 /*SW_SHOWDEFAULT*/);

			//if (LoadingSumatra)
			//{
			//	DdeComm comm;
			//	// Execute
			//	cmdLine = QString("[Open(\"%1\", 0, 0, 0)]").arg(file_path);
			//	comm.execute(DDEAPP, DDETOPIC, cmdLine);
			//}
			//else
			//{
			QByteArray temp_verb;
			QByteArray temp_dir;
			QByteArray temp_file;
			QByteArray temp_param;
			temp_verb = verb.toLocal8Bit();
			temp_dir = QCoreApplication::applicationDirPath().toLocal8Bit();
			temp_file = file.toLocal8Bit();
			temp_param = cmdLine.toLocal8Bit();

			SHELLEXECUTEINFO seinfo = { 0 };
				seinfo.cbSize = sizeof(SHELLEXECUTEINFO);
				//seinfo.fMask = SEE_MASK_ASYNCOK;
				seinfo.fMask = SEE_MASK_FLAG_NO_UI;
				seinfo.lpVerb = (LPCSTR)temp_verb.constData();
				seinfo.lpDirectory = (LPCSTR)temp_dir.constData();
				seinfo.lpFile = (LPCSTR)temp_file.constData();
				seinfo.lpParameters = (LPCSTR)temp_param.constData();
				seinfo.nShow = SW_SHOWNOACTIVATE;
				ShellExecuteEx(&seinfo);
				//WaitForSingleObject(seinfo.hProcess, INFINITE);
				//CloseHandle(seinfo.hProcess);
			//	LoadingSumatra = true;
			//}


			//HANDLE prev_process = m_pdfViewer;
			//m_pdfViewer = seinfo.hProcess;
			//if (prev_process != m_pdfViewer && prev_process != 0)
			//{
			//	TerminateProcess(prev_process, 0);
			//}

			//HINSTANCE prev_inst = m_pdfViewer;
			//m_pdfViewer = ShellExecute(m_hWnd, _T("open"), m_strAppPath + _T("\\SumatraPDF.exe"), cmdLine, nullptr, SW_SHOWNOACTIVATE);
			//if (prev_inst != m_pdfViewer && prev_inst != 0)
			//{

			//}
			Sleep(1000);
			//while (getPageNo() < 0)
			//{
			//	Sleep(100);
			//}


			//Sumatra_PageNumber();
		}

	}
	//m_document->load(file_path);
	//m_pageSelector->setMaximum(m_document->pageCount() - 1); 

	pageSelectedwithMemo(page_no, update_memo);

	//if (file_info != "")
	//{
	//	int page_no = file_info.toInt();
	//	if (page_no > 0)
	//	{
	//		pageSelectedwithMemo(page_no, update_memo);
	//		return;
	//	}
	//}
	//pageSelectedwithMemo(0, update_memo);
}

int widgetRightView::getPageNo()
{
	return Sumatra_PageNumber();
	//return roots[m_iCurrentPDFView]->property("page_no").toInt();

	//auto nav = ui.pdfView->pageNavigation();
	//return nav->currentPage();
}
void widgetRightView::ViewMovie(QString file_path, QString file_info, bool update_memo)
{
	target_time = file_info.toInt();
	ui.stackedWidget->setCurrentIndex(1);

	if (m_currentMVPath == file_path)
	{
		JumpTo(target_time);
		target_time = -1;
		m_player->play();
	}
	else
	{
		m_player->setSource(QUrl::fromLocalFile(file_path));
		m_currentMVPath = file_path;
	}
}

//void widgetRightView::bookmarkSelected(const QModelIndex& index)
//{
//	if (!index.isValid())
//		return;
//
//	const int page = index.data(int(QPdfBookmarkModel::Role::Page)).toInt();
//	const qreal zoomLevel = index.data(int(QPdfBookmarkModel::Role::Level)).toReal();
//	ui.pdfView->pageNavigation()->jump(page, {}, zoomLevel);
//}

void widgetRightView::pageSelectedwithMemo(int page, bool update_memo)
{
	int return_value = 0;
	//QMetaObject::invokeMethod(roots[m_iCurrentPDFView], "goPage",
	//	Q_ARG(int, page));

	//auto nav = ui.pdfView->pageNavigation();
	//nav->jump(page, {}, nav->currentZoom());
	//int page_count = qmlRoot->property("page_count").toInt();

	//if (page <= 0)
	//{
	//	ui.pushButton_3->setEnabled(false);
	//}
	//else if (page < page_count - 1)
	//{
	//	ui.pushButton_3->setEnabled(true);
	//}

	//ui.pushButton_4->setEnabled(true);
	//if (page >= page_count - 1)
	//{
	//	ui.pushButton_4->setEnabled(false);
	//}

	if (update_memo)
		m_pView->_widgetLeftView->UpdateMemo(SEARCH_TYPE::NONE, QString("%1").arg(page));
	else
		m_pView->_widgetLeftView->selectPage(page);// UpdateMemo(SEARCH_TYPE::NONE, QString("%1").arg(page));
}

void widgetRightView::setCurrentPage(int page)
{
	pageSelectedwithMemo(page, false);
}

//void widgetRightView::onPageSelected1(int page)
//{
//	pageSelectedwithMemo(page, false);
//}
//
//void widgetRightView::onPageSelected2(int page)
//{
//	pageSelectedwithMemo(page, false);
//}
//
//void widgetRightView::OnQmlPrint()
//{
//	QStringList arguments;
//	arguments.append("-print-dialog");
//	arguments.append("-exit-when-done");
//	arguments.append(m_currentPDFPath);
//
//	int i_return = QProcess::execute("SumatraPDF.exe", arguments);
//	if (i_return == 0)
//	{
//	}
//	else
//	{
//		/*QMessageBox::critical(this, QString("파일 생성 오류"), QString("PDF 파일 생성에 실패했습니다. 관리자에게 문의하십시요."));*/
//		//	text 추출 오류
//	}
//}
//
//void widgetRightView::onPageModeChanged1()
//{
//	//if (!is_read_pdf[1])
//	//{
//	//	if (is_read_pdf[0])
//	//	{
//	//		roots[1]->setProperty("source", QUrl::fromLocalFile(m_currentPDFPath));
//	//		is_read_pdf[1] = true;
//	//		QMetaObject::invokeMethod(roots[1], "fitPage");
//	//	}
//	//}
//
//	//m_iCurrentPDFView = 1;
//	//if(is_read_pdf[0] && is_read_pdf[1])
//	//	QMetaObject::invokeMethod(roots[m_iCurrentPDFView], "goPage", Q_ARG(int, roots[0]->property("page_no").toInt()));
//	//ui.stackedWidget->setCurrentIndex(m_iCurrentPDFView + 2);
//}
//
//void widgetRightView::onPageModeChanged2()
//{
//	//if (!is_read_pdf[0])
//	//{
//	//	if (is_read_pdf[1])
//	//	{
//	//		roots[0]->setProperty("source", QUrl::fromLocalFile(m_currentPDFPath));
//	//		is_read_pdf[0] = true;
//	//		QMetaObject::invokeMethod(roots[0], "fitPage");
//	//	}
//	//}
//
//	//m_iCurrentPDFView = 0;
//	//if (is_read_pdf[0] && is_read_pdf[1])
//	//	QMetaObject::invokeMethod(roots[m_iCurrentPDFView], "goPage", Q_ARG(int, roots[1]->property("page_no").toInt()));
//	//ui.stackedWidget->setCurrentIndex(m_iCurrentPDFView + 2);
//}

//void widgetRightView::on_actionQuit_triggered()
//{
//	QApplication::quit();
//}
//
//void widgetRightView::on_actionAbout_triggered()
//{
//	QMessageBox::about(this, tr("About PdfViewer"),
//		tr("An example using QPdfDocument"));
//}
//
//void widgetRightView::on_actionAbout_Qt_triggered()
//{
//	QMessageBox::aboutQt(this);
//}
//
//void widgetRightView::on_actionZoom_In_triggered()
//{
//	ui.pdfView->setZoomFactor(ui.pdfView->zoomFactor() * zoomMultiplier);
//}
//
//void widgetRightView::on_actionZoom_Out_triggered()
//{
//	ui.pdfView->setZoomFactor(ui.pdfView->zoomFactor() / zoomMultiplier);
//}
//
//void widgetRightView::on_actionPrevious_Page_triggered()
//{
//	auto nav = ui.pdfView->pageNavigation();
//	nav->jump(nav->currentPage() - 1, {}, nav->currentZoom());
//}
//
//void widgetRightView::on_actionNext_Page_triggered()
//{
//	auto nav = ui.pdfView->pageNavigation();
//	nav->jump(nav->currentPage() + 1, {}, nav->currentZoom());
//}
//
//void widgetRightView::on_actionContinuous_triggered()
//{
//	if (ui.pdfView->pageMode() == QPdfView::MultiPage)
//	{
//		ui.pdfView->setPageMode(QPdfView::SinglePage);
//	}
//	else
//	{
//		auto nav = ui.pdfView->pageNavigation();
//		current_page_no = nav->currentPage();
//
//		ui.pdfView->setPageMode(QPdfView::MultiPage);
//	}
//}
//
//void widgetRightView::on_actionPageModeChanged(QPdfView::PageMode pageMode)
//{
//	if (pageMode == QPdfView::MultiPage)
//	{
//		pageSelected1(current_page_no);
//	}
//}


void widgetRightView::durationChanged(qint64 duration)
{
	m_duration = duration / 1000;
	m_slider->setMaximum(duration);
}

void widgetRightView::positionChanged(qint64 progress)
{
	if (!m_slider->isSliderDown())
		m_slider->setValue(progress);

	updateDurationInfo(progress / 1000);
	m_pView->_widgetLeftView->setMVPos(progress / 1000);
}

void widgetRightView::metaDataChanged()
{
//    auto metaData = m_player->metaData();
//    setTrackInfo(QString("%1 - %2")
//        .arg(metaData.value(QMediaMetaData::AlbumArtist).toString())
//        .arg(metaData.value(QMediaMetaData::Title).toString()));
//
//#if !defined(Q_OS_ANDROID) && !defined(Q_OS_IOS)
//    for (int i = 0; i < QMediaMetaData::NumMetaData; i++) {
//        if (QLineEdit* field = qobject_cast<QLineEdit*>(m_metaDataFields[i]))
//            field->clear();
//        else if (QLabel* label = qobject_cast<QLabel*>(m_metaDataFields[i]))
//            label->clear();
//        m_metaDataFields[i]->setDisabled(true);
//        m_metaDataLabels[i]->setDisabled(true);
//    }
//
//    for (auto& key : metaData.keys()) {
//        int i = int(key);
//        if (key == QMediaMetaData::CoverArtImage) {
//            QVariant v = metaData.value(key);
//            if (QLabel* cover = qobject_cast<QLabel*>(m_metaDataFields[key])) {
//                QImage coverImage = v.value<QImage>();
//                cover->setPixmap(QPixmap::fromImage(coverImage));
//            }
//        }
//        else if (key == QMediaMetaData::ThumbnailImage) {
//            QVariant v = metaData.value(key);
//            if (QLabel* thumbnail = qobject_cast<QLabel*>(m_metaDataFields[key])) {
//                QImage thumbnailImage = v.value<QImage>();
//                thumbnail->setPixmap(QPixmap::fromImage(thumbnailImage));
//            }
//        }
//        else if (QLineEdit* field = qobject_cast<QLineEdit*>(m_metaDataFields[key])) {
//            QString stringValue = metaData.stringValue(key);
//            field->setText(stringValue);
//        }
//        m_metaDataFields[i]->setDisabled(false);
//        m_metaDataLabels[i]->setDisabled(false);
//    }
//#endif
}

void widgetRightView::JumpTo(int secs)
{
	seek(secs * 1000);
}

void widgetRightView::seek(int mseconds)
{
	m_player->setPosition(mseconds);
}

void widgetRightView::statusChanged(QMediaPlayer::MediaStatus status)
{
	handleCursor(status);

	// handle status message
	switch (status) {
	case QMediaPlayer::NoMedia:
	case QMediaPlayer::LoadedMedia:
		setStatusInfo(QString());
		if (target_time >= 0)
		{
			JumpTo(target_time);
			target_time = -1;
			m_player->play();
		}
		break;
	case QMediaPlayer::LoadingMedia:
		setStatusInfo(tr("Loading..."));
		break;
	case QMediaPlayer::BufferingMedia:
	case QMediaPlayer::BufferedMedia:
		setStatusInfo(tr("Buffering %1%").arg(qRound(m_player->bufferProgress() * 100.)));
		break;
	case QMediaPlayer::StalledMedia:
		setStatusInfo(tr("Stalled %1%").arg(qRound(m_player->bufferProgress() * 100.)));
		break;
	case QMediaPlayer::EndOfMedia:
		QApplication::alert(this);
		break;
	case QMediaPlayer::InvalidMedia:
		displayErrorMessage();
		break;
	}
}

void widgetRightView::handleCursor(QMediaPlayer::MediaStatus status)
{
#ifndef QT_NO_CURSOR
	if (status == QMediaPlayer::LoadingMedia ||
		status == QMediaPlayer::BufferingMedia ||
		status == QMediaPlayer::StalledMedia)
		setCursor(QCursor(Qt::BusyCursor));
	else
		unsetCursor();
#endif
}

void widgetRightView::bufferingProgress(float progress)
{
	if (m_player->mediaStatus() == QMediaPlayer::StalledMedia)
		setStatusInfo(tr("Stalled %1%").arg(qRound(progress * 100.)));
	else
		setStatusInfo(tr("Buffering %1%").arg(qRound(progress * 100.)));
}

void widgetRightView::videoAvailableChanged(bool available)
{
	if (!available) {
		disconnect(m_fullScreenButton, &QPushButton::clicked, m_videoWidget, &QVideoWidget::setFullScreen);
		disconnect(m_videoWidget, &QVideoWidget::fullScreenChanged, m_fullScreenButton, &QPushButton::setChecked);
		m_videoWidget->setFullScreen(false);
	}
	else {
		connect(m_fullScreenButton, &QPushButton::clicked, m_videoWidget, &QVideoWidget::setFullScreen);
		connect(m_videoWidget, &QVideoWidget::fullScreenChanged, m_fullScreenButton, &QPushButton::setChecked);

		if (m_fullScreenButton->isChecked())
			m_videoWidget->setFullScreen(true);
	}
}

void widgetRightView::setTrackInfo(const QString& info)
{
	m_trackInfo = info;

	if (m_statusBar) {
		m_statusBar->showMessage(m_trackInfo);
		m_statusLabel->setText(m_statusInfo);
	}
	else {
		if (!m_statusInfo.isEmpty())
			setWindowTitle(QString("%1 | %2").arg(m_trackInfo).arg(m_statusInfo));
		else
			setWindowTitle(m_trackInfo);
	}
}

void widgetRightView::setStatusInfo(const QString& info)
{
	m_statusInfo = info;

	if (m_statusBar) {
		m_statusBar->showMessage(m_trackInfo);
		m_statusLabel->setText(m_statusInfo);
	}
	else {
		if (!m_statusInfo.isEmpty())
			setWindowTitle(QString("%1 | %2").arg(m_trackInfo).arg(m_statusInfo));
		else
			setWindowTitle(m_trackInfo);
	}
}

void widgetRightView::displayErrorMessage()
{
	if (m_player->error() == QMediaPlayer::NoError)
		return;
	setStatusInfo(m_player->errorString());
}

void widgetRightView::updateDurationInfo(qint64 currentInfo)
{
	QString tStr;
	if (currentInfo || m_duration) {
		QTime currentTime((currentInfo / 3600) % 60, (currentInfo / 60) % 60,
			currentInfo % 60, (currentInfo * 1000) % 1000);
		QTime totalTime((m_duration / 3600) % 60, (m_duration / 60) % 60,
			m_duration % 60, (m_duration * 1000) % 1000);
		QString format = "mm:ss";
		if (m_duration > 3600)
			format = "hh:mm:ss";
		tStr = currentTime.toString(format) + " / " + totalTime.toString(format);
	}
	m_labelDuration->setText(tStr);
}

//void widgetRightView::audioOutputChanged(int index)
//{
//    auto device = m_audioOutputCombo->itemData(index).value<QAudioDevice>();
//    m_player->audioOutput()->setDevice(device);
//}

//void widgetRightView::checkPdfLoading()
//{
//	if (set_pdf_path)
//	{
//		if (is_read_pdf[m_iCurrentPDFView] == false)
//		{
//			if (pdf_load_time.elapsed() > pdf_loading_time)
//			{
//				//	이전 파일 로딩 후 시간이 지났나?
//				if (pdf_set_time.elapsed() > pdf_setting_time)
//				{
//					//	이전 파일 설정 후 시간이 지났나?
//					pdf_load_time.start();
//
//					roots[m_iCurrentPDFView]->setProperty("source", QUrl::fromLocalFile(m_currentPDFPath));
//					is_read_pdf[m_iCurrentPDFView] = true;
//					QMetaObject::invokeMethod(roots[m_iCurrentPDFView], "fitPage");
//				}
//				else
//				{
//					pdf_set_time.start();
//				}
//			}
//		}
//	}
//}