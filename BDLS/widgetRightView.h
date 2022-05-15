#pragma once

#include <QWidget>
#include "ui_widgetRightView.h"
//#include <QPdfDocument>
//#include <QPdfPageNavigation>
//#include <QPdfView>
//#include "pageselector.h"
//#include "zoomselector.h"
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QVideoWidget>
#include <QAudioOutput>
#include <QStatusBar>
#include <QSlider>
#include <QLabel>
#include <QPushButton>

class QPdfWidget;
class BDLS;
class widgetRightView : public QWidget
{
	Q_OBJECT

public:
	widgetRightView(QWidget *parent = Q_NULLPTR);
	~widgetRightView();
	BDLS* m_pView;
	//QPdfDocument* m_document;
 //   ZoomSelector* m_zoomSelector;
 //   PageSelector* m_pageSelector;
    QPdfWidget* m_pPdfWidget;
    void ViewPDF(QString file_path, QString file_info = "", QString search_word = "");
    void ViewMovie(QString file_path, QString file_info = "");
    void JumpTo(int secs);

protected:
    void resizeEvent(QResizeEvent* event);

private:
	Ui::widgetRightView ui;

signals:
    void fullScreenChanged(bool fullScreen);

private slots:
    //void bookmarkSelected(const QModelIndex& index);

    // action handlers
    void on_actionQuit_triggered();
    void on_actionAbout_triggered();
    void on_actionAbout_Qt_triggered();
    //void on_actionZoom_In_triggered();
    //void on_actionZoom_Out_triggered();
    //void on_actionPrevious_Page_triggered();
    //void on_actionNext_Page_triggered();
    //void on_actionContinuous_triggered();

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

    Qt::HANDLE m_pdfViewer;

    //QWidget* m_metaDataFields[QMediaMetaData::NumMetaData] = {};
    //QLabel* m_metaDataLabels[QMediaMetaData::NumMetaData] = {};
};
