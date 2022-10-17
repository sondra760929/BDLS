#pragma once

#include <QWidget>
#include "ui_widgetRightView.h"
#include <QPdfDocument>
//#include <QPdfNavigationStack>
#include <QPdfView>
#include "zoomselector.h"
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QVideoWidget>
#include <QAudioOutput>
#include <QStatusBar>
#include <QQuickWidget>
//#include <QQuickitem>
//#include <qqmlcontext.h>
#include <QElapsedTimer>

class BDLS;
class QSpinBox;
class QLabel;

class widgetRightView : public QWidget
{
	Q_OBJECT

public:
	widgetRightView(QWidget *parent = Q_NULLPTR);
	~widgetRightView();
	BDLS* m_pView;
	//QPdfDocument* m_document;
	//ZoomSelector* m_zoomSelector;
	//QSpinBox* m_pageSelector;
	void SearchText(QString search_text, int search_index);
	void ViewPDF(QString file_path, QString file_info = "", bool update_memo = true);
	void ViewMovie(QString file_path, QString file_info = "0", bool update_memo = true);
	void JumpTo(int secs);
	void pageSelectedwithMemo(int page, bool update_memo);
	int getPageNo();
	void setCurrentPage(int page);

	HWND GetFormHandle();
	HWND Sumatra_FrameHandle();
	int Sumatra_PageNumber();

	bool LoadingSumatra = false;

	//	quick_widget
	//QQuickWidget* qmlView1;
	//QObject* qmlRoot1;
	//QQuickWidget* qmlView2;
	//QObject* qmlRoot2;
	//int m_iCurrentPDFView = 0;
	//QList< QQuickWidget* > views;
	//QList< QObject* > roots;
	//QList< bool > is_read_pdf;
	//QElapsedTimer pdf_set_time;
	//QElapsedTimer pdf_load_time;
	//int pdf_loading_time = 3000;
	//int pdf_setting_time = 1000;
	//QTimer* pdf_check_time;
	//bool set_pdf_path = false;

	QString m_currentPDFPath;
	QString m_currentMVPath;

	int current_page_no;

	Qt::HANDLE m_pdfViewer = NULL;

private:
	Ui::widgetRightView ui;

signals:
	void fullScreenChanged(bool fullScreen);

private slots:
	//void bookmarkSelected(const QModelIndex& index);
	//void onPageSelected1(int page);
	//void onPageSelected2(int page);
	//void onPageModeChanged1();
	//void onPageModeChanged2();
	//void OnQmlPrint();
	//void checkPdfLoading();
	//// action handlers
	//void on_actionQuit_triggered();
	//void on_actionAbout_triggered();
	//void on_actionAbout_Qt_triggered();
	//void on_actionZoom_In_triggered();
	//void on_actionZoom_Out_triggered();
	//void on_actionPrevious_Page_triggered();
	//void on_actionNext_Page_triggered();
	//void on_actionContinuous_triggered();
	//void on_actionPageModeChanged(QPdfView::PageMode pageMode);

	void durationChanged(qint64 duration);
	void positionChanged(qint64 progress);
	void metaDataChanged();
	//void tracksChanged();

	//void previousClicked();

	void seek(int mseconds);

	void statusChanged(QMediaPlayer::MediaStatus status);
	void bufferingProgress(float progress);
	void videoAvailableChanged(bool available);

	void displayErrorMessage();

	//void audioOutputChanged(int);

private:
	void setTrackInfo(const QString& info);
	void setStatusInfo(const QString& info);
	void handleCursor(QMediaPlayer::MediaStatus status);
	void updateDurationInfo(qint64 currentInfo);

	QMediaPlayer* m_player = nullptr;
	QAudioOutput* m_audioOutput = nullptr;
	QVideoWidget* m_videoWidget = nullptr;
	QSlider* m_slider = nullptr;
	QLabel* m_labelDuration = nullptr;
	QPushButton* m_fullScreenButton = nullptr;
	//QComboBox* m_audioOutputCombo = nullptr;
	QLabel* m_statusLabel = nullptr;
	QStatusBar* m_statusBar = nullptr;

	QString m_trackInfo;
	QString m_statusInfo;
	qint64 m_duration;
	int target_time = -1;

	QWidget* m_metaDataFields[QMediaMetaData::NumMetaData] = {};
	QLabel* m_metaDataLabels[QMediaMetaData::NumMetaData] = {};
protected:
	virtual void resizeEvent(QResizeEvent* i_pEvent);
};
