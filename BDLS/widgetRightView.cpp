#include "widgetRightView.h"
#include <QPdfBookmarkModel>
#include <QtWidgets>
#include "VideoWidget.h"
#include "playercontrols.h"
#include <QAudioDevice>
#include <QMediaDevices>
#include "BDLS.h"

const qreal zoomMultiplier = qSqrt(2.0);

widgetRightView::widgetRightView(QWidget *parent)
	: QWidget(parent)
	, m_zoomSelector(new ZoomSelector(this))
	, m_pageSelector(new PageSelector(this))
{
	ui.setupUi(this);

	m_document = new QPdfDocument(this);

    QHBoxLayout* layout_0 = new QHBoxLayout(ui.bookmarkTab);
    layout_0->addWidget(ui.bookmarkView);

    m_zoomSelector->setMaximumWidth(150);
    ui.widget->layout()->addWidget(m_zoomSelector);

    m_pageSelector->setMaximumWidth(150);
    ui.widget->layout()->addWidget(m_pageSelector);

    m_pageSelector->setPageNavigation(ui.pdfView->pageNavigation());

    connect(m_zoomSelector, &ZoomSelector::zoomModeChanged, ui.pdfView, &QPdfView::setZoomMode);
    connect(m_zoomSelector, &ZoomSelector::zoomFactorChanged, ui.pdfView, &QPdfView::setZoomFactor);
    m_zoomSelector->reset();

    QPdfBookmarkModel* bookmarkModel = new QPdfBookmarkModel(this);
    bookmarkModel->setDocument(m_document);

    ui.bookmarkView->setModel(bookmarkModel);
    connect(ui.bookmarkView, SIGNAL(activated(QModelIndex)), this, SLOT(bookmarkSelected(QModelIndex)));
    connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(on_actionZoom_In_triggered()));
    connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(on_actionZoom_Out_triggered()));

    //ui.tabWidget->setTabEnabled(1, false); // disable 'Pages' tab for now

    ui.pdfView->setDocument(m_document);

    connect(ui.pdfView, &QPdfView::zoomFactorChanged, m_zoomSelector, &ZoomSelector::setZoomFactor);

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
    QBoxLayout* layout = new QVBoxLayout(ui.page_2);

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
}

widgetRightView::~widgetRightView()
{
}

void widgetRightView::ViewPDF(QString file_path, QString file_info)
{
    m_player->stop();

    ui.stackedWidget->setCurrentIndex(0);
    m_document->load(file_path);
    if (file_info != "")
    {
        int page_no = file_info.toInt();
        if (page_no > 0)
        {
            ui.pdfView->pageNavigation()->setCurrentPage(page_no);
        }
    }
}

void widgetRightView::ViewMovie(QString file_path, QString file_info)
{
    ui.stackedWidget->setCurrentIndex(1);
    m_player->setSource(QUrl::fromLocalFile(file_path));
    m_player->play();
}

void widgetRightView::bookmarkSelected(const QModelIndex& index)
{
    if (!index.isValid())
        return;

    const int page = index.data(QPdfBookmarkModel::PageNumberRole).toInt();
    ui.pdfView->pageNavigation()->setCurrentPage(page);
}

void widgetRightView::on_actionQuit_triggered()
{
    QApplication::quit();
}

void widgetRightView::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About PdfViewer"),
        tr("An example using QPdfDocument"));
}

void widgetRightView::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this);
}

void widgetRightView::on_actionZoom_In_triggered()
{
    ui.pdfView->setZoomFactor(ui.pdfView->zoomFactor() * zoomMultiplier);
}

void widgetRightView::on_actionZoom_Out_triggered()
{
    ui.pdfView->setZoomFactor(ui.pdfView->zoomFactor() / zoomMultiplier);
}

void widgetRightView::on_actionPrevious_Page_triggered()
{
    ui.pdfView->pageNavigation()->goToPreviousPage();
}

void widgetRightView::on_actionNext_Page_triggered()
{
    ui.pdfView->pageNavigation()->goToNextPage();
}

void widgetRightView::on_actionContinuous_triggered()
{
    ui.pdfView->setPageMode(ui.actionContinuous->isChecked() ? QPdfView::MultiPage : QPdfView::SinglePage);
}

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
