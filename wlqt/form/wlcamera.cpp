#include "wlcamera.h"
#include "ui_wlcamera.h"

WLCamera::WLCamera(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WLCamera)
{
    ui->setupUi(this);    

    setCamera(QCameraInfo::defaultCamera());
}

WLCamera::~WLCamera()
{
    delete ui;
}

void WLCamera::setCamera(const QCameraInfo &cameraInfo)
{
qDebug()<<"WLCamera::setCamera"<<cameraInfo.deviceName();
m_camera.reset(new QCamera(cameraInfo));

//connect(m_camera.data(), &QCamera::stateChanged, this, &Camera::updateCameraState);
//connect(m_camera.data(), QOverload<QCamera::Error>::of(&QCamera::error), this, &Camera::displayCameraError);

//m_mediaRecorder.reset(new QMediaRecorder(m_camera.data()));
//connect(m_mediaRecorder.data(), &QMediaRecorder::stateChanged, this, &Camera::updateRecorderState);

m_imageCapture.reset(new QCameraImageCapture(m_camera.data()));

//connect(m_mediaRecorder.data(), &QMediaRecorder::durationChanged, this, &Camera::updateRecordTime);
//connect(m_mediaRecorder.data(), QOverload<QMediaRecorder::Error>::of(&QMediaRecorder::error),
//        this, &Camera::displayRecorderError);

//m_mediaRecorder->setMetaData(QMediaMetaData::Title, QVariant(QLatin1String("Test Title")));

//connect(ui->exposureCompensation, &QAbstractSlider::valueChanged, this, &Camera::setExposureCompensation);

m_camera->setViewfinder(ui->viewCamera);
/*
updateCameraState(m_camera->state());
updateLockStatus(m_camera->lockStatus(), QCamera::UserRequest);
updateRecorderState(m_mediaRecorder->state());
*/
//connect(m_imageCapture.data(), &QCameraImageCapture::readyForCaptureChanged, this, &Camera::readyForCapture);
//connect(m_imageCapture.data(), &QCameraImageCapture::imageCaptured, this, &Camera::processCapturedImage);
//connect(m_imageCapture.data(), &QCameraImageCapture::imageSaved, this, &Camera::imageSaved);
connect(m_imageCapture.data(), QOverload<int, QCameraImageCapture::Error, const QString &>::of(&QCameraImageCapture::error),
        this, &WLCamera::displayCaptureError);
/*
connect(m_camera.data(), QOverload<QCamera::LockStatus, QCamera::LockChangeReason>::of(&QCamera::lockStatusChanged),
        this, &Camera::updateLockStatus);

ui->captureWidget->setTabEnabled(0, (m_camera->isCaptureModeSupported(QCamera::CaptureStillImage)));
ui->captureWidget->setTabEnabled(1, (m_camera->isCaptureModeSupported(QCamera::CaptureVideo)));

updateCaptureMode();
*/
m_camera->start();
}

void WLCamera::displayCaptureError(int id, const QCameraImageCapture::Error error, const QString &errorString)
{
    Q_UNUSED(id);
    Q_UNUSED(error);
    QMessageBox::warning(this, tr("Image Capture Error"), errorString);
   // m_isCapturingImage = false;
}
